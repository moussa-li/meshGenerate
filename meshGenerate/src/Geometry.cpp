#include <fstream>
#include <iostream>
#include <filesystem>
#include <assert.h>
#include <vector>
#include <string>


#include "Geometry.h"


void Geometry::InsertPoint(Point p)
{
    m_Points.push_back(p);
}

void Geometry::InsertEdge(Edge e)
{
    auto v = e.GetVerteices();
    if (v.first >= m_Points.size() || v.second >= m_Points.size())
        std::cout << "Insert Vertices index out of size" << std::endl;
    else
        m_Edges.push_back(e);
}

void Geometry::InsertFace(Face f)
{
    m_Faces.push_back(f);
}

void Geometry::Read(std::string FilePath)
{
    std::fstream file;
    file.open(FilePath, std::ios::in);
    if (file.is_open() == 0)
    {
        std::cout << "FileName : [" << FilePath << "]is not open!" << std::endl;
        assert(0);
    }
	char buffer[1024] = "";
	while(file >> buffer)
		if (std::string(buffer) == "points")
		{
			Read_Points(file);
		}
		else if (std::string(buffer) == "edges")
		{
			Read_Edges(file);
		}
		else if (std::string(buffer) == "faces")
        {
			Read_Faces(file);
		}
        
		//std::cout << buffer << std::endl;
	file.close();
    std::cout << "Read Geometry Done: [" << FilePath << "]" << std::endl;
}

void Geometry::Read_Points(std::fstream &file)
{
    char buffer[1024] = "";
	file >> buffer;
	unsigned int  PointsNumber = atoi(buffer);
	
	for(unsigned int i = 0; i < PointsNumber; i++)
	{
		Point point(i);
		double x, y, z;
		file >> x >> y >> z;
        max_x = std::max(max_x, x);
        min_x = std::min(min_x, x);
        max_y = std::max(max_y, y);
        min_y = std::min(min_y, y);

		point.Set_x(x);
		point.Set_y(y);
		point.Set_z(z);
		InsertPoint(point);
	}
	return;

}

void Geometry::Read_Edges(std::fstream &file)
{
    char buffer[1024] = "";
    file >> buffer;
    unsigned int EdgesNumber = atoi(buffer);

    for (unsigned int i = 0; i < EdgesNumber; i++)
    {
        unsigned int v1, v2;
        file >> v1 >> v2;
        Edge edge(v1, v2);
        InsertEdge(edge);
    }
    return;
}

void Geometry::Read_Faces(std::fstream &file)
{

}