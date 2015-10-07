#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'kodo-js'
VERSION = '0.0.0'

import os
from waflib.TaskGen import feature, after_method

import waflib.extras.wurf_options


def options(opt):

    opt.load('wurf_common_tools')


def resolve(ctx):

    import waflib.extras.wurf_dependency_resolve as resolve

    ctx.load('wurf_common_tools')

    ctx.add_dependency(resolve.ResolveVersion(
        name='waf-tools',
        git_repository='github.com/steinwurf/waf-tools.git',
        major=3))

    ctx.add_dependency(resolve.ResolveVersion(
        name='kodo',
        git_repository='github.com/steinwurf/kodo.git',
        major=32))


def configure(conf):

    conf.load("wurf_common_tools")

    if conf.get_mkspec_platform() != 'emscripten':
        conf.fatal('Kodo-js is Emscripten only!')


def build(bld):

    bld.load("wurf_common_tools")

    bld.recurse('src/kodo_js')


@feature('javascript')
@after_method('apply_link')
def test_kodo_js(self):
    # Only execute the tests within the current project
    if self.path.is_child_of(self.bld.srcnode):
        if self.bld.has_tool_option('run_tests'):
            self.bld.add_post_fun(exec_test_js)


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
