///
/// @file:   optional_header.h
/// @author: GrandChris
/// @date:   2021-12-30
/// @brief:  Portable Executable File Formant
/// @details: https://blog.kowalczyk.info/articles/pefileformat.html
///           https://docs.microsoft.com/en-us/windows/win32/debug/pe-format#ms-dos-stub-image-only
///


#pragma once

#include "optional_header.hpp"
#include <string_view>
#include <charconv>
#include <limits>
#include <ostream>

namespace pei 
{   
    [[nodiscard]] constexpr auto
    svtol(std::string_view const & str) noexcept -> uint32_t
    {
        uint64_t res = 0;

        for(size_t i = 0; i < str.size(); ++i) {
            char const sign = str[i];
            if(!('0' <= sign && sign <= '9')) {
                return 0;
            }

            uint32_t const val = sign - '0';

            res *= 10;
            res += val;

            if(res > std::numeric_limits<uint32_t>::max()) {
                return 0;
            }
        }

        return static_cast<uint32_t>(res);
    }

    /// @class pei::SectionHeader
    ///
    /// @brief Each row of the section table is, in effect, a section header. 
    /// @details This table immediately follows the optional header, if any. This positioning is required
    ///     because the file header does not contain a direct pointer to the section table. Instead, the 
    ///     location of the section table is determined by calculating the location of the first byte 
    ///     after the headers. Make sure to use the size of the optional header as specified in the file header.
    ///
    class SectionHeader final
    {
    public:
        struct DataStructure final 
        {
            /// @brief An 8-byte, null-padded UTF-8 encoded string. If the string is exactly 8 characters long, there
            ///     is no terminating null. For longer names, this field contains a slash (/) that is followed by
            ///     an ASCII representation of a decimal number that is an offset into the string table. Executable
            ///     images do not use a string table and do not support section names longer than 8 characters. Long
            ///     names in object files are truncated if they are emitted to an executable file. 
            char   name[8];
            /// @brief The total size of the section when loaded into memory. If this value is greater than 
            ///     SizeOfRawData, the section is zero-padded. This field is valid only for executable images and
            ///     should be set to zero for object files. 
            uint32_t virtual_size;   
            /// @brief For executable images, the address of the first byte of the section relative to the image
            ///      base when the section is loaded into memory. For object files, this field is the address of
            ///      the first byte before relocation is applied; for simplicity, compilers should set this to zero.
            ///      Otherwise, it is an arbitrary value that is subtracted from offsets during relocation. 
            uint32_t   virtual_address;
            /// @brief The size of the section (for object files) or the size of the initialized data on disk 
            ///     (for image files). For executable images, this must be a multiple of FileAlignment from the
            ///     optional header. If this is less than VirtualSize, the remainder of the section is zero-filled.
            ///     Because the SizeOfRawData field is rounded but the VirtualSize field is not, it is possible for 
            ///     SizeOfRawData to be greater than VirtualSize as well. When a section contains only uninitialized 
            ///     data, this field should be zero. 
            uint32_t   size_of_raw_data;
            /// @brief The file pointer to the first page of the section within the COFF file. For executable 
            ///     images, this must be a multiple of FileAlignment from the optional header. For object files,
            ///     the value should be aligned on a 4-byte boundary for best performance. When a section contains
            ///     only uninitialized data, this field should be zero. 
            uint32_t   pointer_to_raw_data;
            /// @brief The file pointer to the beginning of relocation entries for the section. This is set to 
            ///     zero for executable images or if there are no relocations. 
            uint32_t   pointer_to_relocations;
            /// @brief The file pointer to the beginning of line-number entries for the section. This is set to
            ///     zero if there are no COFF line numbers. This value should be zero for an image because COFF
            ///     debugging information is deprecated. 
            uint32_t   pointer_to_linenumbers;
            /// @brief The number of relocation entries for the section. This is set to zero for executable images. 
            uint16_t  number_of_relocations;
            /// @brief The number of line-number entries for the section. This value should be zero for an image
            ///     because COFF debugging information is deprecated. 
            uint16_t  number_of_linenumbers;
            /// @brief The flags that describe the characteristics of the section. For more information, 
            ///     see Section Flags.
            uint32_t   characteristics;
            
        };
        static_assert(std::is_standard_layout_v<DataStructure>);

        /// 
        /// @brief constructor
        /// @param data the complete data of a binary .exe file
        ///
        constexpr SectionHeader(std::span<char const> const data, size_t const index) noexcept : data_(data), index_(index) {} 

        //  
        /// @brief Returns the name of the section
        ///
        [[nodiscard]] constexpr auto
        name() const noexcept -> std::string_view
        {
            auto const index = base_index() + offsetof(DataStructure, name);

            if(index + sizeof(DataStructure::name) >= data_.size()) {
                return std::string_view();
            }

            std::string_view const name(&data_[index]);

            if(name.starts_with('/'))
            {   // name is located in the string table
                FileHeader const file_header(data_);
                auto const string_table_address = file_header.string_table_address();
                if(string_table_address >= data_.size()) {
                    return name;
                }

                if(name.size() < 3) {
                    return name;
                }

                size_t const index = svtol(name.substr(1));
                // size_t const index = std::atol(name.substr(1).data());
                std::string_view const longer_name(&data_[string_table_address + index]);
                return longer_name;
            }

            return name;
        }

        /// 
        /// @brief The total size of the section when loaded into memory. If this value is greater than 
        ///     SizeOfRawData, the section is zero-padded. This field is valid only for executable images and
        ///     should be set to zero for object files. 
        ///
        [[nodiscard]] constexpr auto
        virtual_size() const noexcept -> decltype(DataStructure::virtual_size)
        {
            auto const index = base_index() + offsetof(DataStructure, virtual_size);
            auto const res = details::bit_cast<decltype(DataStructure::virtual_size)>(data_, index);

            return res;
        }

        /// 
        /// @brief For executable images, the address of the first byte of the section relative to the image
        ///      base when the section is loaded into memory. For object files, this field is the address of
        ///      the first byte before relocation is applied; for simplicity, compilers should set this to zero.
        ///      Otherwise, it is an arbitrary value that is subtracted from offsets during relocation. 
        ///
        [[nodiscard]] constexpr auto
        virtual_address() const noexcept -> decltype(DataStructure::virtual_address)
        {
            auto const index = base_index() + offsetof(DataStructure, virtual_address);
            auto const res = details::bit_cast<decltype(DataStructure::virtual_address)>(data_, index);

            return res;
        }

        /// 
        /// @brief The size of the section (for object files) or the size of the initialized data on disk 
        ///     (for image files). For executable images, this must be a multiple of FileAlignment from the
        ///     optional header. If this is less than VirtualSize, the remainder of the section is zero-filled.
        ///     Because the SizeOfRawData field is rounded but the VirtualSize field is not, it is possible for 
        ///     SizeOfRawData to be greater than VirtualSize as well. When a section contains only uninitialized 
        ///     data, this field should be zero. 
        ///
        [[nodiscard]] constexpr auto
        size_of_raw_data() const noexcept -> decltype(DataStructure::size_of_raw_data)
        {
            auto const index = base_index() + offsetof(DataStructure, size_of_raw_data);
            auto const res = details::bit_cast<decltype(DataStructure::size_of_raw_data)>(data_, index);

            return res;
        }

        /// 
        /// @brief The file pointer to the first page of the section within the COFF file. For executable 
        ///     images, this must be a multiple of FileAlignment from the optional header. For object files,
        ///     the value should be aligned on a 4-byte boundary for best performance. When a section contains
        ///     only uninitialized data, this field should be zero. 
        ///
        [[nodiscard]] constexpr auto
        pointer_to_raw_data() const noexcept -> decltype(DataStructure::pointer_to_raw_data)
        {
            auto const index = base_index() + offsetof(DataStructure, pointer_to_raw_data);
            auto const res = details::bit_cast<decltype(DataStructure::pointer_to_raw_data)>(data_, index);

            return res;
        }

        /// 
        /// @brief The file pointer to the beginning of relocation entries for the section. This is set to 
        ///     zero for executable images or if there are no relocations. 
        ///
        [[nodiscard]] constexpr auto
        pointer_to_relocations() const noexcept -> decltype(DataStructure::pointer_to_relocations)
        {
            auto const index = base_index() + offsetof(DataStructure, pointer_to_relocations);
            auto const res = details::bit_cast<decltype(DataStructure::pointer_to_relocations)>(data_, index);

            return res;
        }

        /// 
        /// @brief The file pointer to the beginning of line-number entries for the section. This is set to
        ///     zero if there are no COFF line numbers. This value should be zero for an image because COFF
        ///     debugging information is deprecated. 
        ///
        [[nodiscard]] constexpr auto
        pointer_to_linenumbers() const noexcept -> decltype(DataStructure::pointer_to_linenumbers)
        {
            auto const index = base_index() + offsetof(DataStructure, pointer_to_linenumbers);
            auto const res = details::bit_cast<decltype(DataStructure::pointer_to_linenumbers)>(data_, index);

            return res;
        }

        /// 
        /// @brief The number of relocation entries for the section. This is set to zero for executable images. 
        ///
        [[nodiscard]] constexpr auto
        number_of_relocations() const noexcept -> decltype(DataStructure::number_of_relocations)
        {
            auto const index = base_index() + offsetof(DataStructure, number_of_relocations);
            auto const res = details::bit_cast<decltype(DataStructure::number_of_relocations)>(data_, index);

            return res;
        }

        /// 
        /// @brief The number of line-number entries for the section. This value should be zero for an image
        ///     because COFF debugging information is deprecated. 
        ///
        [[nodiscard]] constexpr auto
        number_of_linenumbers() const noexcept -> decltype(DataStructure::number_of_linenumbers)
        {
            auto const index = base_index() + offsetof(DataStructure, number_of_linenumbers);
            auto const res = details::bit_cast<decltype(DataStructure::number_of_linenumbers)>(data_, index);

            return res;
        }

        /// 
        /// @brief The flags that describe the characteristics of the section. For more information, 
        ///     see Section Flags.
        ///
        [[nodiscard]] constexpr auto
        characteristics() const noexcept -> decltype(DataStructure::virtual_address)
        {
            auto const index = base_index() + offsetof(DataStructure, virtual_address);
            auto const res = details::bit_cast<decltype(DataStructure::virtual_address)>(data_, index);

            return res;
        }

        /// 
        /// @brief Returns the address of the start of the SectionHeader
        ///
        [[nodiscard]] constexpr auto
        base_index() const noexcept -> uint32_t 
        {   
            OptionalHeader const optional_header(data_);
            return optional_header.base_index() + optional_header.size() + index_ * size();
        }

        /// 
        /// @brief Returns the size of the SectionHeader
        ///
        [[nodiscard]] constexpr auto
        size() const noexcept -> uint32_t 
        {   
            return sizeof(DataStructure);
        }

    private:
        /// @brief the binary data of a .exe file
        std::span<char const> const data_;
        /// @brief the index of this section in the section table
        size_t const index_;
    };

    std::ostream & operator<<(std::ostream & ost, SectionHeader const & section_header) 
    {
        ost << "name:                   " << section_header.name() << std::endl;
        ost << "virtual_size:           " << section_header.virtual_size() << " (0x" << std::hex << section_header.virtual_size() << std::dec << ")" << std::endl;
        ost << "virtual_address:        " << section_header.virtual_address() << " (0x" << std::hex << section_header.virtual_address() << std::dec << ")" << std::endl;
        ost << "size_of_raw_data:       " << section_header.size_of_raw_data() << " (0x" << std::hex << section_header.size_of_raw_data() << std::dec << ")" << std::endl;
        ost << "pointer_to_raw_data:    " << section_header.pointer_to_raw_data() << " (0x" << std::hex << section_header.pointer_to_raw_data() << std::dec << ")" << std::endl;
        ost << "pointer_to_relocations: " << section_header.pointer_to_relocations() << std::endl;
        ost << "pointer_to_linenumbers: " << section_header.pointer_to_linenumbers() << std::endl;
        ost << "number_of_relocations:  " << section_header.number_of_relocations() << std::endl;
        ost << "number_of_linenumbers:  " << section_header.number_of_linenumbers() << std::endl;
        ost << "characteristics:        " << section_header.characteristics() << std::endl;

        return ost;
    }
}
