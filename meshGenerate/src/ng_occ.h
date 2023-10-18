#pragma once


#include <iostream>
#include <climits>

#include "TopTools_IndexedMapOfShape.hxx"
#include "TopoDS.hxx"
#include "TopoDS_Face.hxx"
#include "TopoDS_Shape.hxx"
#include "GProp_GProps.hxx"
#include "BRepGProp.hxx"

using namespace std;

namespace nglib {
#include <nglib.h>
}

#include "Mesh.h"
#include "Result.h"



int ng_occ(std::string pathDir, std::string resDir);

void check_Mesh(Mesh* mesh, Result* res);
