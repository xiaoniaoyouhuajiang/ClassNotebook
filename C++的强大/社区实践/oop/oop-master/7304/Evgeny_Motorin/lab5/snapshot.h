#ifndef SNAPSHOT_H
#define SNAPSHOT_H

#include <stack>
#include <QDebug>
#include <json2graphadapter.h>
#include <customexception.h>


// снимок
class Snapshot {
public:
    QByteArray data;
    int iter_count;
    std::map<QString, Vertex*> replaced_v;
    Snapshot(QByteArray d, int i, std::map<QString, Vertex*> v): data(d), iter_count(i), replaced_v(v) {}
};

// опекун
class Command {
public:
    void makeBackup(Snapshot* s) {
        qDebug() << "backup created!";
        backup.push(new Snapshot(s->data, s->iter_count, s->replaced_v));
    }
    Snapshot* undo() {
        if (backup.size() < 1) {
            throw CustomException("Getting Snapshot error", "Snapshot list is empty");
            //return backup.top();
        }
        auto r = backup.top();
        backup.pop();
        return r;
    }
private:
    std::stack<Snapshot*> backup;
};


#endif // SNAPSHOT_H
