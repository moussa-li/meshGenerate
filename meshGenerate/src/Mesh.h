#pragma once
//#include <list>
#include <fstream>
#include <iostream>
#include <filesystem>
#include <assert.h>
#include <vector>
#include <string>
#include <unordered_map>

#include "Point.h"
#include "Surface.h"
#include "Volume.h"


class Mesh
{
private:
	unsigned int m_Id;

	std::vector<Point> m_Points;
	std::vector<Point> m_PointsCompress;
    std::unordered_map<Point,size_t, pointHash> m_PointsHash;
    //std::unordered_map<size_t, size_t> tmpPointsMap;
	std::vector<Surface> m_Surfaces;
	std::vector<Volume> m_Volumes;


	//TODO:: Part, Set, Color
    void Read_Vol(std::string FilePath);

	bool Read_Points(std::fstream& file);
	bool Read_Surfaces(std::fstream& file);
    bool Read_SurfacesSUV(std::fstream& file);
	bool Read_Volumes(std::fstream& file);

	bool Insert(Point point);
	bool Insert(Surface surface);
    bool Insert(Volume volume);
public:
	Mesh() :m_Id(0) {};
	Mesh(unsigned int id) :m_Id(id) {};

	inline std::vector<Point>  GetPoints() const { return m_Points; }
	inline std::vector<Point>  GetPointsCompress() const { return m_PointsCompress; }
	inline std::unordered_map<Point,size_t, pointHash>  GetPointsHash() const { return m_PointsHash; }
	inline std::vector<Surface>  GetSurfaces() const { return m_Surfaces; }
	inline std::vector<Volume>  GetVolumes() const { return m_Volumes; }

	void Read(std::filesystem::path FileName);
	void Write(std::string FileName);


};
