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
 * File:          $RCSfile: GLPixelGlyph.cpp,v $
 * Date modified: $Date: 2002-12-20 10:24:18 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include "GLPixelGlyph.h"

// Sigh ... I hate windows
#ifdef WIN32
#  include <windows.h>
#endif
#include <GL/gl.h>

namespace gltext
{
   GLPixelGlyph::GLPixelGlyph(int posX, int posY,
                              int width, int height, float* data)
      : mPosX(posX), mPosY(posY), mWidth(width), mHeight(height), mData(data)
   {}

   GLPixelGlyph::~GLPixelGlyph()
   {
      delete [] mData;
   }

   void GLPixelGlyph::render(int penX, int penY) const
   {
      // Bail silently if there's nothing to render.
      if (mData)
      {
         // Move the raster position to the right location and blit the glyph
         // image to the buffer.
         glRasterPos2i(penX + mPosX, penY + mPosY);
         glDrawPixels(mWidth, mHeight, GL_RGBA, GL_FLOAT, mData);
      }
   }
}
