#pragma once

#include <vector>
#include <unordered_map>

#include "Point.h"
#include "Surface.h"

enum VolumeType
{
	Tet4
};


class Volume
{
private:
	unsigned int m_Id;

	VolumeType m_type;

	unsigned int m_PointNumber;
	unsigned int m_SurfaceNumber;

	std::vector<size_t> m_PointIds;
	//std::vector<Surface> m_Surface;

    //static std::unordered_map<VolumeType, int> VolumeTypeMap;

public:
    Volume(unsigned int id, VolumeType type, unsigned int* PointId, size_t PointNumber = 4);

	inline std::vector<size_t>  GetPointIds() const { return m_PointIds; }

};

//Volume::VolumeTypeMap[VolumeType::Tet4] = 4;
