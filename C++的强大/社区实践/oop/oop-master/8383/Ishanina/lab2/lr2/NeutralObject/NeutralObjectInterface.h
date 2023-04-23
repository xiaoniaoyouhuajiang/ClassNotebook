//
// Created by Mila
//

#ifndef UNTITLED_NEUTRALOBJECTINTERFACE_H
#define UNTITLED_NEUTRALOBJECTINTERFACE_H

class NeutralObjectInterface{

public:
    virtual char whatYouName() = 0; //метод для отображения нейтрального объекта на поле как специальной буквы
    virtual NeutralObjectInterface* copy() = 0;//метод копирования
    virtual bool canStepOnIt() = 0;//метод который сообщит можно ли встать на эту клетку
    virtual void operator +(int* characteristic) = 0;
};

#endif //UNTITLED_NEUTRALOBJECTINTERFACE_H
