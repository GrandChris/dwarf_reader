///
/// @file:   optional_header.h
/// @author: GrandChris
/// @date:   2021-12-30
/// @brief:  Portable Executable File Formant
/// @details: https://blog.kowalczyk.info/articles/pefileformat.html
///           https://docs.microsoft.com/en-us/windows/win32/debug/pe-format#ms-dos-stub-image-only
///

#pragma once

#include "file_header.hpp"

namespace pei 
{   
    /// @class pei::OptionalHeader
    ///
    /// @brief Optional Header (Image Only)
    /// @details Every image file has an optional header that provides information to the loader. 
    ///     This header is optional in the sense that some files (specifically, object files) do 
    ///     not have it. For image files, this header is required. An object file can have an 
    ///     optional header, but generally this header has no function in an object file except to 
    ///     increase its size.
    /// @note Note that the size of the optional header is not fixed. The SizeOfOptionalHeader field 
    ///     in the COFF header must be used to validate that a probe into the file for a particular 
    ///     data directory does not go beyond SizeOfOptionalHeader. For more information, see COFF 
    ///     File Header (Object and Image).
    ///
    class OptionalHeader final
    {
    public:
        struct DataDirectory final
        {
            /// @brief The first field, VirtualAddress, is actually the RVA of the table. The RVA is the 
            ///     address of the table relative to the base address of the image when the table is loaded. 
            uint32_t   virtual_address;
            /// @brief The second field gives the size in bytes.
            uint32_t   size;
        };

        struct DataStructure final 
        {
            ///
            /// Standard fields.
            ///     Fields that are defined for all implementations of COFF, including UNIX. 
            ///

            /// @brief The unsigned integer that identifies the state of the image file. The most common number
            ///      is 0x10B, which identifies it as a normal executable file. 0x107 identifies it as a ROM image,
            ///      and 0x20B identifies it as a PE32+ executable. 
            uint16_t   magic;
            /// @brief The linker major version number. 
            uint8_t    major_linker_version;
            /// @brief The linker minor version number. 
            uint8_t    minor_linker_version;
            /// @brief The size of the code (text) section, or the sum of all code sections if there are multiple sections. 
            uint32_t   size_of_code;
            /// @brief The size of the initialized data section, or the sum of all such sections if there are
            ///     multiple data sections. 
            uint32_t   size_of_initialized_data;
            /// @brief The size of the uninitialized data section (BSS), or the sum of all such sections if 
            ///     there are multiple BSS sections. 
            uint32_t   size_of_uninitialized_data;
            /// @brief The address of the entry point relative to the image base when the executable file is
            ///     loaded into memory. For program images, this is the starting address. For device drivers, 
            ///     this is the address of the initialization function. An entry point is optional for DLLs. 
            ///     When no entry point is present, this field must be zero. 
            uint32_t   address_of_entry_point;
            /// @brief The address that is relative to the image base of the beginning-of-code section when it 
            ///     is loaded into memory. 
            uint32_t   base_of_code;
            /// @brief The address that is relative to the image base of the beginning-of-data section when it 
            ///     is loaded into memory. 
            uint32_t   base_of_data;

            ///
            /// Windows-specific fields 
            ///     Additional fields to support specific features of Windows (for example, subsystems). 
            ///

            /// @brief The preferred address of the first byte of image when loaded into memory; must be a 
            ///     multiple of 64 K. The default for DLLs is 0x10000000. The default for Windows CE EXEs is 
            ///     0x00010000. The default for Windows NT, Windows 2000, Windows XP, Windows 95, Windows 98, 
            ///     and Windows Me is 0x00400000. 
            uint32_t   image_base;
            /// @brief The alignment (in bytes) of sections when they are loaded into memory. It must be 
            ///     greater than or equal to FileAlignment. The default is the page size for the architecture. 
            uint32_t   section_alignment;
            /// @brief The alignment factor (in bytes) that is used to align the raw data of sections in the 
            ///     image file. The value should be a power of 2 between 512 and 64 K, inclusive. The default 
            ///     is 512. If the SectionAlignment is less than the architecture's page size, then FileAlignment
            ///     must match SectionAlignment. 
            uint32_t   file_alignment;
            /// @brief The major version number of the required operating system. 
            uint16_t   major_operating_system_version;
            /// @brief The minor version number of the required operating system. 
            uint16_t   minor_operating_system_version;
            /// @brief The major version number of the image. 
            uint16_t   major_image_version;
            /// @brief The minor version number of the image. 
            uint16_t   minor_image_version;
            /// @brief The major version number of the subsystem. 
            uint16_t   major_subsystem_version;
            /// @brief The minor version number of the subsystem. 
            uint16_t   minor_subsystem_version;
            /// @brief Reserved, must be zero. 
            uint32_t   reserved1;
            /// @brief The size (in bytes) of the image, including all headers, as the image is loaded in memory. 
            ///     It must be a multiple of SectionAlignment. 
            uint32_t   size_of_image;
            /// @brief The combined size of an MS-DOS stub, PE header, and section headers rounded up to a multiple 
            ///     of FileAlignment. 
            uint32_t   size_of_headers;
            /// @brief The image file checksum. The algorithm for computing the checksum is incorporated into IMAGHELP.DLL.
            ///     The following are checked for validation at load time: all drivers, any DLL loaded at boot time, 
            ///     and any DLL that is loaded into a critical Windows process. 
            uint32_t   check_sum;
            /// @brief The subsystem that is required to run this image. For more information, see Windows Subsystem. 
            uint16_t   subsystem;
            /// @brief For more information, see DLL Characteristics later in this specification. 
            uint16_t   dll_characteristics;
            /// @brief The size of the stack to reserve. Only SizeOfStackCommit is committed; the rest is made 
            ///     available one page at a time until the reserve size is reached. 
            uint32_t   size_of_stack_reserve;
            /// @brief The size of the stack to commit. 
            uint32_t   size_of_stack_commit;
            /// @brief The size of the local heap space to reserve. Only SizeOfHeapCommit is committed; the rest
            ///     is made available one page at a time until the reserve size is reached. 
            uint32_t   size_of_heap_reserve;
            /// @brief The size of the local heap space to commit. 
            uint32_t   size_of_heap_commit;
            /// @brief Reserved, must be zero. 
            uint32_t   loader_flags;
            /// @brief The number of data-directory entries in the remainder of the optional header. 
            ///     Each describes a location and size. 
            uint32_t   number_of_rva_and_sizes;

            ///
            /// Data directories 
            ///     Address/size pairs for special tables that are found in the image file and are used by the 
            ///     operating system (for example, the import table and the export table). 
            ///

            DataDirectory data_directory[16];
        };
        static_assert(std::is_standard_layout_v<DataStructure>);

        /// 
        /// @brief constructor
        /// @param data the complete data of a binary .exe file
        ///
        constexpr OptionalHeader(std::span<char const> const data) noexcept : data_(data) {} 

        /// 
        /// @brief The unsigned integer that identifies the state of the image file. The most common number
        ///      is 0x10B, which identifies it as a normal executable file. 0x107 identifies it as a ROM image,
        ///      and 0x20B identifies it as a PE32+ executable. 
        /// @return the magic number
        ///
        [[nodiscard]] constexpr auto
        magic() const noexcept -> decltype(DataStructure::magic)
        {
            auto const index = base_index() + offsetof(DataStructure, magic);
            auto const res = details::bit_cast<decltype(DataStructure::magic)>(data_, index);

            return res;
        }

        /// 
        /// @brief Returns the address of the start of the OptionalHeader
        ///
        [[nodiscard]] constexpr auto
        base_index() const noexcept -> uint32_t 
        {   
            FileHeader const file_header(data_);
            return file_header.base_index() + file_header.size();
        }

        /// 
        /// @brief Returns the size of the OptionalHeader
        ///
        [[nodiscard]] constexpr auto
        size() const noexcept -> uint32_t 
        {   
            FileHeader const file_header(data_);
            return file_header.size_of_optional_header();
        }

    private:
        /// @brief the binary data of a .exe file
        std::span<char const> const data_;
    };
}