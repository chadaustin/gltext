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
 * File:          $RCSfile: GlyphCache.h,v $
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
#ifndef GLTEXT_GLYPHCACHE_H
#define GLTEXT_GLYPHCACHE_H

#include "FTGlyph.h"
#include <map>
#include <ft2build.h>
#include FT_FREETYPE_H

namespace gltext
{
   /**
    * Helper class for FontRenderer implementations to cache the rendering of a
    * particular glyph so they don't try to render it multiple times while
    * rendering a string.
    */
   class GlyphCache
   {
   public:
      ~GlyphCache()
      {
         // Delete all cached GLGlyphs.
         Cache::iterator itr;
         for (itr = mCache.begin(); itr != mCache.end(); ++itr)
         {
            delete itr->second;
         }
      }

      /**
       * Puts the given GLGlyph in the cache for the given FT2 glyph. Behavior
       * is undefined if either fontGlyph or glGlyph are NULL.
       */
      void put(const FTGlyph* fontGlyph, GLGlyph* glGlyph)
      {
         mCache[fontGlyph] = glGlyph;
      }
      
      /**
       * Gets the GLGlyph for the given FT2 glyph. Returns NULL if the GL
       * rendered glyph is not yet in this cache.
       */
      const GLGlyph* get(const FTGlyph* glyph) const
      {
         Cache::const_iterator itr = mCache.find(glyph);
         if (itr != mCache.end())
         {
            // Cache hit
            return itr->second;
         }
         // Cache miss
         return 0;
      }

   private:
      typedef std::map<const FTGlyph*, GLGlyph*> Cache;

      /// The mapping between font glyphs and rendered glyphs.
      Cache mCache;
   };
}

#endif
