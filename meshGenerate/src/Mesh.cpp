#include "Mesh.h"
void Mesh::Read(std::filesystem::path FilePath)
{
    if (!std::filesystem::exists(FilePath))
    {

        //}
        
        //if (file.is_open() == 0) {
        std::cout << "FileName : [" << FilePath << "]is not exists!" << std::endl;
        assert(0);
    }
    std::cout << "Read Mesh : [" << FilePath << "]" << std::endl;
    std::string extension = FilePath.extension().string(); // 获取文件后缀

    if (!extension.empty()) {
        if (extension == ".vol")
        {
            Read_Vol(FilePath.string());
        }
        else
        {
            std::cout << "The file type is not supported" << std::endl;
        }
    }
    else {
        std::cout << "The file doesn't have extension" << std::endl;
    }
}
void Mesh::Read_Vol(std::string FilePath)
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
		else if (std::string(buffer) == "surfaceelements")
		{
			Read_Surfaces(file);
		}
		else if (std::string(buffer) == "surfaceelementsuv")
        {
			Read_SurfacesSUV(file);
		}
        else if (std::string(buffer) == "volumeelements")
        {
            Read_Volumes(file);
        }
		//std::cout << buffer << std::endl;
	file.close();
    std::cout << "Read Mesh Done: [" << FilePath << "]" << std::endl;
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

bool Mesh::Read_Volumes(std::fstream &file)
{
    char buffer[1024] = "";
    file >> buffer;
    unsigned int VolumeNumber = atoi(buffer);
    for (unsigned int i = 0; i < VolumeNumber; i++)
    {
        //for (int j = 0; j < 2; j++)
        file >> buffer;
        int PointNumber;
        file >> PointNumber;
        if (PointNumber == 4)
        {
            unsigned int PointId[4];
			file >> PointId[0] >> PointId[1] >> PointId[2] >> PointId[3];
            Volume volume(i, VolumeType::Tet4, PointId);
            Insert(volume);
        }
    }

	return true;
}

bool Mesh::Insert(Point point)
{
	// TODO: check the global point size with tmp point
	//if(m_Points.size())
	m_Points.emplace_back(point);
    if (m_PointsHash.find(point) == m_PointsHash.end())
    {
	    //m_Points.emplace_back(point);
        m_PointsCompress.emplace_back(point);
        m_PointsHash[point] = m_PointsCompress.size()-1;
    }
    // TODO: maybe don`t need to remove duplicate
	return true;
}

bool Mesh::Insert(Surface surface)
{
	// TODO: check the global point size with tmp point
	//if(m_Points.size())
	m_Surfaces.emplace_back(surface);
	return true;
}

bool Mesh::Insert(Volume volume)
{
    m_Volumes.emplace_back(volume);
    return true;
}
