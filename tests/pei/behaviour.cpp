///
/// @file:   pei_test.cpp
/// @author: GrandChris
/// @date:   2021-12-30
/// @brief:  Tests reading a pei file
///

#include "pei/pei.hpp"
#include "FileToHeader_exe.h"
#include "ut/ut.hpp"

#include <iostream>

// template<bool use_static_assert>
// class TestFramework final
// {
// public:
//     template<auto a, auto b>
//     static constexpr auto
//     assert_eq() -> bool
//     {
//         if constexpr(use_static_assert){
//             static_assert(a == b);
//         }

//         return a == b;
//     }

//     // void use_static_assert(bool val) {
//     //     use_static_assert_ = val;
//     // }

// // private:
// //     bool use_static_assert_ = false;
// };

// // class StaticTestFramework
// // {
// // public:
// //     template<auto a, auto b>
// //     static constexpr auto


// //     // template<auto a, auto b>
// //     // using assert_eq = assert_eq_<a, b>();

// //     // virtual constexpr auto
// //     // assert_eq() const -> void
// //     // {
// //     //     static_assert
// //     // }
// // };


// template<auto a, auto b>
// [[nodiscard]] constexpr auto
// assert_eq() -> bool
// {
//     // static_assert(a == b);
//     return a == b;
// }

// constexpr auto
// test_pei(auto tf) -> void
// {
//     using Framework = decltype(tf);

//     constexpr std::span<uint8_t const> data(dwarf_reader_exe);

//     constexpr pei::PeiFile file = pei::get_pei_file(data);

//     constexpr auto res = Framework::assert_eq<file.optional_header.magic, 0x20b>();

//     // return assert_eq<file.optional_header.magic, 0x20b>();

//     // // if (file.optional_header.magic != 0x20b) return false;


//     // return data.size() > 72340;

//     // return true;
// }
// constexpr auto
// test() -> void 
// {
//     TestFramework<false> tf;

//     test_pei(tf);
// }

constexpr auto
tests() noexcept -> bool
{
    ut::Scenario("normal_case") = []() noexcept
    {
        constexpr std::span<char const> data(FileToHeader_exe);

        ut::Given() = []() noexcept{
            constexpr pei::OptionalHeader optional_header(data);
            ut::Then() = [&]() noexcept {
                ut::check(optional_header.magic() == 0x20b);
            };
        };

        ut::Given() = []() noexcept{
            constexpr pei::SectionTable section_table(data);
            constexpr auto number_of_sections = section_table.number_of_sections();
            constexpr pei::SectionHeader section_header = section_table.get_section(0);
            ut::Then() = [&]() noexcept {
                ut::check(number_of_sections > 0);
                constexpr auto name = section_header.name();
                ut::assert_eq(name, ".text");
            };

            // std::cout << number_of_sections << std::endl;
            // for(size_t i = 0; i < number_of_sections; ++i) {
            //     auto section = section_table.get_section(i);
            //     std::cout << i << " " << section.name() << std::endl;
            //     std::cout << i << "     " << section.physical_address() << std::endl;
            // }
        };
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
    static_assert(tests());
    return tests() ? EXIT_SUCCESS : EXIT_FAILURE;
}

