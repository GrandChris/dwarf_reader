///
/// @file:   debug_abbrev_parser.hpp
/// @author: GrandChris
/// @date:   2022-01-03
/// @brief:  TParses the ./debug_abbrev section
///

#pragma once

#include "dwarf/dwarf_tags.hpp"
#include "dwarf/leb128.h"
#define MAGIC_ENUM_RANGE_MIN -128
#define MAGIC_ENUM_RANGE_MAX 256
#include "magic_enum.hpp"
#include <span>
#include <stdexcept>
#include <bit>
#include <ostream>

namespace dwarf
{

    class DebugAbbrevParser
    {
    public:

        ///////////////////////////////////////////////////////////////////////////////
        // Constructor

        explicit constexpr DebugAbbrevParser(std::span<char const> const data, size_t const index = 0) noexcept 
            : data_(data), start_index_(index), index_(index) {} 

        ///////////////////////////////////////////////////////////////////////////////
        // Public Methods

        constexpr auto
        next() noexcept -> bool;


        [[nodiscard]] constexpr auto
        is_abbreviation_code() const noexcept -> bool { return state_ == &state_abbreviation_code; }

        [[nodiscard]] constexpr auto
        is_tag() const noexcept -> bool { return state_ == &state_tag; }

        [[nodiscard]] constexpr auto
        is_children() const noexcept -> bool { return state_ == &state_children; }

        [[nodiscard]] constexpr auto
        is_attribute() const noexcept -> bool { return state_ == &state_attribute; }

        [[nodiscard]] constexpr auto
        is_form() const noexcept -> bool { return state_ == &state_form; }


        [[nodiscard]] constexpr auto
        get_abbreviation_code() const noexcept -> uint32_t { return abbreviation_code_; }

        [[nodiscard]] constexpr auto
        get_children() const noexcept -> dwarf::ChildrenDetermination { return children_; }

        [[nodiscard]] constexpr auto
        get_tag() const noexcept -> dwarf::Tag { return tag_; }

        [[nodiscard]] constexpr auto
        get_attribute() const noexcept -> dwarf::Attribute { return attribute_; }

        [[nodiscard]] constexpr auto
        get_form() const noexcept -> dwarf::Form { return form_; }

    private:

        ///////////////////////////////////////////////////////////////////////////////
        // Private Data

        std::span<char const> const data_;
        size_t const start_index_;
        size_t index_;

        uint32_t abbreviation_code_ = 0;
        dwarf::ChildrenDetermination children_ = {};
        dwarf::Tag tag_ = {};
        dwarf::Attribute attribute_ = {};
        dwarf::Form form_ = {};

        ///////////////////////////////////////////////////////////////////////////////
        // State Machine

        using State = auto (DebugAbbrevParser::* )() -> void;

        State state_ = state_initial;
        State next_state_ = state_abbreviation_code;

        constexpr auto
        state_initial() -> void;

        constexpr auto
        state_abbreviation_code() -> void;

        constexpr auto
        state_tag() -> void;

        constexpr auto
        state_children() -> void;

        constexpr auto
        state_attribute() -> void;

        constexpr auto
        state_form() -> void;
    };

    ///////////////////////////////////////////////////////////////////////////////
    // Implementation

    constexpr auto
    DebugAbbrevParser::next() noexcept -> bool
    {
        state_ = next_state_;
        (this->*state_)();

        return index_ <= data_.size();
    }

    constexpr auto
    DebugAbbrevParser::state_initial() -> void
    {
        next_state_ = state_abbreviation_code;
    }


    constexpr auto
    DebugAbbrevParser::state_abbreviation_code() -> void
    {
        // Each declaration begins with an unsigned LEB128 number representing the abbreviation code itself.
        using ValType = decltype(abbreviation_code_);
        auto [val, n] = details::uleb128<ValType>(data_.subspan(index_));
        if(n == 0 || n > sizeof(ValType)) [[unlikely]] {
            throw std::range_error("parsing of .debug_abbrev abbreviation_code failed: uleb128 wrong format");
        }
        
        abbreviation_code_ = static_cast<ValType>(val);
        index_ += n;    
        next_state_ = state_tag;
    }

    constexpr auto
    DebugAbbrevParser::state_tag() -> void
    {
        // The abbreviation code is followed by another unsigned LEB128 number that encodes the entry’s tag.
        using ValType = std::underlying_type_t<dwarf::Tag>;
        auto [val, n] = details::uleb128<ValType>(data_.subspan(index_));
        if(n == 0 || n > sizeof(ValType)) [[unlikely]] {
            throw std::range_error("parsing of .debug_abbrev tag failed: uleb128 wrong format");
        }
        
        tag_ = static_cast<dwarf::Tag>(val);
        index_ += n;    
        next_state_ = state_children;
    }

    constexpr auto
    DebugAbbrevParser::state_children() -> void
    {
        // Following the tag encoding is a 1-byte value that determines whether a 
        // debugging information entry using this abbreviation has child entries or not
        if(index_ >= data_.size()) [[unlikely]] {
            throw std::range_error("parsing of .debug_abbrev tag children failed");
        }
        using ValType = std::underlying_type_t<dwarf::ChildrenDetermination>;
        ValType const val = std::bit_cast<ValType>(data_[index_]);

        children_ = static_cast<dwarf::ChildrenDetermination>(val);
        index_ += sizeof(ValType);    

        // If the value is DW_CHILDREN_yes, the next physically succeeding entry of any
        // debugging information entry using this abbreviation is the first child of that
        // entry. If the 1-byte value following the abbreviation’s tag encoding is
        // DW_CHILDREN_no, the next physically succeeding entry of any debugging
        // information entry using this abbreviation is a sibling of that entry. (Either the
        // first child or sibling entries may be null entries)

        next_state_ = state_attribute;
    }

    constexpr auto
    DebugAbbrevParser::state_attribute() -> void
    {
        // Finally, the child encoding is followed by a series of attribute specifications. Each
        // attribute specification consists of two parts. The first part is an unsigned LEB128
        // number representing the attribute’s name. The second part is an unsigned
        // LEB128 number representing the attribute’s form. The series of attribute
        // specifications ends with an entry containing 0 for the name and 0 for the form.

        using ValType = std::underlying_type_t<dwarf::Attribute>;
        auto [val, n] = details::uleb128<ValType>(data_.subspan(index_));
        if(n == 0 || n > sizeof(ValType)) [[unlikely]] {
            throw std::range_error("parsing of .debug_abbrev attribute failed: uleb128 wrong format");
        }
        
        attribute_ = static_cast<dwarf::Attribute>(val);
        index_ += n;    
        next_state_ = state_form;
    }


    constexpr auto
    DebugAbbrevParser::state_form() -> void
    {
        // Finally, the child encoding is followed by a series of attribute specifications. Each
        // attribute specification consists of two parts. The first part is an unsigned LEB128
        // number representing the attribute’s name. The second part is an unsigned
        // LEB128 number representing the attribute’s form. The series of attribute
        // specifications ends with an entry containing 0 for the name and 0 for the form.

        using ValType = std::underlying_type_t<dwarf::Form>;
        auto [val, n] = details::uleb128<ValType>(data_.subspan(index_));
        if(n == 0 || n > sizeof(ValType)) [[unlikely]] {
            throw std::range_error("parsing of .debug_abbrev attribute failed: uleb128 wrong format");
        }
        
        form_ = static_cast<dwarf::Form>(val);
        index_ += n;    

        if(attribute_ == static_cast<dwarf::Attribute>(0) && form_ == static_cast<dwarf::Form>(0)) {
            next_state_ = state_abbreviation_code;
        }
        else {
            next_state_ = state_attribute;
        }
    }

    std::ostream & operator<<(std::ostream & ost, DebugAbbrevParser parser) 
    {
        while(parser.next()) {
            if(parser.is_abbreviation_code()){
                ost << parser.get_abbreviation_code() << "    ";
            }
            else if(parser.is_tag()){
                ost << magic_enum::enum_name(parser.get_tag()) << " (" << (static_cast<int>(parser.get_tag())) << ")" << "    ";
            }
            else if(parser.is_children()){
                ost << magic_enum::enum_name(parser.get_children()) << " (" << (static_cast<int>(parser.get_children())) << ")" << std::endl;
            }
            else if(parser.is_attribute()){
                ost << "  " <<  magic_enum::enum_name(parser.get_attribute()) << " (" << (static_cast<int>(parser.get_attribute())) << ")" << "    ";
            }
            else if(parser.is_form()){
                ost << magic_enum::enum_name(parser.get_form()) << " (" << (static_cast<int>(parser.get_form())) << ")" << std::endl;
            }
        }


        // ost << "address: " << unit_header.base_index() << " (0x" << std::hex << unit_header.base_index() << std::dec << ")" << std::endl;
        // ost << "is64bit:     " << std::boolalpha << unit_header.is64bit() << std::noboolalpha << std::endl;
        // ost << "unit_length: " << unit_header.unit_length() << " (0x" << std::hex << unit_header.unit_length() << std::dec << ")" << std::endl;
        // ost << "version:     " << unit_header.version() << std::endl;

        // auto const unit_type = unit_header.unit_type();
        // ost << "unit_type:   " << magic_enum::enum_name(unit_type) << " (" << (static_cast<int>(unit_type)) << ")" << std::endl;

        return ost;
    }

}