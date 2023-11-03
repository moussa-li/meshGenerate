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
	inline double Get_x() const { return m_x; }
	inline double Get_y() const { return m_y; }
	inline double Get_z() const { return m_z; }
	inline void Set_x(double x) { m_x = x; }
	inline void Set_y(double y) { m_y = y; }
	inline void Set_z(double z) { m_z = z; }

    bool operator == (const Point &other) const {
        return m_x == other.Get_x() && m_y == other.Get_y() && m_z == other.Get_z();
    }
};

struct pointHash {
    std::size_t operator()(const Point& p) const {
        std::size_t xHash = std::hash<double>()(p.Get_x());
        std::size_t yHash = std::hash<double>()(p.Get_y());
        std::size_t zHash = std::hash<double>()(p.Get_z());
        return xHash ^ (yHash << 1) ^ (zHash << 2);
    }
};
