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
        factory = new kodo.encoder_factory(41, 42);
        assert.equal(41, factory.max_symbols());
    })
);

Tests.run();

// Make the script return 1 if any tests failed.
if (Tests.testsFailed > 0) {
    process.exit(1);
}
