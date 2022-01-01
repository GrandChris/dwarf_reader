///
/// @file:   scenario.cpp
/// @author: GrandChris
/// @date:   2021-12-31
/// @note:   Modified version from https://github.com/Bareflank/bsl
///

#pragma once

#include <string_view>

namespace ut
{
    /// @class bsl::ut_scenario
    ///
    /// <!-- description -->
    ///   @brief Defines a unit test scenario. A scenario defines a user
    ///     story, describing the "scenario" being tested. A scenario
    ///     should be paired with ut_given, ut_when and ut_then to define
    ///     the scenario in english.
    ///
    class Scenario final
    {
    public:
        /// <!-- description -->
        ///   @brief Constructs a scenario
        ///
        /// <!-- inputs/outputs -->
        ///   @param name the name of the scenario (i.e., test case)
        ///
        explicit constexpr Scenario([[maybe_unused]] std::string_view const name) noexcept
        {

        }

        /// <!-- description -->
        ///   @brief Executes a lambda function as the body of the
        ///     scenario.
        ///
        /// <!-- inputs/outputs -->
        ///   @tparam FUNC_T the type of lambda being executed
        ///   @param mut_func the lambda being executed
        ///   @return Returns a reference to the scenario.
        ///
        template<typename FUNC_T>
        [[maybe_unused]] constexpr auto
        operator=(FUNC_T &&mut_func) &&noexcept -> Scenario &
        {
            mut_func();
            return *this;
        }

        /// <!-- description -->
        ///   @brief Destroyes a previously created bsl::ut_scenario
        ///
        constexpr ~Scenario() noexcept = default;

        /// <!-- description -->
        ///   @brief copy constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///
        constexpr Scenario(Scenario const &o) noexcept = default;

        /// <!-- description -->
        ///   @brief move constructor
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_o the object being moved
        ///
        constexpr Scenario(Scenario &&mut_o) noexcept = default;

        /// <!-- description -->
        ///   @brief copy assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param o the object being copied
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(Scenario const &o) &noexcept
            -> Scenario & = default;

        /// <!-- description -->
        ///   @brief move assignment
        ///
        /// <!-- inputs/outputs -->
        ///   @param mut_o the object being moved
        ///   @return a reference to *this
        ///
        [[maybe_unused]] constexpr auto operator=(Scenario &&mut_o) &noexcept
            -> Scenario & = default;
    };
}

