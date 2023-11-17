#include <algorithm>

#include "Edge.h"

Edge::Edge(unsigned int p1, unsigned int p2)
{
    if (p1 > p2)
        std::swap(p1, p2);
    m_P1 = p1;
    m_P2 = p2;
}