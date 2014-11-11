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
    uint32_t factory_max_symbols(Coder& coder)
    {
        return coder.max_symbols();
    }

    template<class Coder>
    void factory_set_symbols(Coder& coder, uint32_t symbol_size)
    {
        coder.set_symbol_size(symbol_size);
    }

    template<class Coder>
    void factory_set_symbol_size(Coder& coder, uint32_t symbol_size)
    {
        coder.set_symbol_size(symbol_size);
    }

    template<class Coder>
    uint32_t factory_max_symbol_size(Coder& coder)
    {
        return coder.max_symbol_size();
    }

    template<class Coder>
    uint32_t factory_max_payload_size(Coder& coder)
    {
        return coder.max_payload_size();
    }

    template<class Coder>
    uint32_t factory_max_block_size(Coder& coder)
    {
        return coder.max_block_size();
    }

    template<class Coder>
    typename Coder::pointer factory_build(Coder& coder)
    {
        return coder.build();
    }

    template<template<class, class> class Coder, class Field, class TraceTag>
    void factory(const std::string& name)
    {
        using namespace emscripten;

        typedef typename Coder<Field, TraceTag>::factory factory_type;

        class_<factory_type>((name + "_factory").c_str())
            .constructor<uint32_t, uint32_t>()
            .function("max_symbols", &factory_max_symbols<factory_type>)
            .function("set_symbols", &factory_set_symbols<factory_type>)
            .function("set_symbol_size", &factory_set_symbol_size<factory_type>)
            .function("max_symbol_size", &factory_max_symbol_size<factory_type>)
            .function("max_payload_size", &factory_max_payload_size<factory_type>)
            .function("max_block_size", &factory_max_block_size<factory_type>)
            .function("build", &factory_build<factory_type>)
            ;
    }
}
