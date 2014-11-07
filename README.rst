=======
kodo-js
=======

This project contains emscripten bindings for the Kodo library.

.. contents:: Table of Contents:
   :local:

How to Build
============

Follow this guide to download and setup emscripten standalone.

run the following waf configure command::

   python waf configure --bundle-path=../dependencies
   --options=cxx_mkspec=cxx_emscripten126,
   emscripten_path=~/.development/emsdk_portable/emscripten/master/

Build and run unit tests using waf

   python waf --options=run_tests,run_always
