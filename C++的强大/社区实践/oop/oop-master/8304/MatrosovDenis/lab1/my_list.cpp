#include "stdafx.h"
#include "my_list.h"

MyList::MyList(const MyList& copy) {
    std::shared_ptr<Node> tmp_head = copy.head;
    head = nullptr;

    while (tmp_head != nullptr) {
        BaseUnit tmp_obj = BaseUnit(*tmp_head->data.get());
        Push(tmp_obj);
        tmp_head = tmp_head->next;
    }
}

MyList::~MyList() {}

MyList& MyList::operator=(const MyList& copy){

    std::shared_ptr<Node> tmp_head = copy.head;
    head = nullptr;

    while (tmp_head != nullptr) {
        BaseUnit tmp_obj = BaseUnit(*tmp_head->data.get());
        Push(tmp_obj);
        tmp_head = tmp_head->next;
    }

    return *this;
}

void MyList::Push(BaseUnit& d)
{
    Node new_nd;
    new_nd.data = std::make_shared<BaseUnit>(d);
    new_nd.next = nullptr;
    std::shared_ptr<Node> nd = std::make_shared<Node>(new_nd);

    if (head == nullptr)
        head = nd;
    else
    {
        std::shared_ptr<Node> current = head;
        while (current->next != nullptr)
            current = current->next;
        current->next = nd;
    }
}

std::shared_ptr<BaseUnit> MyList::Find(int x, int y) {
    std::shared_ptr<Node> tmp_head = head;
    while(tmp_head != nullptr) {
        if (tmp_head->data->getX() == x && tmp_head->data->getY() == y) {
            return tmp_head->data;
        }
        tmp_head = tmp_head->next;
    }
    return nullptr;
}

bool MyList::Remove(int x, int y) {
    std::shared_ptr<Node> tmp_head = head;
    std::shared_ptr<Node> previous_elem;
    while (tmp_head != nullptr) {
        if (tmp_head->data->getX() == x && tmp_head->data->getY() == y) {
            previous_elem->next = tmp_head->next;
            return true;
        }
        previous_elem = tmp_head;
        tmp_head = tmp_head->next;
    }

    return false;
}

MyList MyList::end() {
    if (this->head != nullptr) {
        MyList tmp_list = *this;
        while (tmp_list.head->data != nullptr) {
            tmp_list.head = tmp_list.head->next;
        }
        return tmp_list;
    }
    return *this;
}

MyList& MyList::operator++() {
    if (this->head != nullptr) {
        MyList tmp_list = *this;
        tmp_list.head = tmp_list.head->next;
        return tmp_list;
    }
    return *this;
}