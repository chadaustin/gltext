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
 * File:          $RCSfile: FTLibrary.cpp,v $
 * Date modified: $Date: 2002-06-16 05:13:57 $
 * Version:       $Revision: 1.3 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include "FTLibrary.h"

namespace gltext
{
   // Init the instance to NULL
   FTLibrary* FTLibrary::sInstance = 0;
   
   FTLibrary::FTLibrary()
      : mLibrary(0)
   {
      // Try to init the FT2 library
      mLibrary = new FT_Library;
      FT_Error error = FT_Init_FreeType(mLibrary);
      if (error)
      {
         // ack ... cleanup mem and set our FT2 lib ptr to NULL
         delete mLibrary;
         mLibrary = 0;
      }
   }

   FTLibrary::~FTLibrary()
   {
      // cleanup our memory
      FT_Done_FreeType(*mLibrary);
      delete mLibrary;
      mLibrary = 0;
   }

   FTLibrary&
   FTLibrary::getInstance()
   {
      if (! sInstance)
      {
         sInstance = new FTLibrary();
      }
      return *sInstance;
   }

   FT_Library&
   FTLibrary::getLibrary()
   {
      return *mLibrary;
   }
}
