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
 * File:          $RCSfile: FTFont.cpp,v $
 * Date modified: $Date: 2002-07-01 01:01:42 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include <iostream>
#include "FTFont.h"
#include "FTLibrary.h"

namespace gltext
{
   FTFont::FTFont(const char* name, FontStyle style, int size)
      throw (std::runtime_error)
      : mName(name), mStyle(style), mSize(size), mFace(0)
   {
      // Get the freetype library handle
      FT_Library& library = FTLibrary::getInstance().getLibrary();
      if (! library)
      {
         throw std::runtime_error("Failed to initialized FreeType2");
      }

      // @todo Determine the path to the font using the style somehow.

      // Try to open the face
      FT_Error error;
      error = FT_New_Face(library,
                          name,
                          0,
                          &mFace);
      if (error)
      {
         throw std::runtime_error("Failed to open font face");
      }

      // Set the point size of this font
      error = FT_Set_Char_Size(mFace,
                               size*64,   // width in 1/64 of points
                               0,         // height same as width
                               72,        // device horiz resolution (dpi)
                               72);       // device vert resolution (dpi)
      if (error)
      {
         FT_Done_Face(mFace);
         throw std::runtime_error("Failed to set the size of the font.");
      }
   }

   FTFont::~FTFont()
   {
      // Free all of our cached glyphs
      GlyphMap::iterator itr;
      for (itr = mGlyphMap.begin(); itr != mGlyphMap.end(); ++itr)
      {
         delete itr->second;
      }

      // Destroy the FreeType 2 Face handle
      if (mFace)
      {
         FT_Done_Face(mFace);
         mFace = 0;
      }
   }

   const char*
   FTFont::getName() const
   {
      return mName.c_str();
   }

   FontStyle
   FTFont::getStyle() const
   {
      return mStyle;
   }

   int
   FTFont::getSize() const
   {
      return mSize;
   }

   int
   FTFont::getAscent() const
   {
      return mFace->size->metrics.ascender >> 6;
   }

   int
   FTFont::getDescent() const
   {
      // FT2 does descent in negative values. We want positive values.
      return mFace->size->metrics.descender >> 6;
   }

   int
   FTFont::getLineGap() const
   {
      return (mFace->size->metrics.height >> 6) - getAscent() - getDescent();
   }

   const FTGlyph*
   FTFont::getGlyph(char c)
   {
      const FTGlyph* glyph = 0;

      // See if we've already loaded that glyph
      GlyphMap::const_iterator itr = mGlyphMap.find(c);
      if (itr != mGlyphMap.end())
      {
         // cache hit
         glyph = itr->second;
      }
      else
      {
         // cache miss
         try
         {
            FTGlyph* newGlyph = new FTGlyph(mFace, c);
            mGlyphMap[c] = newGlyph;
            glyph = newGlyph;
         }
         catch (std::runtime_error& error)
         {
            std::cerr<<"Failed to create glyph: "<<error.what()<<std::endl;
            glyph = 0;
         }
      }
      return glyph;
   }
}
