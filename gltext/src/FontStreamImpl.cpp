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
 * File:          $RCSfile: FontStreamImpl.cpp,v $
 * Date modified: $Date: 2002-12-23 22:21:58 $
 * Version:       $Revision: 1.1 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#include <sstream>
#include "FontStreamImpl.h"

namespace gltext
{
   FontStreamImpl::FontStreamImpl(FontRenderer* renderer)
      : mRenderer(renderer)
   {
      mStream = new std::ostringstream();
   }

   FontStreamImpl::~FontStreamImpl()
   {
      delete mStream;
   }

   FontStream& FontStreamImpl::flush()
   {
      mStream->flush();
      mRenderer->render(mStream->str().c_str());
      delete mStream;
      mStream = new std::ostringstream();
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(long val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(unsigned long val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(bool val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(short val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(unsigned short val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(int val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(unsigned int val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(float val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(double val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(long double val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(char val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(unsigned char val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(const char* val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(const unsigned char* val)
   {
      *mStream << val;
      return *this;
   }

   FontStream& FontStreamImpl::operator<<(FontStream& (*func)(FontStream& stream))
   {
      return func(*this);
   }

   FontStream& flush(FontStream& fs)
   {
      return fs.flush();
   }
}
