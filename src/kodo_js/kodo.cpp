// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <emscripten/bind.h>

#include <cstdint>
#include <vector>

#include <kodo_core/basic_factory.hpp>
#include <kodo_rlnc/coders.hpp>

#include "decoder.hpp"
#include "encoder.hpp"
#include "factory.hpp"

namespace
{
struct encoder : public kodo_rlnc::encoder
{
    using SuperCoder = kodo_rlnc::encoder;

    using config = SuperCoder::factory;
    using factory = kodo_core::basic_factory<encoder>;

    template<class Factory>
    void initialize(Factory& the_factory)
    {
        SuperCoder::initialize(the_factory);

        m_symbol_storage.resize(SuperCoder::block_size());
        SuperCoder::set_const_symbols(storage::storage(m_symbol_storage));
    }

    // Data buffer that will be allocated on the Emscripten heap
    std::vector<uint8_t> m_symbol_storage;
};

struct decoder : public kodo_rlnc::decoder
{
    using SuperCoder = kodo_rlnc::decoder;

    using config = SuperCoder::factory;
    using factory = kodo_core::basic_factory<decoder>;

    template<class Factory>
    void initialize(Factory& the_factory)
    {
        SuperCoder::initialize(the_factory);

        m_symbol_storage.resize(SuperCoder::block_size());
        SuperCoder::set_mutable_symbols(storage::storage(m_symbol_storage));
    }

    // Data buffer that will be allocated on the Emscripten heap
    std::vector<uint8_t> m_symbol_storage;
};

}

EMSCRIPTEN_BINDINGS(kodo)
{
    emscripten::enum_<fifi::api::field>("field")
    .value("binary", fifi::api::field::binary)
    .value("binary4", fifi::api::field::binary4)
    .value("binary8", fifi::api::field::binary8)
    .value("binary16", fifi::api::field::binary16);

    {
        kodo_js::factory<encoder::factory>("encoder_factory");
        kodo_js::encoder<encoder>("encoder");

        kodo_js::factory<decoder::factory>("decoder_factory");
        kodo_js::decoder<decoder>("decoder");
    }
}
