// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

// Load unit testing framework
var fs = require('fs')
var path = require('path')
filedata = fs.readFileSync(path.join(__dirname, 'shoulda.js'),'utf8')
eval(filedata)

kodo = module.require('kodo.js')

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

function create_factory_test(name, factory_type) {
    return context(name,
        setup(function() {
                symbols = 8
                symbol_size = 160
                factory = new factory_type(symbols, symbol_size)
        }),
        should("return the right number of symbols", function() {
            assert.equal(symbols, factory.max_symbols())
            assert.equal(symbols, factory.symbols())
            symbols2 = 4
            factory.set_symbols(symbols2)
            assert.equal(symbols2, factory.symbols())
        }),
        should("return the right symbol size", function() {
            assert.equal(symbol_size, factory.max_symbol_size())
            assert.equal(symbol_size, factory.symbol_size())
            symbol_size2 = 80
            factory.set_symbol_size(symbol_size2)
            assert.equal(symbol_size2, factory.symbol_size())
        }),
        should("return a payload size above 0", function() {
            assert.isTrue(factory.max_payload_size() > 0)
        }),
        should("return the right block size", function() {
            assert.equal(symbol_size * symbols, factory.max_block_size())
        }),
        should("create an object when calling build", function() {
            assert.equal("object", typeof factory.build())
        }))
}

function create_coder_test(name, factory_type) {
    return [
        name,
        setup(function() {
                symbols = 8
                symbol_size = 160
                factory = new factory_type(symbols, symbol_size)
                coder = factory.build()
        }),
        should("return the right number of symbols", function() {
            assert.equal(factory.symbols(), coder.symbols())
        }),

        should("return the right symbol size", function() {
            assert.equal(symbol_size, coder.symbol_size())
        }),
        should("return the right payload size", function() {
            assert.equal(coder.payload_size(), factory.max_payload_size())
        }),
        should("return the right block size", function() {
            assert.equal(symbol_size * symbols, coder.block_size())
        }),
        should("no pivot symbols before decoding/settings symbols", function() {
            for (var i = 0; i < coder.symbols(); i++) {
                assert.isFalse(coder.is_symbol_pivot(i))
            };
        })]
}

function create_decoder_test() {
    test = create_coder_test("decoder", kodo.decoder_factory)
    test.push(
        should("should not be complete initially", function() {
            assert.isFalse(coder.is_complete())
        }),
        should("no symbols should be uncoded initially", function() {
            assert.equal(0, coder.symbols_uncoded())
        }),
        should("all symbols should be uncoded initially", function() {
            for (var i = 0; i < coder.symbols(); i++) {
                assert.isFalse(coder.is_symbol_uncoded(i))
            };
        })
    )
    return context.apply(null, test)
}

// should("recode", function() {
//     coder.recode()
// }),
// should("decode", function() {
//     coder.decode()
// }),
// should("decode_symbol", function() {
//     coder.decode_symbol()
// }),
// should("copy_symbols", function() {
//     coder.copy_symbols()
// }),

function create_encoder_test() {
    test = create_coder_test("encoder", kodo.encoder_factory)
    test.push(
        should("be systematic initially", function() {
            assert.isTrue(coder.is_systematic_on())
        }),
        should("not be systematic if turning it off", function() {
            assert.isTrue(coder.is_systematic_on())
            coder.set_systematic_off()
            assert.isFalse(coder.is_systematic_on())
            coder.set_systematic_on()
            assert.isTrue(coder.is_systematic_on())
        })
    )
    return context.apply(null, test)
}

// should("encode", function() {
//     coder.encode()
// }),
// should("set_const_symbols", function() {
//     coder.set_const_symbols()
// }),
// should("set_const_symbol", function() {
//     coder.set_const_symbol()
// }),

context("kodo",
    create_factory_test('encoder_factory', kodo.encoder_factory),
    create_factory_test('decoder_factory', kodo.decoder_factory),
    create_decoder_test(),
    create_encoder_test(),
    should("work when putting it all to together", function() {
        // Set the number of symbols (i.e. the generation size in RLNC
        // terminology) and the size of a symbol in bytes
        symbols = 8
        symbol_size = 160

        // In the following we will make an encoder/decoder factory.
        // The factories are used to build actual encoders/decoders
        encoder_factory = new kodo.encoder_factory(symbols, symbol_size)
        encoder = encoder_factory.build()

        decoder_factory = new kodo.decoder_factory(symbols, symbol_size)
        decoder = decoder_factory.build()

        // Test number symbols
        assert.equal(symbols, encoder.symbols())
        assert.equal(symbols, encoder_factory.max_symbols())
        assert.equal(symbols, decoder.symbols())
        assert.equal(symbols, decoder_factory.max_symbols())

        // Test symbol size
        assert.equal(symbol_size, encoder.symbol_size())
        assert.equal(symbol_size, encoder_factory.max_symbol_size())
        assert.equal(symbol_size, decoder.symbol_size())
        assert.equal(symbol_size, decoder_factory.max_symbol_size())

        // Create some data
        data_in = random_string(encoder.block_size())

        // Assign the data buffer to the encoder so that we can
        // produce encoded symbols
        encoder.set_const_symbols(data_in)

        number_of_packets = 0
        while(!decoder.is_complete())
        {
            packet = encoder.write_payload()
            number_of_packets += 1
            decoder.read_payload(packet)

            // Make sure we don't get an infinite loop.
            assert.isTrue(number_of_packets <= symbols)
        }
        data_out = decoder.copy_from_symbols()
        assert.arrayEqual(data_in, data_out)
    })
)

Tests.run()

// Make the script return 1 if any tests failed.
if (Tests.testsFailed > 0) {
    process.exit(1)
}
