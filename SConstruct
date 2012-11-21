import glob
import os

env = Environment()

# Construct an object list
sources = ['main.cc']
sources.extend(glob.glob('scene/*.cc'))
object_list = env.Object(source = sources)

# Use clang as a compiler
env.Replace(CXX = 'clang++')
# Force architecture
env.Append( CXXFLAGS = ['-march=i686', '-g'] )

# Allow clang pretty-printing
env['ENV']['TERM'] = os.environ['TERM']

env.Append( LIBS = ['SDL', 'GL', 'GLU'] )
main = env.Program( target = 'mech', source = object_list )

#test = Command( command = 'test', source = 'main', action = './main' )
#env.Depends( test, main )
