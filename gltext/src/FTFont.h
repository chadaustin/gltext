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
 * File:          $RCSfile: FTFont.h,v $
 * Date modified: $Date: 2003-02-14 04:59:43 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#ifndef GLTEXT_FTFONT_H
#define GLTEXT_FTFONT_H

#include <ft2build.h>
#include FT_FREETYPE_H
#include "gltext.h"

namespace gltext
{
   class FTGlyph;

   /**
    * FreeType 2 implementation of the Font interface.
    */
   class FTFont : public RefImpl<Font>
   {
   public:
      /// Creates a new FreeType font with the given face name and
      /// point size.
      static FTFont* create(const char* name, int size, int dpi);

      FTFont(const char* name, int size, FT_Library library, FT_Face face);

      /**
       * Destroys the font, freeing the owned FreeType face struct.
       */
      ~FTFont();

      /// Gets the name of this font.
      const char* GLTEXT_CALL getName();

      /// Gets the point size of this font.
      int GLTEXT_CALL getSize();

      /**
       * Gets the ascent of this font. This is the distance from the baseline to
       * the top of the tallest glyph of this font.
       */
      int GLTEXT_CALL getAscent();

      /**
       * Gets the descent of this font. This is the distance from the baseline
       * to the bottom of the the glyph that descends the most from the
       * baseline.
       */
      int GLTEXT_CALL getDescent();

      /**
       * Gets the distance that must be placed between two lines of text. Thus
       * the baseline to baseline distance can be computed as
       * ascent - descent + linegap.
       */
      int GLTEXT_CALL getLineGap();

      /**
       * Gets the FT2 glyph for the given character. Returns NULL if this font
       * does not support the character requested.
       */
      Glyph* GLTEXT_CALL getGlyph(unsigned char c);

   private:
      /// The name of this font.
      std::string mName;

      /// The point size for this font.
      int mSize;

      /// The FreeType 2 library handle.
      FT_Library mLibrary;

      /// The FreeType 2 face handle.
      FT_Face mFace;

      /// Map of characters to FTGlyphs.  This should be replaced with
      /// a std::map when we need characters larger than 8 bits.
      FTGlyph* mGlyphMap[256];
   };
}

#endif
