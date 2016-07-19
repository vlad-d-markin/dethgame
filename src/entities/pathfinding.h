#ifndef PATHFINDING_H
#define PATHFINDING_H

#include "oxygine-framework.h"
#include "../map.h"
#include <list>
#include <cmath>
#include <vector>

using namespace oxygine;

class Waypoint
{
public:
    Vector2 m_position;
    Waypoint * m_parent;

    int x, y;    
    bool m_opened;
    bool m_closed;
    bool m_is_wall;
    int m_g_score;
    int m_h_score;
    int m_f_score;

    Waypoint(Vector2 point);

    int getGScore(Waypoint * p);
    int getHScore(Waypoint * p);

    void calculateScores(Waypoint * end);
    bool operator==(const Waypoint& other) { return m_position == other.m_position; }
    bool operator!=(const Waypoint& other) { return m_position != other.m_position; }
};


class Pathfinder
{
private:
    std::vector<Waypoint *> m_waypoints_map;
    Map * m_map;
public:
    Pathfinder(Map * map);
    Waypoint * getWaypoint(int x, int y);
    std::list<Vector2> findPath(Vector2 from, Vector2 to);
};

#endif
