#include <iostream>
#include <fstream>

using namespace std;

namespace nglib {
#include <nglib.h>
}

int main (int argc, char ** argv)
{
  using namespace nglib;

  cout << "Netgen Testing" << endl;

  if (argc < 2)
    {
      cerr << "use: ng_vol filename" << endl;
      return 1;
    }

  //cout << printmessage_importance << endl;

  Ng_Mesh * mesh;

  nglib::Ng_Init();

  // creates mesh structure
  //mesh = nglib::Ng_NewMesh ();





  int i, np, nse, ne;
  double point[3];
  int trig[3], tet[4];

  mesh = nglib::Ng_LoadMesh(argv[1]);

  // reads surface mesh from file
 /* ifstream in(argv[1]);

  in >> np;
  cout << "Reading " << np  << " points..."; cout.flush();
  for (i = 1; i <= np; i++)
    {
      in >> point[0] >> point[1] >> point[2];
      nglib::Ng_AddPoint (mesh, point);
    }
  cout << "done" << endl;

  in >> nse;
  cout << "Reading " << nse  << " faces..."; cout.flush();
  for (i = 1; i <= nse; i++)
    {
      in >> trig[0] >> trig[1] >> trig[2];
      nglib::Ng_AddSurfaceElement (mesh, nglib::NG_TRIG, trig);
    }*/
  cout << "done" << endl;


  // generate volume mesh
  nglib::Ng_Meshing_Parameters mp;
  mp.maxh = 1000;
  mp.fineness = 1;
  mp.second_order = 0;

  cout << "start meshing" << endl;
  nglib::Ng_GenerateVolumeMesh(mesh, &mp);
  cout << "meshing done" << endl;

  // volume mesh output
  //np = nglib::Ng_GetNP(mesh);
  //cout << "Points: " << np << endl;

  //for (i = 1; i <= np; i++)
  //  {
  //    nglib:: Ng_GetPoint(mesh, i, point);
  //    cout << i << ": " << point[0] << " " << point[1] << " " << point[2] << endl;
  //  }

  //ne = nglib::Ng_GetNE(mesh);
  //cout << "Elements: " << ne << endl;
  //for (i = 1; i <= ne; i++)
  //  {
  //    nglib::Ng_GetVolumeElement (mesh, i, tet);
  //    cout << i << ": " << tet[0] << " " << tet[1] 
	 //  << " " << tet[2] << " " << tet[3] << endl;
  //  }

  nglib::Ng_SaveMesh(mesh,"test.vol");


  return 0;
}

