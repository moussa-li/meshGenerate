/*=========================================================================

  Program:   Visualization Toolkit
  Module:    vtkAnnotatedCubeActor.h

  Copyright (c) Ken Martin, Will Schroeder, Bill Lorensen
  All rights reserved.
  See Copyright.txt or http://www.kitware.com/Copyright.htm for details.

     This software is distributed WITHOUT ANY WARRANTY; without even
     the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
     PURPOSE.  See the above copyright notice for more information.

=========================================================================*/
/**
 * @class   vtkAnnotatedCubeActor
 * @brief   a 3D cube with face labels
 *
 * vtkAnnotatedCubeActor is a hybrid 3D actor used to represent an anatomical
 * orientation marker in a scene.  The class consists of a 3D unit cube centered
 * on the origin with each face labelled in correspondence to a particular
 * coordinate direction.  For example, with Cartesian directions, the user
 * defined text labels could be: +X, -X, +Y, -Y, +Z, -Z, while for anatomical
 * directions: A, P, L, R, S, I.  Text is automatically centered on each cube
 * face and is not restriceted to single characters. In addition to or in
 * replace of a solid text label representation, the outline edges of the labels
 * can be displayed.  The individual properties of the cube, face labels
 * and text outlines can be manipulated as can their visibility.
 *
 * @warning
 * vtkAnnotatedCubeActor is primarily intended for use with
 * vtkOrientationMarkerWidget. The cube face text is generated by vtkVectorText
 * and therefore the font attributes are restricted.
 *
 * @sa
 * vtkAxesActor vtkOrientationMarkerWidget vtkVectorText
 */

#ifndef vtkAnnotatedCubeActor_h
#define vtkAnnotatedCubeActor_h

#include "vtkProp3D.h"
#include "vtkRenderingAnnotationModule.h" // For export macro

VTK_ABI_NAMESPACE_BEGIN
class vtkActor;
class vtkAppendPolyData;
class vtkAssembly;
class vtkCubeSource;
class vtkFeatureEdges;
class vtkPropCollection;
class vtkProperty;
class vtkRenderer;
class vtkTransform;
class vtkTransformFilter;
class vtkVectorText;

class VTKRENDERINGANNOTATION_EXPORT vtkAnnotatedCubeActor : public vtkProp3D
{
public:
  static vtkAnnotatedCubeActor* New();
  vtkTypeMacro(vtkAnnotatedCubeActor, vtkProp3D);
  void PrintSelf(ostream& os, vtkIndent indent) override;

  /**
   * For some exporters and other other operations we must be
   * able to collect all the actors or volumes. These methods
   * are used in that process.
   */
  void GetActors(vtkPropCollection*) override;

  ///@{
  /**
   * Support the standard render methods.
   */
  int RenderOpaqueGeometry(vtkViewport* viewport) override;
  int RenderTranslucentPolygonalGeometry(vtkViewport* viewport) override;
  ///@}

  /**
   * Does this prop have some translucent polygonal geometry?
   */
  vtkTypeBool HasTranslucentPolygonalGeometry() override;

  /**
   * Shallow copy of an axes actor. Overloads the virtual vtkProp method.
   */
  void ShallowCopy(vtkProp* prop) override;

  /**
   * Release any graphics resources that are being consumed by this actor.
   * The parameter window could be used to determine which graphic
   * resources to release.
   */
  void ReleaseGraphicsResources(vtkWindow*) override;

  ///@{
  /**
   * Get the bounds for this Actor as (Xmin,Xmax,Ymin,Ymax,Zmin,Zmax). (The
   * method GetBounds(double bounds[6]) is available from the superclass.)
   */
  void GetBounds(double bounds[6]);
  double* GetBounds() VTK_SIZEHINT(6) override;
  ///@}

  /**
   * Get the actors mtime plus consider its properties and texture if set.
   */
  vtkMTimeType GetMTime() override;

  ///@{
  /**
   * Set/Get the scale factor for the face text
   */
  void SetFaceTextScale(double);
  vtkGetMacro(FaceTextScale, double);
  ///@}

  ///@{
  /**
   * Get the individual face text properties.
   */
  vtkProperty* GetXPlusFaceProperty();
  vtkProperty* GetXMinusFaceProperty();
  vtkProperty* GetYPlusFaceProperty();
  vtkProperty* GetYMinusFaceProperty();
  vtkProperty* GetZPlusFaceProperty();
  vtkProperty* GetZMinusFaceProperty();
  ///@}

  /**
   * Get the cube properties.
   */
  vtkProperty* GetCubeProperty();

  /**
   * Get the text edges properties.
   */
  vtkProperty* GetTextEdgesProperty();

  ///@{
  /**
   * Set/get the face text.
   */
  vtkSetStringMacro(XPlusFaceText);
  vtkGetStringMacro(XPlusFaceText);
  vtkSetStringMacro(XMinusFaceText);
  vtkGetStringMacro(XMinusFaceText);
  vtkSetStringMacro(YPlusFaceText);
  vtkGetStringMacro(YPlusFaceText);
  vtkSetStringMacro(YMinusFaceText);
  vtkGetStringMacro(YMinusFaceText);
  vtkSetStringMacro(ZPlusFaceText);
  vtkGetStringMacro(ZPlusFaceText);
  vtkSetStringMacro(ZMinusFaceText);
  vtkGetStringMacro(ZMinusFaceText);
  ///@}

  ///@{
  /**
   * Enable/disable drawing the vector text edges.
   */
  void SetTextEdgesVisibility(int);
  int GetTextEdgesVisibility();
  ///@}

  ///@{
  /**
   * Enable/disable drawing the cube.
   */
  void SetCubeVisibility(int);
  int GetCubeVisibility();
  ///@}

  ///@{
  /**
   * Enable/disable drawing the vector text.
   */
  void SetFaceTextVisibility(int);
  int GetFaceTextVisibility();
  ///@}

  ///@{
  /**
   * Augment individual face text orientations.
   */
  vtkSetMacro(XFaceTextRotation, double);
  vtkGetMacro(XFaceTextRotation, double);
  vtkSetMacro(YFaceTextRotation, double);
  vtkGetMacro(YFaceTextRotation, double);
  vtkSetMacro(ZFaceTextRotation, double);
  vtkGetMacro(ZFaceTextRotation, double);
  ///@}

  /**
   * Get the assembly so that user supplied transforms can be applied
   */
  vtkAssembly* GetAssembly() { return this->Assembly; }

protected:
  vtkAnnotatedCubeActor();
  ~vtkAnnotatedCubeActor() override;

  vtkCubeSource* CubeSource;
  vtkActor* CubeActor;

  vtkAppendPolyData* AppendTextEdges;
  vtkFeatureEdges* ExtractTextEdges;
  vtkActor* TextEdgesActor;

  void UpdateProps();

  char* XPlusFaceText;
  char* XMinusFaceText;
  char* YPlusFaceText;
  char* YMinusFaceText;
  char* ZPlusFaceText;
  char* ZMinusFaceText;

  double FaceTextScale;

  double XFaceTextRotation;
  double YFaceTextRotation;
  double ZFaceTextRotation;

  vtkVectorText* XPlusFaceVectorText;
  vtkVectorText* XMinusFaceVectorText;
  vtkVectorText* YPlusFaceVectorText;
  vtkVectorText* YMinusFaceVectorText;
  vtkVectorText* ZPlusFaceVectorText;
  vtkVectorText* ZMinusFaceVectorText;

  vtkActor* XPlusFaceActor;
  vtkActor* XMinusFaceActor;
  vtkActor* YPlusFaceActor;
  vtkActor* YMinusFaceActor;
  vtkActor* ZPlusFaceActor;
  vtkActor* ZMinusFaceActor;

  vtkTransformFilter* InternalTransformFilter;
  vtkTransform* InternalTransform;

  vtkAssembly* Assembly;

private:
  vtkAnnotatedCubeActor(const vtkAnnotatedCubeActor&) = delete;
  void operator=(const vtkAnnotatedCubeActor&) = delete;
};

VTK_ABI_NAMESPACE_END
#endif