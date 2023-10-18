// -*- c++ -*-
/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkCxxABIConfigure.h.in

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/

#ifndef vtkCxxABIConfigure_h
#define vtkCxxABIConfigure_h

/* #undef VTK_HAS_CXXABI_DEMANGLE */

#ifdef VTK_HAS_CXXABI_DEMANGLE
#  include <cxxabi.h>
#endif

#endif //vtkCxxABIConfigure_h
