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
 * File:          $RCSfile: FTGlyph.h,v $
 * Date modified: $Date: 2002-06-15 22:38:46 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#ifndef GLTEXT_FTGLYPH_H
#define GLTEXT_FTGLYPH_H

#include <stdexcept>
#include <ft2build.h>
#include FT_FREETYPE_H
#include FT_GLYPH_H

namespace gltext
{
   /**
    * C++ wrapper for a FreeType2 glyph handle.
    */
   class FTGlyph
   {
   public:
      /**
       * Creates a new glyph from the given font face for the given character.
       */
      FTGlyph(FT_Face face, char c)
         throw(std::runtime_error);

      /// Release the FT2 resources.
      ~FTGlyph();

      /**
       * Gets the width of this glyph.
       */
      int getWidth() const;

      /**
       * Gets the height of this glyph.
       */
      int getHeight() const;
      
      /**
       * Gets the advance width of this glyph.
       */
      int getAdvance() const;

      /**
       * Gets the glyph handle for this glyph.
       */
      FT_Glyph getGlyph() const;

   private:
      /// The FT2 glyph handle
      FT_Glyph mGlyph;

      /// The height of this glyph
      int mWidth;

      /// The width of this glyph
      int mHeight;

      /// Cache of the advance width of this glyph
      int mAdvance;
   };
}

#endif
