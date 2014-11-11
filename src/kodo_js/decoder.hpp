// Copyright Steinwurf ApS 2011-2013.
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

    template<class Decoder>
    uint32_t decoder_recode(Decoder& decoder)
    {
        std::vector<uint8_t> payload(decoder.payload_size());
        return decoder.recode(payload.data());
    }

    template<class Decoder>
    void decoder_decode(Decoder& decoder, std::vector<uint8_t> payload)
    {
        decoder.decode(payload.data());
    }

    template<class Decoder>
    void decoder_decode_symbol(Decoder& decoder, const std::string& symbol_data,
        const std::string& symbol_coefficients)
    {
        std::vector<uint8_t> _symbol_data(decoder.symbol_size());
        std::vector<uint8_t> _symbol_coefficients(decoder.symbol_size());

        std::copy(
            symbol_data.c_str(),
            symbol_data.c_str() + symbol_data.length(),
            _symbol_data.data());

        std::copy(
            symbol_coefficients.c_str(),
            symbol_coefficients.c_str() + symbol_coefficients.length(),
            _symbol_coefficients.data());

        decoder.decode_symbol(_symbol_data.data(), _symbol_coefficients.data());
    }


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

    template<template<class, class> class Coder, class Field, class TraceTag>
    void decoder()
    {
        typedef Coder<Field, TraceTag> decoder_type;

        coder<Coder, Field, TraceTag>("decoder")
            .function("recode", &decoder_recode<decoder_type>)
            .function("decode", &decoder_decode<decoder_type>)
            .function("decode_symbol", &decoder_decode_symbol<decoder_type>)
            .function("is_complete", &decoder_is_complete<decoder_type>)
            .function("symbols_uncoded", &decoder_symbols_uncoded<decoder_type>)
            .function("copy_symbols", &decoder_copy_symbols<decoder_type>)
            .function("is_symbol_uncoded", &decoder_is_symbol_uncoded<decoder_type>)
        ;
    }
}


