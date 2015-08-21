// Copyright Steinwurf ApS 2015.
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

        kodo_js::factory<kodo::rlnc::full_vector_encoder, field_type>("encoder");
        kodo_js::encoder<kodo::rlnc::full_vector_encoder, field_type>("");

        kodo_js::factory<kodo::rlnc::full_vector_decoder, field_type>("decoder");
        kodo_js::decoder<kodo::rlnc::full_vector_decoder, field_type>("");
    }
}
