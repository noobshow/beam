
// Copyright (c) 2010-2018 niXman (i dot nixman dog gmail dot com). All
// rights reserved.
//
// This file is part of YAS(https://github.com/niXman/yas) project.
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)
//
//
//
// Boost Software License - Version 1.0 - August 17th, 2003
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
//
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.

#ifndef __yas__detail__tools__variant_element_switch_hpp
#define __yas__detail__tools__variant_element_switch_hpp

#include <yas/detail/type_traits/type_traits.hpp>
#include <yas/detail/preprocessor/preprocessor.hpp>

#include <boost/mpl/at.hpp>

namespace yas {
namespace detail {

/***************************************************************************/

#define __YAS_GENERATE_VARIANT_SWITCH_CB(unused, i, n) \
    case i: { \
        using elem_t = typename boost::mpl::at_c< \
             typename boost::variant<YAS_PP_ENUM_PARAMS(n, T)>::types \
            ,i \
        >::type; \
        \
        __YAS_CONSTEXPR_IF ( yas::is_writable_archive<Archive>::value ) { \
            elem_t &elem = boost::get<elem_t>(v); \
            __YAS_CONSTEXPR_IF ( F & yas::json ) { \
                ar & YAS_OBJECT(nullptr, elem); \
            } else { \
                ar & elem; \
            } \
        } else { \
            elem_t elem = elem_t(); \
            __YAS_CONSTEXPR_IF ( F & yas::json ) { \
                ar & YAS_OBJECT(nullptr, elem); \
            } else { \
                ar & elem; \
            } \
            \
            v = std::move(elem); \
        } \
        \
        return; \
    };

#define __YAS_GENERATE_VARIANT_SWITCH(n) \
    template<std::size_t F, typename Archive, YAS_PP_ENUM_PARAMS(n, typename T)> \
    void variant_switch(Archive &ar, std::size_t idx, boost::variant<YAS_PP_ENUM_PARAMS(n, T)> &v) { \
        switch ( idx ) { \
            YAS_PP_REPEAT( \
                 n \
                ,__YAS_GENERATE_VARIANT_SWITCH_CB \
                ,n \
            ) \
            default: return; \
        } \
    }

__YAS_GENERATE_VARIANT_SWITCH(1 )
__YAS_GENERATE_VARIANT_SWITCH(2 )
__YAS_GENERATE_VARIANT_SWITCH(3 )
__YAS_GENERATE_VARIANT_SWITCH(4 )
__YAS_GENERATE_VARIANT_SWITCH(5 )
__YAS_GENERATE_VARIANT_SWITCH(6 )
__YAS_GENERATE_VARIANT_SWITCH(7 )
__YAS_GENERATE_VARIANT_SWITCH(8 )
__YAS_GENERATE_VARIANT_SWITCH(9 )
__YAS_GENERATE_VARIANT_SWITCH(10)

#undef __YAS_GENERATE_VARIANT_SWITCH_CB
#undef __YAS_GENERATE_VARIANT_SWITCH

/***************************************************************************/

} // ns detail
} // ns yas

#endif // __yas__detail__tools__variant_element_switch_hpp
