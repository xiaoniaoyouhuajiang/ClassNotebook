

#ifndef UNTITLED13_FIELDCELL_H
#define UNTITLED13_FIELDCELL_H

#include <ostream>
#include "../Landscapes/Landscape.h"
#include "../Objects/GameObject.h"

class FieldCell {

private:

    GameObject *object;
    Landscape *landscape;

public:

    FieldCell(): object(nullptr), landscape(nullptr) {}
    FieldCell(const FieldCell& other);
    FieldCell(FieldCell &&other);
    explicit FieldCell(Landscape *landscape);

    bool isEmpty() { return object == nullptr; }
    bool setObject(GameObject *object);
    bool setLandscape(Landscape *landscape);
    void eraseObject();

    friend std::ostream& operator<< (std::ostream &stream, const FieldCell &cell);

    GameObject *getObject() const { return object; }
    Landscape *getLandscape() const { return landscape; }

    FieldCell& operator=(FieldCell && other);
    FieldCell& operator=(const FieldCell &other);

};


#endif //UNTITLED13_FIELDCELL_H
