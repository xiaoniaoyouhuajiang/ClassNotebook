#ifndef GRAPH_H
#define GRAPH_H

#include <json2graphadapter.h>
#include <QByteArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QStringList>
#include <QString>
#include <QJsonValue>
#include <QJsonArray>
#include <QDebug>
#include <iostream>
#include <vector>
#include <deque>
#include <snapshot.h>
#include <log.h>

// ADAPTER
class JsonAdapterImpl: public Json2GraphAdapterInterface {
public:

    void setJsonData(QByteArray input_data) override {
        CacheLog::get_instance().log_data("init Json Adapter\n");
        this->data = input_data;
        this->getType();
        this->initConnections();
    }

    std::map<Vertex*, Vertex*> getFlows() override {  }

    /**
     * @brief getVertexList
     * @param type
     * @return
     * Парсит Json в список вершин графа,
     * Импортит сурсы в вершины с операциями,
     * Добавляет пути в след. вершины.
     */
    std::map<QString, Vertex*> getVertexList(VertexDataType type) override {
        CacheLog::get_instance().log_data("parsing Json to Graph\n");
        auto object = QJsonDocument::fromJson(data).object();
        auto nodesJson = object.value("nodes");
        if (nodesJson.isArray()) {
            QJsonArray arrayData = nodesJson.toArray();
            for (auto value : arrayData) {
                auto new_vertex = new Vertex(LOCAL_ID++);
                new_vertex->id = value.toObject()["id"].toString(); // записываем id
                auto name = value.toObject()["model"].toObject()["name"].toString();

                all_nodes[new_vertex->id] = value.toObject();

                switch (type) {
                    case VertexDataType::INT: {

                        if (name.contains("NUMBER_RESULT")) {      // если сток
                            new_vertex->type = VertexType::RESULT;
                        } else if (name.contains("NUMBER_INIT")) { // если исток
                            start_vertex_id = value.toObject()["id"].toString();
                            new_vertex->type = VertexType::SOURCE;
                            new_vertex->value = new QString(value.toObject()["model"].toObject()["number"].toString());
                        } else if (name.contains("NumberSource")){ // когда список вершин будет полон, импортим значения
                            LOCAL_ID--;
                            free(new_vertex);
                            continue;
                        } else if (name.contains("Multiplication")) {// операция умножение
                            new_vertex->type = VertexType::INT_MUL;
                        } else if (name.contains("Addition")) {// операция сложения
                            new_vertex->type = VertexType::INT_ADD;
                        } else if (name.contains("Division")) {// операция деления
                            new_vertex->type = VertexType::INT_DIV;
                        } else if (name.contains("Subtraction"))  { // вычитание
                        new_vertex->type = VertexType::INT_SUB;
                        }

                        qDebug() << "add new vertex " << value;
                        break;
                }
                    case VertexDataType::STRING: {
                    qDebug() << "STRING!!";
                    if (name.contains("STRING_RESULT")) {      // если сток
                        new_vertex->type = VertexType::RESULT;
//                    } else if (name.contains("STRING_INIT")) { // если исток
                      } else if (value.toObject()["model"].toObject()["type"].toString().contains("INIT_TYPE")) { // если исток
                        start_vertex_id = value.toObject()["id"].toString();
                        new_vertex->type = VertexType::SOURCE;
                        new_vertex->value = new QString(value.toObject()["model"].toObject()["value"].toString());
                    } else if (name.contains("StringSource")){ // когда список вершин будет полон, импортим значения
                        LOCAL_ID--;
                        free(new_vertex);
                        continue;
                    } else if (name.contains("AdditionString")) {// операция умножение
                        new_vertex->type = VertexType::STR_ADD;
                    } else if (name.contains("RmSymbolString")) {// операция сложения
                        new_vertex->type = VertexType::STR_RM_SYMBOL;
                    } else if (name.contains("ReverseString")) {// операция деления
                        new_vertex->type = VertexType::STR_REVERSE;
                    }
                        break;
                }
                default: {break;}
                }


                // добавляем в мап
                vertex_map[new_vertex->id] = new_vertex;
            }

            qDebug() << "map size " << vertex_map.size();

            qDebug() << "connections size " << connections.size();

            // импортим значения в вершины с операцие и id след. вершин
            for (auto vertex_pair: vertex_map) {
                //auto new_v = new Vertex();
                auto new_v = vertex_pair.second;

                // записываем id след. вершины для source
                if (new_v->type == VertexType::SOURCE) {
                    for (auto connection: connections) {
                        // ищем след. вершину
                        if (connection["out_id"].toString() == vertex_pair.first && connection["in_index"].toInt() == 0) {
                            new_v->next_vertex_id_list.push_back(connection["in_id"].toString());
                            vertex_map[connection["in_id"].toString()]->prev_vertex_id_list.push_back(new_v->id);
                        }
                    }
                    continue;
                }
                if (new_v->type == VertexType::RESULT) { continue; }

                for (auto connection: connections) {                    
                    // ищем след. вершину
                    if (connection["out_id"].toString() == vertex_pair.first) {
                        new_v->next_vertex_id_list.push_back(connection["in_id"].toString());
                        if (vertex_map.find(connection["in_id"].toString()) != vertex_map.end())
                            vertex_map[connection["in_id"].toString()]->prev_vertex_id_list.push_back(vertex_pair.first);
                    }


                    // если сурса коннетится к операции
                    if (connection["in_id"].toString() == vertex_pair.first && connection["in_index"].toInt() == 1) {
                        // если попали на соединение двух вершин с операциями
                        if (!all_nodes[connection["out_id"].toString()]["model"].toObject()["name"].toString().contains("Source")) {
                            continue;
                        }

                        switch (type) {
                            case VertexDataType::INT: {
                                new_v->operator_value = new QString(all_nodes[connection["out_id"].toString()]["model"].toObject()["number"].toString());
                                break;
                            }
                            case VertexDataType::STRING: {
                                new_v->operator_value =
                                        new QString(all_nodes[connection["out_id"].toString()]["model"].toObject()["value"].toString());
                                break;
                            }
                        default: {break;}
                        }
                    }
                }
                vertex_map[new_v->id] = new_v;
            }

            for (auto v: vertex_map) {
                qDebug() << "- - -- - - - -- - - -- - - ";
                qDebug() << v.second->id;
                qDebug() << v.second->next_vertex_id_list;
                qDebug() << v.second->value;
                qDebug() << v.second->operator_value;
            }
        }
        return vertex_map;
    }

    // поиск типа данных
    VertexDataType getType() override {
        CacheLog::get_instance().log_data("searching Vertex type...\n");
        auto object = QJsonDocument::fromJson(data).object();
        auto nodesJson = object.value("nodes");
        if (nodesJson.isArray()) {
            QJsonArray arrayData = nodesJson.toArray();
            for (auto value : arrayData) {
                if (value.isObject()) {
                    auto obj = value.toObject();
                    if (obj.contains("model")) {
                        auto name = obj.take("model").toObject().take("name").toString();
                        if (name.contains("Number")) {
                            CacheLog::get_instance().log_data("vertex type is Integer\n");
                            return VertexDataType::INT;
                        }
                        if (name.contains("STRING")) {
                            CacheLog::get_instance().log_data("vertex type is String\n");
                            return VertexDataType::STRING;
                        }
                    }
                }
            }

        }
        throw "Node Data Type Parse Error";
    }

    // инициализация списка путей
    void initConnections() override {
        CacheLog::get_instance().log_data("parsing connections...\n");
        auto connectionsList = QJsonDocument::fromJson(data).object()["connections"].toArray();
        for (auto connection: connectionsList) {
            connections.push_back(connection.toObject());
        }
    }

    QString start_vertex_id;
private:
    QByteArray data;
    std::map<QString, QJsonObject> all_nodes;
    std::vector<QJsonObject> connections;
    std::map<QString, Vertex*> vertex_map;
    int LOCAL_ID = 0;
};

//- - - - - - --  - - - -- - - -- - - -- -  -- - - - -- - - - -- - - -- --- - - - --
// GRAPH!

class Graph {
public:
    VertexDataType data_type = VertexDataType::UNDEFINED;
private:
    static Graph* instance;
    Graph(const Graph&);
    Graph& operator = (Graph&);
    Graph();
    JsonAdapterImpl* adapter;
    std::map<QString, Vertex*> graph; // {id, vertex}
    std::deque<QString> id_deque;
    int iter_count = 0;
    QByteArray data_byte_array;
    std::vector<QString> checked_vertexes;
    std::map<QString, Vertex*> replaced_v;
public:
    static Graph* getInstance(QByteArray input_json) {
        if(!instance) {
            instance = new Graph(input_json);
        }
        return instance;
    }
    Snapshot* makeSnapshot();
    void restore(Snapshot* s);
    bool changeVeretex(int id, VertexType opearation);
    void debugGraph();
    void move_step();
    void move_forward();
    void move_back();
    void change_vertex(QString id, QString vertex_type);

    QString getStringFormatGraph();
    Graph(QByteArray input_json);
private:
    void make_snapshot();
};

#endif // GRAPH_H
