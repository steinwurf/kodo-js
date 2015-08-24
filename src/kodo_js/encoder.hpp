// Copyigrht Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodo/has_set_systematic_off.hpp>
#include <kodo/has_set_systematic_on.hpp>
#include <kodo/is_systematic_on.hpp>
#include <kodo/set_systematic_off.hpp>
#include <kodo/set_systematic_on.hpp>
#include <kodo/write_feedback.hpp>
#include <kodo/rlnc/sparse_full_vector_encoder.hpp>

#include <string>
#include <vector>

#include "coder.hpp"

namespace kodo_js
{
    template<class Encoder>
    std::string encoder_write_payload(Encoder& encoder)
    {
        std::vector<uint8_t> payload(encoder.payload_size());
        encoder.write_payload(payload.data());
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

    template<class Encoder>
    bool encoder_has_set_systematic_off(Encoder& encoder)
    {
        (void) encoder;
        return kodo::has_set_systematic_off<Encoder>::value;
    }

    template<template<class, class> class Coder, class Field>
    void encoder(const std::string& name)
    {
        typedef Coder<Field, meta::typelist<>> encoder_type;
         coder<Coder, Field>(std::string("encoder") + name)
            .function("encode", &encoder_write_payload<encoder_type>)
            .function("set_symbols", &encoder_set_symbols<encoder_type>)
            .function("set_symbol", &encoder_set_symbol<encoder_type>)
            .function("is_systematic_on", &encoder_is_systematic_on<encoder_type>)
            .function("set_systematic_on", &encoder_set_systematic_on<encoder_type>)
            .function("set_systematic_off", &encoder_set_systematic_off<encoder_type>)
            .function("has_set_systematic_off", &encoder_has_set_systematic_off<encoder_type>)
        ;
    }
}
