#pragma once

#include <vector>
#include <memory>

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
    std::vector<std::shared_ptr<Surface*>> m_Neighbors;

public:
	Surface(unsigned int id, SurfaceType type, unsigned int *PointId);
    Surface(unsigned int P1, unsigned int P2, unsigned int P3);
    Surface(unsigned int P1, unsigned int P2, unsigned int P3, unsigned int p4);
	Surface(SurfaceType type, unsigned int *PointId);

	inline size_t Get_PointNumber() const { return m_PointNumber; }
	inline std::vector<size_t> Get_PointIds() const { return m_PointIds; }
    inline std::vector<std::shared_ptr<Surface*>> Get_Neighbors() const { return m_Neighbors; }
};
