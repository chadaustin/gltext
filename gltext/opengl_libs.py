"""
Figure out what libraries we need to link with to use OpenGL.
Defines the function SetupOpenGL.

Supported platforms:
  Cygwin
  Linux
  IRIX
"""
import sys
import string

def SetupOpenGL(env):
   "Sets up the given environment to be able to build with OpenGL"

   # CYGWIN
   if sys.platform == 'cygwin':
       OPENGL_LIBS = ['opengl32', 'glu32']

   # IRIX
   elif string.find(sys.platform, 'irix') != -1:
       OPENGL_LIBS = ['GLU', 'GL', 'X11', 'Xmu']

   # GENERIC (LINUX?)
   else:
       OPENGL_LIBS = ['GLU', 'GL']

   # Make sure the environment has LIBS defined
   if not env.Dictionary().has_key('LIBS'):
      env['LIBS'] = []

   # Add in the OpenGL libs to the environment
   env['LIBS'].extend(OPENGL_LIBS)
