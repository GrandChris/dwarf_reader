///
/// @file:   pei_test.cpp
/// @author: GrandChris
/// @date:   2021-12-30
/// @brief:  Tests reading a pei file
///

#include "pei/pei.hpp"
#include "tests_example_program_example_program_exe.h"
#include "ut/ut.hpp"
#include "dwarf/debug_abbrev/dubug_abbrev_parser.hpp"
#include "dwarf/debug_info/unit_header/unit_header.hpp"
#include "dwarf/debug_info/unit_header/full_and_partial_compilation_unit_header.hpp"
#include "dwarf/debug_info/debug_info.hpp"

#include <iostream>

constexpr auto
tests() noexcept -> bool
{
    ut::Scenario("normal_case") = []() noexcept
    {
        constexpr std::span<char const> data(tests_example_program_example_program_exe);
        constexpr pei::SectionTable section_table(data);
        constexpr pei::SectionHeader section_header = section_table.find_section(".debug_info");
        constexpr std::span<char const> debug_info = data.subspan(section_header.pointer_to_raw_data(), section_header.size_of_raw_data());

        constexpr pei::SectionHeader section_header_debug_abbrev = section_table.find_section(".debug_abbrev");
        constexpr std::span<char const> debug_abbrev = data.subspan(section_header_debug_abbrev.pointer_to_raw_data(), section_header_debug_abbrev.size_of_raw_data());

        // std::cout << "debug_info.size: "  << debug_info.size() << std::endl;

        // std::cout << section_table.number_of_sections() << std::endl;
        // for(size_t i = 0; i < section_table.number_of_sections() ; ++i) {
        //     auto section = section_table.get_section(i);
        //     std::cout << i << " " << section.name() << std::endl;
        //     std::cout << i << "     " << section.physical_address() << std::endl;
        // }

        ut::Given() = [&]() noexcept {
            constexpr dwarf::DebugAbbrevParser parser(debug_abbrev);
            std::cout << parser << std::endl;
        };

        // ut::Given() = [&]() noexcept{
        //     constexpr dwarf::UnitHeader unit_header(debug_info);

            

        //     ut::Then() = [&]() noexcept {
        //         ut::check(unit_header.unit_type() == dwarf::UnitHeaderUnitType::dw_ut_compile);
        //     };

        //     ut::Then() = [&]() noexcept {
        //         if(unit_header.is(dwarf::UnitHeaderUnitType::dw_ut_compile)) {
        //             constexpr dwarf::SpecializedUnitHeader<dwarf::UnitHeaderUnitType::dw_ut_compile> specialized_unit_header(unit_header);
        //             ut::check(specialized_unit_header.address_size() == 8);
                    
        //             // std::cout << unit_header << std::endl;

       

        //             // std::cout << specialized_unit_header << std::endl;

        //         }
        //         // ut::check(unit_header.unit_type() == dwarf::UnitHeaderUnitType::dw_ut_compile);
        //     };
        // };

        // ut::Given() = [&]() noexcept{
        //     constexpr dwarf::DebugInfo debug_info_section(debug_info);

        //     ut::Then() = [&]() noexcept {
        //         for(dwarf::UnitHeader const unit_header : debug_info_section)
        //         {
        //             // std::cout << "address: " << unit_header.base_index() << " (0x" << std::hex << unit_header.base_index() << std::dec << ")" << std::endl;
        //             // for(size_t i = 0; i < 16; ++i) {
        //             //     std::cout << std::hex << "0x" << static_cast<uint32_t>(std::bit_cast<uint8_t>(debug_info[unit_header.base_index() + i])) << " " << std::dec << std::endl; 
        //             // }

        //             std::cout << unit_header;
        //             if(unit_header.is(dwarf::UnitHeaderUnitType::dw_ut_compile)) {
        //                 auto const specialized_unit_header = unit_header.as<dwarf::UnitHeaderUnitType::dw_ut_compile>();

        //                 std::cout << specialized_unit_header;
        //             }

        //             std::cout << std::endl;
        //         }

        //         // ut::check(unit_header.unit_type() == dwarf::UnitHeaderUnitType::dw_ut_compile);
        //     };
        // };

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

