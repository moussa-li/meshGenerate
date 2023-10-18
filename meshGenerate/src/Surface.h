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
	long long m_PointNumber;

	std::vector<long long> m_PointIds;

public:
	Surface(unsigned int id, SurfaceType type, unsigned int *PointId);

	inline long long Get_PointNumber() const { return m_PointNumber; }
	inline std::vector<long long> Get_PointIds() const { return m_PointIds; }
};
