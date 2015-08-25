#! /usr/bin/env python
# encoding: utf-8

APPNAME = 'kodo-js'
VERSION = '0.0.0'

import os
from waflib.TaskGen import feature, after_method


def recurse_helper(ctx, name):
    if not ctx.has_dependency_path(name):
        ctx.fatal('Load a tool to find %s as system dependency' % name)
    else:
        p = ctx.dependency_path(name)
        ctx.recurse([p])


def options(opt):

    import waflib.extras.wurf_dependency_bundle as bundle
    import waflib.extras.wurf_dependency_resolve as resolve

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='boost',
        git_repository='github.com/steinwurf/boost.git',
        major_version=1))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='cpuid',
        git_repository='github.com/steinwurf/cpuid.git',
        major_version=3))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='fifi',
        git_repository='github.com/steinwurf/fifi.git',
        major_version=20))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='kodo',
        git_repository='github.com/steinwurf/kodo.git',
        major_version=30))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='platform',
        git_repository='github.com/steinwurf/platform.git',
        major_version=1))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='sak',
        git_repository='github.com/steinwurf/sak.git',
        major_version=14))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='recycle',
        git_repository='github.com/steinwurf/recycle.git',
        major_version=1))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='meta',
        git_repository='github.com/steinwurf/meta.git',
        major_version=1))

    bundle.add_dependency(opt, resolve.ResolveGitMajorVersion(
        name='waf-tools',
        git_repository='github.com/steinwurf/waf-tools.git',
        major_version=2))

    opt.load("wurf_configure_output")
    opt.load('wurf_dependency_bundle')
    opt.load('wurf_tools')


def configure(conf):
    if conf.is_toplevel():

        conf.load('wurf_dependency_bundle')
        conf.load('wurf_tools')

        conf.load_external_tool('mkspec', 'wurf_cxx_mkspec_tool')
        conf.load_external_tool('runners', 'wurf_runner')
        conf.load_external_tool('install_path', 'wurf_install_path')
        conf.load_external_tool('project_gen', 'wurf_project_generator')

        recurse_helper(conf, 'boost')
        recurse_helper(conf, 'cpuid')
        recurse_helper(conf, 'recycle')
        recurse_helper(conf, 'meta')
        recurse_helper(conf, 'fifi')
        recurse_helper(conf, 'kodo')
        recurse_helper(conf, 'platform')
        recurse_helper(conf, 'sak')

    if conf.get_mkspec_platform() != 'emscripten':
        conf.fatal('Kodo-js is Emscripten only!')


def build(bld):

    if bld.is_toplevel():

        bld.load('wurf_dependency_bundle')

        recurse_helper(bld, 'boost')
        recurse_helper(bld, 'cpuid')
        recurse_helper(bld, 'recycle')
        recurse_helper(bld, 'meta')
        recurse_helper(bld, 'fifi')
        recurse_helper(bld, 'kodo')
        recurse_helper(bld, 'platform')
        recurse_helper(bld, 'sak')

    bld.recurse('src/kodo_js')


@feature('javascript')
@after_method('apply_link')
def test(self):
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
