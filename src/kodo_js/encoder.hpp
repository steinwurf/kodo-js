// Copyigrht Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodo/is_systematic_on.hpp>
#include <kodo/set_systematic_off.hpp>
#include <kodo/set_systematic_on.hpp>
#include <kodo/write_feedback.hpp>

#include <string>
#include <vector>

#include "coder.hpp"

namespace kodo_js
{
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

    template<template<class, class> class Coder, class Field>
    void encoder(const std::string& name)
    {
        using encoder_type = Coder<Field, meta::typelist<>>;
         coder<Coder, Field>(std::string("encoder") + name)
            .function("set_symbols", &encoder_set_symbols<encoder_type>)
            .function("set_symbol", &encoder_set_symbol<encoder_type>)
            .function("is_systematic_on", &encoder_is_systematic_on<encoder_type>)
            .function("set_systematic_on", &encoder_set_systematic_on<encoder_type>)
            .function("set_systematic_off", &encoder_set_systematic_off<encoder_type>)
        ;
    }
}
