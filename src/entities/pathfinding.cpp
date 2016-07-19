#include "pathfinding.h"
using namespace oxygine;

Waypoint::Waypoint(Vector2 point)
{
    m_position = point;
    m_opened = m_closed = false;
    m_parent = 0;
    m_g_score = m_h_score = 0;
    x = y = 0;
}


int Waypoint::getGScore(Waypoint *p)
{
  return p->m_g_score + (m_position.x == p->m_position.x || m_position.y == p->m_position.y) ? 10 : 14;
}


int Waypoint::getHScore(Waypoint *p)
{
    return (std::abs(p->m_position.x - m_position.x) + std::abs(p->m_position.y - m_position.y)) * 10;
}


void Waypoint::calculateScores(Waypoint * end)
{
    m_g_score = getGScore(m_parent);
    m_h_score = getHScore(end);
    m_f_score = m_g_score + m_h_score;
}


Pathfinder::Pathfinder(Map *map)
{
    m_map = map;
    Vector2 map_size = m_map->getMapSize();
    for(int y = 0; y < map_size.y; y += 64) {
        for(int x = 0; x < map_size.x; x += 64) {
            Vector2 pos = Vector2(x, y);
            bool is_wall = m_map->isPointCollision(pos);

            Waypoint * wp = new Waypoint(pos);
            wp->m_is_wall = is_wall;
            //debug
            //std::cout << (is_wall) ? 'x' : '_';
            wp->x = x;
            wp->y = y;
            m_waypoints_map.push_back(wp);
        }
        //debug
        //std::cout << std::endl;
    }
}


Waypoint * Pathfinder::getWaypoint(int x, int y)
{
    int s = m_waypoints_map.size();
    int idx = y * ((int)m_map->getMapSize().x % 64) + x;

    return m_waypoints_map[y * ((int)m_map->getMapSize().x / 64) + x];
}


std::list<Vector2> Pathfinder::findPath(Vector2 from, Vector2 to)
{
    std::list<Vector2> path;

    std::list<Waypoint *> openedList;
    std::list<Waypoint *> closedList;
    std::list<Waypoint *>::iterator it;

    Waypoint * start = new Waypoint(from);
    Waypoint * end = new Waypoint(to);
    Waypoint * current = 0;
    Waypoint * child = 0;

    openedList.push_back(start);
    start->m_opened = true;

    unsigned int n = 0;

    while((n == 0) || (current != end && n < 60)) {
        // Look for point with smallest F score
        for(it = openedList.begin(); it != openedList.end(); it++) {
            if(it == openedList.begin() || (*it)->m_f_score <= current->m_f_score) {
                current = *it;
            }
        }
        // Path was found
        if(*current == *end) {
            break;
        }
        // Remove current point from openedList and close it
        openedList.remove(current);
        current->m_opened = false;
        closedList.push_back(current);
        current->m_closed = true;

        // Check tiles around current
        for(int x = -1; x <= 1; x++) {
            for(int y = -1; y <=1; y++) {
                // Skip current
                if(x == 0 && y == 0) {
                    continue;
                }
                int a = (int)current->m_position.x;
                child = getWaypoint((int)current->m_position.x / 64 + x, (int)current->m_position.y / 64 + y);

                if(child->m_closed || child->m_is_wall) {
                    continue;
                }

                if(!child->m_opened) {
                    child->m_opened = true;
                    openedList.push_back(child);
                    child->m_parent = current;
                    child->calculateScores(end);
                } else {
                    if(child->m_g_score > child->getGScore(current)) {
                        child->m_parent = current;
                        child->calculateScores(end);
                    }
                }
            }
        }
        n++;
    }

    for(it = openedList.begin(); it != openedList.end(); it++) {
        (*it)->m_opened = false;
    }

    for(it = closedList.begin(); it != closedList.end(); it++) {
        (*it)->m_closed = false;
    }
    path.push_front(to);

    while(current->m_parent != 0 && current != start) {
        path.push_front(current->m_position);
        current = current->m_parent;
    }

    path.push_front(from);
    return path;
}
