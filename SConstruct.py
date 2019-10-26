# flake8: noqa

base_env = Environment(CXX='clang++',
                       CXXFLAGS=['-Werror', '-Wall', '-Wpedantic', '-Wextra', '-g', '-std=c++17', '-I/home/alvar/include/'])
base_env.Append(CPPPATH=['#'])
base_env['OBJPREFIX'] = '#/build/obj/' + base_env['OBJPREFIX']
base_env['PROGPREFIX'] = '#/build/bin/' + base_env['PROGPREFIX']
base_env['PROGSUFFIX'] = '.out'

SConscript('src/SConscript.py', exports='base_env')
# SConscript('tests/SConscript.py', exports='base_env')
