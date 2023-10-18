#include "ng_occ.h"

int ng_occ(std::string pathDir,std::string resDir)
{
    
   using namespace nglib;
   
   cout << "Netgen NgLib - OpenCascade Test Case" << endl;
   
   /*if (argc != 2)
   {
      cerr << "use: ng_occ <src_step>" << endl;
      return 1;
   }*/
   
   // Define pointer to OCC Geometry
   Ng_OCC_Geometry *occ_geom;
   
   Ng_Mesh *occ_mesh;
   
   Ng_Meshing_Parameters mp;
   
   TopTools_IndexedMapOfShape FMap;
   
   Ng_OCC_TopTools_IndexedMapOfShape *occ_fmap = (Ng_OCC_TopTools_IndexedMapOfShape*)&FMap;
   
   // Result of Netgen Operations
   Ng_Result ng_res;

   // Initialise the Netgen Core library
   Ng_Init();

   // Read in the OCC File
   occ_geom = Ng_OCC_Load_STEP(pathDir.c_str());
   if(!occ_geom)
   {
      cout << "Error reading in STEP File: " << pathDir << endl;
	  return 1;
   }
   cout << "Successfully loaded STEP File: " << pathDir << endl;

   occ_mesh = Ng_NewMesh();
   
   ng_res = Ng_OCC_GetFMap(occ_geom,occ_fmap);

   cout << "ng_res = " << ng_res << endl;
	  
   if(!FMap.Extent())
   {
      cout << "Error retrieving Face map...." << endl;
	  return 1;
   }

   cout << "Successfully extracted the Face Map....:" << FMap.Extent() << endl;
   
   for(int i = 1; i <= FMap.Extent(); i++)
   {
      TopoDS_Face OCCface;
	  OCCface = TopoDS::Face(FMap.FindKey(i));
	  
	  GProp_GProps faceProps;
	  BRepGProp::SurfaceProperties(OCCface,faceProps);
	  
      cout << "Index: " << i 
	       << " :: Area: " << faceProps.Mass() 
		   << " :: Hash: " << OCCface.HashCode(1e+6) 
		   << endl;
   }	 
   
   mp.uselocalh = 1;
   mp.elementsperedge = 2.0;
   mp.elementspercurve = 2.0;
   mp.maxh = 10.0;
   mp.grading = 0.2;   
   mp.closeedgeenable = 0;
   mp.closeedgefact = 1.0;
   mp.optsurfmeshenable = 1;
   
   
   cout << "Setting Local Mesh size....." << endl;
   cout << "OCC Mesh Pointer before call = " << occ_mesh << endl;
   Ng_OCC_SetLocalMeshSize(occ_geom, occ_mesh, &mp);
   cout << "Local Mesh size successfully set....." << endl;
      cout << "OCC Mesh Pointer after call = " << occ_mesh << endl;

   
   cout << "Creating Edge Mesh....." << endl;
   ng_res = Ng_OCC_GenerateEdgeMesh(occ_geom, occ_mesh, &mp);
   if(ng_res != NG_OK)
   {
      Ng_DeleteMesh(occ_mesh);
	  cout << "Error creating Edge Mesh.... Aborting!!" << endl;
	  return 1;
   }
   else
   {
      cout << "Edge Mesh successfully created....." << endl;
	  cout << "Number of points = " << Ng_GetNP(occ_mesh) << endl;
   }

   cout << "Creating Surface Mesh....." << endl;

   double x[3] = {0,0,0};
   double y[3] = {1,0,0};
   //Ng_GetPoint(occ_mesh, 100, x);
   //double test = NG_GetH(occ_mesh, x);
   Ng_RestrictMeshSizePoint(occ_mesh, x, 2);
   double test = NG_GetH(occ_mesh, y);
 
   ng_res = Ng_OCC_GenerateSurfaceMesh(occ_geom, occ_mesh, &mp);
   if(ng_res != NG_OK)
   {
      Ng_DeleteMesh(occ_mesh);
	  cout << "Error creating Surface Mesh..... Aborting!!" << endl;
	  return 1;
   }
   else
   {
      cout << "Surface Mesh successfully created....." << endl;
	  cout << "Number of points = " << Ng_GetNP(occ_mesh) << endl;
	  cout << "Number of surface elements = " << Ng_GetNSE(occ_mesh) << endl;
   }
   
   

   cout << "Creating Volume Mesh....." << endl;
   
   ng_res = Ng_GenerateVolumeMesh(occ_mesh, &mp);
   
   cout << "Volume Mesh successfully created....." << endl;
   cout << "Number of points = " << Ng_GetNP(occ_mesh) << endl;
   cout << "Number of volume elements = " << Ng_GetNE(occ_mesh) << endl;
   
   cout << "Saving Mesh as VOL file....." << endl;
   //Ng_SaveMesh(occ_mesh,"test_occ.vol");

/*
Result res(196041);
res.Load("case.dat");
*/
   return 0;
}

void check_Mesh(Mesh* mesh, Result* res)
{

}
