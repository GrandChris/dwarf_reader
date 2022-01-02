///
/// @file:   unit_header.hpp
/// @author: GrandChris
/// @date:   2022-01-01
/// @brief:  Format of Debugging Information
///

#pragma once

#include "dwarf/debug_info/dwarf_tags.hpp"
#include "details/type_list.hpp"
#include "magic_enum.hpp"
#include <span>
#include <cassert>
#include <type_traits>
#include <ostream>



namespace dwarf
{
    template<UnitHeaderUnitType>
    class SpecializedUnitHeader final 
    {
        // not implemented
    };

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
        struct DataStructure32 final
        {
            details::TypeList<0, uint32_t> unit_length; 
            details::TypeList<decltype(unit_length)::end, uint16_t> version; 
            details::TypeList<decltype(version)::end, UnitHeaderUnitType> unit_type; 
        };

        struct DataStructure64 final
        {
            details::TypeList<0, uint32_t> const identifier = 0xffffffff; 
            details::TypeList<decltype(identifier)::end, uint64_t> unit_length; 
            details::TypeList<decltype(unit_length)::end, uint16_t> version; 
            details::TypeList<decltype(version)::end, UnitHeaderUnitType> unit_type; 
        };

        constexpr UnitHeader() noexcept = default;
        // constexpr UnitHeader(UnitHeader const & other) noexcept = default;
        // constexpr UnitHeader(UnitHeader && other) noexcept = default;

        /// 
        /// @brief constructor
        /// @param data the complete data of a binary .exe file
        ///
        explicit constexpr UnitHeader(std::span<char const> const data, size_t const index = 0) noexcept 
            : data_(data), index_(index) {} 

        // [[nodiscard]] constexpr auto
        // operator=(UnitHeader const & other) noexcept -> UnitHeader const &
        // {
        //     data_ = std::span(other.data_);
        //     index_ = other.index_;

        //     return *this;
        // }

        [[nodiscard]] constexpr auto
        operator==(UnitHeader const & other) const noexcept -> bool
        {
            return index_ == other.index_ && data_.data() == other.data_.data() && data_.size() == other.data_.size();
        }


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
            if(version() < 5) 
            {   // unit_type is only available since dwarf5
                return static_cast<UnitHeaderUnitType>(0);
            }

            if(is64bit()){
                auto const res = decltype(DataStructure64::unit_type)::bit_cast(data_, base_index());
                return res;
            }
            else {
                auto const res = decltype(DataStructure32::unit_type)::bit_cast(data_, base_index());
                return res;
            }
        }

        
 

        // template<dwarf::UnitHeaderUnitType unit_type>
        // [[nodiscard]] constexpr auto
        // specialize() const noexcept 
        // {
        //     size_t const index = base_index() + size();
        //     bool const is_64_bit = is64bit();

        //     if constexpr(unit_type == UnitHeaderUnitType::dw_ut_compile 
        //               || unit_type == UnitHeaderUnitType::dw_ut_partial) 
        //     {
        //         return FullAndPartialCompilationUnitHeader(data_, index, is_64_bit);
        //     }
        //     else if constexpr(unit_type == UnitHeaderUnitType::dw_ut_skeleton 
        //                    || unit_type == UnitHeaderUnitType::dw_ut_split_compile) 
        //     {
        //         return SkeletonAndSplitCompilationUnitHeader(data_, index, is_64_bit);
        //     }
        //     else if constexpr(unit_type == UnitHeaderUnitType::dw_ut_type 
        //                    || unit_type == UnitHeaderUnitType::dw_ut_split_type) 
        //     {
        //         return TypeUnitHeader(data_, index, is_64_bit);
        //     }
        //     else {
        //         assert(false);
        //         return *this;
        //     }


        [[nodiscard]] constexpr auto
        is(UnitHeaderUnitType const type) const noexcept -> bool
        {
            if(version() < 5) 
            {   // unit_type is only available since dwarf5
                return false;
            }

            return unit_type() == type;
        }

        template<UnitHeaderUnitType unit_type>
        [[nodiscard]] constexpr auto
        as() const noexcept 
        {
            return SpecializedUnitHeader<unit_type>(*this);
        }

        [[nodiscard]] constexpr auto
        next() const noexcept -> UnitHeader 
        {   
            size_t const next_index = index_ + 4 + unit_length();
            if(next_index >= data_.size()) {
                return UnitHeader();
            }

            UnitHeader const next_unit_header(data_, next_index);
            if(!next_unit_header.valid()) {
                return UnitHeader();
            }

            return next_unit_header;
        }

        [[nodiscard]] constexpr auto
        valid() const noexcept -> bool
        {
            auto const identifier = decltype(DataStructure64::identifier)::bit_cast(data_, base_index());

            return identifier != 0;
        }

        /// 
        /// @brief Returns the address of the start of the UnitHeader
        ///
        [[nodiscard]] constexpr auto
        base_index() const noexcept -> uint32_t 
        {   
            return index_;
        }

        /// 
        /// @brief Returns the size of the unit header
        ///
        [[nodiscard]] constexpr auto
        size() const noexcept -> uint32_t 
        {   
            if(is64bit()){
                return decltype(DataStructure64::unit_type)::end;
            }
            else {
                return decltype(DataStructure32::unit_type)::end;
            }
        }

    protected:
        /// @brief the binary data of the .debug_line section
        std::span<char const> data_ = {};
        size_t index_ = 0;
    };

    std::ostream & operator<<(std::ostream & ost, UnitHeader const & unit_header) 
    {
        ost << "address: " << unit_header.base_index() << " (0x" << std::hex << unit_header.base_index() << std::dec << ")" << std::endl;
        ost << "is64bit:     " << std::boolalpha << unit_header.is64bit() << std::noboolalpha << std::endl;
        ost << "unit_length: " << unit_header.unit_length() << " (0x" << std::hex << unit_header.unit_length() << std::dec << ")" << std::endl;
        ost << "version:     " << unit_header.version() << std::endl;

        auto const unit_type = unit_header.unit_type();
        ost << "unit_type:   " << magic_enum::enum_name(unit_type) << " (" << (static_cast<int>(unit_type)) << ")" << std::endl;

        return ost;
    }



 


    // struct X {
    //     enum { value1 = true, value2 = true };
    // };
    
    // template<class T, std::enable_if_t<T::value1, int> = 0>
    // void func() {} // #1
    
    // template void func<X>(); // #2

}
