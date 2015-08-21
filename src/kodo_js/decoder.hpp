// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <kodo/has_partial_decoding_tracker.hpp>
#include <kodo/is_partial_complete.hpp>
#include <kodo/write_feedback.hpp>

#include <sak/storage.hpp>

#include <algorithm>
#include <string>
#include <vector>

#include "coder.hpp"

namespace kodo_js
{

    // template<class Decoder>
    // uint32_t decoder_recode(Decoder& decoder)
    // {
    //     std::vector<uint8_t> payload(decoder.payload_size());
    //     return decoder.recode(payload.data());
    // }

    // template<class Decoder>
    // void decoder_decode(Decoder& decoder, const std::string& payload)
    // {
    //     decoder.decode((uint8_t*)payload.c_str());
    // }

    // template<class Decoder>
    // void decoder_decode_symbol(Decoder& decoder, const std::string& symbol_data,
    //     const std::string& symbol_coefficients)
    // {
    //     decoder.decode_symbol(
    //         (uint8_t*)symbol_data.c_str(),
    //         (uint8_t*)symbol_coefficients.c_str());
    // }

    template<class Decoder>
    bool decoder_is_complete(Decoder& decoder)
    {
        return decoder.is_complete();
    }

    template<class Decoder>
    uint32_t decoder_symbols_uncoded(Decoder& decoder)
    {
        return decoder.symbols_uncoded();
    }

    template<class Decoder>
    std::string decoder_copy_symbols(Decoder& decoder)
    {
        std::vector<uint8_t> payload(decoder.block_size());
        auto storage = sak::mutable_storage(
            payload.data(), decoder.block_size());
        decoder.copy_symbols(storage);
        return std::string(payload.begin(), payload.end());
    }

    template<class Decoder>
    bool decoder_is_symbol_uncoded(Decoder& decoder, uint32_t index)
    {
        return decoder.is_symbol_uncoded(index);
    }

    template<class Decoder>
    bool decoder_has_partial_decoding_tracker(Decoder& decoder)
    {
        return decoder.has_partial_decoding_tracker();
    }

    template<class Decoder>
    bool decoder_is_partial_complete(Decoder& decoder)
    {
        return decoder.is_partial_complete();
    }

    template<class Decoder>
    void decoder_read_payload(Decoder& decoder, std::string& payload)
    {
        decoder.read((uint8_t*)payload.c_str());
    }

    template<class Decoder>
    uint32_t decoder_symbols_seen(Decoder& decoder)
    {
        return decoder.symbols_seen();
    }

    template<class Decoder>
    void decoder_write_feedback(Decoder& decoder, std::string feedback)
    {
        decoder.write_feedback((uint8_t)*feedback.c_str());
    }

    template<template<class> class Coder, class Field>
    void decoder(const std::string& name)
    {
        // typedef Coder<Field, TraceTag> decoder_type;

        // coder<Coder, Field, TraceTag>(std::string("decoder") + name)
        typedef Coder<Field> decoder_type;

        coder<Coder, Field>(std::string("decoder") + name)
            // .function("recode", &decoder_recode<decoder_type>)
            // .function("decode", &decoder_decode<decoder_type>)
            // .function("decode_symbol", &decoder_decode_symbol<decoder_type>)
            .function("is_complete", &decoder_is_complete<decoder_type>)
            .function("symbols_uncoded", &decoder_symbols_uncoded<decoder_type>)
            .function("copy_symbols", &decoder_copy_symbols<decoder_type>)
            .function("is_symbol_uncoded", &decoder_is_symbol_uncoded<decoder_type>)
            .function("read_payload", &decoder_read_payload<decoder_type>)
            .function("symbols_seen", &decoder_symbols_seen<decoder_type>)
            .function("is_partial_complete", &decoder_is_partial_complete<decoder_type>)
            .function("has_partial_decoding_tracker",
                      &decoder_has_partial_decoding_tracker<decoder_type>)
            .function("write_feedback", &decoder_write_feedback<decoder_type>)

        ;
    }
}
