#pragma once
//#include <list>
#include <vector>
#include <string>

#include "Point.h"
#include "Surface.h"
#include "Element.h"


class Mesh
{
private:
	unsigned int m_Id;

	std::vector<Point> m_Points;
	std::vector<Surface> m_Surfaces;
	std::vector<Element> m_Elements;


	//TODO:: Part, Set, Color

	bool Read_Points(std::fstream& file);
	bool Read_Surfaces(std::fstream& file);
    bool Read_SurfacesSUV(std::fstream& file);
	bool Read_Elements(std::fstream& file);

	bool Insert(Point point);
	bool Insert(Surface surface);
public:
	Mesh() :m_Id(0) {};
	Mesh(unsigned int id) :m_Id(id) {};

	inline std::vector<Point>  GetPoints() const { return m_Points; }
	inline std::vector<Surface>  GetSurfaces() const { return m_Surfaces; }
	inline std::vector<Element>  GetElements() const { return m_Elements; }

	void Read(std::string FileName);
	void Write(std::string FileName);


};
