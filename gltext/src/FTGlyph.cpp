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
 * File:          $RCSfile: FTGlyph.cpp,v $
 * Date modified: $Date: 2002-06-16 05:13:57 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include "FTGlyph.h"

namespace gltext
{
   FTGlyph::FTGlyph(FT_Face face, char c)
      throw(std::runtime_error)
   {
      FT_Error error;

      // Compute the index of the glyph for the given char
      FT_UInt glyph_index = FT_Get_Char_Index(face, int(c));
      if (glyph_index == 0)
      {
         throw std::runtime_error("Character has undefined character code");
      }

      // Try to load the glyph from the face
      error = FT_Load_Glyph(face, glyph_index, FT_LOAD_DEFAULT);
      if (error)
      {
         throw std::runtime_error("Failed to load glyph");
      }

      // Try to cache the glyph
      error = FT_Get_Glyph(face->glyph, &mGlyph);
      if (error)
      {
         throw std::runtime_error("Failed to cache the glyph");
      }

      // Cache glyph metrics
      mWidth = face->glyph->metrics.width >> 6;
      mHeight = face->glyph->metrics.height >> 6;
      mAdvance = face->glyph->metrics.horiAdvance >> 6;
   }

   FTGlyph::~FTGlyph()
   {
      // Release the glyph
      FT_Done_Glyph(mGlyph);
   }

   int
   FTGlyph::getWidth() const
   {
      return mWidth;
   }

   int
   FTGlyph::getHeight() const
   {
      return mHeight;
   }

   int
   FTGlyph::getAdvance() const
   {
      /// @todo this should really be a float...
      return mAdvance;
   }

   FT_Glyph
   FTGlyph::getGlyph() const
   {
      return mGlyph;
   }
}
