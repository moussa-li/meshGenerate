#include "MeshViewer.h"
#include "Mesh.h"

#include "ng_occ.h"

#include <iostream>
#include <algorithm>
#include <filesystem>


int main(int argc, char **argv)
{

    Mesh *mesh = new Mesh(1.f);
    mesh->Read("geometry/square.geo");
    mesh->GenerateSurfaceMesh();
    mesh->Write("mesh/square.vol");

	MeshViewer viewer;

    viewer.Insert_Mesh(mesh);

	viewer.View();
    
    return 0;

}