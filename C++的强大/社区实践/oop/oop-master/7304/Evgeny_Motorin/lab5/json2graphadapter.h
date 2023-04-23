#ifndef JSON2GRAPHADAPTER_H
#define JSON2GRAPHADAPTER_H

#include <QByteArray>
#include <map>
#include <vector>
#include <QString>
#include <vector>
#include <QJsonObject>

enum VertexType {
    SOURCE,
    INT_ADD,
    INT_SUB,
    INT_DIV,
    INT_MUL,
    STR_ADD,
    STR_RM_SYMBOL,
    STR_REVERSE,
    POINT_X_MOVE,
    POINT_Y_MOVE,
    POINT_ADD_POINT,
    RESULT
};

enum VertexDataType {
    INT,    //0
    POINT,   //1
    STRING,     //2
    UNDEFINED   //3
};

class BaseVertex {
public:
    QString id;
    VertexType type;
    std::vector<QString> next_vertex_id_list;
    std::vector<QString> prev_vertex_id_list;

};

class Vertex: public BaseVertex{
public:
    Vertex(int id) : LOCAL_ID(id) {}
    int LOCAL_ID;
    QString* value = nullptr; // результат выполнения вершины
    QString* operator_value = nullptr; // значение применимое во время операции
};

class Json2GraphAdapterInterface {
public:
    virtual ~Json2GraphAdapterInterface() {}
    virtual void setJsonData(QByteArray input_data) = 0;
    //virtual void getAllNodes() = 0;
    virtual std::map<Vertex*, Vertex*> getFlows() = 0;
    virtual std::map<QString, Vertex*> getVertexList(VertexDataType type) = 0;
    virtual void initConnections() = 0;
    virtual VertexDataType getType() = 0;
};

#endif // JSON2GRAPHADAPTER_H
