// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF EVALUATION LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

// Load unit testing framework
module.require('./shoulda.js')

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

function create_factory_test(name, factory_type, field) {
    return context(name,
        setup(function() {
                symbols = 8
                symbol_size = 160
                factory = new factory_type(field, symbols, symbol_size)
        }),
        should("return the correct number of symbols", function() {
            assert.equal(symbols, factory.symbols())
            symbols2 = 4
            factory.set_symbols(symbols2)
            assert.equal(symbols2, factory.symbols())
        }),
        should("return the correct symbol size", function() {
            assert.equal(symbol_size, factory.symbol_size())
            symbol_size2 = 80
            factory.set_symbol_size(symbol_size2)
            assert.equal(symbol_size2, factory.symbol_size())
        }),
        should("create an object when calling build", function() {
            assert.equal("object", typeof factory.build())
        }))
}

function create_coder_test(name, factory_type, field) {
    return [
        name,
        setup(function() {
                symbols = 8
                symbol_size = 160
                factory = new factory_type(field, symbols, symbol_size)
                coder = factory.build()
        }),
        should("return the correct number of symbols", function() {
            assert.equal(factory.symbols(), coder.symbols())
        }),

        should("return the correct symbol size", function() {
            assert.equal(symbol_size, coder.symbol_size())
        }),
        should("return the correct block size", function() {
            assert.equal(symbol_size * symbols, coder.block_size())
        })]
}

function create_decoder_test(field) {
    test = create_coder_test("decoder", kodo.decoder_factory, field)
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

function create_encoder_test(field) {
    test = create_coder_test("encoder", kodo.encoder_factory, field)
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

context("kodo",
    create_factory_test('encoder_factory', kodo.encoder_factory, kodo.field.binary),
    create_factory_test('decoder_factory', kodo.decoder_factory, kodo.field.binary),
    create_decoder_test(kodo.field.binary),
    create_encoder_test(kodo.field.binary),
    should("encode-decode integration test", function() {

        field = kodo.field.binary
        symbols = 8
        symbol_size = 160

        encoder_factory = new kodo.encoder_factory(field, symbols, symbol_size)
        encoder = encoder_factory.build()

        decoder_factory = new kodo.decoder_factory(field, symbols, symbol_size)
        decoder = decoder_factory.build()

        // Test number symbols
        assert.equal(symbols, encoder.symbols())
        assert.equal(symbols, encoder_factory.symbols())
        assert.equal(symbols, decoder.symbols())
        assert.equal(symbols, decoder_factory.symbols())

        // Test symbol size
        assert.equal(symbol_size, encoder.symbol_size())
        assert.equal(symbol_size, encoder_factory.symbol_size())
        assert.equal(symbol_size, decoder.symbol_size())
        assert.equal(symbol_size, decoder_factory.symbol_size())

        // Create random input data
        data_in = random_string(encoder.block_size())
        encoder.set_const_symbols(data_in)

        // Disable systematic coding to test with coded symbols only
        encoder.set_systematic_off()

        number_of_packets = 0
        while (!decoder.is_complete()) {
            packet = encoder.write_payload()
            decoder.read_payload(packet)
            number_of_packets += 1
        }
        assert.isTrue(number_of_packets >= symbols)

        data_out = decoder.copy_from_symbols()
        assert.arrayEqual(data_in, data_out)
    })
)

Tests.run()

// Make the script return 1 if any tests failed.
if (Tests.testsFailed > 0) {
    process.exit(1)
}
