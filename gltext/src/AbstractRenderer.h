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
 * File:          $RCSfile: AbstractRenderer.h,v $
 * Date modified: $Date: 2002-12-23 22:21:58 $
 * Version:       $Revision: 1.6 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#ifndef GLTEXT_ABSTRACTRENDERER_H
#define GLTEXT_ABSTRACTRENDERER_H

#include "gltext.h"
#include "FTFont.h"
#include "GLGlyph.h"

namespace gltext
{
   class AbstractRenderer : public RefImpl< FontRenderer >
   {
   protected:
      AbstractRenderer();
      virtual ~AbstractRenderer();

   public:
      void render(const char* text);
      FontStream& getStream();
      int getWidth(const char* text);
      void setFont(Font* font);
      Font* getFont() const;

   protected:
      /**
       * Makes a rendered glyph ready for OpenGL based on the given FreeType2
       * glyph.
       */
      virtual GLGlyph* makeGlyph(const FTGlyph* glyph) = 0;

   protected:
      FTFont* mFont;
      FontStreamPtr mStream;
   };
}

#endif
