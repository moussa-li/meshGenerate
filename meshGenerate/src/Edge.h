#pragma once
#include <iostream>

class Edge
{
private:
    unsigned int m_P1;
    unsigned int m_P2;
public:
    Edge(unsigned int p1, unsigned int p2);

    inline std::pair<unsigned int, unsigned int> GetVerteices() { return { m_P1, m_P2 }; }
};
