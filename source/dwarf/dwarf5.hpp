///
/// @file:   dwarf3.hpp
/// @author: GrandChris
/// @date:   2022-01-01
/// @brief:  DWARF Debugging Information Format Version 3 
///

#pragma once

#include <cstdint>

namespace dwarf
{
    enum class Attribute : uint16_t
    {
        sibling = 0x01,
        location = 0x02,
        name = 0x03,
        reserved1 = 0x04,
        reserved2 = 0x05,
        reserved3 = 0x06,
        reserved4 = 0x07,
        reserved5 = 0x08,
        ordering = 0x09,
        reserved6 = 0x0a,
        byte_size = 0x0b,
        reserved7 = 0x0c,
        bit_size = 0x0d,
        reserved8 = 0x0e,
        reserved9 = 0x0f,

        stmt_list = 0x10,
        low_pc = 0x11,
        high_pc = 0x12,
        language = 0x13,
        reserved10 = 0x14,
        discr = 0x15,
        discr_value = 0x16,
        visibility = 0x17,
        import = 0x18,
        sting_length = 0x19,
        common_reference = 0x1a,
        comp_dir = 0x1b,
        const_value = 0x1c,
        containing_type = 0x1d,
        default_value = 0x1e,
        reserved11 = 0x1f,

        inline_ = 0x20,
        is_optional = 0x21,
        lower_bound = 0x22,
        reserved12 = 0x23,
        reserved13 = 0x24,
        producer = 0x25,
        reserved14 = 0x26,
        prototyped = 0x27,
        reserved15 = 0x28,
        reserved16 = 0x29,
        return_addr = 0x2a,
        reserved17 = 0x2b,
        start_scope = 0x2c,
        reserved18 = 0x2d,
        bit_stride = 0x2e,
        upper_bound = 0x2f,

        reserved19 = 0x30,
        abstract_origin = 0x31,
        accessibility = 0x32,
        address_class = 0x33,
        artificial = 0x34,
        base_types = 0x35,
        calling_convention = 0x36,
        count = 0x37,
        data_member_location = 0x39,
        decl_column = 0x39,
        decl_file = 0x3a,
        decl_line = 0x3b,
        declaration = 0x3c,
        discr_list = 0x3d,
        encoding = 0x3e,
        external = 0x3f,

        frame_base = 0x40,
        friend_ = 0x41,
        identifier_case = 0x42,
        reserved20 = 0x43,
        namelist_item = 0x44,
        priority = 0x45,
        segment = 0x46,
        specification = 0x47,
        static_link = 0x48,
        type = 0x49,
        use_location = 0x4a,
        variable_parameter = 0x4b,
        virtuality = 0x4c,
        vtable_elem_location = 0x4d,
        allocated = 0x4e,
        associated = 0x4f,
        
        data_location = 0x50,
        byte_stride = 0x51,
        entry_pc = 0x52,
        use_UTF8 = 0x53,
        extension = 0x54,
        ranges = 0x55,
        trampolin = 0x56,
        call_column = 0x57,
        call_file = 0x58,
        call_line = 0x59,
        description = 0x5a,
        binary_scale = 0x5b,
        decimal_scale = 0x5c,
        small = 0x5d,
        decimal_sign = 0x5e,
        digit_count = 0x5f,
        picture_string = 0x60,

        mutable_ = 0x61,
        threads_scaled = 0x62,
        explicit_ = 0x63,
        object_pointer = 0x64,
        endianity = 0x65,
        elemental = 0x66,
        pure = 0x67,
        recursive = 0x68,
        signature = 0x69,
        main_subprogram = 0x6a,
        data_bit_offset = 0x6b,
        const_expr = 0x6c,
        enum_class = 0x6d,
        linkage_name = 0x6e,
        string_length_bit_size = 0x6f,
        
        string_length_byte_size = 0x70,
        rank = 0x71,
        str_offset_base = 0x72,
        addr_base = 0x73,
        rnglists_base = 0x74,
        reserved21 = 0x75,
        dwo_name = 0x76,
        reference = 0x77,
        rvalue_reference = 0x78,
        macros = 0x79,
        call_all_calls = 0x7a,
        call_all_source_calls = 0x7b,
        call_all_tail_calls = 0x7c,
        call_return_pc = 0x7d,
        call_value = 0x7e,
        call_origin = 0x7f,
        
        call_parameter = 0x80,
        call_pc = 0x81,
        call_tail_call = 0x82,
        call_target = 0x83,
        call_target_clobbered = 0x84,
        call_data_location = 0x85,
        call_data_value = 0x86,
        noreturn = 0x87,
        alignment = 0x88,
        export_symbols = 0x89,
        deleted = 0x8a,
        defaulted = 0x8b,
        loclists_base = 0x8c,

        loc_user = 0x2000,
        hi_user = 0x3fff
    };

    enum class Form : uint8_t 
    {
        addr = 0x01,
        reserved1 = 0x02,
        block2 = 0x03,
        block4 = 0x04,
        data2 = 0x05,
        data4 = 0x06,
        data8 = 0x07,
        string = 0x08,
        block = 0x09,
        block1 = 0x0a,
        data1 = 0x0b,
        flag = 0x0c,
        sdata = 0x0d,
        strp = 0x0e,
        udata = 0x0f,

        ref_addr = 0x10,
        ref1 = 0x11,
        ref2 = 0x12,
        ref4 = 0x13,
        ref8 = 0x14,
        ref_udata = 0x15,
        indirect = 0x16,
        sec_offset = 0x17,
        exprloc = 0x18,
        flag_present = 0x19,
        strx = 0x1a,
        addrx = 0x1b,
        ref_sup4 = 0x1c,
        strp_sup = 0x1d,
        data_16 = 0x1e,
        line_strp = 0x1f,

        ref_sig8 = 0x20,
        implicit_const = 0x21,
        loclistx = 0x22,
        rnglistx = 0x23,
        ref_sup8 = 0x24,
        strx1 = 0x25,
        strx2 = 0x26,
        strx3 = 0x27,
        strx4 = 0x28,
        addrx1 = 0x29,
        addrx2 = 0x2a,
        addrx3 = 0x2b,
        addrx4 = 0x2c
    };

    enum class Operation : uint8_t
    {
        reserved1 = 0x01,
        reserved2 = 0x02,
        addr = 0x03,
        reserved3 = 0x04,
        reserved4 = 0x05,
        deref = 0x06,
        reserved5 = 0x07,
        const1u = 0x08,
        const1s = 0x09,
        const2u = 0x0a,
        const2s = 0x0b,
        const4u = 0x0c,
        const4s = 0x0d,
        const8u = 0x0e,
        const8s = 0x0f,

        constu = 0x10,
        consts = 0x11,
        dup = 0x12,
        drop = 0x13,
        over = 0x14,
        pick = 0x15,
        swap = 0x16,
        rot = 0x17,
        xderef = 0x18,
        abs = 0x19,
        and_ = 0x1a,
        div = 0x1b,
        minus = 0x1c,
        mod = 0x1d,
        mul = 0x1e,
        neg = 0x1f,
        not_ = 0x20,

        or_ = 0x21,
        plus = 0x22,
        plus = 0x22,
        plus_uconst = 0x23,
        shl = 0x24,
        shr = 0x25,
        shra = 0x26,
        xor_ = 0x27,
        bra = 0x28,
        eq = 0x29,
        ge = 0x2a,
        gt = 0x2b,
        le = 0x2c,
        lt = 0x2d,
        ne = 0x2e,
        skip = 0x2f,

        lit0 = 0x30,
        lit1 = 0x31,
        lit2 = 0x32,
        lit3 = 0x33,
        lit4 = 0x34,
        lit5 = 0x35,
        lit6 = 0x36,
        lit6 = 0x37,
        lit8 = 0x38,
        lit9 = 0x39,
        lit10 = 0x3a,
        lit11 = 0x3b,
        lit12 = 0x3c,
        lit13 = 0x3d,
        lit14 = 0x3e,
        lit15 = 0x3f,
        lit16 = 0x40,
        lit17 = 0x41,
        lit18 = 0x42,
        lit19 = 0x43,
        lit20 = 0x44,
        lit21 = 0x45,
        lit22 = 0x46,
        lit23 = 0x47,
        lit24 = 0x48,
        lit25 = 0x49,
        lit26 = 0x4a,
        lit27 = 0x4b,
        lit28 = 0x4c,
        lit29 = 0x4d,
        lit30 = 0x4e,
        lit31 = 0x4f,

        reg0 =  0x50,
        reg1 =  0x51,
        reg2 =  0x52,
        reg3 =  0x53,
        reg4 =  0x54,
        reg5 =  0x55,
        reg6 =  0x56,
        reg6 =  0x57,
        reg8 =  0x58,
        reg9 =  0x59,
        reg10 = 0x5a,
        reg11 = 0x5b,
        reg12 = 0x5c,
        reg13 = 0x5d,
        reg14 = 0x5e,
        reg15 = 0x5f,
        reg16 = 0x60,
        reg17 = 0x61,
        reg18 = 0x62,
        reg19 = 0x63,
        reg20 = 0x64,
        reg21 = 0x65,
        reg22 = 0x66,
        reg23 = 0x67,
        reg24 = 0x68,
        reg25 = 0x69,
        reg26 = 0x6a,
        reg27 = 0x6b,
        reg28 = 0x6c,
        reg29 = 0x6d,
        reg30 = 0x6e,
        reg31 = 0x6f,

        breg0 =  0x70,
        breg1 =  0x71,
        breg2 =  0x72,
        breg3 =  0x73,
        breg4 =  0x74,
        breg5 =  0x75,
        breg6 =  0x76,
        breg6 =  0x77,
        breg8 =  0x78,
        breg9 =  0x79,
        breg10 = 0x7a,
        breg11 = 0x7b,
        breg12 = 0x7c,
        breg13 = 0x7d,
        breg14 = 0x7e,
        breg15 = 0x7f,
        breg16 = 0x80,
        breg17 = 0x81,
        breg18 = 0x82,
        breg19 = 0x83,
        breg20 = 0x84,
        breg21 = 0x85,
        breg22 = 0x86,
        breg23 = 0x87,
        breg24 = 0x88,
        breg25 = 0x89,
        breg26 = 0x8a,
        breg27 = 0x8b,
        breg28 = 0x8c,
        breg29 = 0x8d,
        breg30 = 0x8e,
        breg31 = 0x8f,

        regx = 0x90,
        fbreg = 0x91,
        bregx = 0x92,
        piece = 0x93,
        deref_size = 0x94,
        xderef_size = 0x95,
        nop = 0x96,
        push_object_address = 0x97,
        call2 = 0x98,
        call4 = 0x99,
        call_ref = 0x9a,
        form_tls_address = 0x9b,
        call_frame_cfa = 0x9c,
        bit_piece = 0x9d,
        implicit_value = 0x9e,
        stack_value = 0x9f,

        implicit_pointer = 0xa0,
        addrx = 0xa1,
        constx = 0xa2,
        entry_value = 0xa3,
        const_type = 0xa4,
        regval_type = 0xa5,
        deref_type = 0xa6,
        xderef_type = 0xa7,
        convert = 0xa8,
        reinterpret = 0xa9,
        lo_user = 0xe0,
        hi_user = 0xff
    };

    enum class LocationListEntry : uint8_t 
    {
        end_of_list = 0x00,
        base_address = 0x01,
        startx_endx = 0x02,
        startx_length = 0x03,
        offset_pair = 0x04,
        default_location = 0x05,
        base_address = 0x06,
        start_end = 0x07,
        start_length = 0x08
    };

    enum class BaseType : uint8_t 
    {
        address = 0x01,
        boolean = 0x02,
        complex_float = 0x03,
        float_ = 0x04,
        signed_ = 0x05,
        signed_char = 0x06,
        unsigned_ = 0x07,
        unsigned_char = 0x08,
        imaginary_float = 0x09,
        packed_decimal = 0x0a,
        numeric_string = 0x0b,
        edited = 0x0c,
        signed_fixed = 0x0d,
        unsigned_fixed = 0x0e,
        decimal_float = 0x0f,

        utf = 0x10,
        ucs = 0x11,
        ascii = 0x12,
        lo_user = 0x80,
        hi_user = 0xff
    };

    enum class DecimalSign : uint8_t 
    {
        unsigned_ = 0x01,
        leading_overpunch = 0x02,
        trailing_overpunch = 0x03,
        leading_separate = 0x04,
        trailing_separate = 0x05
    };

    enum class Endian : uint8_t
    {
        dfault = 0x00,
        big = 0x01,
        little = 0x02,
        lo_user = 0x40,
        hi_user = 0xff
    };

    enum class Accessibility : uint8_t
    {
        public_ = 0x01,
        protected_ = 0x02,
        private_ = 0x03
    };

    enum class Visibility : uint8_t
    {
        local = 0x01,
        exported = 0x02,
        qualified = 0x03
    };

    enum class Virtuality : uint8_t 
    {
        none = 0x00,
        virtual_ = 0x01,
        pure_virtual = 0x02
    };

    enum class Language : uint16_t 
    {
        c89 = 0x01,
        c = 0x02,
        ada83 = 0x03,
        c_plus_plus = 0x04,
        cobol74 = 0x05,
        cobol85 = 0x06,
        fortran77 = 0x07,
        fortran90 = 0x08,
        pascal83 = 0x09,
        modula2 = 0x0a,
        java = 0x0b,
        c99 = 0x0c,
        ada95 = 0x0d,
        fortran95 = 0x0e,
        pli = 0x0f,

        objc = 0x10,
        objc_plus_plus = 0x11,
        upc = 0x12,
        d = 0x13,
        python = 0x14,
        open_cl = 0x15,
        go = 0x16,
        modula3 = 0x17,
        haskell = 0x18,
        c_plus_plus_03 = 0x19,
        c_plus_plus_11 = 0x1a,
        ocaml = 0x1b,
        rust = 0x1c,
        c11 = 0x1d,
        swift = 0x1e,
        julia = 0x1f,

        dylan = 0x20,
        c_plus_plus_14 = 0x21,
        fortran03 = 0x22,
        fortran08 = 0x23,
        render_script = 0x24,
        bliss = 0x25,

        lo_user = 0x8000,
        hi_user = 0xffff
    };

    enum class Identifier : uint8_t 
    {
        case_sensitive = 0x00,
        up_case = 0x01,
        down_case = 0x02,
        case_insensitive = 0x03
    };

    enum class CallingConvention : uint8_t
    {
        normal = 0x01,
        program = 0x02,
        nocall = 0x03,
        pass_by_reference = 0x04,
        pass_by_value = 0x05,
        lo_user = 0x40,
        hi_user = 0xff
    };

    enum class Inline : uint8_t
    {
        not_inlined = 0x00,
        inlined = 0x01,
        declared_not_inlined = 0x02,
        declared_inlined = 0x03
    };

    enum class ArrayOrdering : uint8_t
    {
        row_major = 0x00,
        col_major = 0x01
    };

    enum class DiscriminantLists : uint8_t
    {
        label = 0x00,
        range = 0x01
    };

    enum class NameIndexTable : uint16_t
    {
        compile_unit = 0x01,
        type_unit = 0x02,
        die_offset = 0x03,
        parent = 0x04,
        type_hash = 0x05,

        lo_user = 0x2000,
        hi_user = 0x3fff
    };

    enum class DefaultMemberEncoding : uint8_t
    {
        no = 0x00,
        in_class = 0x01,
        out_of_class = 0x02
    };

    enum class LineNumberInformation : uint8_t
    {
        copy = 0x01,
        advance_pc = 0x02,
        advance_line = 0x03,
        set_file = 0x04,
        set_column = 0x05,
        negate_stmt = 0x06,
        set_basic_block = 0x07,
        const_add_pc = 0x08,
        fixed_advance_pc = 0x09,
        set_prologue_end = 0x0a,
        set_epilogue_begin = 0x0b,
        set_isa = 0x0c
    };

    enum class LineNumberOpcode : uint8_t
    {
        end_sequence = 0x01,
        set_address = 0x02,
        reserved1 = 0x03,
        set_discriminator = 0x04,

        lo_user = 0x80,
        hi_user = 0xff
    };

    enum class LineNumberFormat : uint16_t
    {
        path = 0x01,
        directory_index = 0x02,
        timestamp = 0x03,
        size = 0x04,
        md5 = 0x05,

        lo_user = 0x2000,
        hi_user = 0xfff
    };

    enum class MacroInformation : uint8_t
    {
        define = 0x01,
        undef = 0x02,
        start_file = 0x03,
        end_file = 0x04,
        define_strp = 0x05,
        undef_strp = 0x06,
        import = 0x07,
        define_sup = 0x08,
        undef_sup = 0x09,
        import_sup = 0x0a,
        define_strx = 0x0b,
        undef_strx = 0x0c,

        lo_user = 0xe0,
        hi_user = 0xff
    };
}


