///
/// @file:   compilation_unit_header.hpp
/// @author: GrandChris
/// @date:   2022-01-01
/// @brief:  Format of Debugging Information
///

#pragma once

// #include "dwarf_tags.hpp"

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
    class FullAndPartialCompilationUnitHeader final
    {
    public:
        template<typename LengthType = uint32_t>
        struct DataStructure final 
        {
            uint8_t address_size;
            LengthType debug_abbrev_offset;
        };
        using DataStructure32 = DataStructure<uint32_t>;
        using DataStructure64 = DataStructure<uint64_t>;

        static_assert(std::is_standard_layout_v<DataStructure32>);
        static_assert(std::is_standard_layout_v<DataStructure64>);
        static_assert(std::is_trivially_copyable_v<DataStructure32>);
        static_assert(std::has_unique_object_representations_v<DataStructure32>);
        static_assert(std::has_unique_object_representations_v<DataStructure64>);

        const size_t size = sizeof(DataStructure32);

        /// 
        /// @brief constructor
        /// @param data the complete data of a binary .exe file
        ///
        constexpr FullAndPartialCompilationUnitHeader(std::span<char const> const data, size_t const index, bool is_64_bit) noexcept 
            : data_(data), index_(index), is_64_bit_(is_64_bit) {} 


        [[nodiscard]] constexpr auto
        base_index() const noexcept -> uint32_t 
        {   
            return index_;
        }

        [[nodiscard]] constexpr auto
        address_size() const noexcept -> decltype(DataStructure64::address_size)
        {
            if(is_64_bit_){
                auto const index = base_index() + offsetof(DataStructure64, address_size);
                auto const res = details::bit_cast<decltype(DataStructure64::address_size)>(data_, index);
                return res;
            }
            else {
                auto const index = base_index() + offsetof(DataStructure32, address_size);
                auto const res = details::bit_cast<decltype(DataStructure32::address_size)>(data_, index);
                return res;
            };
        }

        [[nodiscard]] constexpr auto
        debug_abbrev_offset() const noexcept ->  decltype(DataStructure64::debug_abbrev_offset)
        {
            if(is_64_bit_){
                auto const index = base_index() + offsetof(DataStructure64, debug_abbrev_offset);
                auto const res = details::bit_cast<decltype(DataStructure64::debug_abbrev_offset)>(data_, index);
                return res;
            }
            else {
                auto const index = base_index() + offsetof(DataStructure32, debug_abbrev_offset);
                auto const res = details::bit_cast<decltype(DataStructure32::debug_abbrev_offset)>(data_, index);
                return res;
            };
        }
    
        /// 
        /// @brief Returns the address of the start of the UnitHeader
        ///
        [[nodiscard]] constexpr auto
        size() const noexcept -> uint32_t 
        {   
            if(is_64_bit_){
                return sizeof(DataStructure64);
            }
            else {
                return sizeof(DataStructure32);
            }
        }

    private:
        std::span<char const> const data_;
        size_t const index_;
        bool const is_64_bit_;
    };

    std::ostream & operator<<(std::ostream & ost, FullAndPartialCompilationUnitHeader const & header) 
    {
        ost << "address_size:        " << static_cast<int>(header.address_size()) << std::endl;
        ost << "debug_abbrev_offset: " << header.debug_abbrev_offset() << " (0x" << std::hex << header.debug_abbrev_offset() << std::dec << ")" << std::endl;

        return ost;
    }
}
