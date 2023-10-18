#include "Surface.h"

Surface::Surface(unsigned int id, SurfaceType type, unsigned int *PointId)
	: m_Id(id), m_type(type), m_PointNumber(int(type))	
{
	for (int i = 0; i < m_PointNumber; i++)
		m_PointIds.emplace_back(PointId[i]);
}