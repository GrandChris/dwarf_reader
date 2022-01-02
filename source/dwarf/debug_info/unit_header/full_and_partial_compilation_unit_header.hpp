///
/// @file:   compilation_unit_header.hpp
/// @author: GrandChris
/// @date:   2022-01-01
/// @brief:  Format of Debugging Information
///

#pragma once

// #include "dwarf_tags.hpp"
#include "details/type_list.hpp"
#include "dwarf/debug_info/unit_header/unit_header.hpp"

namespace dwarf
{
    /// @class dwarf::DIE
    ///
    /// @brief Format of Debugging Information
    /// @details For each compilation unit compiled with a DWARF producer, a contribution is
    ///     made to the .debug_info section of the object file. Each such contribution
    ///     consists of a compilation unit header (see Section 7.5.1.1 on page 200) followed
    ///     by a single DW_TAG_compile_unit or DW_TAG_partial_unit debugging
    ///     information entry, together with its children.
    ///
    class FullAndPartialCompilationUnitHeader : public UnitHeader
    {
    public:
        template<typename LengthType = uint32_t>
        struct SpecializedDataStructure final 
        {
            details::TypeList<0, uint8_t> address_size; 
            details::TypeList<decltype(address_size)::end, LengthType> debug_abbrev_offset; 
        };
        using SpecializedDataStructure32 = SpecializedDataStructure<uint32_t>;
        using SpecializedDataStructure64 = SpecializedDataStructure<uint64_t>;

        [[nodiscard]] constexpr auto
        address_size() const noexcept -> decltype(SpecializedDataStructure64::address_size)::Type
        {
            if(is64bit()){
                auto const res = decltype(SpecializedDataStructure64::address_size)::bit_cast(data_, specialized_index());
                return res;
            }
            else {
                auto const res = decltype(SpecializedDataStructure32::address_size)::bit_cast(data_, specialized_index());
                return res;
            }
        }

        [[nodiscard]] constexpr auto
        debug_abbrev_offset() const noexcept -> decltype(SpecializedDataStructure64::debug_abbrev_offset)::Type
        {
            if(is64bit()){
                auto const res = decltype(SpecializedDataStructure64::debug_abbrev_offset)::bit_cast(data_, specialized_index());
                return res;
            }
            else {
                auto const res = decltype(SpecializedDataStructure32::debug_abbrev_offset)::bit_cast(data_, specialized_index());
                return res;
            }
        }

        /// 
        /// @brief constructor
        /// @param data the complete data of a binary .exe file
        ///
        constexpr FullAndPartialCompilationUnitHeader(UnitHeader const & unit_header) noexcept 
            : UnitHeader(unit_header) {}

        /// 
        /// @brief Returns the size of the unit header
        ///
        [[nodiscard]] constexpr auto
        size() const noexcept -> uint32_t 
        {   
            size_t const base_size = UnitHeader::size();

            if(is64bit()){
                return base_size + decltype(SpecializedDataStructure64::debug_abbrev_offset)::end;
            }
            else {
                return base_size + decltype(SpecializedDataStructure32::debug_abbrev_offset)::end;
            }
        }


    private:
        /// 
        /// @brief Returns the address of the start of the UnitHeader
        ///
        [[nodiscard]] constexpr auto
        specialized_index() const noexcept -> uint32_t 
        {   
            return index_ + UnitHeader::size();
        }
    };

    std::ostream & operator<<(std::ostream & ost, FullAndPartialCompilationUnitHeader const & header) 
    {
        // ost << static_cast<UnitHeader>(header);

        ost << "address_size:        " << static_cast<int>(header.address_size()) << std::endl;
        ost << "debug_abbrev_offset: " << header.debug_abbrev_offset() << " (0x" << std::hex << header.debug_abbrev_offset() << std::dec << ")" << std::endl;

        return ost;
    }


    template<>
    class SpecializedUnitHeader<UnitHeaderUnitType::dw_ut_compile> final : public FullAndPartialCompilationUnitHeader
    {
        using FullAndPartialCompilationUnitHeader::FullAndPartialCompilationUnitHeader;
    };  

    // template<>
    // class SpecializedUnitHeader<UnitHeaderUnitType::dw_ut_partial> final : public FullAndPartialCompilationUnitHeader 
    // {
    //     using FullAndPartialCompilationUnitHeader;
    // };     
}
