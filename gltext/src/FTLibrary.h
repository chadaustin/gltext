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
 * File:          $RCSfile: FTLibrary.h,v $
 * Date modified: $Date: 2002-06-16 05:13:57 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#ifndef GLTEXT_FTLIBRARY_H
#define GLTEXT_FTLIBRARY_H

#include <ft2build.h>
#include FT_FREETYPE_H

namespace gltext
{
   /**
    * A singleton that manages the unique FreeType 2 FT_Library handle.
    */
   class FTLibrary
   {
   private:
      FTLibrary();
      FTLibrary(const FTLibrary& lib); // not implemented on purpose
      ~FTLibrary();

   public:
      /**
       * Gets the singleton instance of this class. This will try to initialize
       * the FreeType library handle.
       */
      static FTLibrary& getInstance();

      /**
       * Gets the FreeType 2 FT_Library handle.
       *
       * @return  the handle; or NULL if it failed to be initialized properly
       */
      FT_Library& getLibrary();

   private:
      /// The FT2 library handle.
      FT_Library* mLibrary;

      /// The singleton instance of this class.
      static FTLibrary* sInstance;
   };
}

#endif
