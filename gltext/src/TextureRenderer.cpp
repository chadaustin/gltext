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
 * File:          $RCSfile: TextureRenderer.cpp,v $
 * Date modified: $Date: 2002-12-21 02:48:31 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include "TextureRenderer.h"
#include "GLTextureGlyph.h"
#include <iostream>
#include <iomanip>

namespace gltext
{
   TextureRenderer::TextureRenderer()
   {}

   TextureRenderer::~TextureRenderer()
   {}

   GLGlyph*
   TextureRenderer::makeGlyph(const FTGlyph* glyph)
   {
      FT_Error error;

      // newGlyph will be overwritten by FT_Glyph_To_Bitmap when glyph is
      // rendered as the bitmap.
      FT_Glyph newGlyph = glyph->getGlyph();
      error = FT_Glyph_To_Bitmap(&newGlyph, ft_render_mode_normal, 0, false);
      if (error)
      {
         return 0;
      }

      FT_BitmapGlyph bmpGlyph = (FT_BitmapGlyph)newGlyph;
      int width = bmpGlyph->bitmap.width;
      int height = bmpGlyph->bitmap.rows;
      int pitch = bmpGlyph->bitmap.pitch;
      int posX = bmpGlyph->left;
      int posY = height - bmpGlyph->top;
      const unsigned char* srcBuffer = bmpGlyph->bitmap.buffer;

      // Get the current OpenGL color
      float color[4];
      glGetFloatv(GL_CURRENT_COLOR, color);

      // Run through the FT2 glyph bitmap and color it with the current GL
      // color. Unfortunately, it appears that the FT2 bitmap is upside down.
      unsigned int* data = new unsigned int[width*height];
      int srcRow = height;
      std::cout<<"--------------------------------------------"<<std::endl;
      for (int r=0; r<height; ++r)
      {
         --srcRow;
         for (int c=0; c<width; ++c)
         {
            int srcOffset = sizeof(unsigned char)*(srcRow * pitch + c);
            int destOffset = r * width + c;
            float srcAlpha = (float)srcBuffer[srcOffset] / 255.0f;
            data[destOffset] =
                  ((unsigned int)(color[0]*srcAlpha*255.0f) << 24)
                | ((unsigned int)(color[1]*srcAlpha*255.0f) << 16)
                | ((unsigned int)(color[2]*srcAlpha*255.0f) << 8)
                | ((unsigned int)(color[3]*srcAlpha*255.0f));
            std::cout<<std::setfill('0')<<std::setw(8)<<std::hex<<data[destOffset]<<std::dec<<","<<std::flush;
         }
         std::cout<<std::endl;
      }

      // Free the bitmap glyph
      FT_Done_Glyph(newGlyph);

      return new GLTextureGlyph(posX, posY, width, height, data);
   }
}
