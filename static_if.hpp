#ifndef GUNUNU_STATIC_IF_HPP
#define GUNUNU_STATIC_IF_HPP

/*
    STATIC_IF library for C++14 (g++ 5.1.0 or clang++ 3.6.0)
    
    copyright 2011-2015 (c) gununu
    
    Use, modification, and distribution is subject to the Boost Software License, Version 1.0. 
    (See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)


    Usage:
    Start with STATIC_IF and finish with STATIC_ENDIF.
    
    Can't use following statement in block.
    "return", "break", "continue" and "goto"
    
    
    Example:

    template <int Val>
    struct S {
        static_assert(Val < 10, "");
    };
    
    void func() {
        int a;
        const int N = 30; 
        STATIC_IF( N < 10 ) {     // (REQUIRED) if block
            S<LAZY_VALUE(N)> v;   // (REQUIRED) LAZY_VALUE or LAZY_TYPE is needed to avoid S's static_assert on clang.
            v.foobar();
            N;                    // Note: g++ 4.9.2 can't use const local variables.
        } STATIC_ELSEIF( N==10 ) { //(optional) elseif block
            
            STATIC_IF(true){      // (optional) nested if block
                cout << "foo";
            }STATIC_ENDIF   
            
        } STATIC_ELSEIF( N==20 ) { // (optional) can use elseif as many times
            
            cout << a;            // can use local variable
            
        } STATIC_ELSE {           // (optional) else block
            
        } STATIC_ENDIF            // (REQUIRED) end block
    }
*/

#include <type_traits>

namespace gununu {
    template<bool b>
    struct bool_ { static const bool value = false; };
    template<> struct bool_<true> { static const bool value = true; };

    struct caller_false {
        template <bool E, typename F> caller_false call(bool_<E>, F&&){return caller_false();}
    };
    struct caller_true {
        template <typename F> caller_false call(bool_<true>, F&& f){ f(std::true_type{}); return caller_false(); };
        template <typename F> caller_true  call(bool_<false>, F&&) { return caller_true(); }
    };

    struct avoid_user_return {};
} //namespace gununu

#define STATIC_BREAKIF   do { return gununu::avoid_user_return(); } while(0); 

#define STATIC_IF(e)     do { gununu::caller_true().call(gununu::bool_<(e)>(),  [&](auto _gununu_arg_)mutable->gununu::avoid_user_return{
#define STATIC_ELSEIF(e) STATIC_BREAKIF (void)_gununu_arg_;}).call(gununu::bool_<(e)>(),  [&](auto _gununu_arg_)mutable->gununu::avoid_user_return{
#define STATIC_ELSE      STATIC_BREAKIF (void)_gununu_arg_;}).call(gununu::bool_<true>(), [&](auto _gununu_arg_)mutable->gununu::avoid_user_return{
#define STATIC_ENDIF     STATIC_BREAKIF (void)_gununu_arg_;}); } while(0);

#define LAZY_VALUE(v)   ((_gununu_arg_ != std::false_type{}) ? v : throw 0) 
#define LAZY_TYPE(t)    typename std::conditional<_gununu_arg_ != std::false_type{}, t, void>::type

#endif //GUNUNU_STATIC_IF_HPP
