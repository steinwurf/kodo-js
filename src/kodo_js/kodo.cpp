// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <emscripten/bind.h>

#include <kodo_core/basic_factory.hpp>
#include <kodo_core/basic_proxy_stack.hpp>
#include <kodo_core/block_decoder.hpp>
#include <kodo_core/block_encoder.hpp>
#include <kodo_core/coefficient_info.hpp>
#include <kodo_core/coefficient_storage.hpp>
#include <kodo_core/coefficient_storage_layers.hpp>
#include <kodo_core/coefficient_value_access.hpp>
#include <kodo_core/common_encoder_layers.hpp>
#include <kodo_core/deep_storage_layers.hpp>
#include <kodo_core/default_on_systematic_encoder.hpp>
#include <kodo_core/final_layer.hpp>
#include <kodo_core/finite_field.hpp>
#include <kodo_core/linear_block_encoder.hpp>
#include <kodo_core/nested_set_seed.hpp>
#include <kodo_core/nested_write_payload.hpp>
#include <kodo_core/payload_info.hpp>
#include <kodo_core/plain_symbol_id_reader.hpp>
#include <kodo_core/plain_symbol_id_reader_layers.hpp>
#include <kodo_core/plain_symbol_id_size.hpp>
#include <kodo_core/plain_symbol_id_writer.hpp>
#include <kodo_core/plain_symbol_id_writer_layers.hpp>
#include <kodo_core/storage_aware_encoder.hpp>
#include <kodo_core/symbol_decoding_status_updater.hpp>
#include <kodo_core/symbol_id_decoder.hpp>
#include <kodo_core/symbol_id_encoder.hpp>
#include <kodo_core/systematic_decoder_layers.hpp>
#include <kodo_core/trace_layer.hpp>
#include <kodo_core/uniform_generator_layers.hpp>
#include <kodo_core/write_symbol_tracker.hpp>
#include <kodo_core/zero_symbol_encoder.hpp>
#include <kodo_rlnc/full_vector_recoding_stack.hpp>
#include <kodo_core/common_decoder_layers.hpp>

#include "decoder.hpp"
#include "encoder.hpp"
#include "factory.hpp"

namespace
{
using encoder =
    // Payload Codec API
    kodo_core::payload_info<
    // Block Coder API
    kodo_core::block_encoder<
    // Codec Header API
    kodo_core::default_on_systematic_encoder<
    kodo_core::symbol_id_encoder<
    // Symbol ID API
    kodo_core::plain_symbol_id_writer_layers<
    // Coefficient Generator API
    kodo_core::uniform_generator_layers<
    // Codec API
    kodo_core::common_encoder_layers<
    // Coefficient Storage API
    kodo_core::coefficient_value_access<
    kodo_core::coefficient_info<
    // Symbol Storage API
    kodo_core::deep_storage_layers<
    // Finite Field API
    kodo_core::finite_field<
    // Trace layer
    kodo_core::trace_layer<
    // Final Layer
    kodo_core::final_layer
    >>>>>>>>>>>>;
using encoder_factory = kodo_core::basic_factory<encoder>;

using decoder =
    kodo_core::nested_write_payload<
    kodo_core::nested_set_seed<
    kodo_core::basic_proxy_stack<
    kodo_core::proxy_args<>, kodo_rlnc::full_vector_recoding_stack,
    kodo_core::payload_info<
    // Block Coder API
    kodo_core::block_decoder<
    // Codec Header API
    kodo_core::systematic_decoder_layers<
    kodo_core::symbol_id_decoder<
    // Symbol ID API
    kodo_core::plain_symbol_id_reader_layers<
    // Decoder API
    kodo_core::symbol_decoding_status_updater<
    kodo_core::common_decoder_layers<
    // Coefficient Storage API
    kodo_core::coefficient_storage_layers<
    // Storage API
    kodo_core::deep_storage_layers<
    // Finite Field API
    kodo_core::finite_field<
    // Trace Layer
    kodo_core::trace_layer<
    // Final Layer
    kodo_core::final_layer
    >>>>>>>>>>>>>>;
using decoder_factory = kodo_core::basic_factory<decoder>;
}

EMSCRIPTEN_BINDINGS(kodo)
{
    emscripten::enum_<fifi::api::field>("field")
        .value("binary", fifi::api::field::binary)
        .value("binary4", fifi::api::field::binary4)
        .value("binary8", fifi::api::field::binary8)
        .value("binary16", fifi::api::field::binary16)
        .value("prime2325", fifi::api::field::prime2325)
        ;
    {
        kodo_js::factory<encoder_factory>("encoder");
        kodo_js::encoder<encoder>("");

        kodo_js::factory<decoder_factory>("decoder");
        kodo_js::decoder<decoder>("");
    }
}
