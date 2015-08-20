// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

#include <emscripten/bind.h>

#include <fifi/binary.hpp>

#include <kodo/rlnc/full_vector_decoder.hpp>
#include <kodo/rlnc/full_vector_encoder.hpp>
// #include <kodo/disable_trace.hpp> -- update

#include "decoder.hpp"
#include "encoder.hpp"
#include "factory.hpp"

EMSCRIPTEN_BINDINGS(kodo)
{
    {
        using field_type = fifi::binary;
        using trace_tag = kodo::disable_trace;

        kodo_js::factory<kodo::full_rlnc_encoder, field_type, trace_tag>("encoder");
        kodo_js::encoder<kodo::full_rlnc_encoder, field_type, trace_tag>("");

        kodo_js::factory<kodo::full_rlnc_decoder, field_type, trace_tag>("decoder");
        kodo_js::decoder<kodo::full_rlnc_decoder, field_type, trace_tag>("");
    }
}
