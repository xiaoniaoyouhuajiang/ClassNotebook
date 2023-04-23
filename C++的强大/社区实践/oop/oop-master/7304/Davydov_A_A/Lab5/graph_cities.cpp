#include "graph_cities.h"
#include "myexception.h"
#include <QDebug>
#include <algorithm>


void graph_cities::add_edge(City &v1, City & v2, int cost, vector<QString> road_type)
{
    for(auto & e : edges)
        if(e.first == v1 && e.second.first == v2)
            throw MyException("Add road error", "Road from " + v1.get_name() + " to " + v2.get_name() + " already exists");

    qDebug() << "Add edge";
    edges.push_back(pair<City, pair<City, int>>(v1, pair<City, int>(v2, cost)));
    edges.push_back(pair<City, pair<City, int>>(v2, pair<City, int>(v1, cost)));
    edge_type.push_back(road_type);
    edge_type.push_back(road_type);
}

/*
void graph_cities::add_vertex(City &c)
{
    qDebug() << "Add vertex";
    edges.push_back(pair<City, pair<City, int>>(c, pair<City, int>(c, 0)));
    edge_type.push_back({"Land", "Water", "Air"});
}
*/

void graph_cities::update_vertex(City &c)
{
    qDebug() << "Update vertex";

    for(auto & edge : edges)
        if(edge.first.get_name().toLower() == c.get_name().toLower())
            edge.first = c;
}

std::vector<std::pair<City, pair<City, int>>> & graph_cities::get_edges() { return edges;}

std::vector<std::pair<pair<City, int>, vector<QString>>> & graph_cities::get_neighboring(City &c)
{
    neighboring.clear();
    int idx = 0;

    for(auto & edge : edges)
    {
        if(edge.first == c)
            neighboring.push_back(std::pair<pair<City, int>, vector<QString>>(edge.second, edge_type[idx]));

        idx += 1;
    }

    sort(neighboring.begin(), neighboring.end(), [](const std::pair<pair<City, int>, vector<QString>> & a, const std::pair<pair<City, int>, vector<QString>> & b) -> bool
    {
        return a.first.second < b.first.second;
    });

    return neighboring;
}


bool can_pass(Transport *t, std::vector<QString> & road_type)
{
    for(auto & type : road_type)
        if(type.toLower() == t->get_transport_type().toLower())
            return true;

    return false;
}


int greedy_algorith(City &from, City &to, graph_cities & graph, Production *p, int weight,int passengers)
{
    bool has_from = false, has_to = false;

    for(auto & e : graph.get_edges())
        if(e.first.get_name().toLower() == from.get_name())
            has_from = true;
        else if(e.first.get_name().toLower() == to.get_name())
            has_to = true;

    if(!has_to || !has_from)
        return 0;

    map<QString, bool> visitedVertex;
    std::vector<std::pair<City, pair<City, int>>>::iterator it_for_graph;
    vector<City> cur_path;
    vector<int> cost;
    bool no_path = false;

    for(it_for_graph = graph.get_edges().begin(); it_for_graph!= graph.get_edges().end(); it_for_graph++)
        visitedVertex[it_for_graph->first.get_name()] = false;

    cur_path.push_back(from);

    for(int i=0; i < graph.get_edges().size(); ++i)
    {
            if(cur_path.size() == 0)
            {
                no_path = true;
                break;
            }

            if(cur_path[cur_path.size()-1] == to)
                break;

            qDebug() << "Cur: " << cur_path[cur_path.size() - 1].get_name();
            visitedVertex[cur_path[cur_path.size() - 1].get_name()] = true; //mark last added vertex as visited
            vector<std::pair<pair<City, int>, vector<QString>>> incident_vertexs;
            std::vector<std::pair<pair<City, int>, vector<QString>>> neighboring = graph.get_neighboring(cur_path[cur_path.size() - 1]);

            //simplify cycle with iterator
            for(auto &incident_vertex: neighboring)
            {
                if(!visitedVertex[incident_vertex.first.first.get_name()])
                {
                    qDebug() << "Incident: " +  incident_vertex.first.first.get_name();
                    incident_vertexs.push_back(incident_vertex);
                }
            }

            //back at 1 step
            if(incident_vertexs.size()==0)
            {
                cur_path.pop_back();
                cost.pop_back();
                continue;
            }

            City min("");

            for(auto & edge : incident_vertexs)
            {
                for(auto & t : cur_path[cur_path.size() - 1].get_transports())
                {
                    for(auto & type : t->get_transported_type())
                        if(type.toLower() == p->get_product_type().toLower())
                            if(t->get_capacity() >= weight && can_pass(t, edge.second))
                            {
                                min = edge.first.first;
                                cost.push_back(t->get_cost() * edge.first.second);
                                break;
                            }

                    if(min.get_name()!= "")
                        break;
                }

                if(min.get_name()!= "")
                    break;
            }

            if(!min.get_name().length())
                throw MyException("Transporting production error", "City " + cur_path.back().get_name() +
                                  " hasn't transport for going by any roads");
            cur_path.push_back(min);
    }

    if(no_path)
        throw MyException("Transporting production error", "Path from " + from.get_name() + " to " + to.get_name() +
                          " doesn't exist");

    int summary_cost = 0;

    for(auto c : cost)
        summary_cost += c;

    return summary_cost;
}
