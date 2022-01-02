///
/// @file:   debug_info.hpp
/// @author: GrandChris
/// @date:   2022-01-01
/// @brief:  The ./debug_info section
///

#pragma once

#include "dwarf/dwarf_tags.hpp"
#include "details/bit_cast.hpp"
#include <span>

namespace dwarf
{
    template<Attribute>
    class SpecializedAttribute final 
    {
        // not implemented
    };


    class AttributeBase final 
    {
    public:
    constexpr AttributeBase() noexcept = default;

        /// 
        /// @brief constructor
        /// @param data the complete data of a binary .exe file
        ///
        explicit constexpr AttributeBase(std::span<char const> const data, size_t const index = 0) noexcept 
            : data_(data), index_(index) {} 

        [[nodiscard]] constexpr auto
        operator==(AttributeBase const & other) const noexcept -> bool
        {
            return index_ == other.index_;
        }

        [[nodiscard]] constexpr auto
        attribute() const noexcept -> Attribute 
        {
            auto const res = details::bit_cast<Attribute>(data_, index_);
            return res;
        }

        [[nodiscard]] constexpr auto
        is(Attribute const type) const noexcept -> bool
        {
            return attribute() == type;
        }

        template<Attribute attribute>
        [[nodiscard]] constexpr auto
        as() const noexcept 
        {
            return SpecializedAttribute<attribute>(*this);
        }

        [[nodiscard]] constexpr auto
        next() const noexcept -> AttributeBase 
        {   
            if(attribute() == static_cast<Attribute>(0)) {
                return *this;   // the end of the list is marked with a 0
            }

            return AttributeBase(data_, index_ + sizeof(Attribute));
        }

    private:

        std::span<char const> data_;
        size_t index_ = 0;
    };
}