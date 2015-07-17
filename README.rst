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

Follow this guide to download and setup emscripten standalone.
http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html

**Warning:** On some systems there are problems compiling kodo-js, with the latest emsdk

Run the following waf configure command::

   python waf configure --options=cxx_mkspec=cxx_emscripten126,emscripten_path={path-to-emscripten}

Where *path-to-emscripten* could be ``~/dev/emsdk_portable/emscripten/master/``.

Build and run unit tests using waf::

   python waf --options=run_tests,run_always
