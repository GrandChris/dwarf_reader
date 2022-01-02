///
/// @file:   debug_info.hpp
/// @author: GrandChris
/// @date:   2022-01-01
/// @brief:  The ./debug_info section
///

#pragma once

// #include "dwarf/debug_info/unit_header/unit_header.hpp"
#include "details/iterator.hpp"
#include <span>


namespace dwarf
{
    /// @class dwarf::DIE
    ///
    /// @brief Debug Abbrev Table
    /// @details The abbreviations tables for all compilation units are contained in a separate
    ///     object file section called .debug_abbrev.
    ///     The abbreviations table for a single compilation unit consists of a series of
    ///     abbreviation declarations. Each declaration specifies the tag and attributes for a
    ///     particular form of debugging information entry. Each declaration begins with an
    ///     unsigned LEB128 number representing the abbreviation code itself. It is this code
    ///     that appears at the beginning of a debugging information entry in the
    ///     .debug_info section.
    ///
    class DebugAbbrevTable final
    {
    public:
    /// 
    /// @brief constructor
    /// @param debug_abbrev the .debug_abbrev section of the .exe file
    ///
    constexpr DebugAbbrevTable(std::span<char const> const debug_abbrev) noexcept 
        : data_(debug_abbrev) {} 


    [[nodiscard]] constexpr auto
    begin() const noexcept -> details::Iterator<UnitHeader>
    {
        return details::Iterator<UnitHeader>(UnitHeader(data_));
    }

    [[nodiscard]] constexpr auto
    end() const noexcept -> details::Iterator<UnitHeader>
    {
        return details::Iterator<UnitHeader>(UnitHeader());
    }

    [[nodiscard]] constexpr auto
    size() const noexcept -> size_t 
    {   
        return data_.size();
    }

    private:
        /// @brief the binary data of the .debug_line section
        std::span<char const> const data_;
    };
}
