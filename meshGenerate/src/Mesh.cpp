#include <fstream>
#include <iostream>
#include <assert.h>

#include "Mesh.h"
void Mesh::Read(std::string FileName)
{
	std::fstream file;
	file.open(FileName, std::ios::in);
	if (file.is_open() == 0) {
		std::cout << "FileName : [" << FileName << "]is not open!" << std::endl;
		assert(0);
	}
	char buffer[1024] = "";
	while(file >> buffer)
		if (std::string(buffer) == "points")
		{
			Read_Points(file);
		}
		else if (std::string(buffer) == "surfaceelements")
		{
			Read_Surfaces(file);
		}
		else if (std::string(buffer) == "surfaceelementsuv")
        {
			Read_SurfacesSUV(file);
		}
		std::cout << buffer << std::endl;
	file.close();
}

void Mesh::Write(std::string FileName)
{

}

bool Mesh::Read_Points(std::fstream &file)
{
	char buffer[1024] = "";
	file >> buffer;
	unsigned int  PointsNumber = atoi(buffer);
	
	for(unsigned int i = 0; i < PointsNumber; i++)
	{
		Point point(i);
		double x, y, z;
		file >> x >> y >> z;
		point.Set_x(x);
		point.Set_y(y);
		point.Set_z(z);
		Insert(point);
	}
	return true;
}

bool Mesh::Read_Surfaces(std::fstream &file)
{
	char buffer[1024] = "";
	file >> buffer;
	unsigned int SurfaceNumber = atoi(buffer);
	for (unsigned int i = 0; i < SurfaceNumber; i++)
	{
		for (int j = 0; j < 4; j++)
			file >> buffer;
		int PointNumber;
		file >> PointNumber;
		if (PointNumber == 3)
		{
			unsigned int PointId[3];
			file >> PointId[0] >> PointId[1] >> PointId[2];
			Surface surface(i, SurfaceType::Tri, PointId);
			Insert(surface);
		}
		else if (PointNumber == 4)
		{
			unsigned int PointId[4];
			file >> PointId[0] >> PointId[1] >> PointId[2] >> PointId[3];
			Surface surface(i, SurfaceType::Quad, PointId);
			Insert(surface);
		}
	}
	return true;
}

bool Mesh::Read_SurfacesSUV(std::fstream& file)
{
    char buffer[1024] = "";
	file >> buffer;
	unsigned int SurfaceNumber = atoi(buffer);
	for (unsigned int i = 0; i < SurfaceNumber; i++)
	{
		for (int j = 0; j < 4; j++)
			file >> buffer;
		int PointNumber;
		file >> PointNumber;
		if (PointNumber == 3)
		{
			unsigned int PointId[3];
			file >> PointId[0] >> PointId[1] >> PointId[2];
			Surface surface(i, SurfaceType::Tri, PointId);
			Insert(surface);
		}
		else if (PointNumber == 4)
		{
			unsigned int PointId[4];
			file >> PointId[0] >> PointId[1] >> PointId[2] >> PointId[3];
			Surface surface(i, SurfaceType::Quad, PointId);
			Insert(surface);
		}
        for(int skip_index = 0; skip_index < 6; skip_index++)
            file >> buffer;
	}
	return true;
}

bool Mesh::Read_Elements(std::fstream &file)
{
	return true;
}

bool Mesh::Insert(Point point)
{
	// TODO: check the global point size with tmp point
	//if(m_Points.size())
	m_Points.emplace_back(point);
	return true;
}

bool Mesh::Insert(Surface surface)
{
	// TODO: check the global point size with tmp point
	//if(m_Points.size())
	m_Surfaces.emplace_back(surface);
	return true;
}