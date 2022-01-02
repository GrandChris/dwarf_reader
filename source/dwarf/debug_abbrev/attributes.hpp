///
/// @file:   debug_info.hpp
/// @author: GrandChris
/// @date:   2022-01-01
/// @brief:  The ./debug_info section
///

#pragma once

// #include "dwarf/debug_info/unit_header/unit_header.hpp"
#include "dwarf/dwarf_tags.hpp"
#include "dwarf/debug_abbrev/attribute/attribute_base.hpp"
#include "details/iterator.hpp"
#include <span>


namespace dwarf
{
    /// @class dwarf::DIE
    ///
    /// @brief Debug Abbrev
    /// @details The abbreviations tables for all compilation units are contained in a separate
    ///     object file section called .debug_abbrev.
    ///     The abbreviations table for a single compilation unit consists of a series of
    ///     abbreviation declarations. Each declaration specifies the tag and attributes for a
    ///     particular form of debugging information entry. Each declaration begins with an
    ///     unsigned LEB128 number representing the abbreviation code itself. It is this code
    ///     that appears at the beginning of a debugging information entry in the
    ///     .debug_info section.
    ///
    class Attributes final
    {
    public:

    constexpr Attributes() noexcept = default;
    
    /// 
    /// @brief constructor
    /// @param debug_abbrev the .debug_abbrev section of the .exe file
    ///
    constexpr Attributes(std::span<char const> const debug_abbrev, size_t const index) noexcept 
        : data_(debug_abbrev), index_(index) {} 


        [[nodiscard]] constexpr auto
        begin() const noexcept -> details::Iterator<AttributeBase>
        {
            return details::Iterator<AttributeBase>(AttributeBase(data_, index_));
        }

        [[nodiscard]] constexpr auto
        end() const noexcept -> details::Iterator<AttributeBase>
        {
            return details::Iterator<AttributeBase>(AttributeBase());
        }


        // [[nodiscard]] constexpr auto
        // attribute(size_t const index) const noexcept -> Attribute 
        // {
        //     return Attribute();
        // }


        /// 
        /// @brief Returns the address of the start of the UnitHeader
        ///
        // [[nodiscard]] constexpr auto
        // base_index() const noexcept -> uint32_t 
        // {   
        //     return index_;
        // }

        // /// 
        // /// @brief Returns the size of the unit header
        // ///
        // [[nodiscard]] constexpr auto
        // size() const noexcept -> uint32_t 
        // {   
        //     if(is64bit()){
        //         return decltype(DataStructure64::unit_type)::end;
        //     }
        //     else {
        //         return decltype(DataStructure32::unit_type)::end;
        //     }
        // }

    private:
        /// @brief the binary data of the .debug_line section
        std::span<char const> const data_;
        size_t const index_ = 0;
    };
}
