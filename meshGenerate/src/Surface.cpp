#include <algorithm>
#include "Surface.h"

Surface::Surface(unsigned int id, SurfaceType type, unsigned int *PointId)
	: m_Id(id), m_type(type), m_PointNumber(int(type))	
{
    // Sort
    for (int i = 0; i < m_PointNumber-1; i++)
    {
        for (int j = i+1; j < m_PointNumber; j++)
        {
            if (PointId[i] > PointId[j])
                std::swap(PointId[i], PointId[j]);
        }
    }

	for (int i = 0; i < m_PointNumber; i++)
		m_PointIds.emplace_back(PointId[i]);
}

Surface::Surface(SurfaceType type, unsigned int *PointId)
	: m_Id(0), m_type(type), m_PointNumber(int(type))	
{
	for (int i = 0; i < m_PointNumber; i++)
		m_PointIds.emplace_back(PointId[i]);
}


Surface::Surface(unsigned int P1, unsigned int P2, unsigned int P3)
    : m_type(SurfaceType::Tri), m_PointNumber(3)
{
    // Sort
    if (P1 > P2)
        std::swap(P1, P2);
    if (P1 > P3)
        std::swap(P1, P3);
    if (P2 > P3)
        std::swap(P2, P3);
    
    m_PointIds.emplace_back(P1);
    m_PointIds.emplace_back(P2);
    m_PointIds.emplace_back(P3);
}
Surface::Surface(unsigned int P1, unsigned int P2, unsigned int P3, unsigned int P4)
{
}
