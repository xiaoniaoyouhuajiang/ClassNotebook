#pragma once
#include "stdafx.h"
#include "GameObjects.h"
#include <memory>

struct Node
{
    std::shared_ptr<BaseUnit> data;
    std::shared_ptr<Node> next;
};

class MyList
{
private:
    std::shared_ptr<Node> head;
public:

    MyList()
    {
        head = nullptr; 
    }

    MyList(const MyList& copy);
    MyList(const MyList&& copy);

    ~MyList();

    MyList& operator=(const MyList& copy);


    MyList* begin() {
        return this;
    }

    MyList end();

    Node takeHead() {
        return *head;
    }

    void PrintAll();

    void Push(BaseUnit& d);
    std::shared_ptr<BaseUnit> Find(int x, int y);
    bool Remove(int x, int y);
    MyList& operator++();
};