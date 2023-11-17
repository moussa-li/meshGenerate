#ifdef showMesh
#include "MeshViewer.h"
#include "Mesh.h"

#include "ng_occ.h"

#include <iostream>
#include <algorithm>
#include <filesystem>


int main(int argc, char **argv)
{
 //  if (argc < 2)
 //  {
 //     cerr << "use: ng_occ <src_step>" << endl;
 //     return 1;
 //  }

    vector<Mesh> meshes;
    for (int i = 0; i < 8; i++)
    {
        Mesh mesh;
        
        std::filesystem::path inputDir = "mesh/VisualResultsCroase/zhengfangti/volfined" + to_string(i) + ".vol";
        mesh.Read(inputDir);
        meshes.push_back(mesh);

    }

	MeshViewer viewer;

 
    for (int i = 0; i < 8; i++)
    {
        float color[3] = { ((i+1) & 1)?0.5:1,((i+1) & 2)?0.5:1,((i+1) & 4)?0.5:1 };
        viewer.Insert_Mesh(&meshes[i],color);
    }

	viewer.View();

    
    return 0;

}
#endif