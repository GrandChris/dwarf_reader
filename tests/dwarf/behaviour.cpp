///
/// @file:   pei_test.cpp
/// @author: GrandChris
/// @date:   2021-12-30
/// @brief:  Tests reading a pei file
///

#include "pei/pei.hpp"
#include "FileToHeader_exe.h"
#include "ut/ut.hpp"
#include "dwarf/unit_header/unit_header.hpp"

#include <iostream>

constexpr auto
tests() noexcept -> bool
{
    ut::Scenario("normal_case") = []() noexcept
    {
        constexpr std::span<char const> data(FileToHeader_exe);
        constexpr pei::SectionTable section_table(data);
        constexpr pei::SectionHeader section_header = section_table.find_section(".debug_info");
        constexpr std::span<char const> debug_info = data.subspan(section_header.pointer_to_raw_data(), section_header.size_of_raw_data());

        // std::cout << section_table.number_of_sections() << std::endl;
        // for(size_t i = 0; i < section_table.number_of_sections() ; ++i) {
        //     auto section = section_table.get_section(i);
        //     std::cout << i << " " << section.name() << std::endl;
        //     std::cout << i << "     " << section.physical_address() << std::endl;
        // }

        ut::Given() = [&]() noexcept{
            constexpr dwarf::UnitHeader unit_header(debug_info);

            std::cout << unit_header << std::endl;

            ut::Then() = [&]() noexcept {
                ut::check(unit_header.unit_type() == dwarf::UnitHeaderUnitType::dw_ut_compile);
            };

            ut::Then() = [&]() noexcept {
                if(unit_header.unit_type() == dwarf::UnitHeaderUnitType::dw_ut_compile) {
                    constexpr dwarf::FullAndPartialCompilationUnitHeader specialized_unit_header = unit_header.specialize<dwarf::UnitHeaderUnitType::dw_ut_compile>();
                    
                    std::cout << specialized_unit_header << std::endl;

                }
                // ut::check(unit_header.unit_type() == dwarf::UnitHeaderUnitType::dw_ut_compile);
            };
        };

        // ut::Given() = []() noexcept{
        //     constexpr pei::SectionTable section_table(data);
        //     constexpr auto number_of_sections = section_table.number_of_sections();
        //     constexpr pei::SectionHeader section_header = section_table.get_section(0);
        //     ut::Then() = [&]() noexcept {
        //         ut::check(number_of_sections > 0);
        //         constexpr auto name = section_header.name();
        //         ut::assert_eq(name, ".text");
        //     };

            // std::cout << number_of_sections << std::endl;
            // for(size_t i = 0; i < number_of_sections; ++i) {
            //     auto section = section_table.get_section(i);
            //     std::cout << i << " " << section.name() << std::endl;
            //     std::cout << i << "     " << section.physical_address() << std::endl;
            // }

    };

    return true;
}


/// <!-- description -->
///   @brief Main function for this unit test. If a call to bsl::ut_check() fails
///     the application will fast fail. If all calls to bsl::ut_check() pass, this
///     function will successfully return with bsl::exit_success.
///
/// <!-- inputs/outputs -->
///   @return Always returns bsl::exit_success.
///
[[nodiscard]] auto
main() noexcept -> int
{
    // static_assert(tests());
    return tests() ? EXIT_SUCCESS : EXIT_FAILURE;
}

