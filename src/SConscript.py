# flake8: noqa

Import('base_env')

src_env = base_env.Clone()

src_env.Append(LIBS='readline')
src_env['OBJPREFIX'] = src_env['OBJPREFIX'] + 'src/'

src_env.Program(target='DesktopCalculator', source=Glob('*.cpp'))
