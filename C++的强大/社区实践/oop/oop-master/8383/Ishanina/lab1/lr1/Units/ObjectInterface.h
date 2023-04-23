//
// Created by Mila on 23.02.2020.
//

#ifndef UNTITLED_OBJECTINTERFACE_H
#define UNTITLED_OBJECTINTERFACE_H
//----------------------------------- Интерфейс объекта --------------------------------//
class ObjectInterface{
public:

    virtual void whatYouName() = 0; //метод для отображения юнита на поле как специальной буквы
    virtual ObjectInterface* copy() = 0;//метод копирования

};
#endif //UNTITLED_OBJECTINTERFACE_H
