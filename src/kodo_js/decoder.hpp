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
    std::string decoder_copy_from_symbols(Decoder& decoder)
    {
        std::vector<uint8_t> payload(decoder.block_size());
        auto storage = sak::mutable_storage(
            payload.data(), decoder.block_size());
        decoder.copy_from_symbols(storage);
        return std::string(payload.begin(), payload.end());
    }

    template<class Decoder>
    bool decoder_is_symbol_uncoded(Decoder& decoder, uint32_t index)
    {
        return decoder.is_symbol_uncoded(index);
    }

    template<class Decoder>
    void decoder_read_payload(Decoder& decoder, const std::string payload)
    {
        decoder.read_payload((uint8_t*) payload.c_str());
    }

    template<class Decoder>
    uint32_t decoder_symbols_seen(Decoder& decoder)
    {
        return decoder.symbols_seen();
    }

    template<template<class, class> class Coder, class Field>
    void decoder(const std::string& name)
    {
        using decoder_type = Coder<Field, meta::typelist<>>;

        coder<Coder, Field>(std::string("decoder") + name)
            .function("is_complete", &decoder_is_complete<decoder_type>)
            .function("symbols_uncoded", &decoder_symbols_uncoded<decoder_type>)
            .function("copy_from_symbols", &decoder_copy_from_symbols<decoder_type>)
            .function("is_symbol_uncoded", &decoder_is_symbol_uncoded<decoder_type>)
            .function("read_payload", &decoder_read_payload<decoder_type>)
            .function("symbols_seen", &decoder_symbols_seen<decoder_type>)
        ;
    }
}
