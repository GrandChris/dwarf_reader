///
/// @file:   given.cpp
/// @author: GrandChris
/// @date:   2021-12-31
/// @note:   Modified version from https://github.com/Bareflank/bsl
///

#pragma once

#include <string_view>

namespace ut
{
    /// @class bsl::Given
    ///
    /// <!-- description -->
    ///   @brief Defines the initial state of a unit test scenario including
    ///     the creation of any objects that might participate in the
    ///     unit test.
    ///
    class Given final
    {
    public:
        /// <!-- description -->
        ///   @brief Default constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param name the name of the scenario (i.e., test case)
        ///
        explicit constexpr Given([[maybe_unused]] std::string_view const name = "ignored") noexcept
        {
        }

        /// <!-- description -->
        ///   @brief Executes a lambda function as the body of the
        ///     "given" portion of the scenario.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam FUNC_T the type of lambda being executed
        ///   @param mut_func the lambda being executed
        ///   @return Returns a reference to the Given.
        ///
        template<typename FUNC_T>
        [[maybe_unused]] constexpr auto
        operator=(FUNC_T &&mut_func) &&noexcept -> Given &
        {
            mut_func();
            return *this;
        }

        /// <!-- description -->
        ///   @brief Destroyes a previously created bsl::Given
        ///
        constexpr ~Given() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr Given(Given const &o) noexcept = default;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_o the object being moved
        ///
        constexpr Given(Given &&mut_o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(Given const &o) &noexcept
            -> Given & = default;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(Given &&mut_o) &noexcept
            -> Given & = default;
    };
}
