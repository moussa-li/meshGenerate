#pragma once


#include <iostream>
#include <climits>

#include "TopTools_IndexedMapOfShape.hxx"
#include "TopoDS.hxx"
#include "TopoDS_Face.hxx"
#include "TopoDS_Shape.hxx"
#include "GProp_GProps.hxx"
#include "BRepGProp.hxx"

#include <vtkSmartPointer.h>
#include <vtkXMLUnstructuredGridReader.h>
#include <vtkUnstructuredGrid.h>
#include <vtkCellData.h>
#include <vtkPointData.h>
#include <vtkDoubleArray.h>



using namespace std;

namespace nglib {
#include <nglib.h>
}

#include "Mesh.h"
#include "Result.h"

void test_generate(std::string pathDir);

int ng_occ(std::string pathDir, std::string resDir);

void check_Mesh(std::string pathDir);
