///
/// @file:   debug_info.hpp
/// @author: GrandChris
/// @date:   2022-01-01
/// @brief:  The ./debug_info section
///

#pragma once

#include "dwarf/debug_info/unit_header/unit_header.hpp"
#include "details/iterator.hpp"
#include <span>


namespace dwarf
{
    class DebugInfo final
    {
    public:
    /// 
    /// @brief constructor
    /// @param data the complete data of a binary .exe file
    ///
    constexpr DebugInfo(std::span<char const> const data) noexcept 
        : data_(data) {} 


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
