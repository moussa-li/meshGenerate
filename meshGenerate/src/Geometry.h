#pragma once
#include<vector>

#include "Point.h"
#include "Edge.h"
#include "Face.h"


class Geometry
{
private:
    std::vector<Point> m_Points;
    std::vector<Edge> m_Edges;
    std::vector<Face> m_Faces;

public:
    double max_x, max_y, min_x, min_y; // Bounding Box

public:
    inline std::vector<Point> GetPoints() { return m_Points; }
    inline std::vector<Edge> GetEdges() { return m_Edges; }
    inline std::vector<Face> GetFace() { return m_Faces; }
    
    void InsertPoint(Point p);
    void InsertEdge(Edge e);
    void InsertFace(Face f);
        
    void Read(std::string FIlePath);

    void Read_Points(std::fstream &file);
    void Read_Edges(std::fstream &file);
    void Read_Faces(std::fstream &file);

};
