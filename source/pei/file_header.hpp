///
/// @file:   dos_header.h
/// @author: GrandChris
/// @date:   2021-12-30
/// @brief:  Portable Executable File Formant
/// @details: https://blog.kowalczyk.info/articles/pefileformat.html
///           https://docs.microsoft.com/en-us/windows/win32/debug/pe-format#ms-dos-stub-image-only
///

#pragma once

#include "dos_header.hpp"

namespace pei 
{   
    /// @class pei::FileHeader
    ///
    /// @brief COFF file header
    /// @details At the beginning of an object file, or immediately after the signature of an image file,
    ///     is a standard COFF file header in the following format. Note that the Windows loader limits 
    ///     the number of sections to 96.
    ///
    class FileHeader final
    {
    public:
        struct DataStructure final      // DOS .EXE header
        {
            /// @brief The number that identifies the type of target machine. 
            uint16_t  machine;    
            /// @brief The number of sections. This indicates the size of the section table, which immediately
            ///     follows the headers.             
            uint16_t  number_of_sections;   
            /// @brief The low 32 bits of the number of seconds since 00:00 January 1, 1970 
            ///     (a C run-time time_t value), which indicates when the file was created. 
            uint32_t  time_date_stamp;
            /// @brief The file offset of the COFF symbol table, or zero if no COFF symbol table is present.
            ///     This value should be zero for an image because COFF debugging information is deprecated. 
            uint32_t  pointer_to_symbol_table;
            /// @brief The number of entries in the symbol table. This data can be used to locate the string 
            ///     table, which immediately follows the symbol table. This value should be zero for an image 
            ///     because COFF debugging information is deprecated. 
            uint32_t  number_of_symbols;
            /// @brief The size of the optional header, which is required for executable files but not for 
            ///     object files. This value should be zero for an object file. For a description of the 
            ///     header format, see Optional Header (Image Only). 
            uint16_t  size_of_optional_header;
            /// @brief The flags that indicate the attributes of the file. For specific flag values, 
            ///     see Characteristics. 
            uint16_t  characteristics;
        };
        static_assert(std::is_standard_layout_v<DataStructure>);

        /// 
        /// @brief constructor
        /// @param data the complete data of a binary .exe file
        ///
        constexpr FileHeader(std::span<char const> const data) noexcept : data_(data) {} 

        /// 
        /// @brief Returns the number of sections. This indicates the size of the section table, which immediately
        ///     follows the headers.
        /// @return the number of sections
        ///
        [[nodiscard]] constexpr auto
        number_of_sections() const noexcept -> decltype(DataStructure::number_of_sections)
        {
            auto const index = base_index() + offsetof(DataStructure, number_of_sections);
            auto const res = details::bit_cast<decltype(DataStructure::number_of_sections)>(data_, index);

            return res;
        }

        /// 
        /// @brief The file offset of the COFF symbol table, or zero if no COFF symbol table is present. This value
        ///     should be zero for an image because COFF debugging information is deprecated. 
        /// @return the address of the symbol table
        ///
        [[nodiscard]] constexpr auto
        pointer_to_symbol_table() const noexcept -> decltype(DataStructure::pointer_to_symbol_table)
        {
            auto const index = base_index() + offsetof(DataStructure, pointer_to_symbol_table);
            auto const res = details::bit_cast<decltype(DataStructure::pointer_to_symbol_table)>(data_, index);

            return res;
        }

        /// 
        /// @brief The number of entries in the symbol table. This data can be used to locate the string table, 
        ///     which immediately follows the symbol table. This value should be zero for an image because COFF 
        ///     debugging information is deprecated. 
        /// @return the numbers of symbols in the symbol table
        ///
        [[nodiscard]] constexpr auto
        number_of_symbols() const noexcept -> decltype(DataStructure::number_of_symbols)
        {
            auto const index = base_index() + offsetof(DataStructure, number_of_symbols);
            auto const res = details::bit_cast<decltype(DataStructure::number_of_symbols)>(data_, index);

            return res;
        }

        /// 
        /// @brief The size of the optional header, which is required for executable files but not for object
        ///     files. This value should be zero for an object file. For a description of the header format,
        ///     see Optional Header (Image Only). 
        /// @return the size of the optional header
        ///
        [[nodiscard]] constexpr auto
        size_of_optional_header() const noexcept -> decltype(DataStructure::size_of_optional_header)
        {
            auto const index = base_index() + offsetof(DataStructure, size_of_optional_header);
            auto const res = details::bit_cast<decltype(DataStructure::size_of_optional_header)>(data_, index);

            return res;
        }

        /// 
        /// @brief Returns the address of the string table, where the long names of the sections are located.
        /// @return the address of the string table
        ///
        [[nodiscard]] constexpr auto
        string_table_address() const noexcept -> uint32_t 
        {
            size_t const symbol_length = 18;
            return pointer_to_symbol_table() + number_of_symbols() * symbol_length;
        }

        /// 
        /// @brief Returns the address of the start of the FileHeader
        ///
        [[nodiscard]] constexpr auto
        base_index() const noexcept -> uint32_t 
        {   
            DosHeader const dos_header(data_);
            return dos_header.file_header_address();
        }

        /// 
        /// @brief Returns the size of the FileHeader
        ///
        [[nodiscard]] constexpr auto
        size() const noexcept -> uint32_t 
        {   
            return sizeof(DataStructure);
        }

    private:
        /// @brief the binary data of a .exe file
        std::span<char const> const data_;
    };
}
