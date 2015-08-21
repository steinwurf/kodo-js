// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <emscripten/bind.h>

#include <string>
#include <iostream>


namespace kodo_js
{

    template<class Factory>
    void factory_set_symbols(Factory& factory, uint32_t symbol_size)
    {
        factory.set_symbols(symbol_size);
    }

    template<class Factory>
    uint32_t factory_symbols(Factory& factory)
    {
        return factory.symbols();
    }

    template<class Factory>
    uint32_t factory_max_symbols(Factory& factory)
    {
        return factory.max_symbols();
    }

    template<class Factory>
    void factory_set_symbol_size(Factory& factory, uint32_t symbol_size)
    {
        factory.set_symbol_size(symbol_size);
    }

    template<class Factory>
    uint32_t factory_symbol_size(Factory& factory)
    {
        return factory.symbol_size();
    }

    template<class Factory>
    uint32_t factory_max_symbol_size(Factory& factory)
    {
        return factory.max_symbol_size();
    }

    template<class Factory>
    uint32_t factory_max_payload_size(Factory& factory)
    {
        return factory.max_payload_size();
    }

    template<class Factory>
    uint32_t factory_max_block_size(Factory& factory)
    {
        return factory.max_block_size();
    }

    template<class Factory>
    typename Factory::pointer factory_build(Factory& factory)
    {
        return factory.build();
    }

    template<template<class> class Coder, class Field>
    void factory(const std::string& name)
    {
        using namespace emscripten;

        typedef typename Coder<Field>::factory factory_type;

        class_<factory_type>((name + "_factory").c_str())
            .constructor<uint32_t, uint32_t>()
            .function("set_symbols", &factory_set_symbols<factory_type>)
            .function("symbols", &factory_symbols<factory_type>)
            .function("max_symbols", &factory_max_symbols<factory_type>)

            .function("set_symbol_size", &factory_set_symbol_size<factory_type>)
            .function("symbol_size", &factory_symbol_size<factory_type>)
            .function("max_symbol_size", &factory_max_symbol_size<factory_type>)
            .function("max_payload_size", &factory_max_payload_size<factory_type>)
            .function("max_block_size", &factory_max_block_size<factory_type>)
            .function("build", &factory_build<factory_type>)
            ;
    }
}
