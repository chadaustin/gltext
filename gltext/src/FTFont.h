/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/************************************************************** gltext-head beg
 *
 * GLText
 *
 * Original Authors:
 *    Ben Scott <bscott@iastate.edu>
 *
 * -----------------------------------------------------------------
 * File:          $RCSfile: FTFont.h,v $
 * Date modified: $Date: 2002-06-11 04:27:18 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 *********************************************************** gltext-head-end */
/*************************************************************** gltext-cpr beg
 *
 * GLText
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
 ************************************************************ gltext-cpr-end */
#ifndef GLTEXT_FTFONT_H
#define GLTEXT_FTFONT_H

#include "gltext.h"
#include <stdexcept>
#include <map>
#include "FTGlyph.h"
#include "InterfaceImpl.h"

namespace gltext
{
   /**
    * FreeType 2 implementation of the Font interface.
    */
   class FTFont : public InterfaceImpl< Font >
   {
   public:
      /**
       * Creates a new FreeType font with the given face name, style and point
       * size.
       */
      FTFont(const char* name, FontStyle style, int size)
         throw (std::runtime_error);

      /**
       * Destroys the font, freeing the owned FreeType face struct.
       */
      virtual ~FTFont();

      /// Gets the name of this font.
      const char* getName() const;

      /// Gets the style of this font.
      FontStyle getStyle() const;

      /// Gets the point size of this font.
      int getSize() const;

      /**
       * Gets the ascent of this font. This is the distance from the baseline to
       * the top of the tallest glyph of this font.
       */
      int getAscent() const;

      /**
       * Gets the descent of this font. This is the distance from the baseline
       * to the bottom of the the glyph that descends the most from the
       * baseline.
       */
      int getDescent() const;

      /**
       * Gets the distance that must be placed between two lines of text. Thus
       * the baseline to baseline distance can be computed as
       * ascent + descent + linegap.
       */
      int getLineGap() const;

      /**
       * Gets the FT2 glyph for the given character. Returns NULL if this font
       * does not support the character requested.
       */
      const FTGlyph* getGlyph(char c);

   private:
      /// The name of this font.
      std::string mName;

      /// The style for this font.
      FontStyle mStyle;

      /// The point size for this font.
      int mSize;

      /// The FreeType 2 face handle.
      FT_Face mFace;

      typedef std::map<char, FTGlyph*> GlyphMap;
      /// Map of characters to FTGlyphs.
      GlyphMap mGlyphMap;
   };
}

#endif
