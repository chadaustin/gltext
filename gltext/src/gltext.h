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
 * Date modified: $Date: 2002-12-23 22:48:48 $
 * Version:       $Revision: 1.12 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#ifndef GLTEXT_H
#define GLTEXT_H

#ifndef __cplusplus
#  error GLText requires C++
#endif

#include <sstream>

// The calling convention for cross-DLL calls in win32
#ifdef WIN32
#  define GLTEXT_CALL __stdcall
#else
#  define GLTEXT_CALL
#endif

#define GLTEXT_FUNC(ret, decl) extern "C" ret GLTEXT_CALL decl

namespace gltext
{
   /**
    * Base class for classes the manage their own memory using reference
    * counting.
    *
    * This class was originally written by Chad Austin for the audiere project
    * and released under the LGPL.
    */
   class RefCounted
   {
   protected:
      /**
       * Protected so users of recounted classes don't use std::auto_ptr or the
       * delete operator.
       *
       * Interfaces that derive from RefCounted should define an inline, empty,
       * protected destrutor as well.
       */
      ~RefCounted() {}
   public:
      /**
       * Add a reference to this object. This will increment the internal
       * reference count.
       */
      virtual void ref() = 0;

      /**
       * Remove a reference from this object. This will decrement the internal
       * reference count. When this count reaches 0, the object is destroyed.
       */
      virtual void unref() = 0;
   };

   /**
    * This defines a smart pointer to some type T that implements the RefCounted
    * interface. This object will do all the nasty reference counting for you.
    *
    * This class was originally written by Chad Austin for the audiere project
    * and released under the LGPL.
    */
   template< typename T >
   class RefPtr
   {
   public:
      RefPtr(T* ptr = 0)
      {
         mPtr = 0;
         *this = ptr;
      }

      RefPtr(const RefPtr<T>& ptr)
      {
         mPtr = 0;
         *this = ptr;
      }

      ~RefPtr()
      {
         if (mPtr)
         {
            mPtr->unref();
            mPtr = 0;
         }
      }

      RefPtr<T>& operator=(T* ptr)
      {
         if (ptr != mPtr)
         {
            if (mPtr)
            {
               mPtr->unref();
            }
            mPtr = ptr;
            if (mPtr)
            {
               mPtr->ref();
            }
         }
         return *this;
      }

      RefPtr<T>& operator=(const RefPtr<T>& ptr)
      {
         *this = ptr.mPtr;
         return *this;
      }

      T* operator->() const
      {
         return mPtr;
      }

      T& operator*() const
      {
         return *mPtr;
      }

      operator bool() const
      {
         return (mPtr != 0);
      }

      T* get() const
      {
         return mPtr;
      }

   private:
      T* mPtr;
   };


   /**
    * A basic implementation of the RefCounted interface.  Derive your
    * implementations from RefImpl<YourInterface>.
    *
    * This class was originally written by Chad Austin for the audiere project
    * and released under the LGPL.
    */
   template< class Interface >
   class RefImpl : public Interface
   {
   protected:
      RefImpl()
         : mRefCount(0)
      {}

      /**
       * So the implementation can put its destruction logic in the destructor,
       * as natural C++ code does.
       */
      virtual ~RefImpl() {}

   public:
      void ref()
      {
         ++mRefCount;
      }

      void unref()
      {
         if (--mRefCount == 0)
         {
            delete this;
         }
      }

   private:
      int mRefCount;
   };


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
      PIXMAP,
      TEXTURE
   };

   /**
    * Represents a particular font face.
    */
   class Font : public RefCounted
   {
   protected:
      ~Font() {}

   public:
      /// Gets the name of this font.
      virtual const char* getName() const = 0;

      /// Gets the style of this font.
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
   };
   typedef RefPtr<Font> FontPtr;

   class FontStream;

   /**
    * Interface to an object that knows how to render a font.
    */
   class FontRenderer : public RefCounted
   {
   protected:
      ~FontRenderer() {}

   public:
      /**
       * Renders the text in the given string as glyphs using this font
       * renderer's current font.
       */
      virtual void render(const char* text) = 0;

      /**
       * Gets a stream for this renderer. All output to the stream will be sent
       * as text to this renderer when it has been flushed.
       */
      virtual FontStream& getStream() = 0;

      /**
       * Computes the width of the given text string if it were to be rendered
       * with this renderer.
       */
      virtual int getWidth(const char* text) = 0;

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
   };
   typedef RefPtr<FontRenderer> FontRendererPtr;

   /**
    * Provides a stream with which to use to provide text to a renderer.
    */
   class FontStream : public RefCounted
   {
   protected:
      ~FontStream() {}

   public:
      /**
       * Flushes the output in the given font stream through the renderer.
       */
      virtual FontStream& flush() = 0;

      ///@{
      /**
       * Renders the value of the given type as text.
       */
      virtual FontStream& operator<<(long val) = 0;
      virtual FontStream& operator<<(unsigned long val) = 0;
      virtual FontStream& operator<<(bool val) = 0;
      virtual FontStream& operator<<(short val) = 0;
      virtual FontStream& operator<<(unsigned short val) = 0;
      virtual FontStream& operator<<(int val) = 0;
      virtual FontStream& operator<<(unsigned int val) = 0;
      virtual FontStream& operator<<(float val) = 0;
      virtual FontStream& operator<<(double val) = 0;
      virtual FontStream& operator<<(long double val) = 0;
      virtual FontStream& operator<<(char val) = 0;
      virtual FontStream& operator<<(unsigned char val) = 0;
      virtual FontStream& operator<<(const char* val) = 0;
      virtual FontStream& operator<<(const unsigned char* val) = 0;
      virtual FontStream& operator<<(FontStream& (*func)(FontStream& stream)) = 0;
      ///@}
   };
   typedef RefPtr<FontStream> FontStreamPtr;

   /**
    * PRIVATE API - for internal use only
    * Anonymous namespace containing our exported functions. They are extern "C"
    * so we don't mangle the names and they export nicely as shared libraries.
    */
   namespace
   {
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

      /// Flushes the given font stream.
      GLTEXT_FUNC(FontStream*, GLTextFlushStream(
         FontStream* stream));
   }

   /**
    * Gets the version string for GLText.
    *
    * @return  GLText version information
    */
   inline const char* GetVersion()
   {
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

   /**
    * Flushes the output in the given font stream through the renderer.
    */
   inline FontStream& flush(FontStream& fs)
   {
      return *GLTextFlushStream(&fs);
   }

}

#endif
