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
 * File:          $RCSfile: AbstractRenderer.cpp,v $
 * Date modified: $Date: 2003-02-03 19:40:40 $
 * Version:       $Revision: 1.7 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include <iostream>
#include "AbstractRenderer.h"

namespace gltext
{
   AbstractRenderer::AbstractRenderer(Font* font)
      : mFont(font)
   {
   }

   void AbstractRenderer::render(const char* text)
   {
      int penX = 0;

      // Run through each char and generate a glyph to draw
      for (const char* itr = text; *itr; ++itr)
      {
         // Get the glyph for the current character
         Glyph* fontGlyph = mFont->getGlyph(*itr);
         if (!fontGlyph)
         {
            continue;
         }

         // Check the cache first
         GLGlyph* drawGlyph = mCache.get(fontGlyph);
         if (!drawGlyph)
         {
            // Cache miss. Ask this renderer to create a new one
            drawGlyph = makeGlyph(fontGlyph);
            if (!drawGlyph)
            {
               // AAACK! Couldn't create the glyph. Fail silently.
               continue;
            }
            mCache.put(fontGlyph, drawGlyph);
         }

         // Now tell the glyph to render itself.
         drawGlyph->render(penX, 0);
         penX += fontGlyph->getAdvance();
      }
   }

   int AbstractRenderer::getWidth(const char* text)
   {
      if (! text)
      {
         return 0;
      }

      int width = 0;

      // Iterate over each character adding its width
      for (const char* itr = text; *itr != 0; ++itr)
      {
         // Get the glyph for the current character
         Glyph* fontGlyph = mFont->getGlyph(*itr);
         if (fontGlyph)
         {
            // Add this glyph's advance
            width += fontGlyph->getAdvance();
         }
      }

      return width;
   }
}
