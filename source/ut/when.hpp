///
/// @file:   when.cpp
/// @author: GrandChris
/// @date:   2021-12-31
/// @note:   Modified version from https://github.com/Bareflank/bsl
///

#pragma once

#include <string>

namespace bsl
{
    /// @class bsl::When
    ///
    /// <!-- description -->
    ///   @brief Defines the "action" of a unit test scenario
    ///
    class When final
    {
    public:
        /// <!-- description -->
        ///   @brief Default constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param name the name of the scenario (i.e., test case)
        ///
        explicit constexpr When([[maybe_unused]] std::string const & name = "ignored") noexcept
        {
        }

        /// <!-- description -->
        ///   @brief Executes a lambda function as the body of the
        ///     "when" portion of the scenario.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam FUNC_T the type of lambda being executed
        ///   @param mut_func the lambda being executed
        ///   @return Returns a reference to the When.
        ///
        template<typename FUNC_T>
        [[maybe_unused]] constexpr auto
        operator=(FUNC_T &&mut_func) &&noexcept -> When &
        {
            mut_func();
            return *this;
        }

        /// <!-- description -->
        ///   @brief Destroyes a previously created bsl::When
        ///
        constexpr ~When() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr When(When const &o) noexcept = default;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_o the object being moved
        ///
        constexpr When(When &&mut_o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(When const &o) &noexcept
            -> When & = default;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(When &&mut_o) &noexcept -> When & = default;
    };
}

