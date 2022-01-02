//
// @file:   type_list.hpp
// @author: GrandChris
// @date:   2022-01-02
//

#pragma once

#include "details/bit_cast.hpp"

namespace details
{
    /// 
    /// @brief Base type to create a list of types with offsets
    ///
    /// @tparam offset Offset to previous type
    /// @tparam T Name of the current Type
    ///
    template<size_t offset, typename T>
    struct TypeList 
    {
        using Type = T;
        static constexpr size_t size = sizeof(Type);

        static constexpr size_t begin = offset;
        static constexpr size_t end = begin + size;  

        [[nodiscard]] static constexpr auto
        bit_cast(std::span<char const> const data, size_t const index) noexcept -> Type
        {
            auto const full_index = index + begin;
            auto const res = details::bit_cast<Type>(data, full_index);

            return res;
        }

        Type val;  

        constexpr TypeList() = default;
        constexpr TypeList(Type const & other) : val(other) {}
    };
}
