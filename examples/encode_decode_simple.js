// Copyright Steinwurf ApS 2018.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

var kodo = module.require('kodo.js')

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

function encode_decode_simple() {
    // Choose the finite field, the number of symbols (i.e. generation size)
    // and the symbol size in bytes
    var field = kodo.field.binary
    var symbols = 8
    var symbol_size = 160

    // In the following we will make an encoder/decoder factory.
    // The factories are used to build actual encoders/decoders
    var encoder_factory = new kodo.encoder_factory(field, symbols, symbol_size)
    var encoder = encoder_factory.build()

    var decoder_factory = new kodo.decoder_factory(field, symbols, symbol_size)
    var decoder = decoder_factory.build()

    // Create some random data
    var data_in = random_string(encoder.block_size())

    // Assign the data buffer to the encoder so that we can
    // produce encoded symbols
    encoder.set_const_symbols(data_in)

    var packet_number = 0
    while (!decoder.is_complete())
    {
        packet = encoder.write_payload()
        console.log("Packet %d encoded!", packet_number)
        decoder.read_payload(packet)
        console.log("Packet %d decoded!", packet_number)
        packet_number += 1
        console.log("Decoder rank: %d/%d", decoder.rank(), decoder.symbols())
    }
    var data_out = decoder.copy_from_symbols()
    console.log("Checking results...")
    if (data_out === data_in) {
        console.log("Data decoded correctly")
    } else {
        console.log("Unable to decode please file a bug report :)")
        process.exit(1)
    }
}

encode_decode_simple()
