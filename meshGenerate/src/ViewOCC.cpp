//#include "MeshViewer.h"
//#include "Mesh.h"
//
//int main()
//{
//
//	Mesh *mesh = new Mesh;
//
//	mesh->Read("E:\\研究资料\\超算生成网格\\refinedSurfmesh3.vol");
//
//	MeshViewer viewer(mesh);
//
//	viewer.View();
//	return 0;
//}
#ifdef ViewOCC

#include "MakeBottle.h"
#include <STEPControl_Reader.hxx>
#include <Standard_Integer.hxx>
#include <TopoDS_Shape.hxx>
#include <IFSelect_ReturnStatus.hxx>
#include <IFSelect_PrintCount.hxx>
#include <IVtkTools_ShapeDataSource.hxx>
#include <IVtkOCC_ShapeMesher.hxx>
#include <IVtkTools_DisplayModeFilter.hxx>
#include <vtkType.h>
#include <vtkAutoInit.h>
#include <vtkRenderWindow.h>
#include <vtkActor.h>
#include <vtkRenderer.h>
#include <vtkRenderWindowInteractor.h>
#include <vtkPolyDataMapper.h>
#include <vtkInteractorStyleTrackballCamera.h>

VTK_MODULE_INIT(vtkRenderingOpenGL2)
VTK_MODULE_INIT(vtkInteractionStyle)

int ViewOCC(int argc, char **argv)
{

    //Handle(TopoDS_Shape) h_int = new TopoDS_Shape();
  //Handle(Geom_CylindricalSurface) aCyl1 = new Geom_CylindricalSurface(neckAx2, myNeckRadius * 0.99);
    //std::cout << h_int->IsNull() << std::endl;

    STEPControl_Reader reader;
    IFSelect_ReturnStatus stat = reader.ReadFile(argv[1]);
    IFSelect_PrintCount mode = IFSelect_CountByItem;
    Standard_Integer NbRoots = reader.NbRootsForTransfer();
    Standard_Integer num = reader.TransferRoots();
    Standard_Integer NbTrans = reader.TransferRoots();
    //TopoDS_Shape result = reader.OneShape();
    const Standard_Real myWidth = 70;
    const Standard_Real myHeight = 50;
    const Standard_Real myThickness = 30;
    TopoDS_Shape result = MakeBottle(myWidth, myHeight, myThickness);

    // TopoDS_Shape shape = reader.Shape();

    vtkNew<IVtkTools_ShapeDataSource> occSource;
    //occSource->SetShape(new IVtkOCC_Shape(shape));
    occSource->SetShape(new IVtkOCC_Shape(result));

    vtkNew<IVtkTools_DisplayModeFilter> filter;
    filter->AddInputConnection(occSource->GetOutputPort());
    filter->SetDisplayMode(DM_Shading);

    vtkNew<vtkPolyDataMapper> mapper;
    mapper->SetInputConnection(filter->GetOutputPort());

    vtkNew<vtkActor> actor;
    actor->SetMapper(mapper);

    vtkNew<vtkRenderer> ren;
    ren->AddActor(actor);

    vtkNew<vtkRenderWindow> renWin;
    renWin->AddRenderer(ren);
    renWin->SetSize(960, 800);

    vtkNew<vtkInteractorStyleTrackballCamera> istyle;
    vtkNew<vtkRenderWindowInteractor> iren;

    iren->SetRenderWindow(renWin);
    iren->SetInteractorStyle(istyle);

    renWin->Render();
    iren->Start();

    return 0;
}

#endif