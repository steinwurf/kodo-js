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
    template<class Encoder>
    std::string encoder_encode(Encoder& encoder)
    {
        std::vector<uint8_t> payload(encoder.payload_size());
        encoder.encode(payload.data());
        return std::string(payload.begin(), payload.end());
    }

    template<class Encoder>
    void encoder_set_symbols(Encoder& encoder, const std::string& data)
    {
        auto storage = sak::const_storage(
            (uint8_t*)data.c_str(), data.length());
        encoder.set_symbols(storage);
    }

    template<class Encoder>
    void encoder_set_symbol(Encoder& encoder, uint32_t index, const std::string& data)
    {
        auto storage = sak::const_storage(
            (uint8_t*)data.c_str(), data.length());
        encoder.set_symbol(index, storage);
    }

    template<class Encoder>
    bool encoder_is_systematic_on(const Encoder& encoder)
    {
        return kodo::is_systematic_on(encoder);
    }

    template<class Encoder>
    void encoder_set_systematic_on(Encoder& encoder)
    {
        kodo::set_systematic_on(encoder);
    }

    template<class Encoder>
    void encoder_set_systematic_off(Encoder& encoder)
    {
        kodo::set_systematic_off(encoder);
    }

    template<template<class, class> class Coder, class Field, class TraceTag>
    void encoder(const std::string& name)
    {
        typedef Coder<Field, TraceTag> encoder_type;
        coder<Coder, Field, TraceTag>(std::string("encoder") + name)
            .function("encode", &encoder_encode<encoder_type>)
            .function("set_symbols", &encoder_set_symbols<encoder_type>)
            .function("set_symbol", &encoder_set_symbol<encoder_type>)
            .function("is_systematic_on", &encoder_is_systematic_on<encoder_type>)
            .function("set_systematic_on", &encoder_set_systematic_on<encoder_type>)
            .function("set_systematic_off", &encoder_set_systematic_off<encoder_type>)
        ;
    }
}
