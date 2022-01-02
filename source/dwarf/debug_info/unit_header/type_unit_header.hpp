///
/// @file:   compilation_unit_header.hpp
/// @author: GrandChris
/// @date:   2022-01-01
/// @brief:  Format of Debugging Information
///

#pragma once

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
    class TypeUnitHeader final
    {
    public:
        template<typename LengthType = uint32_t>
        struct DataStructure final 
        {
            uint8_t address_size;
            LengthType debug_abbrev_offset;
            uint8_t type_signature;
            LengthType type_offset;
        };

        using DataStructure32 = DataStructure<uint32_t>;
        using DataStructure64 = DataStructure<uint64_t>;

        static_assert(std::is_standard_layout_v<DataStructure32>);
        static_assert(std::is_standard_layout_v<DataStructure64>);

        /// 
        /// @brief constructor
        /// @param data the complete data of a binary .exe file
        ///
        constexpr TypeUnitHeader(std::span<char const> const data, size_t const index, bool is_64_bit) noexcept 
            : data_(data), index_(index), is_64_bit_(is_64_bit) {} 


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
}
