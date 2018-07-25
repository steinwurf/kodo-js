// Copyright Steinwurf ApS 2018.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

var kodo = module.require('kodo.js')

// Helper functions
function random_string(length) {
    var s = ""

    var random_char=function() {
        var n = Math.floor(Math.random() * 62)
        if(n < 10) return n //1-10
        if(n < 36) return String.fromCharCode(n + 55) //A-Z
        return String.fromCharCode(n + 61) //a-z
    }

    while(s.length < length) s += random_char()
    return s
}

// Use high-resolution clock in node.js
function clock(start) {
    if ( !start ) return process.hrtime()
    var end = process.hrtime(start)
    // hrtime returns real time in a [seconds, nanoseconds] array
    // convert this to microseconds
    return end[0] * 1000000.0 + end[1] / 1000.0
}

function run_coding_test(field, symbols, symbol_size) {

    var start_setup = clock()

    var encoder_factory = new kodo.encoder_factory(field, symbols, symbol_size)
    var encoder = encoder_factory.build()

    var decoder_factory = new kodo.decoder_factory(field, symbols, symbol_size)
    var decoder = decoder_factory.build()

    var setup_time = clock(start_setup)

    // Create some random data
    var data_in = random_string(encoder.block_size())

    // Assign the data buffer to the encoder so that we can
    // produce encoded symbols
    encoder.set_const_symbols(data_in)

    // We measure pure coding, so we always turn off the systematic mode
    encoder.set_systematic_off()

    var payloads = []
    var payload_count = 2 * symbols

    var start_encoding = clock()

    for (var i = 0; i < payload_count; i++) {
        var payload = encoder.write_payload()
        payloads.push(payload)
    }

    var encoding_time = clock(start_encoding)

    // Calculate the encoding rate in megabytes / seconds
    var encoded_bytes = payload_count * symbol_size
    var encoding_rate = encoded_bytes / encoding_time

    console.log(payloads[0].constructor.name)
    var start_decoding = clock()

    for (var i = 0; i < payload_count; i++) {
        if (decoder.is_complete())
            break
        decoder.read_payload(payloads[i])
    }

    var decoding_time = clock(start_decoding)

    var data_out = decoder.copy_from_symbols()

    // Calculate the decoding rate in megabytes / seconds
    var decoded_bytes = symbols * symbol_size
    var decoding_rate = decoded_bytes / decoding_time

    console.log("Setup time: %d microsec", setup_time.toFixed(2))
    console.log("Encoding time: %d microsec", encoding_time.toFixed(2))
    console.log("Decoding time: %d microsec", decoding_time.toFixed(2))
    console.log("Encoding rate: %d MB/s", encoding_rate.toFixed(6))
    console.log("Decoding rate: %d MB/s", decoding_rate.toFixed(6))

    if (data_out === data_in) {
        console.log("Data decoded correctly.")
    } else {
        console.log("Decoding failed!")
        process.exit(1)
    }
}

console.log('Usage: benchmark.js [field] [symbols] [symbol_size]')
var args = process.argv.slice(2)
console.log('Current arguments:', args)

var field_name = args[0] || "binary"

if (field_name in kodo.field) {
    var field = kodo.field[field_name]
} else {
    console.log("Invalid field argument:", field_name)
    field_name = "binary"
    var field = kodo.field.binary
}

var symbols = Number(args[1]) || 16
var symbol_size = Number(args[2]) || 1600

console.log("Selected benchmark parameters:")
console.log("  Field:", field_name)
console.log("  Symbols:", symbols)
console.log("  Symbol size:", symbol_size)

run_coding_test(field, symbols, symbol_size)
