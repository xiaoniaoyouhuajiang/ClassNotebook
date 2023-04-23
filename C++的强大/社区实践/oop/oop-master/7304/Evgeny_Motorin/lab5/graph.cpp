#include <graph.h>
#include <QJsonDocument>
#include <QJsonObject>
#include <deque>
#include <log.h>

Graph::Graph(QByteArray input_json) {
    data_byte_array = input_json;
    adapter = new JsonAdapterImpl();
    adapter->setJsonData(input_json);
    data_type = adapter->getType();
    graph = adapter->getVertexList(data_type);
    auto v = new std::vector<QString>();
    v->push_back(adapter->start_vertex_id);
    id_deque.push_back(adapter->start_vertex_id);
}

/*void Graph::move_forward() {
    debugGraph();
    if (current_id_list->size() == 1 && graph[current_id_list->at(0)]->type == VertexType::RESULT) {
        qDebug() << "result" << graph[current_id_list->at(0)]->value;
        return;
    }

    qDebug() << "----------";
    auto new_vec = new std::vector<QString>();

    for (int i = 0; i < current_id_list->size(); i++) {
        QString current_id = current_id_list->at(i);

        for (auto next_id : graph[current_id]->next_vertex_id_list) {
            if (graph[next_id]->type == VertexType::RESULT) {
                graph[next_id]->value = graph["current_id"]->value;
                qDebug() << "RESULT: " << *(graph[next_id]->value);
                return;
            }


            // если выершины нет в след. обзоде - добавляем
            if (std::find(new_vec->begin(), new_vec->end(), next_id) == new_vec->end())
                new_vec->push_back(next_id);

            qDebug() << "moving to " << next_id;

            if (graph[next_id]->operator_value == nullptr && graph[next_id]->type != VertexType::RESULT) { // если нет значения для операции
                qDebug() << "operator is null" << graph[next_id]->id << " value " << graph[next_id]->operator_value;
                graph[next_id]->operator_value = new QString(*(graph[next_id]->operator_value = graph[current_id]->value));
            }
            else { // если есть - совершаем операцию
                qDebug() << "operator is not null" << graph[next_id]->id;
                switch (graph[next_id]->type) {
                    case VertexType::INT_ADD: {
                        graph[next_id]->value = new QString(QString::number(graph[next_id]->operator_value->toInt() + graph[current_id]->value->toInt()));
                        qDebug() << "OPEARATION: ADD: " << graph[next_id]->value;
                        break;
                    }
                    case VertexType::INT_DIV: {
                    auto numb = graph[next_id]->operator_value->toInt() + graph[current_id]->value->toInt();
                    graph[next_id]->value = new QString(QString::number(numb).toInt());
                    //graph[next_id]->value = new QString("50");
                    qDebug() << "OPEARATION: DIV "<< graph[next_id]->value->toInt();
                    qDebug() << "OPEARATION: DIV "<< graph[next_id]->operator_value->toInt();
                    qDebug() << "OPEARATION: DIV "<< graph[current_id]->value->toInt();
                        break;
                    }
                    case VertexType::INT_MUL: {
                        graph[next_id]->value = new QString(QString::number(graph[next_id]->operator_value->toInt() * graph[current_id]->value->toInt()));
                       qDebug() << "OPEARATION: MUL "<< graph[next_id]->value;
                        break;
                    }
                    case VertexType::INT_SUB: {
                    qDebug() << "OPEARATION: SUB";
                        graph[next_id]->value = new QString(QString::number(graph[next_id]->operator_value->toInt() - graph[current_id]->value->toInt()));
                        break;
                    }
                case VertexType::RESULT: {
                    graph[next_id]->value = graph[current_id]->value;
                    qDebug() << "RESUUULT!!!!!!!!";
                    break;
                }
                default: {qDebug() << "default";break;}
                }
            }
        }
    }

    free(current_id_list);
    current_id_list = new_vec;
    debugGraph();
}*/

bool Graph::changeVeretex(int id, VertexType opearation) {
    for (auto pair: graph) {
        if (pair.second->LOCAL_ID == id) {
            pair.second->type = opearation;
            replaced_v[pair.first] = pair.second;
            return true;
        }
    }

    return false;
}

void Graph::move_step() {
    this->iter_count++;
    auto vertex = graph[id_deque.front()];
    if (vertex->type == VertexType::RESULT) {
        vertex->value = graph[vertex->prev_vertex_id_list[0]]->value;
        return;
    }
    id_deque.pop_front();

    for (QString next_id: vertex->next_vertex_id_list) {
        while (std::find(id_deque.begin(), id_deque.end(), next_id) != id_deque.end()) {
            id_deque.erase(std::find(id_deque.begin(), id_deque.end(), next_id));
        }
        id_deque.push_back(next_id);
    }

    checked_vertexes.push_back(vertex->id);

    switch (vertex->type) {
        case VertexType::INT_ADD: {
            CacheLog::get_instance().log_data("OPEARATION: ADD\n");
            if (vertex->prev_vertex_id_list.size() > 1)
                vertex->operator_value = new QString(*(graph[vertex->prev_vertex_id_list[1]]->value));
            vertex->value = new QString(QString::number((graph[vertex->prev_vertex_id_list[0]]->value)->toInt() + (vertex->operator_value)->toInt()));
            break;
        }
        case VertexType::INT_DIV: {
        CacheLog::get_instance().log_data("OPEARATION: INT DIV\n");
            if (vertex->prev_vertex_id_list.size() > 1)
                vertex->operator_value = new QString(*(graph[vertex->prev_vertex_id_list[1]]->value));
            vertex->value = new QString(QString::number((graph[vertex->prev_vertex_id_list[0]]->value)->toInt() / (vertex->operator_value)->toInt()));
            break;
        }
        case VertexType::INT_MUL: {
            CacheLog::get_instance().log_data("OPEARATION: INT MUL\n");
            if (vertex->prev_vertex_id_list.size() > 1)
                vertex->operator_value = new QString(*(graph[vertex->prev_vertex_id_list[1]]->value));
            vertex->value = new QString(QString::number((graph[vertex->prev_vertex_id_list[0]]->value)->toInt() * (vertex->operator_value)->toInt()));
            break;
        }
        case VertexType::INT_SUB: {
            qDebug() << "OPEARATION: INT SUB";
            CacheLog::get_instance().log_data("OPEARATION: INT SUB\n");
            if (vertex->prev_vertex_id_list.size() > 1)
                vertex->operator_value = new QString(*(graph[vertex->prev_vertex_id_list[1]]->value));
            vertex->value = new QString(QString::number((graph[vertex->prev_vertex_id_list[0]]->value)->toInt() - (vertex->operator_value)->toInt()));
            break;
        }
    case VertexType::STR_ADD: {
        CacheLog::get_instance().log_data("OPEARATION: STRING ADD\n");
        if (vertex->prev_vertex_id_list.size() > 1)
            vertex->operator_value = new QString(*(graph[vertex->prev_vertex_id_list[1]]->value));
        vertex->value = new QString(*(graph[vertex->prev_vertex_id_list[0]]->value) + *(vertex->operator_value));
        break;
    }
    case VertexType::STR_REVERSE: {
        CacheLog::get_instance().log_data("OPEARATION: STRING REVERSE\n");
        if (vertex->prev_vertex_id_list.size() > 1)
            vertex->operator_value = new QString(*(graph[vertex->prev_vertex_id_list[1]]->value));
        auto new_s = QString("");
        for (int i = graph[vertex->prev_vertex_id_list[0]]->value->size() - 1; i >= 0; i--) {
                new_s += graph[vertex->prev_vertex_id_list[0]]->value->at(i);
        }
        vertex->value = new QString(new_s);
        break;
    }
    case VertexType::STR_RM_SYMBOL: {
        CacheLog::get_instance().log_data("OPEARATION: STRING RM S\n");
        if (vertex->prev_vertex_id_list.size() > 1)
            vertex->operator_value = new QString(*(graph[vertex->prev_vertex_id_list[1]]->value));
        auto new_s = new QString("");
        for (QChar c: *(graph[vertex->prev_vertex_id_list[0]]->value)) {
            if (!vertex->operator_value->contains(QString(c)))
                new_s->append(c);
        }
        vertex->value = new_s;
        break;
    }
    case VertexType::RESULT: {
        CacheLog::get_instance().log_data("RESULT\n");
        break;
    }
    default: {break;}
    }
}

//JsonAdapterImpl* adapter;
//std::vector<QString>* current_id_list;
//std::map<QString, Vertex*> graph; // {id, vertex}
//std::deque<QString> id_deque;

Snapshot* Graph::makeSnapshot() {
    return new Snapshot(data_byte_array, iter_count, this->replaced_v);
}

void Graph::restore(Snapshot* s) {
    free(this->adapter);
    this->adapter = new JsonAdapterImpl();
    this->adapter->setJsonData(s->data);
    this->id_deque.clear();
    this->graph.clear();
    this->graph = adapter->getVertexList(this->data_type);
    this->id_deque.push_back(this->adapter->start_vertex_id);
    this->checked_vertexes.clear();

    for (auto p: s->replaced_v) graph[p.first] = p.second;

    this->replaced_v = s->replaced_v;

    for (int i = 0;i < s->iter_count;i++) this->move_step();

    this->iter_count = s->iter_count;
    CacheLog::get_instance().log_data("RESTORED!, count: " + QString::number(iter_count) + "\n");
}

QString Graph::getStringFormatGraph() {
    QString line = "---------------------------------\n";
    QString s = "";
    switch (data_type) {
        case VertexDataType::INT: {s += "-- DATA TYPE: Int --\n"; break;}
        case VertexDataType::STRING: {s += "-- DATA TYPE: String --\n"; break;}
        default: { break; }
    }
    s += "-- Vertex count: ";
    s += QString::number(graph.size());
    s += " --\n";
    auto sep = "    ";
    for (auto vertex: graph) {
        auto ns = QString("%1").arg(vertex.second->LOCAL_ID);
        s += line;
        if (std::find(checked_vertexes.begin(), checked_vertexes.end(), vertex.first) != checked_vertexes.end())
            s+= "+++++++++++CHECKED++++++++++\n";
        s+= "ID = "; s+=ns;s+="\n";
        switch (vertex.second->type) {
        case SOURCE: {
            s += "SOURCE: \n";
            s += sep;
            s += "value: ";
            s += vertex.second->value;s+="\n";
            break;
        }
        case RESULT: {
            s += "RESULT: \n";
            s += sep;
            s += "value: ";
            s += vertex.second->value;s+="\n";
            break;
        }
        case INT_ADD: {
            s += "ADD: \n";
            s += sep;
            s += "value: ";
            s += vertex.second->value;s+="\n";
            s += sep;
            s += "oparetor_value: ";
            s += vertex.second->operator_value;s+="\n";
            break;
        }
        case INT_DIV: {
            s += "DIVISION: \n";
            s += sep;
            s += "value: ";
            s += vertex.second->value;s+="\n";
            s += sep;
            s += "oparetor_value: ";
            s += vertex.second->operator_value;s+="\n";
            break;
        }
        case INT_MUL: {
            s += "MULTIPLY: \n";
            s += sep;
            s += "value: ";
            s += vertex.second->value;s+="\n";
            s += sep;
            s += "oparetor_value: ";
            s += vertex.second->operator_value;s+="\n";
            break;
        }
        case INT_SUB: {
            s += "SUBSTR: \n";
            s += sep;
            s += "value: ";
            s += vertex.second->value;s+="\n";
            s += sep;
            s += "oparetor_value: ";
            s += vertex.second->operator_value;s+="\n";
            break;
        }
        case STR_ADD: {
            s += "STRING ADD: \n";
            s += sep;
            s += "value: ";
            s += vertex.second->value;s+="\n";
            s += sep;
            s += "oparetor_value: ";
            s += vertex.second->operator_value;s+="\n";
            break;
        }
        case STR_REVERSE: {
            s += "STRING REVERSE: \n";
            s += sep;
            s += "value: ";
            s += vertex.second->value;s+="\n";
            s += sep;
            s += "oparetor_value: ";
            s += vertex.second->operator_value;s+="\n";
            break;
        }
        case STR_RM_SYMBOL: {
            s += "STRING RM SYMBOL: \n";
            s += sep;
            s += "value: ";
            s += vertex.second->value;s+="\n";
            s += sep;
            s += "oparetor_value: ";
            s += vertex.second->operator_value;s+="\n";
            break;
        }
        default: {break;}
        }
    }
    return s;
}

void Graph::debugGraph() {
    CacheLog::get_instance().log_data("\n\n");
    CacheLog::get_instance().log_data("STEP: " + QString::number(iter_count) + "\n");
    CacheLog::get_instance().log_data(getStringFormatGraph() + "\n");
    /*qDebug() << "-----GRAPH DEBUG INF-----";
    for (auto ver: graph) {
        qDebug() << "LOCAL ID: " << ver.second->LOCAL_ID;
        qDebug() << "ID: " << ver.second->id;
        if (ver.second->value != nullptr)
            qDebug() << "VALUE: " << *(ver.second->value);
        if (ver.second->operator_value != nullptr)
            qDebug() << "VALUE OPERATOR: " << *(ver.second->operator_value);
        qDebug() << "NEXT ID: ";
        for (auto id: ver.second->next_vertex_id_list) {
            qDebug() << id;
        }
        qDebug() << "PREV ID: ";
        for (auto id: ver.second->prev_vertex_id_list) {
            qDebug() << id;
        }
        qDebug() << "END";
    }*/
}
