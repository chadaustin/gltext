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
 * File:          $RCSfile: gltext.h,v $
 * Date modified: $Date: 2002-07-01 01:01:42 $
 * Version:       $Revision: 1.4 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#ifndef GLTEXT_H
#define GLTEXT_H

#ifndef __cplusplus
#  error GLText requires C++
#endif

// Make sure we pull in windows.h on windows
#ifdef WIN32
#  define WIN32_LEAN_AND_MEAN
#  include <windows.h>
#endif

// The calling convention for cross-DLL calls in win32
#ifdef WIN32
#  define GLTEXT_CALL __stdcall
#else
#  define GLTEXT_CALL
#endif

#define GLTEXT_FUNC(ret, decl) extern "C" ret GLTEXT_CALL decl

namespace gltext
{
   /// Styles of fonts supported.
   enum FontStyle
   {
      PLAIN       = 0,  ///< Plain style
      BOLD        = 1,  ///< Bold style
      ITALIC      = 2,  ///< Italic style
      BOLDITALIC  = 3   ///< Bold and italic. Equivalent to BOLD | ITALIC.
   };

   /// Renderer types supported
   enum FontRendererType
   {
      BITMAP,
      PIXMAP
   };

   /**
    * Represents a particular font face.
    */
   class Font
   {
   public:
      /// Gets the name of this font.
      virtual const char* getName() const = 0;

      /// Gets the style of this font.ENDERER
      virtual FontStyle getStyle() const = 0;

      /// Gets the point size of this font.
      virtual int getSize() const = 0;

      /**
       * Gets the ascent of this font. This is the distance from the baseline to
       * the top of the tallest glyph of this font.
       */
      virtual int getAscent() const = 0;

      /**
       * Gets the descent of this font. This is the distance from the baseline
       * to the bottom of the the glyph that descends the most from the
       * baseline.
       */
      virtual int getDescent() const = 0;

      /**
       * Gets the distance that must be placed between two lines of text. Thus
       * the baseline to baseline distance can be computed as
       * ascent + descent + linegap.
       */
      virtual int getLineGap() const = 0;

      /**
       * Override default delete implementation so that memory allocated on
       * GLText's side of the shared library is deleted on that side.
       */
      void operator delete(void* p)
      {
         if (p)
         {
            Font* f = static_cast<Font*>(p);
            f->destroy();
         }
      }

   protected:
      /**
       * Destroy the font object, freeing any associated memory. Implementors of
       * this interface should just call "delete this" in this method.
       */
      virtual void destroy() = 0;
   };

   /**
    * Interface to an object that knows how to render a font.
    */
   class FontRenderer
   {
   public:
      /**
       * Renders the text in the given string as glyphs using this font
       * renderer's current font.
       */
      virtual void render(const char* text) = 0;

      /**
       * Sets the font this renderer should use.
       *
       * @param font    the new font to use
       */
      virtual void setFont(Font* font) = 0;

      /**
       * Gets the font this renderer should use.
       *
       * @return  this renderer's font
       */
      virtual Font* getFont() const = 0;

      /**
       * Override default delete implementation so that memory allocated on
       * GLText's side of the shared library is deleted on that side.
       */
      void operator delete(void* p)
      {
         if (p)
         {
            FontRenderer* f = static_cast<FontRenderer*>(p);
            f->destroy();
         }
      }

   protected:
      /**
       * Destroy the font renderer object, freeing any associated memory.
       * Implementors of this interface should just call "delete this" in this
       * method.
       */
      virtual void destroy() = 0;
   };

   /**
    * PRIVATE API - for internal use only
    * Anonymous namespace containing our exported functions. They are extern "C"
    * so we don't mange the names and they export nicely as shared libraries.
    */
   namespace {
      /// Gets version information
      GLTEXT_FUNC(const char*, GLTextGetVersion());

      /// Creates a new Font by name.
      GLTEXT_FUNC(Font*, GLTextCreateFont(
         const char* name,
         FontStyle style,
         int size));

      /// Creates a new FontRenderer.
      GLTEXT_FUNC(FontRenderer*, GLTextCreateRenderer(
         FontRendererType type));
   }

   /**
    * Gets the version string for GLText.
    *
    * @return  GLText version information
    */
   inline const char* GetVersion() {
      return GLTextGetVersion();
   }

   /**
    * Creates a new font from the given name, style and point size.
    *
    * @param name    the name of a particular font face.
    * @param style   the style constant for the Font. This can be PLAIN, BOLD,
    *                ITALIC or BOLD|ITALIC. Any other bitwise combination of
    *                these values will be ignored.
    * @param size    the point size of the font.
    */
   inline Font* CreateFont(const char* name, FontStyle style, int size)
   {
      return GLTextCreateFont(name, style, size);
   }

   /**
    * Creates a new font renderer of the given type.
    *
    * @param type    the type of renderer to create.
    */
   inline FontRenderer* CreateRenderer(FontRendererType type)
   {
      return GLTextCreateRenderer(type);
   }
}

#endif
