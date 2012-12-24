import glob
import os

env = Environment(TARGET_ARCH = 'i386')

env['CPPPATH'] = ['.', '.\include\glew-1.9.0\include', '.\include\glm-0.9.4.1', '.\include\SDL\include']
env['CPPFLAGS'] = ['/MTd']

# Construct an object list
sources = ['main.cc', 'RenderingContext.cc']
sources.extend(glob.glob('scene/*.cc'))
sources.extend(glob.glob('animations/*.cc'))
sources.extend(glob.glob('shaders/*.cc'))
object_list = env.Object(source = sources)

env.Append( LIBS = ['SDL', 'OpenGL32', 'GLU32', 'GLEW32'] )
main = env.Program( target = 'mech', source = object_list, 
	LINKFLAGS = ['/SUBSYSTEM:WINDOWS','/MACHINE:I386','/SUBSYSTEM:CONSOLE'],
	LIBPATH = ['.\include\SDL\VisualC\SDL\Win32\Debug', '.\include\glew-1.9.0\lib'])

