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
 * Date modified: $Date: 2002-07-01 01:01:42 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include <iostream>
#include "AbstractRenderer.h"
#include "GlyphCache.h"

namespace gltext
{
   AbstractRenderer::AbstractRenderer()
      : mFont(0)
   {}

   AbstractRenderer::~AbstractRenderer()
   {}

   void AbstractRenderer::render(const char* text)
   {
      // Fail silently if we don't have a current font
      if (! mFont)
      {
         std::cerr<<"This renderer doesn't have a current font."<<std::endl;
         return;
      }

      GlyphCache cache;
      int penX = 0;

      // Run through each char and generate a glyph to draw
      for (const char* itr = text; *itr != 0; ++itr)
      {
         // Get the glyph for the current character
         const FTGlyph* fontGlyph = mFont->getGlyph(*itr);
         if (fontGlyph)
         {
            // Check the cache first
            const GLGlyph* drawGlyph = cache.get(fontGlyph);
            if (! drawGlyph)
            {
               // Cache miss. Ask this renderer to create a new one
               GLGlyph* newGlyph = makeGlyph(fontGlyph);
               if (! newGlyph)
               {
                  // AAACK! Couldn't create the glyph. Fail silently.
                  continue;
               }
               cache.put(fontGlyph, newGlyph);
               drawGlyph = newGlyph;
            }

            // Now tell the glyph to render itself.
            drawGlyph->render(penX, 0);
            penX += fontGlyph->getAdvance();
         }
      }
   }

   void AbstractRenderer::setFont(Font* font)
   {
      mFont = (FTFont*)font;
   }

   Font* AbstractRenderer::getFont() const
   {
      return mFont;
   }
}
