flags = [
        '-Wall',
        '-Werror',
        '-DUSE_CLANG_COMPLETER',
        '-std=c99',
        '-x', 'c',
    ]

def FlagsForFile(fname):
    return {
            'flags' : flags,
            'do_cache' : True
        }
