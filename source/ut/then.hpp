///
/// @file:   then.cpp
/// @author: GrandChris
/// @date:   2021-12-31
/// @note:   Modified version from https://github.com/Bareflank/bsl
///

#pragma once

#include <string_view>

namespace ut
{
    /// @class bsl::Then
    ///
    /// <!-- description -->
    ///   @brief Defines the expected "result" of a unit test scenario.
    ///
    class Then final
    {
    public:
        /// <!-- description -->
        ///   @brief Default constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param name the name of the scenario (i.e., test case)
        ///
        explicit constexpr Then([[maybe_unused]] std::string_view const name  = "ignored") noexcept
        {

        }

        /// <!-- description -->
        ///   @brief Executes a lambda function as the body of the
        ///     "then" portion of the scenario.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam FUNC_T the type of lambda being executed
        ///   @param mut_func the lambda being executed
        ///   @return Returns a reference to the Then.
        ///
        template<typename FUNC_T>
        [[maybe_unused]] constexpr auto
        operator=(FUNC_T &&mut_func) &&noexcept -> Then &
        {
            mut_func();
            return *this;
        }

        /// <!-- description -->
        ///   @brief Destroyes a previously created bsl::Then
        ///
        constexpr ~Then() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr Then(Then const &o) noexcept = default;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_o the object being moved
        ///
        constexpr Then(Then &&mut_o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(Then const &o) &noexcept
            -> Then & = default;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(Then &&mut_o) &noexcept -> Then & = default;
    };
}

