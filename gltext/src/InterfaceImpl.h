/* -*- Mode: C++; tab-width: 3; indent-tabs-mode: nil c-basic-offset: 3 -*- */
// vim:cindent:ts=3:sw=3:et:tw=80:sta:
/*************************************************************** gltext-cpr beg
 *
 * GLText - OpenGL TrueType Front Renderer
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
 * File:          $RCSfile: InterfaceImpl.h,v $
 * Date modified: $Date: 2002-06-15 22:38:46 $
 * Version:       $Revision: 1.2 $
 * -----------------------------------------------------------------
 *
 ************************************************************ gltext-cpr-end */
#ifndef GLTEXT_INTERFACEIMPL_H
#define GLTEXT_INTERFACEIMPL_H

namespace gltext
{
   /**
    * Implementation helper for an implementation of a GLText interface. This
    * helper should make sure memory gets cleaned up safely and cleanly across
    * DLL boundaries.
    *
    * <h3>Example Usage</h3>
    * \code
    *    class MyImpl : public InterfaceImpl< MyInterface >
    *    {
    *    public:
    *       virtual ~MyImpl();
    *       // more methods here ...
    *    };
    * \endcode
    *
    * Ideas used to develop this helper class were taken from Chad Austin's
    * article, "Binary-compatible C++ Interfaces".
    * @see http://aegisknight.org/cppinterface.html
    */
   template< class Interface >
   class InterfaceImpl : public Interface
   {
   public:
      /**
       * A virtual destructor is required to implement the interface. This will
       * force the implementation and derived classes to have virtual
       * destructors.
       */
      virtual ~InterfaceImpl() {}

      /**
       * Overloaded operator delete calls global operator delete since
       * Interface modified this functionality to protect memory.
       *
       * @param p    pointer to the memory to delete
       */
      void operator delete(void* p)
      {
         ::operator delete(p);
      }

   protected:
      /**
       * Implementation of Interface's destroy method. This function will
       * make sure this object gets deleted in a polymorphic manner. You
       * should NOT reimplement this method.
       */
      virtual void destroy()
      {
         delete this;
      }
   };
}

#endif
