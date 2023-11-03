#include "ng_occ.h"
#include <algorithm>

void test_generate(std::string pathDir)
{
    using namespace nglib;
    
    Ng_Mesh* mesh;
    Ng_Init();
    mesh = Ng_LoadMesh(pathDir.c_str());
    
    Ng_Meshing_Parameters mp;
    mp.fineness = 1;

    Ng_GenerateVolumeMesh(mesh, &mp);
}

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
   //double test = NG_GetH(occ_mesh, y);
 
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
   Ng_SaveMesh(occ_mesh,"test_occ.vol");

/*
Result res(196041);
res.Load("case.dat");
*/
   return 0;
}

void check_Mesh(std::string pathDir)
{
    // 指定你的VTU文件的路径
    const char* vtu_file_path = pathDir.c_str();

    vtkSmartPointer<vtkXMLUnstructuredGridReader> reader = vtkSmartPointer<vtkXMLUnstructuredGridReader>::New();
    reader->SetFileName(vtu_file_path);
    reader->Update();

    vtkSmartPointer<vtkUnstructuredGrid> unstructuredGrid = reader->GetOutput();

    // 获取 von Mises 应力数据
    vtkSmartPointer<vtkDoubleArray> vonMisesData = vtkDoubleArray::SafeDownCast(unstructuredGrid->GetPointData()->GetArray("vonmises"));

    if (vonMisesData) {
        vector<int> res(5);

        int numCells = unstructuredGrid->GetNumberOfCells();
        for (int i = 0; i < numCells; i++)
        {
            vtkCell* cell = unstructuredGrid->GetCell(i);
            int numPoint = cell->GetNumberOfPoints();

            double max_value = INT_MIN, min_value = INT_MAX;

            for (int j = 0; j < numPoint; j++)
            {
                int PointId = cell->GetPointId(j);
                double value = vonMisesData->GetValue(PointId);
                max_value = std::max(max_value, value);
                min_value = std::min(min_value, value);
                //std::cout << vonMisesData->GetValue(PointId) << " ";
            }
            if (min_value == 0)
                continue;
            double rate = max_value / min_value;
            if (rate <= 2)
                res[0]++;
            else if (rate > 2 && rate <= 5)
                res[1]++;
            else if (rate > 5 && rate <= 10)
                res[2]++;
            else if (rate > 1000 && rate <= 10000)
                res[3]++;
            else res[4]++;
                        //std::cout << std::endl;

        }
        for (int i = 0; i < 5; i++)
                std::cout << res[i] << std::endl;

        /*int numPoints = vonMisesData->GetNumberOfTuples();
        std::cout << "von Mises Stress Data:" << std::endl;
        for (int i = 0; i < numPoints; i++) {
            double value = vonMisesData->GetValue(i);
            std::cout << "Value at Point " << i << ": " << value << std::endl;
        }*/
    } else {
        std::cerr << "von Mises stress data not found in the VTU file." << std::endl;
        return ;
    }

    return;

}
