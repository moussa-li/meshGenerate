/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtk_fast_float.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
#ifndef vtk_fast_float_h
#define vtk_fast_float_h

/* Use the fast_float library configured for VTK.  */
#define VTK_MODULE_USE_EXTERNAL_vtkfast_float 0

#if VTK_MODULE_USE_EXTERNAL_vtkfast_float
# include <fast_float/fast_float.h>
#else
# include <vtkfast_float/vtkfast_float/fast_float.h>
#endif

#endif
