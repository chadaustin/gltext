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
 * File:          $RCSfile: FontStreamImpl.h,v $
 * Date modified: $Date: 2002-12-23 22:21:58 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#ifndef GLTEXT_FONTSTREAMIMPL_H
#define GLTEXT_FONTSTREAMIMPL_H

#include "gltext.h"
#include <sstream>

namespace gltext
{
   class FontStreamImpl : public RefImpl<FontStream>
   {
   public:
      FontStreamImpl(FontRenderer* renderer);
      virtual ~FontStreamImpl();

      FontStream& flush();

      FontStream& operator<<(long val);
      FontStream& operator<<(unsigned long val);
      FontStream& operator<<(bool val);
      FontStream& operator<<(short val);
      FontStream& operator<<(unsigned short val);
      FontStream& operator<<(int val);
      FontStream& operator<<(unsigned int val);
      FontStream& operator<<(float val);
      FontStream& operator<<(double val);
      FontStream& operator<<(long double val);
      FontStream& operator<<(char val);
      FontStream& operator<<(unsigned char val);
      FontStream& operator<<(const char* val);
      FontStream& operator<<(const unsigned char* val);
      FontStream& operator<<(FontStream& (*func)(FontStream& stream));

   private:
      FontRendererPtr mRenderer;
      std::ostringstream* mStream;
   };
}

#endif
