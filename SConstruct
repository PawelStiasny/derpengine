import glob
import os
import sys

# Use local include paths on Windows.
if sys.platform == 'win32':
	env = Environment(TARGET_ARCH = 'i386')
	env['CXX'] = 'cl'
	env['CPPPATH'] = ['.', '.\external\include']
	env['CPPFLAGS'] = ['/MTd','/DWIN32']
	env['LINKFLAGS'] = ['/SUBSYSTEM:WINDOWS','/MACHINE:I386','/SUBSYSTEM:CONSOLE']
	env['LIBPATH'] = ['.\external\lib']
	env.Append( LIBS = ['SDL', 'OpenGL32', 'GLU32', 'GLEW32'] )
else:
	env = Environment()
	if sys.platform.startswith('linux'):
		env.Append( CPPFLAGS = ['-DLINUX'] )
	env.Append( LIBS = ['SDL2', 'GL', 'GLU', 'GLEW'] )
	if ARGUMENTS.get('debug', 0):
		env.Append( CPPFLAGS = ['-O0', '-march=native', '-g'] )
	else:
		env.Append( CPPFLAGS = ['-Ofast', '-march=native'] )

# Construct an object list
sources = ['main.cc']
sources.extend(glob.glob('scene/*.cc'))
sources.extend(glob.glob('animations/*.cc'))
sources.extend(glob.glob('core/*.cc'))
sources.extend(glob.glob('util/*.cc'))
object_list = env.Object(source = sources)

main = env.Program( target = 'mech', source = object_list )

