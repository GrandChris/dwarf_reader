//
// @file:   bit_cast.hpp
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
            throw std::range_error("bit_cast: index out of bounds");
            return T();
        }

        char arr[sizeof(T)] = {};
        std::copy(data.begin() + index, data.begin() + index + sizeof(T), std::begin(arr));

        return std::bit_cast<T>(arr);
    }
};


