"""
Figure out what libraries we need to link with to use GLUT.
Defines the function SetupGLUT.

Supported platforms:
  Cygwin
  Linux
  IRIX
"""
import sys
import string

def SetupGLUT(env):
   "Sets up the given environment to be able to build with GLUT"

   # CYGWIN
   if sys.platform == 'cygwin':
       GLUT_LIBS = ['glut32']

   # IRIX
   elif string.find(sys.platform, 'irix') != -1:
       GLUT_LIBS = ['glut']

   # GENERIC (LINUX?)
   else:
       GLUT_LIBS = ['glut']

   # Make sure the environment has LIBS defined
   if not env.Dictionary().has_key('LIBS'):
      env['LIBS'] = [];

   # Add in the GLUT libs to the environment
   env['LIBS'].extend(GLUT_LIBS)
