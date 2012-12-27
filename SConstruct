import glob
import os

env = Environment()

env['CPPPATH'] = ['.', '/usr/include/SDL']

# Construct an object list
sources = ['main.cc', 'RenderingContext.cc']
sources.extend(glob.glob('scene/*.cc'))
sources.extend(glob.glob('animations/*.cc'))
sources.extend(glob.glob('shaders/*.cc'))
object_list = env.Object(source = sources)

if ARGUMENTS.get('debug', 0):
	# Use clang as a compiler
	env.Replace(CXX = 'clang++')
	# Force architecture
	env.Append( CXXFLAGS = ['-march=i686', '-g', '-Wall'] )

	# Allow clang pretty-printing
	env['ENV']['TERM'] = os.environ['TERM']

env.Append( LIBS = ['SDL', 'GL', 'GLU', 'GLEW'] )
main = env.Program( target = 'mech', source = object_list )

env.PDF('doc/spec.tex')
