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
 * File:          $RCSfile: GLTextureGlyph.cpp,v $
 * Date modified: $Date: 2003-02-03 19:40:41 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include "GLTextureGlyph.h"
#include <string.h>
#include <iostream>
#include <iomanip>

namespace gltext
{
   int nextPowerOf2(int n)
   {
      int i = 1;
      while (i < n)
      {
         i *= 2;
      }
      return i;
   }

   GLTextureGlyph::GLTextureGlyph(int offx, int offy,
                                  int width, int height, u8* data)
      : mOffsetX(offx), mOffsetY(offy), mWidth(width), mHeight(height)
   {
      // Make a texture sized at a power of 2
      mTexWidth = nextPowerOf2(mWidth);
      mTexHeight = nextPowerOf2(mHeight);
      u8* pixels = new u8[mTexWidth * mTexHeight];
      memset(pixels, 0, mTexWidth * mTexHeight);

      for (int row = 0; row < mHeight; ++row)
      {
         memcpy(pixels + mTexWidth * row, data + mWidth * row, mWidth);
      }

      // Get a unique texture name for our new texture
      glGenTextures(1, &mTexName);

      // Generate a 2D texture with our image data
      glBindTexture(GL_TEXTURE_2D, mTexName);
      glTexImage2D(
            GL_TEXTURE_2D,
            0,
            1,
            mTexWidth,
            mTexHeight,
            0,
            GL_LUMINANCE,
            GL_UNSIGNED_BYTE,
            pixels);

      // Setup clamping and our min/mag filters
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
      glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);

      // Free image data memory
      delete [] pixels;
      delete [] data;
   }

   GLTextureGlyph::~GLTextureGlyph()
   {
      // Free our texture resource
      glDeleteTextures(1, &mTexName);
   }

   void GLTextureGlyph::render(int penX, int penY) const
   {
      // Enable texturing and bind our texture
      glEnable(GL_TEXTURE_2D);
      glBindTexture(GL_TEXTURE_2D, mTexName);

      // Draw the texture-mapped quad
      glPushMatrix();

      // Translate over to the font position
      glTranslatef(GLfloat(penX + mOffsetX), GLfloat(penY + mOffsetY), 0);

      float realWidth = float(mWidth) / mTexWidth;
      float realHeight = float(mHeight) / mTexHeight;

      glBegin(GL_QUADS);
      glTexCoord2f(0,         0);            glVertex2i(0,      0);
      glTexCoord2f(realWidth, 0);            glVertex2i(mWidth, 0);
      glTexCoord2f(realWidth, realHeight);   glVertex2i(mWidth, mHeight);
      glTexCoord2f(0,         realHeight);   glVertex2i(0,      mHeight);
      glEnd();

      glPopMatrix();

      // Unbind our texture and disable texturing
      glBindTexture(GL_TEXTURE_2D, 0);
      glDisable(GL_TEXTURE_2D);
   }
}
