
#ifndef VTKFILTERSDSP_EXPORT_H
#define VTKFILTERSDSP_EXPORT_H

#ifdef VTKFILTERSDSP_STATIC_DEFINE
#  define VTKFILTERSDSP_EXPORT
#  define VTKFILTERSDSP_NO_EXPORT
#else
#  ifndef VTKFILTERSDSP_EXPORT
#    ifdef FiltersDSP_EXPORTS
        /* We are building this library */
#      define VTKFILTERSDSP_EXPORT __declspec(dllexport)
#    else
        /* We are using this library */
#      define VTKFILTERSDSP_EXPORT __declspec(dllimport)
#    endif
#  endif

#  ifndef VTKFILTERSDSP_NO_EXPORT
#    define VTKFILTERSDSP_NO_EXPORT 
#  endif
#endif

#ifndef VTKFILTERSDSP_DEPRECATED
#  define VTKFILTERSDSP_DEPRECATED __declspec(deprecated)
#endif

#ifndef VTKFILTERSDSP_DEPRECATED_EXPORT
#  define VTKFILTERSDSP_DEPRECATED_EXPORT VTKFILTERSDSP_EXPORT VTKFILTERSDSP_DEPRECATED
#endif

#ifndef VTKFILTERSDSP_DEPRECATED_NO_EXPORT
#  define VTKFILTERSDSP_DEPRECATED_NO_EXPORT VTKFILTERSDSP_NO_EXPORT VTKFILTERSDSP_DEPRECATED
#endif

#if 0 /* DEFINE_NO_DEPRECATED */
#  ifndef VTKFILTERSDSP_NO_DEPRECATED
#    define VTKFILTERSDSP_NO_DEPRECATED
#  endif
#endif

/* VTK-HeaderTest-Exclude: vtkFiltersDSPModule.h */

/* Include ABI Namespace */
#include "vtkABINamespace.h"

#endif /* VTKFILTERSDSP_EXPORT_H */
