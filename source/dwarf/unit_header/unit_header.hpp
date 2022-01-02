///
/// @file:   unit_header.hpp
/// @author: GrandChris
/// @date:   2022-01-01
/// @brief:  Format of Debugging Information
///

#pragma once

#include "dwarf/dwarf_tags.hpp"
#include "dwarf/unit_header/full_and_partial_compilation_unit_header.hpp"
#include "dwarf/unit_header/skeleton_and_split_compilation_unit_header.hpp"
#include "dwarf/unit_header/type_unit_header.hpp"
#include "details/type_list.hpp"
#include "magic_enum.hpp"
#include <span>
#include <cassert>
#include <type_traits>



// using LengthTypeDwarf32 = uint32_t;
// using LengthTypeDwarf64 = uint64_t;

// class FullAndPartialCompilationUnitHeader final{};
// class SkeletonAndSplitCompilationUnitHeader final{};
// class TypeUnitHeader final{};

// template<typename LengthTypeDwarf, dwarf::UnitType unit_type>
// [[nodiscard]] constexpr auto
// specialize_unit_header() noexcept {
//     switch (unit_type)
//     {
//     case dwarf::UnitType::compile:
//         return FullAndPartialCompilationUnitHeader<LengthTypeDwarf>();
//         break;
//     case dwarf::UnitType::skeleton:
//         return SkeletonAndSplitCompilationUnitHeader<LengthTypeDwarf>();
    
//     default:
//         break;
//     }(unit_type) {

//     }
// } 



namespace dwarf
{
    // template<typename T>
    // class TypeList {}




    /// @class dwarf::DIE
    ///
    /// @brief Format of Debugging Information
    /// @details For each compilation unit compiled with a DWARF producer, a contribution is
    ///     made to the .debug_info section of the object file. Each such contribution
    ///     consists of a compilation unit header (see Section 7.5.1.1 on page 200) followed
    ///     by a single DW_TAG_compile_unit or DW_TAG_partial_unit debugging
    ///     information entry, together with its children.
    ///
    class UnitHeader
    {
    public:
        // enum class DwarfVersion
        // {
        //     dwarf32,
        //     dwarf64
        // };

        // struct LengthType final
        // {
        //     using Dwarf32 = uint32_t;
        //     using Dwarf64 = uint64_t;
        // };  



        
        struct DataStructure32 final
        {
            details::TypeList<0, uint32_t> unit_length; 
            details::TypeList<decltype(unit_length)::end, uint16_t> version; 
            details::TypeList<decltype(version)::end, UnitHeaderUnitType> unit_type; 
        };

        struct DataStructure64 final
        {
            details::TypeList<0, uint16_t> const identifier = 0xffffffff; 
            details::TypeList<decltype(identifier)::end, uint64_t> unit_length; 
            details::TypeList<decltype(unit_length)::end, uint16_t> version; 
            details::TypeList<decltype(version)::end, UnitHeaderUnitType> unit_type; 
        };

        // static_assert(std::is_standard_layout_v<DataStructure32>);
        // static_assert(std::is_standard_layout_v<DataStructure64>);
        // static_assert(std::is_trivially_copyable_v<DataStructure32>);
        // static_assert(std::is_trivially_copyable_v<DataStructure64>);
        // static_assert(std::has_unique_object_representations_v<DataStructure32>);
        // static_assert(std::has_unique_object_representations_v<DataStructure64>);

        // struct FullAndPartialCompilationUnitHeaders final
        // {
        //     uint8_t address_size;
        //     LengthType debug_abbrev_offset;
        // };

        // struct SkeletonAndSplitCompilationUnitHeaders32 final
        // {
        //     uint8_t address_size;
        //     LengthType debug_abbrev_offset;
        //     uint8_t dwo_id;
        // };

        // struct TypeUnitHeaders32 final
        // {
        //     uint8_t address_size;
        //     LengthType debug_abbrev_offset;
        //     uint8_t type_signature;
        //     LengthType type_offset;
        // };

        /// 
        /// @brief constructor
        /// @param data the complete data of a binary .exe file
        ///
        constexpr UnitHeader(std::span<char const> const data, size_t const index = 0) noexcept : data_(data), index_(index) {} 


        [[nodiscard]] constexpr auto
        is64bit() const noexcept -> bool
        {
            constexpr DataStructure64 header64bit = {};

            auto const identifier = decltype(DataStructure64::identifier)::bit_cast(data_, base_index());

            return identifier == header64bit.identifier.val;
        }


        /// 
        /// @brief The total size of the section when loaded into memory. If this value is greater than 
        ///     SizeOfRawData, the section is zero-padded. This field is valid only for executable images and
        ///     should be set to zero for object files. 
        ///
        [[nodiscard]] constexpr auto
        unit_length() const noexcept -> decltype(DataStructure64::unit_length)::Type
        {
            if(is64bit()){
                auto const res = decltype(DataStructure64::unit_length)::bit_cast(data_, base_index());
                return res;
            }
            else {
                auto const res = decltype(DataStructure32::unit_length)::bit_cast(data_, base_index());
                return res;
            }
        }

        [[nodiscard]] constexpr auto
        version() const noexcept -> decltype(DataStructure64::version)::Type
        {
            if(is64bit()){
                auto const res = decltype(DataStructure64::version)::bit_cast(data_, base_index());
                return res;
            }
            else {
                auto const res = decltype(DataStructure32::version)::bit_cast(data_, base_index());
                return res;
            }
        }

        [[nodiscard]] constexpr auto
        unit_type() const noexcept -> decltype(DataStructure64::unit_type)::Type
        {
            if(is64bit()){
                auto const res = decltype(DataStructure64::unit_type)::bit_cast(data_, base_index());
                return res;
            }
            else {
                auto const res = decltype(DataStructure32::unit_type)::bit_cast(data_, base_index());
                return res;
            }
        }
 

        template<dwarf::UnitHeaderUnitType unit_type>
        [[nodiscard]] constexpr auto
        specialize() const noexcept 
        {
            size_t const index = base_index() + size();
            bool const is_64_bit = is64bit();

            if constexpr(unit_type == UnitHeaderUnitType::dw_ut_compile 
                      || unit_type == UnitHeaderUnitType::dw_ut_partial) 
            {
                return FullAndPartialCompilationUnitHeader(data_, index, is_64_bit);
            }
            else if constexpr(unit_type == UnitHeaderUnitType::dw_ut_skeleton 
                           || unit_type == UnitHeaderUnitType::dw_ut_split_compile) 
            {
                return SkeletonAndSplitCompilationUnitHeader(data_, index, is_64_bit);
            }
            else if constexpr(unit_type == UnitHeaderUnitType::dw_ut_type 
                           || unit_type == UnitHeaderUnitType::dw_ut_split_type) 
            {
                return TypeUnitHeader(data_, index, is_64_bit);
            }
            else {
                assert(false);
                return *this;
            }

            // switch (unit_type)
            // {
            // case dwarf::UnitHeaderUnitType::dw_ut_compile:
            // case dwarf::UnitHeaderUnitType::dw_ut_partial:
            //     return FullAndPartialCompilationUnitHeader(data_, index_);
            // break;

            // case dwarf::UnitHeaderUnitType::dw_ut_skeleton:
            // case dwarf::UnitHeaderUnitType::dw_ut_split_compile:
            //     return SkeletonAndSplitCompilationUnitHeader(data_, index_);
            // break;

            // case dwarf::UnitHeaderUnitType::dw_ut_type:
            // case dwarf::UnitHeaderUnitType::dw_ut_split_type:
            //     return TypeUnitHeader(data_, index_);
            // break;
            
            // default:
            //     assert(false);
            //     return *this;
            // break;
            // }
        } 

        // [[nodiscard]] constexpr auto
        // index_specialized_header() const noexcept -> uint64_t
        // {
        //     if(is64bit()) {
        //         auto const index = base_index() + offsetof(CommonHeader64, unit_type) + sizeof(CommonHeader64::unit_type);
        //         return index;
        //     }
        //     else {
        //         auto const index = base_index() + offsetof(CommonHeader32, unit_type) + sizeof(CommonHeader32::unit_type);
        //         return index;
        //     }
        // }

        /// 
        /// @brief Returns the address of the start of the UnitHeader
        ///
        [[nodiscard]] constexpr auto
        base_index() const noexcept -> uint32_t 
        {   
            return index_;
        }

        /// 
        /// @brief Returns the address of the start of the UnitHeader
        ///
        [[nodiscard]] constexpr auto
        size() const noexcept -> uint32_t 
        {   
            if(is64bit()){
                return sizeof(DataStructure64);
            }
            else {
                return sizeof(DataStructure32);
            }
        }

    protected:
        /// @brief the binary data of the .debug_line section
        std::span<char const> const data_;
        size_t const index_;
    };

    std::ostream & operator<<(std::ostream & ost, UnitHeader const & unit_header) 
    {
        ost << "is664bit:    " << std::boolalpha << unit_header.is64bit() << std::noboolalpha << std::endl;
        ost << "unit_length: " << unit_header.unit_length() << " (0x" << std::hex << unit_header.unit_length() << std::dec << ")" << std::endl;
        ost << "version:     " << unit_header.version() << std::endl;

        auto const unit_type = unit_header.unit_type();
        ost << "unit_type:   " << magic_enum::enum_name(unit_type) << " (" << (static_cast<int>(unit_type)) << ")" << std::endl;

        return ost;
    }
}
