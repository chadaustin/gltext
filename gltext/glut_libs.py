"""
Figure out what libraries we need to link with to use GLUT.
Defines GLUT_LIBS.

Supported platforms:
  Cygwin
  Linux
  IRIX
"""
import sys
import string

# CYGWIN
if sys.platform == 'cygwin':
    GLUT_LIBS = ['glut32']

# IRIX
elif string.find(sys.platform, 'irix') != -1:
    GLUT_LIBS = ['glut']

# GENERIC (LINUX?)
else:
    GLUT_LIBS = ['glut']
