=======
kodo-js
=======

This project contains emscripten bindings for the Kodo library.

.. contents:: Table of Contents:
   :local:

How to Build
============

Follow this guide to download and setup emscripten standalone.
http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html

Run the following waf configure command::

   python waf configure --options=cxx_mkspec=cxx_emscripten126,emscripten_path={path-to-emscripten}

Where *path-to-emscripten* could be ``~/dev/emsdk_portable/emscripten/master/``.

Build and run unit tests using waf::

   python waf --options=run_tests,run_always
