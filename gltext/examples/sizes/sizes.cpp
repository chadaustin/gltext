/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/*************************************************************** gltext-cpr beg
 *
 * GLText - OpenGL TrueType Font Renderer
 * GLText is (C) Copyright 2002 by Ben Scott
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Library General Public
 * License as published by the Free Software Foundation; either
 * version 2 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Library General Public License for more details.
 *
 * You should have received a copy of the GNU Library General Public
 * License along with this library; if not, write to the
 * Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: sizes.cpp,v $
 * Date modified: $Date: 2003-02-07 23:02:35 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include <iostream>
#include <assert.h>
#include <GL/glut.h>
#include <gltext.h>

int gContext = 0;
gltext::FontRendererPtr renderer;

void idle()
{
   if (glutGetWindow() != gContext)
   {
      glutSetWindow(gContext);
   }
   glutPostRedisplay();
}

void display()
{
   glClearColor(0,0,0,1);
   glClear(GL_COLOR_BUFFER_BIT);
   glMatrixMode(GL_MODELVIEW);
      glLoadIdentity();

   glColor4f(0,0,1,1);
   int size = 4;
   for (int y=0; y<480; )
   {
      gltext::FontPtr font(gltext::OpenFont("../arial.ttf", size));
      if (! font)
      {
         std::cerr << "Can't create font" << std::endl;
         exit(1);
      }
      
      gltext::FontRendererPtr renderer(gltext::CreateRenderer(gltext::TEXTURE, font.get()));
      if (! renderer)
      {
         std::cerr << "Can't create renderer" << std::endl;
         exit(1);
      }

      glPushMatrix();
      y += font->getAscent();
      glTranslatef(5, y, 0);
      gltext::FontStream(renderer).get() << "The quick, brown fox jumped over the lazy dog.";
      glPopMatrix();

      y += (font->getDescent() + font->getLineGap());
      size += 2;
   }

   glutSwapBuffers();
}

void reshape(int width, int height)
{
   glViewport(0, 0, width, height);
   glMatrixMode(GL_PROJECTION);
      glLoadIdentity();
      gluOrtho2D(0, width, height, 0);
}

void keydown(unsigned char key, int x, int y)
{
   if (key == 27 || key == 'q')
   {
      exit(0);
   }
}

int
main(int argc, char** argv)
{
   glutInitWindowSize(640, 480);
   glutInitWindowPosition(50, 50);
   glutInit(&argc, argv);
   glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
   gContext = glutCreateWindow("Sizes Example");

   glutDisplayFunc(display);
   glutIdleFunc(idle);
   glutReshapeFunc(reshape);
   glutKeyboardFunc(keydown);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glutMainLoop();
}
