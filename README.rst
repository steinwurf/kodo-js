=======
kodo-js
=======

This project contains emscripten bindings for the Kodo library.

.. contents:: Table of Contents:
   :local:

If you have any questions about this library, please contact
us at our developer mailing list (hosted at Google Groups):

* http://groups.google.com/group/steinwurf-dev

How to build
============

Follow this guide to download and setup the Portable Emscripten SDK:
http://kripken.github.io/emscripten-site/docs/getting_started/downloads.html

Note that Emscripten is not compatible with Python 3, **always use Python 2.7**
when running the SDK commands and the compiler.

Now you should be able to clone and configure kodo-js (if you don't have
the ``python2`` command on your system, just write ``python`` instead)::

    git clone git@github.com:steinwurf/kodo-js.git
    cd kodo-js
    python2 waf configure --cxx_mkspec=cxx_default_emscripten --emscripten_path="path-to-emscripten"

For example, *path-to-emscripten* can be: ``~/emsdk-portable/emscripten/1.37.22``

Build and run the unit tests using waf::

    python2 waf --run_tests

Possible issues
---------------

Node.js is bundled with the Emscripten SDK 1.37 and above, but older versions
require a manual installation of the ``nodejs`` package.

If you have an older version of Emscripten and you installed the ``nodejs``
package on Ubuntu or Debian, then consider that the Node.js binary is called
``nodejs`` (not ``node``). If emscripten cannot find this binary, then
you need to change the following line in ``~/.emscripten`` (the file is
created when you run ``./emsdk activate latest``)::

    NODE_JS = 'node'

To this::

    NODE_JS = 'nodejs'