// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <emscripten/bind.h>

#include <cstdint>
#include <vector>

#include <storage/storage.hpp>

#include <kodo_core/basic_factory.hpp>
#include <kodo_rlnc/coders.hpp>

#include "decoder.hpp"
#include "encoder.hpp"
#include "factory.hpp"

namespace
{
// Shallow storage is not a viable option for Embind, because we cannot map
// a user-defined data buffer to the Emscripten heap, so we need to allocate
// internal storage during initialize (this replicates deep storage)
class encoder : public kodo_rlnc::encoder
{
public:

    using SuperCoder = kodo_rlnc::encoder;

    using config = SuperCoder::factory;
    using factory = kodo_core::basic_factory<encoder>;

public:

    template<class Factory>
    void initialize(Factory& the_factory)
    {
        SuperCoder::initialize(the_factory);

        m_symbol_storage.resize(SuperCoder::block_size());
        SuperCoder::set_const_symbols(storage::storage(m_symbol_storage));
    }

    void set_const_symbols(const storage::const_storage& source)
    {
        storage::copy(storage::storage(m_symbol_storage), source);
    }

    void set_const_symbol(uint32_t index, const storage::const_storage& source)
    {
        assert(index < SuperCoder::symbols());

        storage::mutable_storage dest_data = storage::storage(m_symbol_storage);
        uint32_t offset = index * SuperCoder::symbol_size();
        dest_data = storage::offset(dest_data, offset);

        storage::copy(dest_data, source);
    }

protected:

    // Data buffer that will be allocated on the Emscripten heap
    std::vector<uint8_t> m_symbol_storage;
};

class decoder : public kodo_rlnc::decoder
{
public:

    using SuperCoder = kodo_rlnc::decoder;

    using config = SuperCoder::factory;
    using factory = kodo_core::basic_factory<decoder>;

public:

    template<class Factory>
    void initialize(Factory& the_factory)
    {
        SuperCoder::initialize(the_factory);

        m_symbol_storage.resize(SuperCoder::block_size());
        SuperCoder::set_mutable_symbols(storage::storage(m_symbol_storage));
    }

protected:

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
