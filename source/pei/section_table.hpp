///
/// @file:   section_table.h
/// @author: GrandChris
/// @date:   2021-12-30
/// @brief:  Portable Executable File Formant
/// @details: https://blog.kowalczyk.info/articles/pefileformat.html
///           https://docs.microsoft.com/en-us/windows/win32/debug/pe-format#ms-dos-stub-image-only
///

#pragma once

#include "section_header.hpp"

namespace pei 
{   
    /// @class pei::SectionTable
    ///
    /// @brief Each row of the section table is, in effect, a section header. 
    /// @details This table immediately follows the optional header, if any. This positioning is required
    ///     because the file header does not contain a direct pointer to the section table. Instead, the 
    ///     location of the section table is determined by calculating the location of the first byte 
    ///     after the headers. Make sure to use the size of the optional header as specified in the file header.
    ///
    class SectionTable final 
    {
    public:

        /// 
        /// @brief constructor
        /// @param data the complete data of a binary .exe file
        ///
        constexpr SectionTable(std::span<char const> const data) noexcept : data_(data) {} 

        /// 
        /// @brief Returns a section
        /// @param index the index in the section table
        ///
        [[nodiscard]] constexpr auto
        get_section(size_t const index) const noexcept -> SectionHeader 
        {   
            if(index >= number_of_sections()) {
                assert(false);
                return SectionHeader(data_, 0);
            }

            return SectionHeader(data_, index);
        }

        /// 
        /// @brief Returns the section with the given name
        /// @param index the index in the section table
        ///
        [[nodiscard]] constexpr auto
        find_section(std::string_view const name) const noexcept -> SectionHeader 
        {   
            for(size_t i = 0; i < number_of_sections(); ++i) {
                auto const section = get_section(i);

                if(section.name() == name) {
                    return section;
                }
            }

            return SectionHeader(data_, 0);
        }

        /// 
        /// @brief Returns the number of sections
        ///
        [[nodiscard]] constexpr auto
        number_of_sections() const noexcept -> uint32_t 
        {   
            FileHeader const file_header(data_);
            return file_header.number_of_sections();
        }

    private:
        /// @brief the binary data of a .exe file
        std::span<char const> const data_;
    };
}