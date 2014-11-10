// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <emscripten/bind.h>
#include <kodo/enable_trace.hpp>

#include <iostream>

namespace kodo_js
{
    template<template<class, class> class Coder, class Field, class TraceTag>
    auto coder(const std::string& name) ->
        emscripten::class_<Coder<Field, TraceTag>>
    {
        typedef Coder<Field, TraceTag> coder_type;

        auto coder_class = emscripten::class_<coder_type>(name.c_str())
            // .function("payload_size", &coder_type::payload_size)
            // .function("block_size", &coder_type::block_size)
            // .function("symbol_size", &coder_type::symbol_size)
            // .function("symbols", &coder_type::symbols)
            // .function("rank", &coder_type::rank)
            // .function("is_symbol_pivot", &coder_type::is_symbol_pivot)
        ;

        return coder_class;
    }
}
