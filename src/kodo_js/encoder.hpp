// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

// #include <kodo/disable_trace.hpp> -- update
// #include <kodo/enable_trace.hpp> -- update
//#include <kodo/has_systematic_encoder.hpp>
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
    // template<class Encoder>
    // std::string encoder_encode(Encoder& encoder)
    // {
    //     std::vector<uint8_t> payload(encoder.payload_size());
    //     encoder.encode(payload.data());
    //     return std::string(payload.begin(), payload.end());
    // }

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
        return kodo::is_systematic_on(*encoder);
    }

    template<class Encoder>
    void encoder_set_systematic_on(Encoder& encoder)
    {
        kodo::set_systematic_on(*encoder);
    }

    template<class Encoder>
    void encoder_set_systematic_off(Encoder& encoder)
    {
        kodo::set_systematic_off(*encoder);
    }

    template<class Encoder>
    //    bool encoder_has_set_systematic_off(Encoder& encoder)
    bool encoder_has_set_systematic_off()
    {
//        kodo::has_set_systematic_off(*encoder);
        return kodo::has_set_systematic_off<Encoder>::value;
    }

    template<class Encoder>
    uint32_t encoder_width(Encoder& encoder)
    {
        return encoder.width();
    }

    template<class Encoder>
    void encoder_set_width(Encoder& encoder, uint32_t width)
    {
        encoder.set_width(width);
    }

    template<class Encoder>
    uint32_t encoder_width_raito(Encoder& encoder)
    {
        return encoder.width_raito();
    }

    template<class Encoder>
    void encoder_set_width_raito(Encoder& encoder, uint32_t width_raito)
    {
        encoder.set_width_raito(width_raito);
    }

    template<class Encoder>
    void encoder_read_feedback(Encoder& encoder, std::string feedback)
    {
        encoder.read_feedback((uint8_t*) feedback.c_str());
    }

    template<class Encoder>
    uint8_t encoder_pseudo_systematic(Encoder& encoder)
    {
        return encoder.pseudo_systematic();
    }

    template<class Encoder>
    void encoder_set_pseudo_systematic(Encoder& encoder, bool pseudo_systematic)
    {
        encoder.set_pseudo_systematic(pseudo_systematic);
    }

    template<class Encoder>
    uint8_t encoder_pre_charging(Encoder& encoder)
    {
        return encoder.pre_charging();
    }

    template<class Encoder>
    void encoder_set_pre_charging(Encoder& encoder, bool pre_charging)
    {
        encoder.set_pre_charging(pre_charging);
    }


    template<template<class> class Field>
    void encoder(const std::string& name)
    {
        // typedef Coder<Field, TraceTag> encoder_type;
        // coder<Coder, Field, TraceTag>(std::string("encoder") + name)
         typedef Coder<Field> encoder_type;
         coder<Coder, Field>(std::string("encoder") + name)
            // .function("encode", &encoder_encode<encoder_type>)
            .function("set_symbols", &encoder_set_symbols<encoder_type>)
            .function("set_symbol", &encoder_set_symbol<encoder_type>)
            .function("is_systematic_on", &encoder_is_systematic_on<encoder_type>)
            .function("set_systematic_on", &encoder_set_systematic_on<encoder_type>)
            .function("set_systematic_off", &encoder_set_systematic_off<encoder_type>)
            .function("has_set_systematic_off", &encoder_has_set_systematic_off<encoder_type>)
            .function("width", &encoder_width<encoder_type>)
            .function("set_width", &encoder_set_width<encoder_type>)
            .function("width_raito", &encoder_width_raito<encoder_type>)
            .function("set_width_raito", &encoder_set_width_raito<encoder_type>)
            .function("read_feedback", &encoder_read_feedback<encoder_type>)
            .function("pseudo_systematic", &encoder_pseudo_systematic<encoder_type>)
            .function("set_pseudo_systematic", &encoder_set_pseudo_systematic<encoder_type>)
            .function("pre_charging", &encoder_pre_charging<encoder_type>)
            .function("set_pre_charging", &encoder_set_pre_charging<encoder_type>)
        ;
    }
}
