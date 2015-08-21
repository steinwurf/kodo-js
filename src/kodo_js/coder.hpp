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

    template<class Coder>
    uint32_t coder_payload_size(Coder& coder)
    {
        return coder.payload_size();
    }

    template<class Coder>
    uint32_t coder_block_size(Coder& coder)
    {
        return coder.block_size();
    }

    template<class Coder>
    uint32_t coder_symbol_size(Coder& coder)
    {
        return coder.symbol_size();
    }

    template<class Coder>
    uint32_t coder_symbols(Coder& coder)
    {
        return coder.symbols();
    }

    template<class Coder>
    uint32_t coder_rank(Coder& coder)
    {
        return coder.rank();
    }

    template<class Coder>
    bool coder_is_symbol_pivot(Coder& coder, uint32_t index)
    {
        return coder.is_symbol_pivot(index);
    }

    template<class Coder>
    bool coder_has_feedback_size(Coder& coder)
    {
        return coder.has_feedback_size();
    }

    template<class Coder>
    uint32_t coder_feedback_size(Coder& coder)
    {
        return coder.feedback_size();
    }

    template<class Coder>
    uint32_t coder_write_payload(Coder& coder, const std::string& payload)
    {
        return coder.write_payload((uint8_t*)payload.c_str());
    }

    //template<class Coder<class Field>>
    template<template<class> Coder, class Field>
    auto coder(const std::string& name)
    {
        // typedef Coder<Field, TraceTag> coder_type;
        typedef Coder<Field> coder_type;

        auto coder_class = emscripten::class_<coder_type>(name.c_str())
            .template smart_ptr<std::shared_ptr<coder_type>>(name.c_str())
            .function("symbols", &coder_symbols<coder_type>)
            .function("symbol_size", &coder_symbol_size<coder_type>)
            .function("rank", &coder_rank<coder_type>)
            .function("block_size", &coder_block_size<coder_type>)
            .function("payload_size", &coder_payload_size<coder_type>)
            .function("is_symbol_pivot", &coder_is_symbol_pivot<coder_type>)
            .function("has_feedback_size", &coder_has_feedback_size<coder_type>)
            .function("write_payload", &coder_write_payload<coder_type>)
        ;

        return coder_class;
    }
}
