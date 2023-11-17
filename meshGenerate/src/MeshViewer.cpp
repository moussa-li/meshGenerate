#include "MeshViewer.h"


MeshViewer::MeshViewer() {
	//‰÷»æ
	m_Renderer = vtkSptr<vtkRenderer>::New();
	m_Renderer->SetBackground(1.0, 1.0, 1.0);
	
	//‰÷»æ¥∞ø⁄
	m_RenWin = vtkSptr<vtkRenderWindow>::New();
	m_RenWin->SetSize(600, 400);
	m_RenWin->AddRenderer(m_Renderer);

	//‰÷»æΩªª•
	m_RenInteractor = vtkSptr<vtkRenderWindowInteractor>::New();
	m_RenInteractor->SetRenderWindow(m_RenWin);
	vtkSptrNew(style, vtkInteractorStyleTrackballCamera);
	m_RenInteractor->SetInteractorStyle(style);

    };

//MeshViewer::MeshViewer() : m_Mesh(nullptr) {
//	//‰÷»æ
//	m_Renderer = vtkSptr<vtkRenderer>::New();
//	m_Renderer->SetBackground(1.0, 1.0, 1.0);
//	
//	//‰÷»æ¥∞ø⁄
//	m_RenWin = vtkSptr<vtkRenderWindow>::New();
//	m_RenWin->SetSize(600, 400);
//	m_RenWin->AddRenderer(m_Renderer);
//
//	//‰÷»æΩªª•
//	m_RenInteractor = vtkSptr<vtkRenderWindowInteractor>::New();
//	m_RenInteractor->SetRenderWindow(m_RenWin);
//
//	m_Actors = vtkSptr<vtkActor>::New();
//
//	vtkSptrNew(points, vtkPoints);
//
//	//≤‚ ‘”√µ„
//	for (int i = 0; i < 10; i++) {
//		points->InsertPoint(i, i, i, 0);
//	}
//
//	vtkSptrNew(vesselPointsPolyData, vtkPolyData);
//	vesselPointsPolyData->SetPoints(points);
//
//	vtkSptrNew(vertexGlyphFilter, vtkVertexGlyphFilter);
//	vertexGlyphFilter->AddInputData(vesselPointsPolyData);
//	vertexGlyphFilter->Update();
//
//	vtkSptrNew(pointsMapper, vtkPolyDataMapper);
//	pointsMapper->SetInputConnection(vertexGlyphFilter->GetOutputPort());
//
//	m_Actors->SetMapper(pointsMapper);
//	m_Actors->GetProperty()->SetColor(0.0, 0.1, 1.0);
//	m_Actors->GetProperty()->SetAmbient(0.5);
//	m_Actors->GetProperty()->SetPointSize(0.2);
//
//	m_Renderer->AddActor(m_Actors);
//};


void MeshViewer::Insert_Mesh(Mesh* mesh)
{
    m_Actors = vtkSptr<vtkActor>::New();

	vtkSptrNew(points, vtkPoints);

	std::vector<Point> MeshPoints = mesh->GetPoints();
	/*for (auto it = MeshPoints.begin(); it != MeshPoints.end(); ++it)
	{
		points->InsertPoint((it)->Get_Id(), (it)->Get_x(), (it)->Get_y(), (it)->Get_z());
	}*/
    for (int i = 0; i < MeshPoints.size(); i++)
    {
		points->InsertPoint(i, MeshPoints[i].Get_x(), MeshPoints[i].Get_y(), MeshPoints[i].Get_z());
    }


	vtkSptrNew(cells, vtkCellArray);
	std::vector<Surface> MeshSurfaces = mesh->GetSurfaces();
    for (int MeshSurfaceIndex = 0; MeshSurfaceIndex < MeshSurfaces.size(); MeshSurfaceIndex++)
    {

		std::vector<size_t> PointIds = MeshSurfaces[MeshSurfaceIndex].Get_PointIds();
		vtkIdType *pointIds = new vtkIdType[MeshSurfaces[MeshSurfaceIndex].Get_PointNumber()];
        for(long long i = 0; i < MeshSurfaces[MeshSurfaceIndex].Get_PointNumber(); i++)
		    pointIds[i] = PointIds[i];
		cells->InsertNextCell(MeshSurfaces[MeshSurfaceIndex].Get_PointNumber(), pointIds);
    	delete[] pointIds;
    }
	//for (auto it = MeshSurfaces.begin(); it != MeshSurfaces.end(); ++it)
	//{
	//	std::vector<size_t> PointIds = it->Get_PointIds();
	//	vtkIdType *pointIds = new vtkIdType[it->Get_PointNumber()];
	//	for(long long i = 0; i < it->Get_PointNumber(); i++)
	//		pointIds[i] = PointIds[i]-1;
	//		//pointIds[i] = PointIds[i];
	//	cells->InsertNextCell(it->Get_PointNumber(), pointIds);
	//	delete[] pointIds;
	//}
	vtkSptrNew(vesselPointsPolyData, vtkPolyData);
	vesselPointsPolyData->SetPoints(points);
	vesselPointsPolyData->SetPolys(cells);

	//vtkSptrNew(vertexGlyphFilter, vtkVertexGlyphFilter);
	//vertexGlyphFilter->AddInputData(vesselPointsPolyData);
	//vertexGlyphFilter->Update();

	vtkSptrNew(Mapper, vtkPolyDataMapper);
	//pointsMapper->SetInputConnection(vertexGlyphFilter->GetOutputPort());
	Mapper->SetInputData(vesselPointsPolyData);

	m_Actors->SetMapper(Mapper);
	//m_Actors->GetProperty()->SetRepresentationToWireframe();
    m_Actors->GetProperty()->EdgeVisibilityOn();
    m_Actors->GetProperty()->SetOpacity(1.0);
	//m_Actors->GetProperty()->SetColor(0, 1, 0);
	m_Actors->GetProperty()->SetLineWidth(1);
	m_Actors->GetProperty()->SetColor(0.0, 1.0, 0.0);
	//m_Actors->GetProperty()->SetAmbient(0.5);
	//m_Actors->GetProperty()->SetPointSize(1);

	m_Renderer->AddActor(m_Actors);

    m_Meshes[mesh] = m_Actors;

}

void MeshViewer::Insert_Mesh(Mesh* mesh, float* color)
{
    m_Actors = vtkSptr<vtkActor>::New();

	vtkSptrNew(points, vtkPoints);

	std::vector<Point> MeshPoints = mesh->GetPoints();
	for (auto it = MeshPoints.begin(); it != MeshPoints.end(); ++it)
	{
		points->InsertPoint((it)->Get_Id(), (it)->Get_x(), (it)->Get_y(), (it)->Get_z());
	}


	vtkSptrNew(cells, vtkCellArray);
	std::vector<Surface> MeshSurfaces = mesh->GetSurfaces();
	for (auto it = MeshSurfaces.begin(); it != MeshSurfaces.end(); ++it)
	{
		std::vector<size_t> PointIds = it->Get_PointIds();
		vtkIdType *pointIds = new vtkIdType[it->Get_PointNumber()];
		for(long long i = 0; i < it->Get_PointNumber(); i++)
			pointIds[i] = PointIds[i]-1;
			//pointIds[i] = PointIds[i];
		cells->InsertNextCell(it->Get_PointNumber(), pointIds);
		delete[] pointIds;
	}
	vtkSptrNew(vesselPointsPolyData, vtkPolyData);
	vesselPointsPolyData->SetPoints(points);
	vesselPointsPolyData->SetPolys(cells);

	//vtkSptrNew(vertexGlyphFilter, vtkVertexGlyphFilter);
	//vertexGlyphFilter->AddInputData(vesselPointsPolyData);
	//vertexGlyphFilter->Update();

	vtkSptrNew(Mapper, vtkPolyDataMapper);
	//pointsMapper->SetInputConnection(vertexGlyphFilter->GetOutputPort());
	Mapper->SetInputData(vesselPointsPolyData);

	m_Actors->SetMapper(Mapper);
	//m_Actors->GetProperty()->SetRepresentationToWireframe();
    m_Actors->GetProperty()->EdgeVisibilityOn();
    m_Actors->GetProperty()->SetOpacity(1.0);
	//m_Actors->GetProperty()->SetColor(0, 1, 0);
	m_Actors->GetProperty()->SetLineWidth(1);
	m_Actors->GetProperty()->SetColor(color[0],color[1],color[2]);
	//m_Actors->GetProperty()->SetAmbient(0.5);
	//m_Actors->GetProperty()->SetPointSize(1);

	m_Renderer->AddActor(m_Actors);

    m_Meshes[mesh] = m_Actors;


}

void MeshViewer::View()
{

	m_RenInteractor->Initialize();
	m_RenInteractor->Start();
}