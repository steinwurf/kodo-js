// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <emscripten/bind.h>

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
void decoder_read_payload(Decoder& decoder, const emscripten::val& arr)
{
    // Embind does not provide an efficient solution to pass a TypedArray
    // to C++ without copying, but this can change in future versions:
    // https://github.com/kripken/emscripten/issues/5519
    // The implementation below is inspired by this blog post:
    // https://sean.voisen.org/blog/2018/03/rendering-images-emscripten-wasm/

    using namespace emscripten;

    // Fetc the length of the input Uint8Array that is not allocated on the
    // Emscripten heap
    unsigned int length = arr["length"].as<unsigned int>();
    // Creating a vector will allocate space on the Emscripten heap
    std::vector<uint8_t> payload(length);
    val memory = val::module_property("buffer");
    // Create a new typed array that is a "view" onto the vector's memory
    val memoryView = val::global("Uint8Array").new_(
        memory, reinterpret_cast<uintptr_t>(payload.data()), length);
    // Copy the input Uint8Array onto the Emscripten heap using "set"
    memoryView.call<void>("set", arr);

    decoder.read_payload(payload.data());
}

template<class Decoder>
std::string decoder_copy_from_symbols(Decoder& decoder)
{
    return std::string(decoder.m_symbol_storage.begin(),
                       decoder.m_symbol_storage.end());
}

template<class Decoder>
uint32_t decoder_symbols_missing(Decoder& decoder)
{
    return decoder.symbols_missing();
}

template<class Decoder>
uint32_t decoder_symbols_uncoded(Decoder& decoder)
{
    return decoder.symbols_uncoded();
}

template<class Decoder>
uint32_t decoder_symbols_partially_decoded(Decoder& decoder)
{
    return decoder.symbols_partially_decoded();
}

template<class Decoder>
bool decoder_is_symbol_missing(Decoder& decoder, uint32_t index)
{
    return decoder.is_symbol_missing(index);
}

template<class Decoder>
bool decoder_is_symbol_uncoded(Decoder& decoder, uint32_t index)
{
    return decoder.is_symbol_uncoded(index);
}

template<class Decoder>
bool decoder_is_symbol_partially_decoded(Decoder& decoder, uint32_t index)
{
    return decoder.is_symbol_partially_decoded(index);
}

template<class Coder>
void decoder(const std::string& name)
{
    coder<Coder>(name)
    .function("is_complete", &decoder_is_complete<Coder>)
    .function("read_payload", &decoder_read_payload<Coder>)
    .function("copy_from_symbols", &decoder_copy_from_symbols<Coder>)
    .function("symbols_missing", &decoder_symbols_missing<Coder>)
    .function("symbols_uncoded", &decoder_symbols_uncoded<Coder>)
    .function("symbols_partially_decoded",
              &decoder_symbols_partially_decoded<Coder>)
    .function("is_symbol_missing", &decoder_is_symbol_missing<Coder>)
    .function("is_symbol_uncoded", &decoder_is_symbol_uncoded<Coder>)
    .function("is_symbol_partially_decoded",
              &decoder_is_symbol_partially_decoded<Coder>)
    ;
}
}
