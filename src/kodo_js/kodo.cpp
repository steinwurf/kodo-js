// Copyright Steinwurf ApS 2015.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <emscripten/bind.h>

#include <kodo_core/basic_factory.hpp>
#include <kodo_core/basic_proxy_stack.hpp>
#include <kodo_core/block_decoder.hpp>
#include <kodo_core/block_encoder.hpp>
#include <kodo_core/coefficient_info.hpp>
#include <kodo_core/coefficient_offset.hpp>
#include <kodo_core/coefficient_storage_layers.hpp>
#include <kodo_core/common_decoder_layers.hpp>
#include <kodo_core/common_encoder_layers.hpp>
#include <kodo_core/deep_storage_layers.hpp>
#include <kodo_core/default_systematic_phase.hpp>
#include <kodo_core/final_layer.hpp>
#include <kodo_core/finite_field.hpp>
#include <kodo_core/nested_set_seed.hpp>
#include <kodo_core/nested_write_payload.hpp>
#include <kodo_core/partial_decoding_tracker.hpp>
#include <kodo_core/rank_symbol_decoding_status_updater.hpp>
#include <kodo_core/storage_aware_systematic_phase.hpp>
#include <kodo_core/symbol_decoding_status_updater.hpp>
#include <kodo_core/trace_layer.hpp>

#include <kodo_rlnc/detail/coding_vector_selector.hpp>
#include <kodo_rlnc/detail/payload_reader.hpp>
#include <kodo_rlnc/detail/payload_writer.hpp>
#include <kodo_rlnc/detail/recoding_stack.hpp>
#include <kodo_rlnc/detail/seed_generator.hpp>
#include <kodo_rlnc/detail/uniform_generator.hpp>

#include "decoder.hpp"
#include "encoder.hpp"
#include "factory.hpp"

namespace
{
using encoder =
    // Payload API
    kodo_core::block_encoder<
    kodo_rlnc::detail::payload_writer<
    kodo_core::default_systematic_phase<true,
    kodo_core::storage_aware_systematic_phase<
    // Symbol ID API
    kodo_rlnc::detail::coding_vector_selector<
    // Coefficient Generator API
    kodo_rlnc::detail::seed_generator<
    kodo_rlnc::detail::uniform_generator<
    // Encoder API
    kodo_core::common_encoder_layers<
    // Coefficient Storage API
    kodo_core::coefficient_offset<
    kodo_core::coefficient_info<
    // Symbol Storage API
    kodo_core::deep_storage_layers<
    // Finite Field API
    kodo_core::finite_field<
    // Trace layer
    kodo_core::trace_layer<
    // Final Layer
    kodo_core::final_layer
    >>>>>>>>>>>>>;
using encoder_factory = kodo_core::basic_factory<encoder>;

using decoder =
    // Payload API
    kodo_core::nested_write_payload<
    kodo_core::nested_set_seed<
    kodo_core::basic_proxy_stack<
    kodo_core::proxy_args<>, kodo_rlnc::detail::recoding_stack,
    kodo_core::partial_decoding_tracker<
    kodo_core::rank_symbol_decoding_status_updater<
    kodo_core::block_decoder<
    kodo_rlnc::detail::payload_reader<
    kodo_rlnc::detail::coding_vector_selector<
    // Coefficient Generator API
    kodo_rlnc::detail::uniform_generator<
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
    >>>>>>>>>>>>>>>;
using decoder_factory = kodo_core::basic_factory<decoder>;
}

EMSCRIPTEN_BINDINGS(kodo)
{
    emscripten::enum_<fifi::api::field>("field")
    .value("binary", fifi::api::field::binary)
    .value("binary4", fifi::api::field::binary4)
    .value("binary8", fifi::api::field::binary8)
    .value("binary16", fifi::api::field::binary16);

    {
        kodo_js::factory<encoder_factory>("encoder_factory");
        kodo_js::encoder<encoder>("encoder");

        kodo_js::factory<decoder_factory>("decoder_factory");
        kodo_js::decoder<decoder>("decoder");
    }
}
