#ifndef _ObjectID
#define _ObjectID

class ObjectID {
public:
    explicit ObjectID();
    ObjectID getObjectID() const;

    bool operator==(ObjectID const &rhs);
    int getNumberID() const;

    friend std::ostream& operator<<(std::ostream &out, ObjectID obj);


private:
    int ID;
    static int currentID;
};

#endif