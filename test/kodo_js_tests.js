// Copyright Steinwurf ApS 2011-2013.
// Distributed under the "STEINWURF RESEARCH LICENSE 1.0".
// See accompanying file LICENSE.rst or
// http://www.steinwurf.com/licensing

// Load unit testing framework
var fs = require('fs');
var path = require('path');
filedata = fs.readFileSync(path.join(__dirname, 'shoulda.js'),'utf8');
eval(filedata);

kodo = module.require('kodo.js');
context("kodo",
    should("work", function() {
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
        data_in = "some very nice data"

        // Assign the data buffer to the encoder so that we can
        // produce encoded symbols
        encoder.set_symbols(data_in)

        while(!decoder.is_complete())
        {
            packet = encoder.encode()
            decoder.decode(packet)
        }
        data_out = decoder.copy_symbols().slice(0, data_in.length)
        assert.arrayEqual(data_in, data_out)
    })
);

Tests.run();

// Make the script return 1 if any tests failed.
if (Tests.testsFailed > 0) {
    process.exit(1);
}
