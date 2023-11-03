#pragma once

#include <vector>

#include "Point.h"


enum class SurfaceType
{
	Tri = 3,Quad = 4
};
class Surface
{
private:
	unsigned int m_Id;
	SurfaceType m_type;
	size_t m_PointNumber;

	std::vector<size_t> m_PointIds;

public:
	Surface(unsigned int id, SurfaceType type, unsigned int *PointId);

	inline size_t Get_PointNumber() const { return m_PointNumber; }
	inline std::vector<size_t> Get_PointIds() const { return m_PointIds; }
};
