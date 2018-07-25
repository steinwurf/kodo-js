// Copyigrht Steinwurf ApS 2015.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <emscripten/bind.h>

#include <string>

#include <storage/storage.hpp>

#include "coder.hpp"

namespace kodo_js
{
template<class Encoder>
void encoder_set_const_symbols(Encoder& encoder, const std::string& data)
{
    auto source =
        storage::const_storage((uint8_t*)data.c_str(), data.length());

    // Copy the temporary string data to the permanent storage
    storage::copy(storage::storage(encoder.m_symbol_storage), source);
}

template<class Encoder>
void encoder_set_const_symbol(Encoder& encoder, uint32_t index,
                              const std::string& data)
{
    auto source =
        storage::const_storage((uint8_t*)data.c_str(), data.length());

    uint32_t size = encoder.symbol_size();
    uint32_t offset = index * size;

    auto symbol =
        storage::storage(encoder.m_symbol_storage.data() + offset, size);

    // Copy the temporary string data to the permanent storage
    storage::copy(symbol, source);
}

template<class Encoder>
bool encoder_is_systematic_on(const Encoder& encoder)
{
    return encoder.is_systematic_on();
}

template<class Encoder>
void encoder_set_systematic_on(Encoder& encoder)
{
    encoder.set_systematic_on();
}

template<class Encoder>
void encoder_set_systematic_off(Encoder& encoder)
{
    encoder.set_systematic_off();
}

template<class Coder>
void encoder(const std::string& name)
{
    coder<Coder>(name)
    .function("set_const_symbols", &encoder_set_const_symbols<Coder>)
    .function("set_const_symbol", &encoder_set_const_symbol<Coder>)
    .function("is_systematic_on", &encoder_is_systematic_on<Coder>)
    .function("set_systematic_on", &encoder_set_systematic_on<Coder>)
    .function("set_systematic_off", &encoder_set_systematic_off<Coder>)
    ;
}
}
