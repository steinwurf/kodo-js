// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <emscripten/bind.h>

#include <string>
#include <iostream>


namespace kodo_js
{
    template<class Coder>
    uint32_t max_symbols(Coder& coder)
    {
        return coder.max_symbols();
    }

    template<template<class, class> class Coder, class Field, class TraceTag>
    void factory(const std::string& name)
    {
        using namespace emscripten;

        typedef typename Coder<Field, TraceTag>::factory factory_type;

        class_<factory_type>((name + "_factory").c_str())
            .constructor<uint32_t, uint32_t>()
            .function("max_symbols", &max_symbols<factory_type>)
            // .function("max_symbols", &factory_type::max_symbols);
            // .function("set_symbols", &factory_type::set_symbols)
            // .function("set_symbol_size", &factory_type::set_symbol_size)
            // .function("max_symbol_size", &factory_type::max_symbol_size)
            // .function("max_payload_size", &factory_type::max_payload_size)
            // .function("max_block_size", &factory_type::max_block_size)
            // .function("build", &factory_type::build)
            ;
    }
}
