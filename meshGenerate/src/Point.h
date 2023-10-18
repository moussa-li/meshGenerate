#pragma once

class Point
{
private:
	unsigned int m_Id;
	double m_x, m_y, m_z;
public:
	Point(unsigned int id, double x, double y, double z) 
		: m_Id(id), m_x(x), m_y(y), m_z(z)
	{};
	Point(unsigned int id, double x, double y)
		: m_Id(id), m_x(x), m_y(y), m_z(0)
	{};
	Point(unsigned int id)
		: m_Id(id)
	{};


	inline unsigned int Get_Id() { return m_Id; }
	inline double Get_x() { return m_x; }
	inline double Get_y() { return m_y; }
	inline double Get_z() { return m_z; }
	inline void Set_x(double x) { m_x = x; }
	inline void Set_y(double y) { m_y = y; }
	inline void Set_z(double z) { m_z = z; }
};
