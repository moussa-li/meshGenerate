#include "Volume.h"

Volume::Volume(unsigned int id, VolumeType type, unsigned int* PointId, size_t PointNumber)
    : m_Id(id), m_type(type)
{
    for (size_t i = 0; i < PointNumber; i++)
        m_PointIds.emplace_back(PointId[i]);
}

