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
    enum class UnitHeaderUnitType : uint8_t
    {
        dw_ut_compile = 0x01,
        dw_ut_type = 0x02,
        dw_ut_partial = 0x03,
        dw_ut_skeleton = 0x04,
        dw_ut_split_compile = 0x05,
        dw_ut_split_type = 0x06,

        dw_ut_lo_user = 0x80,
        dw_ut_hi_user = 0xff
    };

    enum class Tag : uint16_t
    {
        dw_tag_array_type = 0x01,
        dw_tag_class_type = 0x02,
        dw_tag_entry_point = 0x03,
        dw_tag_enumeration_type = 0x04,
        dw_tag_formal_parameter = 0x05,
        dw_tag_reserved1 = 0x06,
        dw_tag_reserved2 = 0x07,
        dw_tag_imported_decleration = 0x08,
        dw_tag_reserved3 = 0x09,
        dw_tag_label = 0x0a,
        dw_tag_lexical_block = 0x0b,
        dw_tag_reserved4 = 0x0c,
        dw_tag_member = 0x0d,
        dw_tag_reserved5 = 0x0e,
        dw_tag_pointer_type = 0x0f,

        dw_tag_reference_type = 0x10,
        dw_tag_compile_unit = 0x11,
        dw_tag_string_type = 0x12,
        dw_tag_structure_type = 0x13,
        dw_tag_reserved6 = 0x14,
        dw_tag_subroutine_type = 0x15,
        dw_tag_typedef_ = 0x16,
        dw_tag_union_type = 0x17,
        dw_tag_unspecified_parameters = 0x18,
        dw_tag_variant = 0x19,
        dw_tag_common_block = 0x1a,
        dw_tag_common_inclusion = 0x1b,
        dw_tag_inheritance = 0x1c,
        dw_tag_inlined_subroutine = 0x1d,
        dw_tag_module = 0x1e,
        dw_tag_ptr_to_member_type = 0x1f,

        dw_tag_set_type = 0x20,
        dw_tag_subrange_type = 0x21,
        dw_tag_with_stmt = 0x22,
        dw_tag_access_declaration = 0x23,
        dw_tag_base_type = 0x24,
        dw_tag_catch_block = 0x25,
        dw_tag_const_type = 0x26,
        dw_tag_constant = 0x27,
        dw_tag_enumerator = 0x28,
        dw_tag_file_type = 0x29,
        dw_tag_friend_ = 0x2a,
        dw_tag_namelist = 0x2b,
        dw_tag_namelist_item = 0x2c,
        dw_tag_packed_type = 0x2d,
        dw_tag_subprogram = 0x2e,
        dw_tag_template_type_parameter = 0x2f,

        dw_tag_template_value_parameter = 0x30,
        dw_tag_thrown_type = 0x31,
        dw_tag_try_block = 0x32,
        dw_tag_variant_part = 0x33,
        dw_tag_variable = 0x34,
        dw_tag_volatile_type = 0x35,
        dw_tag_dwarf_procedure = 0x36,
        dw_tag_restrict_type = 0x37,
        dw_tag_namespace_ = 0x39,
        dw_tag_imported_module = 0x3a,
        dw_tag_unspecified_type = 0x3b,
        dw_tag_partial_unit = 0x3c,
        dw_tag_imported_unit = 0x3d,
        dw_tag_reserved7 = 0x3e,
        dw_tag_consdition = 0x3f,

        dw_tag_shared_type = 0x40,
        dw_tag_type_unit = 0x41,
        dw_tag_rvalue_reference_type = 0x42,
        dw_tag_template_alias = 0x43,
        dw_tag_coarray_type = 0x44,
        dw_tag_generic_subrange = 0x45,
        dw_tag_dynamic_type = 0x46,
        dw_tag_atomic_type = 0x47,
        dw_tag_call_site = 0x48,
        dw_tag_call_site_parameter = 0x49,
        dw_tag_skeleton_unit = 0x4a,
        dw_tag_immutable_type = 0x4b,

        dw_tag_lo_user = 0x4080,
        dw_tag_hi_user = 0xffff
    };

    enum class ChildrenDetermination : uint8_t 
    {
        dw_children_no = 0x00,
        dw_children_yes = 0x01
    };

    enum class Attribute : uint16_t
    {
        dw_at_sibling = 0x01,
        dw_at_location = 0x02,
        dw_at_name = 0x03,
        dw_at_reserved1 = 0x04,
        dw_at_reserved2 = 0x05,
        dw_at_reserved3 = 0x06,
        dw_at_reserved4 = 0x07,
        dw_at_reserved5 = 0x08,
        dw_at_ordering = 0x09,
        dw_at_reserved6 = 0x0a,
        dw_at_byte_size = 0x0b,
        dw_at_reserved7 = 0x0c,
        dw_at_bit_size = 0x0d,
        dw_at_reserved8 = 0x0e,
        dw_at_reserved9 = 0x0f,

        dw_at_stmt_list = 0x10,
        dw_at_low_pc = 0x11,
        dw_at_high_pc = 0x12,
        dw_at_language = 0x13,
        dw_at_reserved10 = 0x14,
        dw_at_discr = 0x15,
        dw_at_discr_value = 0x16,
        dw_at_visibility = 0x17,
        dw_at_import = 0x18,
        dw_at_sting_length = 0x19,
        dw_at_common_reference = 0x1a,
        dw_at_comp_dir = 0x1b,
        dw_at_const_value = 0x1c,
        dw_at_containing_type = 0x1d,
        dw_at_default_value = 0x1e,
        dw_at_reserved11 = 0x1f,

        dw_at_inline_ = 0x20,
        dw_at_is_optional = 0x21,
        dw_at_lower_bound = 0x22,
        dw_at_reserved12 = 0x23,
        dw_at_reserved13 = 0x24,
        dw_at_producer = 0x25,
        dw_at_reserved14 = 0x26,
        dw_at_prototyped = 0x27,
        dw_at_reserved15 = 0x28,
        dw_at_reserved16 = 0x29,
        dw_at_return_addr = 0x2a,
        dw_at_reserved17 = 0x2b,
        dw_at_start_scope = 0x2c,
        dw_at_reserved18 = 0x2d,
        dw_at_bit_stride = 0x2e,
        dw_at_upper_bound = 0x2f,

        dw_at_reserved19 = 0x30,
        dw_at_abstract_origin = 0x31,
        dw_at_accessibility = 0x32,
        dw_at_address_class = 0x33,
        dw_at_artificial = 0x34,
        dw_at_base_types = 0x35,
        dw_at_calling_convention = 0x36,
        dw_at_count = 0x37,
        dw_at_data_member_location = 0x39,
        dw_at_decl_column = 0x39,
        dw_at_decl_file = 0x3a,
        dw_at_decl_line = 0x3b,
        dw_at_declaration = 0x3c,
        dw_at_discr_list = 0x3d,
        dw_at_encoding = 0x3e,
        dw_at_external = 0x3f,

        dw_at_frame_base = 0x40,
        dw_at_friend_ = 0x41,
        dw_at_identifier_case = 0x42,
        dw_at_reserved20 = 0x43,
        dw_at_namelist_item = 0x44,
        dw_at_priority = 0x45,
        dw_at_segment = 0x46,
        dw_at_specification = 0x47,
        dw_at_static_link = 0x48,
        dw_at_type = 0x49,
        dw_at_use_location = 0x4a,
        dw_at_variable_parameter = 0x4b,
        dw_at_virtuality = 0x4c,
        dw_at_vtable_elem_location = 0x4d,
        dw_at_allocated = 0x4e,
        dw_at_associated = 0x4f,
        
        dw_at_data_location = 0x50,
        dw_at_byte_stride = 0x51,
        dw_at_entry_pc = 0x52,
        dw_at_use_UTF8 = 0x53,
        dw_at_extension = 0x54,
        dw_at_ranges = 0x55,
        dw_at_trampolin = 0x56,
        dw_at_call_column = 0x57,
        dw_at_call_file = 0x58,
        dw_at_call_line = 0x59,
        dw_at_description = 0x5a,
        dw_at_binary_scale = 0x5b,
        dw_at_decimal_scale = 0x5c,
        dw_at_small = 0x5d,
        dw_at_decimal_sign = 0x5e,
        dw_at_digit_count = 0x5f,
        dw_at_picture_string = 0x60,

        dw_at_mutable_ = 0x61,
        dw_at_threads_scaled = 0x62,
        dw_at_explicit_ = 0x63,
        dw_at_object_pointer = 0x64,
        dw_at_endianity = 0x65,
        dw_at_elemental = 0x66,
        dw_at_pure = 0x67,
        dw_at_recursive = 0x68,
        dw_at_signature = 0x69,
        dw_at_main_subprogram = 0x6a,
        dw_at_data_bit_offset = 0x6b,
        dw_at_const_expr = 0x6c,
        dw_at_enum_class = 0x6d,
        dw_at_linkage_name = 0x6e,
        dw_at_string_length_bit_size = 0x6f,
        
        dw_at_string_length_byte_size = 0x70,
        dw_at_rank = 0x71,
        dw_at_str_offset_base = 0x72,
        dw_at_addr_base = 0x73,
        dw_at_rnglists_base = 0x74,
        dw_at_reserved21 = 0x75,
        dw_at_dwo_name = 0x76,
        dw_at_reference = 0x77,
        dw_at_rvalue_reference = 0x78,
        dw_at_macros = 0x79,
        dw_at_call_all_calls = 0x7a,
        dw_at_call_all_source_calls = 0x7b,
        dw_at_call_all_tail_calls = 0x7c,
        dw_at_call_return_pc = 0x7d,
        dw_at_call_value = 0x7e,
        dw_at_call_origin = 0x7f,
        
        dw_at_call_parameter = 0x80,
        dw_at_call_pc = 0x81,
        dw_at_call_tail_call = 0x82,
        dw_at_call_target = 0x83,
        dw_at_call_target_clobbered = 0x84,
        dw_at_call_data_location = 0x85,
        dw_at_call_data_value = 0x86,
        dw_at_noreturn = 0x87,
        dw_at_alignment = 0x88,
        dw_at_export_symbols = 0x89,
        dw_at_deleted = 0x8a,
        dw_at_defaulted = 0x8b,
        dw_at_loclists_base = 0x8c,

        dw_at_loc_user = 0x2000,
        dw_at_hi_user = 0x3fff
    };

    enum class Form : uint8_t 
    {
        dw_form_addr = 0x01,
        dw_form_reserved1 = 0x02,
        dw_form_block2 = 0x03,
        dw_form_block4 = 0x04,
        dw_form_data2 = 0x05,
        dw_form_data4 = 0x06,
        dw_form_data8 = 0x07,
        dw_form_string = 0x08,
        dw_form_block = 0x09,
        dw_form_block1 = 0x0a,
        dw_form_data1 = 0x0b,
        dw_form_flag = 0x0c,
        dw_form_sdata = 0x0d,
        dw_form_strp = 0x0e,
        dw_form_udata = 0x0f,

        dw_form_ref_addr = 0x10,
        dw_form_ref1 = 0x11,
        dw_form_ref2 = 0x12,
        dw_form_ref4 = 0x13,
        dw_form_ref8 = 0x14,
        dw_form_ref_udata = 0x15,
        dw_form_indirect = 0x16,
        dw_form_sec_offset = 0x17,
        dw_form_exprloc = 0x18,
        dw_form_flag_present = 0x19,
        dw_form_strx = 0x1a,
        dw_form_addrx = 0x1b,
        dw_form_ref_sup4 = 0x1c,
        dw_form_strp_sup = 0x1d,
        dw_form_data_16 = 0x1e,
        dw_form_line_strp = 0x1f,

        dw_form_ref_sig8 = 0x20,
        dw_form_implicit_const = 0x21,
        dw_form_loclistx = 0x22,
        dw_form_rnglistx = 0x23,
        dw_form_ref_sup8 = 0x24,
        dw_form_strx1 = 0x25,
        dw_form_strx2 = 0x26,
        dw_form_strx3 = 0x27,
        dw_form_strx4 = 0x28,
        dw_form_addrx1 = 0x29,
        dw_form_addrx2 = 0x2a,
        dw_form_addrx3 = 0x2b,
        dw_form_addrx4 = 0x2c
    };

    enum class Operation : uint8_t
    {
        dw_op_reserved1 = 0x01,
        dw_op_reserved2 = 0x02,
        dw_op_addr = 0x03,
        dw_op_reserved3 = 0x04,
        dw_op_reserved4 = 0x05,
        dw_op_deref = 0x06,
        dw_op_reserved5 = 0x07,
        dw_op_const1u = 0x08,
        dw_op_const1s = 0x09,
        dw_op_const2u = 0x0a,
        dw_op_const2s = 0x0b,
        dw_op_const4u = 0x0c,
        dw_op_const4s = 0x0d,
        dw_op_const8u = 0x0e,
        dw_op_const8s = 0x0f,

        dw_op_constu = 0x10,
        dw_op_consts = 0x11,
        dw_op_dup = 0x12,
        dw_op_drop = 0x13,
        dw_op_over = 0x14,
        dw_op_pick = 0x15,
        dw_op_swap = 0x16,
        dw_op_rot = 0x17,
        dw_op_xderef = 0x18,
        dw_op_abs = 0x19,
        dw_op_and_ = 0x1a,
        dw_op_div = 0x1b,
        dw_op_minus = 0x1c,
        dw_op_mod = 0x1d,
        dw_op_mul = 0x1e,
        dw_op_neg = 0x1f,
        dw_op_not_ = 0x20,

        dw_op_or_ = 0x21,
        dw_op_plus = 0x22,
        dw_op_plus_uconst = 0x23,
        dw_op_shl = 0x24,
        dw_op_shr = 0x25,
        dw_op_shra = 0x26,
        dw_op_xor_ = 0x27,
        dw_op_bra = 0x28,
        dw_op_eq = 0x29,
        dw_op_ge = 0x2a,
        dw_op_gt = 0x2b,
        dw_op_le = 0x2c,
        dw_op_lt = 0x2d,
        dw_op_ne = 0x2e,
        dw_op_skip = 0x2f,

        dw_op_lit0 = 0x30,
        dw_op_lit1 = 0x31,
        dw_op_lit2 = 0x32,
        dw_op_lit3 = 0x33,
        dw_op_lit4 = 0x34,
        dw_op_lit5 = 0x35,
        dw_op_lit6 = 0x36,
        dw_op_lit7 = 0x37,
        dw_op_lit8 = 0x38,
        dw_op_lit9 = 0x39,
        dw_op_lit10 = 0x3a,
        dw_op_lit11 = 0x3b,
        dw_op_lit12 = 0x3c,
        dw_op_lit13 = 0x3d,
        dw_op_lit14 = 0x3e,
        dw_op_lit15 = 0x3f,
        dw_op_lit16 = 0x40,
        dw_op_lit17 = 0x41,
        dw_op_lit18 = 0x42,
        dw_op_lit19 = 0x43,
        dw_op_lit20 = 0x44,
        dw_op_lit21 = 0x45,
        dw_op_lit22 = 0x46,
        dw_op_lit23 = 0x47,
        dw_op_lit24 = 0x48,
        dw_op_lit25 = 0x49,
        dw_op_lit26 = 0x4a,
        dw_op_lit27 = 0x4b,
        dw_op_lit28 = 0x4c,
        dw_op_lit29 = 0x4d,
        dw_op_lit30 = 0x4e,
        dw_op_lit31 = 0x4f,

        dw_op_reg0 =  0x50,
        dw_op_reg1 =  0x51,
        dw_op_reg2 =  0x52,
        dw_op_reg3 =  0x53,
        dw_op_reg4 =  0x54,
        dw_op_reg5 =  0x55,
        dw_op_reg6 =  0x56,
        dw_op_reg7 =  0x57,
        dw_op_reg8 =  0x58,
        dw_op_reg9 =  0x59,
        dw_op_reg10 = 0x5a,
        dw_op_reg11 = 0x5b,
        dw_op_reg12 = 0x5c,
        dw_op_reg13 = 0x5d,
        dw_op_reg14 = 0x5e,
        dw_op_reg15 = 0x5f,
        dw_op_reg16 = 0x60,
        dw_op_reg17 = 0x61,
        dw_op_reg18 = 0x62,
        dw_op_reg19 = 0x63,
        dw_op_reg20 = 0x64,
        dw_op_reg21 = 0x65,
        dw_op_reg22 = 0x66,
        dw_op_reg23 = 0x67,
        dw_op_reg24 = 0x68,
        dw_op_reg25 = 0x69,
        dw_op_reg26 = 0x6a,
        dw_op_reg27 = 0x6b,
        dw_op_reg28 = 0x6c,
        dw_op_reg29 = 0x6d,
        dw_op_reg30 = 0x6e,
        dw_op_reg31 = 0x6f,

        dw_op_breg0 =  0x70,
        dw_op_breg1 =  0x71,
        dw_op_breg2 =  0x72,
        dw_op_breg3 =  0x73,
        dw_op_breg4 =  0x74,
        dw_op_breg5 =  0x75,
        dw_op_breg6 =  0x76,
        dw_op_breg7 =  0x77,
        dw_op_breg8 =  0x78,
        dw_op_breg9 =  0x79,
        dw_op_breg10 = 0x7a,
        dw_op_breg11 = 0x7b,
        dw_op_breg12 = 0x7c,
        dw_op_breg13 = 0x7d,
        dw_op_breg14 = 0x7e,
        dw_op_breg15 = 0x7f,
        dw_op_breg16 = 0x80,
        dw_op_breg17 = 0x81,
        dw_op_breg18 = 0x82,
        dw_op_breg19 = 0x83,
        dw_op_breg20 = 0x84,
        dw_op_breg21 = 0x85,
        dw_op_breg22 = 0x86,
        dw_op_breg23 = 0x87,
        dw_op_breg24 = 0x88,
        dw_op_breg25 = 0x89,
        dw_op_breg26 = 0x8a,
        dw_op_breg27 = 0x8b,
        dw_op_breg28 = 0x8c,
        dw_op_breg29 = 0x8d,
        dw_op_breg30 = 0x8e,
        dw_op_breg31 = 0x8f,

        dw_op_regx = 0x90,
        dw_op_fbreg = 0x91,
        dw_op_bregx = 0x92,
        dw_op_piece = 0x93,
        dw_op_deref_size = 0x94,
        dw_op_xderef_size = 0x95,
        dw_op_nop = 0x96,
        dw_op_push_object_address = 0x97,
        dw_op_call2 = 0x98,
        dw_op_call4 = 0x99,
        dw_op_call_ref = 0x9a,
        dw_op_form_tls_address = 0x9b,
        dw_op_call_frame_cfa = 0x9c,
        dw_op_bit_piece = 0x9d,
        dw_op_implicit_value = 0x9e,
        dw_op_stack_value = 0x9f,

        dw_op_implicit_pointer = 0xa0,
        dw_op_addrx = 0xa1,
        dw_op_constx = 0xa2,
        dw_op_entry_value = 0xa3,
        dw_op_const_type = 0xa4,
        dw_op_regval_type = 0xa5,
        dw_op_deref_type = 0xa6,
        dw_op_xderef_type = 0xa7,
        dw_op_convert = 0xa8,
        dw_op_reinterpret = 0xa9,

        dw_op_lo_user = 0xe0,
        dw_op_hi_user = 0xff
    };

    enum class LocationListEntry : uint8_t 
    {
        dw_lle_end_of_list = 0x00,
        dw_lle_base_addressx = 0x01,
        dw_lle_startx_endx = 0x02,
        dw_lle_startx_length = 0x03,
        dw_lle_offset_pair = 0x04,
        dw_lle_default_location = 0x05,
        dw_lle_base_address = 0x06,
        dw_lle_start_end = 0x07,
        dw_lle_start_length = 0x08
    };

    enum class BaseTypeAttributeEncoding : uint8_t 
    {
        dw_ate_address = 0x01,
        dw_ate_boolean = 0x02,
        dw_ate_complex_float = 0x03,
        dw_ate_float_ = 0x04,
        dw_ate_signed_ = 0x05,
        dw_ate_signed_char = 0x06,
        dw_ate_unsigned_ = 0x07,
        dw_ate_unsigned_char = 0x08,
        dw_ate_imaginary_float = 0x09,
        dw_ate_packed_decimal = 0x0a,
        dw_ate_numeric_string = 0x0b,
        dw_ate_edited = 0x0c,
        dw_ate_signed_fixed = 0x0d,
        dw_ate_unsigned_fixed = 0x0e,
        dw_ate_decimal_float = 0x0f,

        dw_ate_utf = 0x10,
        dw_ate_ucs = 0x11,
        dw_ate_ascii = 0x12,

        dw_ate_lo_user = 0x80,
        dw_ate_hi_user = 0xff
    };

    enum class DecimalSignCode : uint8_t 
    {
        dw_ds_unsigned_ = 0x01,
        dw_ds_leading_overpunch = 0x02,
        dw_ds_trailing_overpunch = 0x03,
        dw_ds_leading_separate = 0x04,
        dw_ds_trailing_separate = 0x05
    };

    enum class EndianCode : uint8_t
    {
        dw_end_dfault = 0x00,
        dw_end_big = 0x01,
        dw_end_little = 0x02,
        dw_end_lo_user = 0x40,
        dw_end_hi_user = 0xff
    };

    enum class AccessibilityCode : uint8_t
    {
        dw_access_public_ = 0x01,
        dw_access_protected_ = 0x02,
        dw_access_private_ = 0x03
    };

    enum class VisibilityCode : uint8_t
    {
        dw_vis_local = 0x01,
        dw_vis_exported = 0x02,
        dw_vis_qualified = 0x03
    };

    enum class VirtualityCode : uint8_t 
    {
        dw_virtuality_none = 0x00,
        dw_virtuality_virtual_ = 0x01,
        dw_virtuality_pure_virtual = 0x02
    };

    enum class SourceLanguage : uint16_t 
    {
        dw_lang_c89 = 0x01,
        dw_lang_c = 0x02,
        dw_lang_ada83 = 0x03,
        dw_lang_c_plus_plus = 0x04,
        dw_lang_cobol74 = 0x05,
        dw_lang_cobol85 = 0x06,
        dw_lang_fortran77 = 0x07,
        dw_lang_fortran90 = 0x08,
        dw_lang_pascal83 = 0x09,
        dw_lang_modula2 = 0x0a,
        dw_lang_java = 0x0b,
        dw_lang_c99 = 0x0c,
        dw_lang_ada95 = 0x0d,
        dw_lang_fortran95 = 0x0e,
        dw_lang_pli = 0x0f,

        dw_lang_objc = 0x10,
        dw_lang_objc_plus_plus = 0x11,
        dw_lang_upc = 0x12,
        dw_lang_d = 0x13,
        dw_lang_python = 0x14,
        dw_lang_open_cl = 0x15,
        dw_lang_go = 0x16,
        dw_lang_modula3 = 0x17,
        dw_lang_haskell = 0x18,
        dw_lang_c_plus_plus_03 = 0x19,
        dw_lang_c_plus_plus_11 = 0x1a,
        dw_lang_ocaml = 0x1b,
        dw_lang_rust = 0x1c,
        dw_lang_c11 = 0x1d,
        dw_lang_swift = 0x1e,
        dw_lang_julia = 0x1f,

        dw_lang_dylan = 0x20,
        dw_lang_c_plus_plus_14 = 0x21,
        dw_lang_fortran03 = 0x22,
        dw_lang_fortran08 = 0x23,
        dw_lang_render_script = 0x24,
        dw_lang_bliss = 0x25,

        dw_lang_lo_user = 0x8000,
        dw_lang_hi_user = 0xffff
    };

    enum class IdentifierCase : uint8_t 
    {
        dw_id_case_sensitive = 0x00,
        dw_id_up_case = 0x01,
        dw_id_down_case = 0x02,
        dw_id_case_insensitive = 0x03
    };

    enum class CallingConvention : uint8_t
    {
        dw_cc_normal = 0x01,
        dw_cc_program = 0x02,
        dw_cc_nocall = 0x03,
        dw_cc_pass_by_reference = 0x04,
        dw_cc_pass_by_value = 0x05,

        dw_cc_lo_user = 0x40,
        dw_cc_hi_user = 0xff
    };

    enum class InlineCode : uint8_t
    {
        dw_inl_not_inlined = 0x00,
        dw_inl_inlined = 0x01,
        dw_inl_declared_not_inlined = 0x02,
        dw_inl_declared_inlined = 0x03
    };

    enum class ArrayOrdering : uint8_t
    {
        dw_ord_row_major = 0x00,
        dw_ord_col_major = 0x01
    };

    enum class DiscriminantLists : uint8_t
    {
        dw_dsc_label = 0x00,
        dw_dsc_range = 0x01
    };

    enum class NameIndexTable : uint16_t
    {
        dw_idx_compile_unit = 0x01,
        dw_idx_type_unit = 0x02,
        dw_idx_die_offset = 0x03,
        dw_idx_parent = 0x04,
        dw_idx_type_hash = 0x05,

        dw_idx_lo_user = 0x2000,
        dw_idx_hi_user = 0x3fff
    };

    enum class DefaultMemberEncoding : uint8_t
    {
        dw_defaulted_no = 0x00,
        dw_defaulted_in_class = 0x01,
        dw_defaulted_out_of_class = 0x02
    };

    enum class LineNumberInformation : uint8_t
    {
        dw_lns_copy = 0x01,
        dw_lns_advance_pc = 0x02,
        dw_lns_advance_line = 0x03,
        dw_lns_set_file = 0x04,
        dw_lns_set_column = 0x05,
        dw_lns_negate_stmt = 0x06,
        dw_lns_set_basic_block = 0x07,
        dw_lns_const_add_pc = 0x08,
        dw_lns_fixed_advance_pc = 0x09,
        dw_lns_set_prologue_end = 0x0a,
        dw_lns_set_epilogue_begin = 0x0b,
        dw_lns_set_isa = 0x0c
    };

    enum class LineNumberOpcode : uint8_t
    {
        dw_lne_end_sequence = 0x01,
        dw_lne_set_address = 0x02,
        dw_lne_reserved1 = 0x03,
        dw_lne_set_discriminator = 0x04,

        dw_lne_lo_user = 0x80,
        dw_lne_hi_user = 0xff
    };

    enum class LineNumberHeaderEntryFormat : uint16_t
    {
        dw_lnct_path = 0x01,
        dw_lnct_directory_index = 0x02,
        dw_lnct_timestamp = 0x03,
        dw_lnct_size = 0x04,
        dw_lnct_md5 = 0x05,

        dw_lnct_lo_user = 0x2000,
        dw_lnct_hi_user = 0xfff
    };

    enum class MacroInformation : uint8_t
    {
        dw_macro_define = 0x01,
        dw_macro_undef = 0x02,
        dw_macro_start_file = 0x03,
        dw_macro_end_file = 0x04,
        dw_macro_define_strp = 0x05,
        dw_macro_undef_strp = 0x06,
        dw_macro_import = 0x07,
        dw_macro_define_sup = 0x08,
        dw_macro_undef_sup = 0x09,
        dw_macro_import_sup = 0x0a,
        dw_macro_define_strx = 0x0b,
        dw_macro_undef_strx = 0x0c,

        dw_macro_lo_user = 0xe0,
        dw_macro_hi_user = 0xff
    };
}


