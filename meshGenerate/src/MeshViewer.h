#pragma once
#include <vector>
#include <iostream>
#include <unordered_map>

#include "Mesh.h"

#include<vtkSmartPointer.h>
#include<vtkConeSource.h>
#include<vtkPolyDataMapper.h>
#include<vtkActor.h>
#include<vtkRenderer.h>
#include<vtkRenderWindow.h>
#include<vtkRenderWindowInteractor.h>
#include<vtkInteractorStyleTrackballCamera.h>

#include <vtkVertexGlyphFilter.h>
#include <vtkProperty.h>
 
#include "vtkAutoInit.h" 
VTK_MODULE_INIT(vtkRenderingOpenGL2);
VTK_MODULE_INIT(vtkInteractionStyle);
VTK_MODULE_INIT(vtkRenderingFreeType)

#define vtkSptr vtkSmartPointer
#define vtkSptrNew(var, Type) vtkSptr<Type> var = vtkSptr<Type>::New()




class MeshViewer
{
private:
    std::unordered_map<Mesh*, vtkSptr<vtkActor>> m_Meshes;
	//Mesh* m_Mesh;
	//TODO: Result

	vtkSptr<vtkRenderer> m_Renderer;
	vtkSptr<vtkRenderWindow> m_RenWin;
	vtkSptr<vtkRenderWindowInteractor> m_RenInteractor;

	vtkSptr<vtkActor> m_Actors;
public:
	//MeshViewer(Mesh* mesh);
	MeshViewer();

    void Insert_Mesh(Mesh* mesh);
    void Insert_Mesh(Mesh* mesh, float *color);
	void View();
};
