//
// @file:   iterator.hpp
// @author: GrandChris
// @date:   2021-11-12
// @brief:  Program entry point
//

#pragma once

#include <span>
#include <stdexcept>
#include <cstdint>
#include <bit>

namespace details
{
    template<typename T>
    class Iterator final
    {
    public:

        [[nodiscard]] constexpr
        Iterator(T const & data) noexcept 
            : data_(data) {} 

        [[nodiscard]] constexpr auto
        operator++() noexcept 
        {
            data_ = data_.next();
        }

        [[nodiscard]] constexpr auto
        operator==(Iterator const & other) const noexcept -> bool
        {
            return data_ == other.data_;
        }

        [[nodiscard]] constexpr auto
        operator*() const -> T const &
        {
            return data_;
        }

    private:
        T data_ = {};
    };
};


