#pragma once

#include <vector>

#include "Point.h"
#include "Surface.h"

enum ElementType
{
	Tet4
};

class Element
{
private:
	unsigned int m_Id;

	ElementType m_type;

	unsigned int m_PointNumber;
	unsigned int m_SurfaceNumber;

	std::vector<Point> m_Points;
	std::vector<Surface> m_Surface;

public:
	Element(unsigned int id, ElementType type) 
		: m_Id(id), m_type(type)
	{};
};
