#ifndef GRAPH_CITIES_H
#define GRAPH_CITIES_H

#include "city.h"
#include <vector>
#include <utility>

class graph_cities
{
public:
    void add_edge(City &v1, City & v2, int cost, vector<QString> road_type);
    //void add_vertex(City &c);
    void update_vertex(City &c);
    std::vector<std::pair<pair<City, int>, vector<QString>>> & get_neighboring(City &c);
    std::vector<std::pair<City, pair<City, int>>> & get_edges();
private:
    std::vector<std::pair<City, pair<City, int>>> edges;
    std::vector<std::pair<pair<City, int>, vector<QString>>> neighboring;
    std::vector<std::vector<QString>> edge_type;
};

/*
 * greedy algoright for searching transporting path
 * return -> int : summary cost of passed way
*/
int greedy_algorith(City &from, City &to, graph_cities & graph, Production *p, int weight,int passengers);

#endif // GRAPH_CITIES_H
