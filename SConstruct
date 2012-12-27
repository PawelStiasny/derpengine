import glob
import os
import sys

# Use local include paths on Windows.
if sys.platform == 'win32':
	env = Environment(TARGET_ARCH = 'i386')
	env['CXX'] = 'cl'
	env['CPPPATH'] = ['.', '.\include\glew-1.9.0\include', '.\include\glm-0.9.4.1', '.\include\SDL-1.2.15\include']
	env['CPPFLAGS'] = ['/MTd']
	env['LINKFLAGS'] = ['/SUBSYSTEM:WINDOWS','/MACHINE:I386','/SUBSYSTEM:CONSOLE']
	env['LIBPATH'] = ['.\include\SDL-1.2.15\lib\\x86', '.\include\glew-1.9.0\lib']
else:
	env = Environment()
	env['CPPPATH'] = ['.', '/usr/include/SDL']

# Construct an object list
sources = ['main.cc', 'RenderingContext.cc']
sources.extend(glob.glob('scene/*.cc'))
sources.extend(glob.glob('animations/*.cc'))
sources.extend(glob.glob('shaders/*.cc'))
object_list = env.Object(source = sources)

env.Append( LIBS = ['SDL', 'OpenGL32', 'GLU32', 'GLEW32'] )
main = env.Program( target = 'mech', source = object_list ) 

