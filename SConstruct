import glob
import os
import sys

# Use local include paths on Windows.
if sys.platform == 'win32':
	env = Environment(TARGET_ARCH = 'i386')
	env['CXX'] = 'cl'
	env['CPPPATH'] = ['.', '.\include\glew-1.9.0\include', '.\include\glm-0.9.4.1', '.\include\SDL\include']
	env['CPPFLAGS'] = ['/MTd','/DWIN32']
	env['LINKFLAGS'] = ['/SUBSYSTEM:WINDOWS','/MACHINE:I386','/SUBSYSTEM:CONSOLE']
	env['LIBPATH'] = ['.\include\SDL\VisualC\SDL\Win32\Debug', '.\include\glew-1.9.0\lib']
	env.Append( LIBS = ['SDL', 'OpenGL32', 'GLU32', 'GLEW32'] )
else:
	env = Environment()
	env.Append( LIBS = ['SDL2', 'GL', 'GLU', 'GLEW'] )
	if ARGUMENTS.get('debug', 0):
		env.Append( CPPFLAGS = ['-O0', '-march=native', '-g'] )
	else:
		env.Append( CPPFLAGS = ['-Ofast', '-march=native'] )

# Construct an object list
sources = ['main.cc', 'RenderingContext.cc', 'ShadowmapRenderingContext.cc', 'SceneManager.cc', 'DemoSceneManager.cc', 'InputState.cc', 'Settings.cc']
sources.extend(glob.glob('scene/*.cc'))
sources.extend(glob.glob('animations/*.cc'))
sources.extend(glob.glob('shaders/*.cc'))
object_list = env.Object(source = sources)

main = env.Program( target = 'mech', source = object_list )

