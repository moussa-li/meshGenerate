#ifdef MAIN
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

	///*Mesh *mesh = new Mesh;
	//mesh->Read("mesh/VisualResults/wholewall3/volfined0.vol");

 //   Mesh *mesh1 = new Mesh;
	//mesh->Read("mesh/VisualResults/wholewall3/volfined0.vol");
	//mesh1->Read("mesh/volfined1.vol");


 //   Mesh *mesh2 = new Mesh;
	//mesh->Read("mesh/VisualResults/wholewall3/volfined0.vol");
	//mesh2->Read("mesh/volfined2.vol");


 //   Mesh *mesh3 = new Mesh;
	//mesh->Read("mesh/VisualResults/wholewall3/volfined0.vol");*/


	//////mesh->Read("merge_mesh.vol");
 ////   //ng_occ(argv[1],argv[2]);

 ////   Result res(mesh->GetPointsCompress().size());
 ////   res.Load("case3.dat");


 ////   check_Mesh(mesh, &res);

 ////   //Mesh *mesh2 = new Mesh;

	//////mesh2->Read("C:\\Users\\moussa\\Downloads\\body_r0_l3_16_max10.0_min0.0\\body_r0_l3_16_max10.0_min0.0\\volfined\\volfined1.vol");


	MeshViewer viewer;

 //   //viewer.Insert_Mesh(mesh);
 //   /*float color[3] = { 1.f,0,0 };
 //   float color2[3] = { 1.f,1.f,0 };
 //   float color3[3] = { 1.f,1.f,1.f };
 //   float color4[3] = { 0.f,1.f,0 };*/
    for (int i = 0; i < 8; i++)
    {
        float color[3] = { ((i+1) & 1)?0.5:1,((i+1) & 2)?0.5:1,((i+1) & 4)?0.5:1 };
        viewer.Insert_Mesh(&meshes[i],color);
    }
 //   //viewer.Insert_Mesh(mesh1,color2);
 //   //viewer.Insert_Mesh(mesh2,color3);
 //   //viewer.Insert_Mesh(mesh3,color4);
 ////   //viewer.Insert_Mesh(mesh2,color2);

	viewer.View();

    


   //test_generate("refinedSurfmesh886.vol");

    //check_Mesh("beam1.vtu");

    //ng_occ("geometry/beam1.step", "");

    return 0;

}
#endif