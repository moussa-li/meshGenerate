#include <unordered_set>
#include <unordered_map>


#include "Mesh.h"

struct PairHash {
    template <class T1, class T2>
    std::size_t operator() (const std::pair<T1, T2> &pair) const {
        auto h1 = std::hash<T1>{}(pair.first);
        auto h2 = std::hash<T2>{}(pair.second);
        return h1 ^ h2;
    }
};

struct PairEqual {
    template <class T1, class T2>
    bool operator() (const std::pair<T1, T2> &lhs, const std::pair<T1, T2> &rhs) const {
        return lhs.first == rhs.first && lhs.second == rhs.second;
    }
};

struct SurfaceHash {
    std::size_t operator()(const Surface& s) const {
        auto pointIds = s.Get_PointIds();
        return pointIds[0] ^ pointIds[1] ^ pointIds[2];
    }
};
struct SurfaceEqual {
    bool operator() (const Surface& ls, const Surface& rs) const {
        auto LpointIds = ls.Get_PointIds();
        auto RpointIds = rs.Get_PointIds();
        return LpointIds[0] == RpointIds[0] && LpointIds[1] == RpointIds[1] && LpointIds[2] == RpointIds[2];
    }
};

void Mesh::Read(std::filesystem::path FilePath)
{
    if (!std::filesystem::exists(FilePath))
    {

        std::cout << "FileName : [" << FilePath << "]is not exists!" << std::endl;
        assert(0);
    }
    std::cout << "Read File : [" << FilePath << "]" << std::endl;
    std::string extension = FilePath.extension().string(); // 获取文件后缀

    if (!extension.empty()) {
        if (extension == ".vol")
        {
            Read_Vol(FilePath.string());
        }
        else if (extension == ".geo")
        {
            Read_Geo(FilePath.string());
        }
        else
        {
            std::cout << "The file type is not supported" << std::endl;
        }
    }
    else {
        std::cout << "The file doesn't have extension" << std::endl;
    }
}
void Mesh::Read_Vol(std::string FilePath)
{
    std::fstream file;
    file.open(FilePath, std::ios::in);
    if (file.is_open() == 0)
    {
        std::cout << "FileName : [" << FilePath << "]is not open!" << std::endl;
        assert(0);
    }
	char buffer[1024] = "";
	while(file >> buffer)
		if (std::string(buffer) == "points")
		{
			Read_Points(file);
		}
		else if (std::string(buffer) == "surfaceelements")
		{
			Read_Surfaces(file);
		}
		else if (std::string(buffer) == "surfaceelementsuv")
        {
			Read_SurfacesSUV(file);
		}
        else if (std::string(buffer) == "volumeelements")
        {
            Read_Volumes(file);
        }
		//std::cout << buffer << std::endl;
	file.close();
    std::cout << "Read Mesh Done: [" << FilePath << "]" << std::endl;
}

void Mesh::Read_Geo(std::string FilePath)
{
    m_Geometry.Read(FilePath);
    max_x = m_Geometry.max_x;
    max_y = m_Geometry.max_y;
    min_x = m_Geometry.min_x;
    min_y = m_Geometry.min_y;
}

void Mesh::Write(std::filesystem::path FilePath)
{
    std::fstream file(FilePath, std::ios::out);
    //file.open;
    if (file.is_open())
    {

        file << "mesh3d\n" <<
            "dimension\n" <<
            "3" <<
            "geomtype" <<
            "0" <<
            "# surfnr	domin	domout	tlosurf	bcprop\n" <<
            "facedescriptors\n" <<
            "1\n" <<
            "1 1 0 1 1\n";
 
        Write_Points(file);
        Write_Surfaces(file);

    }
    else {
        std::cout << "File [" << FilePath << "] is not open" << std::endl;
    }
    file.close();
    std::cout << "Write Mesh Done: [" << FilePath << "]" << std::endl;
    //Write_Volume();
}

bool Mesh::Read_Points(std::fstream &file)
{
	char buffer[1024] = "";
	file >> buffer;
	unsigned int  PointsNumber = atoi(buffer);
	
	for(unsigned int i = 0; i < PointsNumber; i++)
	{
		Point point(i);
		double x, y, z;
		file >> x >> y >> z;
        max_x = std::max(max_x, x);
        min_x = std::min(min_x, x);
        max_y = std::max(max_y, y);
        min_y = std::min(min_y, y);

		point.Set_x(x);
		point.Set_y(y);
		point.Set_z(z);
		Insert_Point(point);
	}
	return true;
}

bool Mesh::Read_Surfaces(std::fstream &file)
{
	char buffer[1024] = "";
	file >> buffer;
	unsigned int SurfaceNumber = atoi(buffer);
	for (unsigned int i = 0; i < SurfaceNumber; i++)
	{
		for (int j = 0; j < 4; j++)
			file >> buffer;
		int PointNumber;
		file >> PointNumber;
		if (PointNumber == 3)
		{
			unsigned int PointId[3];
			file >> PointId[0] >> PointId[1] >> PointId[2];
			Surface surface(i, SurfaceType::Tri, PointId);
			Insert_Surface(surface);
		}
		else if (PointNumber == 4)
		{
			unsigned int PointId[4];
			file >> PointId[0] >> PointId[1] >> PointId[2] >> PointId[3];
			Surface surface(i, SurfaceType::Quad, PointId);
			Insert_Surface(surface);
		}
	}
	return true;
}

bool Mesh::Read_SurfacesSUV(std::fstream& file)
{
    char buffer[1024] = "";
	file >> buffer;
	unsigned int SurfaceNumber = atoi(buffer);
	for (unsigned int i = 0; i < SurfaceNumber; i++)
	{
		for (int j = 0; j < 4; j++)
			file >> buffer;
		int PointNumber;
		file >> PointNumber;
		if (PointNumber == 3)
		{
			unsigned int PointId[3];
			file >> PointId[0] >> PointId[1] >> PointId[2];
			Surface surface(i, SurfaceType::Tri, PointId);
			Insert_Surface(surface);
		}
		else if (PointNumber == 4)
		{
			unsigned int PointId[4];
			file >> PointId[0] >> PointId[1] >> PointId[2] >> PointId[3];
			Surface surface(i, SurfaceType::Quad, PointId);
			Insert_Surface(surface);
		}
        for(int skip_index = 0; skip_index < 6; skip_index++)
            file >> buffer;
	}
	return true;
}

bool Mesh::Read_Volumes(std::fstream &file)
{
    char buffer[1024] = "";
    file >> buffer;
    unsigned int VolumeNumber = atoi(buffer);
    for (unsigned int i = 0; i < VolumeNumber; i++)
    {
        //for (int j = 0; j < 2; j++)
        file >> buffer;
        int PointNumber;
        file >> PointNumber;
        if (PointNumber == 4)
        {
            unsigned int PointId[4];
			file >> PointId[0] >> PointId[1] >> PointId[2] >> PointId[3];
            Volume volume(i, VolumeType::Tet4, PointId);
            Insert_Volume(volume);
        }
    }

	return true;
}

bool Mesh::Write_Points(std::fstream& file)
{
/*#          X             Y             Z
points
7170
  -43.9999999999999005   -285.0000000000000000    150.0000000000000000*/
    file << "#          X             Y             Z" << std::endl;
    file << "points" << std::endl;
    file << m_Points.size() << std::endl;
    for (int i = 0; i < m_Points.size(); i++)
    {
        Point p = m_Points[i];
        file << " " << p.Get_x() << " " << p.Get_y() << " " << p.Get_z() << std::endl;
    }
    return true;
}

bool Mesh::Write_Surfaces(std::fstream& file)
{
/*# surfnr    bcnr   domin  domout      np      p1      p2      p3
surfaceelements
14336
*/
    file << "# surfnr    bcnr   domin  domout      np      p1      p2      p3" << std::endl;
    file << "surfaceelements" << std::endl;
    file << m_Surfaces.size() << std::endl;
    for (int i = 0; i < m_Surfaces.size(); i++)
    {
        Surface s = m_Surfaces[i];
        auto pIds = s.Get_PointIds();
        file << " 1 0 1 0 3 " << pIds[0]+1 << " " << pIds[1]+1 << " " << pIds[2]+1 << std::endl;
    }
    return true;
}

bool Mesh::Insert_Point(Point point)
{
	// TODO: check the global point size with tmp point
	//if(m_Points.size())
	m_Points.emplace_back(point);
    if (m_PointsHash.find(point) == m_PointsHash.end())
    {
	    //m_Points.emplace_back(point);
        m_PointsCompress.emplace_back(point);
        m_PointsHash[point] = m_PointsCompress.size()-1;
    }
    // TODO: maybe don`t need to remove duplicate
	return true;
}

bool Mesh::Insert_Surface(Surface surface)
{
	// TODO: check the global point size with tmp point
	//if(m_Points.size())
    auto pointIds = surface.Get_PointIds();
    for (int i = 0; i < pointIds.size(); i++)
    {
        Point *tmp_p = &m_Points[pointIds[i]];
        auto &neighbors = tmp_p->Get_Neighbors();
        for (int j = 1; j < pointIds.size(); j++)
        {
            //Point* tmp_p1 = &m_Points[pointIds[(i + j) % pointIds.size()]];
            if (neighbors.find(pointIds[(i + j) % pointIds.size()]) == neighbors.end())
            {
                neighbors.insert(pointIds[(i + j) % pointIds.size()]);
            }
        }
    }
	m_Surfaces.emplace_back(surface);
	return true;
}

bool Mesh::Insert_Volume(Volume volume)
{
    m_Volumes.emplace_back(volume);
    return true;
}


std::vector<Surface>::iterator Mesh::Delete_Surface(std::vector<Surface>::iterator it)
{
    Surface s = *it;
    auto pointIds = s.Get_PointIds();
    for (int i = 0; i < pointIds.size(); i++)
    {
        Point *tmp_p = &m_Points[pointIds[i]];
        auto &neighbors = tmp_p->Get_Neighbors();
        for (int j = 1; j < pointIds.size(); j++)
        {
            //Point* tmp_p1 = &m_Points[];
            if (neighbors.find(pointIds[(i + j) % pointIds.size()]) != neighbors.end())
            {
                neighbors.erase(pointIds[(i + j) % pointIds.size()]);
            }
        }
    }
    it = m_Surfaces.erase(it);
    return it;
}

Cricle Mesh::Get_Circumcircle(Surface *s)
{
    std::vector<size_t> pointids = s->Get_PointIds();
    Point& p1 = m_Points[pointids[0]];
    Point& p2 = m_Points[pointids[1]];
    Point& p3 = m_Points[pointids[2]];
    double D = 2 * (p1.Get_x() - p3.Get_x());
    double E = 2 * (p1.Get_y() - p3.Get_y());
    double F = p1.Get_x() * p1.Get_x() - p3.Get_x() * p3.Get_x() + p1.Get_y() * p1.Get_y() - p3.Get_y() * p3.Get_y();
    double G = 2 * (p1.Get_x() - p2.Get_x());
    double H = 2 * (p1.Get_y() - p2.Get_y());
    double I = p1.Get_x() * p1.Get_x() - p2.Get_x() * p2.Get_x() + p1.Get_y() * p1.Get_y() - p2.Get_y() * p2.Get_y();

    Cricle c;
    c.x = (F * H - I * E) / (D * H - G * E);
    c.y = (D * I - G * F) / (D * H - G * E);
    c.R = std::sqrt((c.x - p1.Get_x())*(c.x - p1.Get_x()) + (c.y - p1.Get_y())*(c.y - p1.Get_y()));


    return c;
}

double Mesh::GetDistance(double x1, double y1, double x2, double y2)
{
    return sqrt((x1 - x2) * (x1 - x2) + (y1 - y2) * (y1 - y2));
}


bool Mesh::PointInnerCircumcircle(Cricle* c, Point* p) 
{
    double distance = std::sqrt((p->Get_x() - c->x)*(p->Get_x() - c->x) + (p->Get_y() - c->y)*(p->Get_y() - c->y));
    return distance < c->R;
}


void Mesh::GenerateSurfaceMesh()
{
    //check bounding box
    if (max_x <= min_x || max_y <= min_y) {
        std::cout << "invalid init mesh" << std::endl;
        return;
    }

    // disperse
    //std::unordered_set<unsigned int> PointSet;
    auto Points = m_Geometry.GetPoints();
    auto Edges = m_Geometry.GetEdges();
    for (int i = 0; i < Edges.size(); i++)
    {
        auto v = Edges[i].GetVerteices();
        Point p1 = Points[v.first];
        Point p2 = Points[v.second];
        double distance = sqrt((p1.Get_x() - p2.Get_x()) * (p1.Get_x() - p2.Get_x()) + (p1.Get_y() - p2.Get_y()) * (p1.Get_y() - p2.Get_y()));
        int degree = distance / max_h;
        double dx = (p2.Get_x() - p1.Get_x()) / degree;
        double dy = (p2.Get_y() - p1.Get_y()) / degree;
        for (int i = 1; i < degree; i++)
        {
            double new_x = (dx * i) + p1.Get_x();
            double new_y = (dy * i) + p1.Get_y();
            Point new_p(Points.size(), new_x, new_y, 0);
            Points.push_back(new_p);
        }
    }


    // store inner points
    std::unordered_set<unsigned int> InnerPoints;
    for (int i = 0; i < Points.size(); i++)
    {
        InnerPoints.insert(Points[i].Get_Id());
    }
    std::unordered_set<Surface, SurfaceHash, SurfaceEqual> InnerSurfaces;

    m_Points.clear();
    // init super triangle
    /*
    **1------0**
    **|    / |**
    **|  /   |**
    **2------3**
    */
    Point p0(max_x + max_h, max_y + max_h);
    Point p1(min_x - max_h, max_y + max_h);
    Point p2(min_x - max_h, min_y - max_h);
    Point p3(max_x + max_h, min_y - max_h);
    m_Points.push_back(p0);
    m_Points.push_back(p1);
    m_Points.push_back(p2);
    m_Points.push_back(p3);
    Surface s1(0, 1, 2);
    Insert_Surface(s1);
    Surface s2(0, 2, 3);
    Insert_Surface(s2);


    std::unordered_map<unsigned int, std::vector<size_t>> PointsMap2Surface;

    // insert boundary point

    for (int i = 0; i < Points.size(); i++)
    {
        Points[i].Set_Id(m_Points.size());
        m_Points.push_back(Points[i]);
        std::unordered_set<std::pair<unsigned int,unsigned int>, PairHash, PairEqual> NewEdges;
        for (auto it = m_Surfaces.begin(); it != m_Surfaces.end();)
        {
            Cricle c = Get_Circumcircle(&(*it));
            if (PointInnerCircumcircle(&c, &Points[i])) {
                auto pointIds = it->Get_PointIds();
                for (int pointIdsIndex = 0; pointIdsIndex < pointIds.size(); pointIdsIndex++)
                {
                    unsigned int p1 = pointIds[pointIdsIndex % pointIds.size()];
                    unsigned int p2 = pointIds[(pointIdsIndex + 1) % pointIds.size()];
                    if (p1 > p2)
                        std::swap(p1, p2);
                    std::pair<unsigned int, unsigned int> edge(p1,p2);
                    if (NewEdges.find(edge) == NewEdges.end())
                    {
                        NewEdges.insert(edge);
                    }
                    else
                    {
                        NewEdges.erase(edge);
                    }
                }
                InnerSurfaces.erase(*it);
                it = Delete_Surface(it);
            }
            else {
                ++it;
            }
        }
        for (auto it = NewEdges.begin(); it != NewEdges.end(); ++it)
        {
            unsigned int p1 = Points[i].Get_Id();
            unsigned int p2 = it->first;
            unsigned int p3 = it->second;
            Surface s(p1, p2, p3);
            Insert_Surface(s);
            if (p1>=4&&p2>=4&&p3>=4)
            {
                InnerSurfaces.insert(s);
            }
        }
        
    }
    size_t OuterPointIndex = m_Points.size();

    // insert inner points
    while (1)
    {
        size_t start_pointIndex = m_Points.size();
        for (auto it = InnerSurfaces.begin(); it != InnerSurfaces.end(); ++it)
        {

            Cricle c = Get_Circumcircle(const_cast<Surface*>(&(*it)));
            auto p = it->Get_PointIds();
            double p1_x = m_Points[p[0]].Get_x(), p2_x = m_Points[p[1]].Get_x(), p3_x = m_Points[p[2]].Get_x();
            double p1_y = m_Points[p[0]].Get_y(), p2_y = m_Points[p[1]].Get_y(), p3_y = m_Points[p[2]].Get_y();
            if (p1_x == p2_x && p1_x == p3_x)
                continue;
            if (p1_y == p2_y && p1_y == p3_y)
                continue;
            if ((p1_x == p2_x && p1_y == p2_y)||(p1_x==p3_x&&p1_y==p3_y)||(p2_x==p3_x&&p2_y==p3_y))
                continue;
            double new_x = (p1_x + p2_x + p3_x) / 3;
            double new_y = (p1_y + p2_y + p3_y) / 3;
            if (GetDistance(new_x, new_y, p1_x, p1_y) < max_h ||
                GetDistance(new_x, new_y, p2_x, p2_y) < max_h ||
                GetDistance(new_x, new_y, p3_x, p3_y) < max_h
                ) continue;
            
            Point new_p(m_Points.size(), new_x, new_y, 0);
            InnerPoints.insert(new_p.Get_Id());
            m_Points.push_back(new_p);
        }
        std::cout << "The number of Insert New Inner Points is " << m_Points.size() << std::endl;
        if (start_pointIndex == m_Points.size())break;
        for(int i = start_pointIndex; i < m_Points.size(); i++)
        {
            std::unordered_set<std::pair<unsigned int,unsigned int>, PairHash, PairEqual> NewEdges;
            for (auto it = m_Surfaces.begin(); it != m_Surfaces.end();)
            {
                if (InnerSurfaces.find(*it) == InnerSurfaces.end()) { ++it; continue; }
                Cricle c = Get_Circumcircle(&(*it));
                if (PointInnerCircumcircle(&c, &m_Points[i])) {
                    auto pointIds = it->Get_PointIds();
                    for (int pointIdsIndex = 0; pointIdsIndex < pointIds.size(); pointIdsIndex++)
                    {
                        unsigned int p1 = pointIds[pointIdsIndex % pointIds.size()];
                        unsigned int p2 = pointIds[(pointIdsIndex + 1) % pointIds.size()];
                        if (p1 > p2)
                            std::swap(p1, p2);
                        std::pair<unsigned int, unsigned int> edge(p1,p2);
                        if (NewEdges.find(edge) == NewEdges.end())
                        {
                            NewEdges.insert(edge);
                        }
                        else
                        {
                            NewEdges.erase(edge);
                        }
                    }
                    InnerSurfaces.erase(*it);
                    it = Delete_Surface(it);
                }
                else {
                    ++it;
                }
            }
            for (auto it = NewEdges.begin(); it != NewEdges.end(); ++it)
            {
                unsigned int p1 = m_Points[i].Get_Id();
                unsigned int p2 = it->first;
                unsigned int p3 = it->second;
                Surface s(p1, p2, p3);
                Insert_Surface(s);
                if (p1>=4&&p2>=4&&p3>=4)
                {
                    InnerSurfaces.insert(s);
                }
            }
        }
        std::cout << "The number of Insert New  Surfaces is " << m_Surfaces.size() << std::endl;

    }

    // delete outer element
    for (auto it = m_Surfaces.begin(); it!=m_Surfaces.end();)
    {
        auto pointIds = it->Get_PointIds();
        unsigned int p1 = pointIds[0];
        unsigned int p2 = pointIds[1];
        unsigned int p3 = pointIds[2];
        if (p1 < 4 || p2 < 4 || p3 < 4)
        {
            it = Delete_Surface(it);
        }
        else {
            ++it;
        }
    }

    // TODO: boundary restoration

    //smoothing
    for (int iter = 0; iter < 100; iter++)
    {

    for (int i = OuterPointIndex; i < m_Points.size(); i++)
    {
        double sum_x = 0, sum_y = 0;
        auto &PointNeighbors = m_Points[i].Get_Neighbors();
        for (auto it = PointNeighbors.begin(); it != PointNeighbors.end(); ++it)
        {
            sum_x += m_Points[*it].Get_x();
            sum_y += m_Points[*it].Get_y();
        }
        double bary_x = sum_x / PointNeighbors.size();
        double bary_y = sum_y / PointNeighbors.size();
        Point* p = &m_Points[i];
        p->Set_x(p->Get_x()*0 + bary_x*1);
        p->Set_y(p->Get_y()*0 + bary_y*1);
    }
    
    }
}
