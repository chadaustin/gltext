/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/*************************************************************** gltext-cpr beg
 *
 * GLText - OpenGL TrueType Front Renderer
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
 * File:          $RCSfile: BitmapRenderer.cpp,v $
 * Date modified: $Date: 2002-06-15 22:59:55 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include "BitmapRenderer.h"
#include "GLPixelGlyph.h"

namespace gltext
{
   BitmapRenderer::BitmapRenderer()
   {}

   BitmapRenderer::~BitmapRenderer()
   {}

   GLGlyph*
   BitmapRenderer::makeGlyph(const FTGlyph* glyph)
   {
      FT_Error error;

      // newGlyph will be overwritten by FT_Glyph_To_Bitmap when glyph is
      // rendered as the bitmap.
      FT_Glyph newGlyph = glyph->getGlyph();
      error = FT_Glyph_To_Bitmap(&newGlyph, ft_render_mode_mono, 0, false);
      if (error)
      {
         std::cout<<"||||||||||||||||| ERROR ||||||||||||||||||||"<<std::endl;
         return 0;
      }

      FT_BitmapGlyph bmpGlyph = (FT_BitmapGlyph)newGlyph;
      // width and height are in pixels (bits in this case)
      int width = bmpGlyph->bitmap.width;
      int height = bmpGlyph->bitmap.rows;
      // pitch is in bytes
      int pitch = bmpGlyph->bitmap.pitch;
      int posX = bmpGlyph->left;
      int posY = height - bmpGlyph->top;
      const unsigned char* srcBuffer = bmpGlyph->bitmap.buffer;

      // Get the current OpenGL color
      float color[4];
      glGetFloatv(GL_CURRENT_COLOR, color);

      // Run through the FT2 glyph bitmap and color it with the current GL
      // color. Unfortunately, it appears that the FT2 bitmap is upside down.
      float* data = new float[width*height*4];
      int srcRow = height;
      for (int r=0; r<height; ++r)
      {
         --srcRow;
         for (int c=0; c<width; ++c)
         {
            int bytePos = srcRow * pitch + (c/8);
            int bit = c % 8;
            unsigned char byte = srcBuffer[bytePos];
            bool on = (byte & (0x80 >> bit)) != 0;

            int destOffset = 4*(r * width + c);
            if (on)
            {
               data[destOffset + 0] = color[0];
               data[destOffset + 1] = color[1];
               data[destOffset + 2] = color[2];
               data[destOffset + 3] = color[3];
            }
            else
            {
               data[destOffset + 0] = 0;
               data[destOffset + 1] = 0;
               data[destOffset + 2] = 0;
               data[destOffset + 3] = 0;
            }
         }
      }

      // Free the bitmap glyph
      FT_Done_Glyph(newGlyph);

      return new GLPixelGlyph(posX, posY, width, height, data);
   }
}
