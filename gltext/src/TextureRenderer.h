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
 * File:          $RCSfile: TextureRenderer.h,v $
 * Date modified: $Date: 2002-09-27 02:59:34 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#ifndef GLTEXT_TEXTURERENDERER_H
#define GLTEXT_TEXTURERENDERER_H

#include "AbstractRenderer.h"

namespace gltext
{
   /**
    * Renders fonts anti-aliased with 256 levels of the current OpenGL color
    * using a texture-mapped quad that is affected by the current OpenGL matrix
    * stack.
    */
   class TextureRenderer : public AbstractRenderer
   {
   public:
      /**
       * Creates a new renderer without a font to render with.
       */
      TextureRenderer();
      virtual ~TextureRenderer();

   protected:
      /**
       * Creates a GLGlyph specialized for this type of renderer.
       */
      GLGlyph* makeGlyph(const FTGlyph* glyph);
   };
}

#endif