#!/usr/bin/env python2

APPNAME = 'KiwiOS'
VERSION = '0.1.0'

top = '.'
out = 'build'

def configure(ctx):
    print('Configuring in: %s' % (ctx.path.abspath()))

def build(ctx):
    print('Building...')
