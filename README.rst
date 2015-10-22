=======
kodo-js
=======

This project contains emscripten bindings for the Kodo library.

.. contents:: Table of Contents:
   :local:

If you have any questions or suggestions about this library, please contact
us at our developer mailing list (hosted at Google Groups):

* http://groups.google.com/group/steinwurf-dev

How to Build
============

Follow this guide to download and setup the Portable Emscripten SDK:
http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html

Note that Emscripten is not compatible with Python 3, always use Python 2.7
when running the SDK commands and the compiler.

On Ubuntu and Debian, the Node.js binary is called ``nodejs`` (not ``node``),
so you need to change the following line in ``~/.emscripten`` (the file is
created when you run ``./emsdk activate latest``)::

    NODE_JS = 'node'

To this::

    NODE_JS = 'nodejs'

Now you should be able to clone and configure kodo-js::

    git clone git@github.com:steinwurf/kodo-js.git
    cd kodo-js
    python waf configure --cxx_mkspec=cxx_default_emscripten --emscripten_path="path-to-emscripten"

For example, *path-to-emscripten* can be: ``~/emsdk_portable/emscripten/tag-1.34.7``

Build and run the unit tests using waf::

    python waf --run_tests
