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
 * File:          $RCSfile: main.cpp,v $
 * Date modified: $Date: 2002-07-01 02:46:25 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include <GL/glut.h>
#include <gltext.h>
#include <assert.h>
#include <iostream>

int gContext = 0;
gltext::FontRenderer* renderer = 0;

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
   for (int y=0; y<640; )
   {
      gltext::Font* font = 0;
      font = gltext::CreateFont("../../test/arial.ttf", gltext::PLAIN, size);
      renderer->setFont(font);
      glPushMatrix();
      y += font->getAscent();
      glTranslatef(5, y, 0);
      renderer->render("The quick, brown fox jumped over the ... I forget!");
      glPopMatrix();

      y += (font->getDescent() + font->getLineGap());
      delete font;
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

   renderer = gltext::CreateRenderer(gltext::PIXMAP);
   if (! renderer)
   {
      std::cerr<<"Couldn't create font renderer!"<<std::endl;
      return 1;
   }

   glutMainLoop();
}
