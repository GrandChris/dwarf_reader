///
/// @file:   ut.cpp
/// @author: GrandChris
/// @date:   2021-12-31
///

#pragma once

#include "scenario.hpp"
#include "given.hpp"
#include "when.hpp"
#include "then.hpp"
#include "source_location.hpp"
#include "color.hpp"

#include <iostream>

namespace ut {

/// <!-- description -->
///   @brief Immediately the application with a failure
///
[[noreturn]] constexpr void
stdlib_fast_fail() noexcept         
{                                   
    ::exit(EXIT_FAILURE);    
}                                 

/// <!-- description -->
///   @brief This is a non-constexpr function that can be used to detect
///     when a unit test check fails. If this function is called at
///     compile-time, it will not compile, resulting in a human readable
///     error message.
///
inline void
ut_check_failed() noexcept
{}

[[maybe_unused]] constexpr auto
check(bool const test, source_location const &sloc = here()) noexcept -> bool
{
    if (!test) [[unlikely]] 
    {                               
        ut::details::line_type const l{sloc.line()};   
        char const * const f{sloc.file_name()};       
        char const * const m{ut::mag.data()};        
        char const * const y{ut::ylw.data()};        
        char const * const c{ut::cyn.data()};        
        char const * const r{ut::rst.data()};      

        ut_check_failed();    

        fprintf(stderr, "%s[CHECK FAILED]%s\n", m, r);                 
        fprintf(stderr, "  --> %s%s%s:%s%d%s\n", y, f, r, c, l, r);    

        stdlib_fast_fail();    
    }

    return test;
}


template<typename T1, typename T2>
[[maybe_unused]] constexpr auto
assert_eq(T1 const & a, T2 const & b, source_location const &sloc = here()) noexcept -> bool
{
    bool const test = a == b;
    if (!test) [[unlikely]] 
    {                               
        ut::details::line_type const l{sloc.line()};   
        char const * const f{sloc.file_name()};       
        char const * const m{ut::mag.data()};        
        char const * const y{ut::ylw.data()};        
        char const * const c{ut::cyn.data()};        
        char const * const r{ut::rst.data()};      

        ut_check_failed();        

        fprintf(stderr, "%s[CHECK FAILED]%s\n", m, r);                 
        fprintf(stderr, "  --> %s%s%s:%s%d%s\n", y, f, r, c, l, r);    
        std::cerr <<    "      " << a << " != " << b << std::endl;

        stdlib_fast_fail();    
    }

    return test;
}

};

