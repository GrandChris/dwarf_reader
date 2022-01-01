//
// @file:   main.cpp
// @author: GrandChris
// @date:   2021-11-12
// @brief:  Program entry point
//

// #include "sml/sml.h"
// #include "sml/transition.h"

#include <iostream>
// #include "pei/dwarf_reader_exe.h"


using namespace std;


// auto
// print_pei()
// {
//     constexpr std::span<uint8_t const> data(dwarf_reader_exe);
//     constexpr pei::PeiFile file = pei::get_pei_file(data);

//     cout << file.dos_header.lfanew << endl;

//     cout << "### File Header" << endl;
//     cout << "machine: " << file.file_header.machine << endl;
//     cout << "number_of_sections: " << file.file_header.number_of_sections << endl;
//     cout << "time_date_stamp: " << file.file_header.time_date_stamp << endl;
//     cout << "pointer_to_symbol_table: " << file.file_header.pointer_to_symbol_table << endl;
//     cout << "number_of_symbols: " << file.file_header.number_of_symbols << endl;
//     cout << "size_of_optional_header: " << file.file_header.size_of_optional_header << endl;
//     cout << "characteristics: " << file.file_header.characteristics << endl;
//     cout << endl;

//     cout << "### Optional Header" << endl;
//     cout << "magic: " << file.optional_header.magic << endl;
//     cout << "major_linker_version: " << static_cast<uint32_t>(file.optional_header.major_linker_version) << endl;
//     cout << "minor_linker_version: " << file.optional_header.minor_linker_version << endl;
//     cout << "size_of_code: " << file.optional_header.size_of_code << endl;
//     cout << "size_of_initialized_data: " << file.optional_header.size_of_initialized_data << endl;
//     cout << "size_of_uninitialized_data: " << file.optional_header.size_of_uninitialized_data << endl;
//     cout << "address_of_entry_point: " << file.optional_header.address_of_entry_point << endl;
//     cout << "base_of_code: " << file.optional_header.base_of_code << endl;
//     cout << "base_of_data: " << file.optional_header.base_of_data << endl;
//     cout << endl;

//     cout << "image_base: " << file.optional_header.image_base << endl;
//     cout << "section_alignment: " << file.optional_header.section_alignment << endl;
//     cout << "file_alignment: " << file.optional_header.file_alignment << endl;
//     cout << "major_operating_system_version: " << file.optional_header.major_operating_system_version << endl;
//     cout << "minor_operating_system_version: " << file.optional_header.minor_operating_system_version << endl;
//     cout << "major_image_version: " << file.optional_header.major_image_version << endl;
//     cout << "minor_image_version: " << file.optional_header.minor_image_version << endl;
//     cout << "major_subsystem_version: " << file.optional_header.major_subsystem_version << endl;
//     cout << "minor_subsystem_version: " << file.optional_header.minor_subsystem_version << endl;
//     cout << "reserved1: " << file.optional_header.reserved1 << endl;
//     cout << "size_of_image: " << file.optional_header.size_of_image << endl;
//     cout << "size_of_headers: " << file.optional_header.size_of_headers << endl;
//     cout << "check_sum: " << file.optional_header.check_sum << endl;
//     cout << "subsystem: " << file.optional_header.subsystem << endl;
//     cout << "dll_characteristics: " << file.optional_header.dll_characteristics << endl;
//     cout << "size_of_stack_reserve: " << file.optional_header.size_of_stack_reserve << endl;
//     cout << "size_of_stack_commit: " << file.optional_header.size_of_stack_commit << endl;
//     cout << "size_of_heap_reserve: " << file.optional_header.size_of_heap_reserve << endl;
//     cout << "size_of_heap_commit: " << file.optional_header.size_of_heap_commit << endl;
//     cout << "loader_flags: " << file.optional_header.loader_flags << endl;
//     cout << "number_of_rva_and_sizes: " << file.optional_header.number_of_rva_and_sizes << endl;
//     cout << endl;
// }

auto
main() -> int 
{
    cout << "Hello World!" << endl;

    // print_pei();

    return 0;
} 

