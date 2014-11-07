// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodo/has_partial_decoding_tracker.hpp>
#include <kodo/is_partial_complete.hpp>
#include <kodo/write_feedback.hpp>

#include <sak/storage.hpp>

#include <algorithm>
#include <string>
#include <vector>

#include "coder.hpp"

namespace kodo_js
{
    template<template<class, class> class Coder, class Field, class TraceTag>
    void decoder()
    {
        typedef Coder<Field, TraceTag> decoder_type;

        coder<Coder, Field, TraceTag>("decoder")
            // .function("recode", &recode<decoder_type>)
            // .function("decode", &decode<decoder_type>)
            // .function("decode_symbol", &decode_symbol<decoder_type>)
            // .function("is_complete", &decoder_type::is_complete)
            // .function("symbols_uncoded", &decoder_type::symbols_uncoded)
            // .function("copy_symbols", &copy_symbols<decoder_type>)
            // .function("is_symbol_uncoded", &decoder_type::is_symbol_uncoded)
        ;
    }
}


