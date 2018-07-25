// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#pragma once

#include <emscripten/bind.h>

#include <cstdint>
#include <string>
#include <vector>

namespace kodo_js
{
template<class Coder>
emscripten::val coder_write_payload(Coder& coder)
{
    using namespace emscripten;

    std::vector<uint8_t> payload(coder.payload_size());
    uint32_t length = coder.write_payload(payload.data());

    val user_array = val::global("Uint8Array").new_(length);
    val heap = val::module_property("buffer");
    val payload_view = val::global("Uint8Array").new_(
        heap, reinterpret_cast<uintptr_t>(payload.data()), length);
    user_array.call<void>("set", payload_view);

    return user_array;
}

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
uint32_t coder_feedback_size(Coder& coder)
{
    return coder.feedback_size();
}

template<class Coder>
auto coder(const std::string& name) -> emscripten::class_<Coder>
{
    using namespace emscripten;

    auto coder_class =
        class_<Coder>(name.c_str())
        .template smart_ptr<std::shared_ptr<Coder>>(name.c_str())
        .function("write_payload",
                 &coder_write_payload<Coder>, allow_raw_pointers())
        .function("symbols", &coder_symbols<Coder>)
        .function("symbol_size", &coder_symbol_size<Coder>)
        .function("rank", &coder_rank<Coder>)
        .function("block_size", &coder_block_size<Coder>)
        .function("payload_size", &coder_payload_size<Coder>)
        ;

    return coder_class;
}
}
