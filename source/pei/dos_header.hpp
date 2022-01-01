///
/// @file:   dos_header.h
/// @author: GrandChris
/// @date:   2021-12-30
/// @brief:  Portable Executable File Formant
/// @details: https://blog.kowalczyk.info/articles/pefileformat.html
///           https://docs.microsoft.com/en-us/windows/win32/debug/pe-format#ms-dos-stub-image-only
///


#pragma once

#include <span>
#include <bit>
#include <cstdint>
#include <cassert>

namespace pei 
{   
    namespace details 
    {

        /// 
        /// @brief Obtain a value of type To by reinterpreting the object representation of From. 
        //           This is done with a "char const" data array as input data.
        ///
        /// @tparam T the type to be reinterpreted at
        /// @param data the input data
        /// @param index a index inside the data where the data type is located
        /// @return T the type to be reinterpreted at
        ///
        template<typename T>
        [[nodiscard]] constexpr auto
        bit_cast(std::span<char const> data, size_t const index) -> T
        {
            if(!(index + sizeof(T) < data.size())) {
                assert(false);
                return T();
            }

            uint8_t arr[sizeof(T)] = {};
            std::copy(data.begin() + index, data.begin() + index + sizeof(T), std::begin(arr));

            return std::bit_cast<T>(arr);
        }
    }

    /// @class pei::DosHeader
    ///
    /// @brief MS-DOS Stub (Image Only)
    /// @details The MS-DOS stub is a valid application that runs under MS-DOS. 
    ///      It is placed at the front of the EXE image.
    ///
    class DosHeader final
    {
    public:
        struct DataStructure final  // DOS .EXE header
        {   
            /// @brief Magic number
            uint16_t magic;        
            /// @brief Bytes on last page of file
            uint16_t cblp;
            /// @brief  Pages in file 
            uint16_t cp;
            /// @brief Relocations
            uint16_t crlc;
            /// @brief Size of header in paragraphs
            uint16_t cparhdr;
            /// @brief Minimum extra paragraphs needed
            uint16_t minalloc;
            /// @brief Maximum extra paragraphs needed
            uint16_t maxalloc;
            /// @brief Initial (relative) SS value
            uint16_t ss;
            /// @brief Initial SP value
            uint16_t sp;
            /// @brief Checksum
            uint16_t csum;
            /// @brief Initial IP value
            uint16_t ip;
            /// @brief Initial (relative) CS value
            uint16_t cs;
            /// @brief File address of relocation table
            uint16_t lfarlc;
            /// @brief Overlay number
            uint16_t ovno;
            /// @brief Reserved words
            uint16_t res[4];
            /// @brief OEM identifier (for e_oeminfo)
            uint16_t oemid;
            /// @brief OEM information; e_oemid specific
            uint16_t oeminfo;
            /// @brief Reserved words
            uint16_t res2[10];
            /// @brief File address of new exe header
            uint32_t lfanew; 
        };
        static_assert(std::is_standard_layout_v<DataStructure>);

        /// 
        /// @brief constructor
        /// @param data the complete data of a binary .exe file
        ///
        constexpr DosHeader(std::span<char const> const data) noexcept : data_(data) {} 

        /// 
        /// @brief Returns the address of the new .exe header
        /// @return the address of the new .exe header
        ///
        [[nodiscard]] constexpr auto
        file_header_address() const noexcept -> uint32_t 
        {
            size_t const nt_signature_size = 4;

            auto const offset = offsetof(DataStructure, lfanew);
            auto const lfanew = details::bit_cast<decltype(DataStructure::lfanew)>(data_, offset);

            return lfanew + nt_signature_size;
        }

    private:
        /// @brief the binary data of a .exe file
        std::span<char const> const data_;
    };

}