// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodo/disable_trace.hpp>
#include <kodo/enable_trace.hpp>
#include <kodo/has_systematic_encoder.hpp>
#include <kodo/is_systematic_on.hpp>
#include <kodo/set_systematic_off.hpp>
#include <kodo/set_systematic_on.hpp>
#include <kodo/write_feedback.hpp>
#include <kodo/rlnc/sparse_full_rlnc_encoder.hpp>

#include <string>
#include <vector>

#include "coder.hpp"

namespace kodo_js
{
    template<template<class, class> class Coder, class Field, class TraceTag>
    void encoder()
    {
        typedef Coder<Field, TraceTag> encoder_type;
        coder<Coder, Field, TraceTag>("encoder")
            // .function("encode", &encode<encoder_type>)
            // .function("set_symbols", &set_symbols<encoder_type>)
            // .function("set_symbol", &set_symbol<encoder_type>)
        ;
    }
}
