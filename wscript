#! /usr/bin/env python
# encoding: utf-8

import os

APPNAME = 'kodo-js'
VERSION = '0.0.0'


def configure(conf):

    if conf.get_mkspec_platform() != 'emscripten':
        conf.fatal('Kodo-js is Emscripten only!')


def build(bld):

    bld.recurse('src/kodo_js')

    if bld.is_toplevel():
        if bld.has_tool_option('run_tests'):
            bld.add_post_fun(exec_test_js)


def exec_test_js(bld):
    nodejs = bld.env['NODEJS'][0]
    env = dict(os.environ)
    env['NODE_PATH'] = os.path.join(bld.out_dir, 'src', 'kodo_js')

    # First, run the unit tests in the 'test' folder
    if os.path.exists('test'):
        for f in sorted(os.listdir('test')):
            if f == 'shoulda.js':
                continue
            if f.endswith('.js'):
                test = os.path.join('test', f)
                bld.cmd_and_log('{0} {1}\n'.format(nodejs, test), env=env)

    # Then run the examples in the 'examples' folder
    if os.path.exists('examples'):
        for f in sorted(os.listdir('examples')):
            if f.endswith('.js'):
                example = os.path.join('examples', f)
                bld.cmd_and_log(
                    '{0} {1} --dry-run\n'.format(nodejs, example), env=env)
