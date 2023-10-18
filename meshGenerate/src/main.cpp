#ifdef MAIN
#include "MeshViewer.h"
#include "Mesh.h"

#include "ng_occ.h"

int main(int argc, char **argv)
{
   if (argc < 2)
   {
      cerr << "use: ng_occ <src_step>" << endl;
      return 1;
   }



	Mesh *mesh = new Mesh;

	//mesh->Read("merge_mesh.vol");
    //ng_occ(argv[1],argv[2]);

    //Result res(mesh->GetPoints().size());
    //res.Load("case.dat");

	mesh->Read("C:\\Users\\moussa\\Downloads\\body_r0_l3_16_max10.0_min0.0\\body_r0_l3_16_max10.0_min0.0\\volfined\\volfined0.vol");

    Mesh *mesh2 = new Mesh;

	mesh2->Read("C:\\Users\\moussa\\Downloads\\body_r0_l3_16_max10.0_min0.0\\body_r0_l3_16_max10.0_min0.0\\volfined\\volfined1.vol");


	MeshViewer viewer;

    //viewer.Insert_Mesh(mesh);
    float color[3] = { 1.f,0,0 };
    float color2[3] = { 1.f,1.f,0 };
    viewer.Insert_Mesh(mesh,color);
    viewer.Insert_Mesh(mesh2,color2);

	viewer.View();

    delete mesh;
    delete mesh2;
	return 0;
}
#endif