#ifndef CONTROLLER_H
#define CONTROLLER_H

using namespace std;

#include "my_except.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mynode.h"
#include "graphwidget.h"
#include "node.h"
#include "edge.h"
#include "strings.h"
#include "save.h"
#include <QFile>
#include <QDebug>
#include "logger.h"
#include <iostream>
#include <cstring>
#include <cstdio>
#include <cstdlib>
#include <QObject>
#include <string>
#include <QFileDialog>
#include <cmath>
#include "personalclass.h"

GraphWidget* widget = 0;

class Snapshot;

QString my_buff;

class Snapshot{
public:
    double first;
    double second;
    double third;
    double fourth;
    int count;

    Snapshot(double n1,double n2,double n3,double n4)
    {
        first = n1;
        second = n2;
        third = n3;
        fourth = n4;
        count = 1;
    }

    template<typename T>
    void reclaim(node<T>* ptr){
        count = 1;
        first = ptr->firstInput;
        second = ptr->secondInput;
        third = ptr->firstResult;
        fourth = ptr->secondResult;
        QString out = QString("reclaiming ") + first + " " + second + " " + third + " " + fourth;
        Logger::getInstance()->printDebug(out);
    }

    ~Snapshot(){}
};

class Controller
{
private:
    static Controller* instance;
    Controller(){}
    Controller(const Controller&);
    Controller& operator = (Controller&);

public:
    Snapshot* snap;
    node<int>* currInt;
    node<double>* currDouble;
    node<cord>* currCord;
    int size;
    int x;
    int y;
    Node* prev;
    Node* curr;

    template<typename T>
    Snapshot* createSnapshot(T* ptr){
        Snapshot* obj = new Snapshot(ptr->firstInput,ptr->secondInput,ptr->firstResult,ptr->secondResult);
        return obj;
    }

    static Controller* getInstance(){
        if (!instance){
            QString out = QString("created main class");
            Logger::getInstance()->printInfo(out);
            instance = new Controller();
            instance->snap = 0;
            instance->currInt = NULL;
            instance->currDouble = NULL;
            instance->currCord = NULL;
        }
        return instance;
    }

    template <typename T>
    node<T>* checkPtr(node<T>* ptr){
        if (ptr->abs != NULL){
            return ptr->abs;
        }
        if (ptr->add != NULL){
            return ptr->add;
        }
        if (ptr->neg != NULL){
            return ptr->neg;
        }
        if (ptr->dechun != NULL){
            return ptr->dechun;
        }
        if (ptr->div != NULL){
            return ptr->div;
        }
        if (ptr->divmod != NULL){
            return ptr->divmod;
        }
        if (ptr->mul != NULL){
            return ptr->mul;
        }
        if (ptr->muldiv != NULL){
            return ptr->muldiv;
        }
        return ptr;
    }

    template<typename T>
    void assignSwap(QString oper,node<T>* &ptr){
        if (ptr->prev == NULL){
            QString out = QString("cant swap start node");
            Logger::getInstance()->printWarning(out);
            return;
        }
        if (strcmp(oper.toStdString().data(),"neg") == 0){
            if (ptr->prev->neg != NULL)
                ptr = ptr->prev->neg;
        }
        if (strcmp(oper.toStdString().data(),"abs") == 0){
            if (ptr->prev->abs != NULL)
                ptr = ptr->prev->abs;
        }
        if (strcmp(oper.toStdString().data(),"add") == 0){
            if (ptr->prev->add != NULL)
                ptr = ptr->prev->add;
        }
        if (strcmp(oper.toStdString().data(),"mul") == 0){
            if (ptr->prev->mul != NULL)
                ptr = ptr->prev->mul;
        }
        if (strcmp(oper.toStdString().data(),"div") == 0){
            if (ptr->prev->div != NULL)
                ptr = ptr->prev->div;
        }
        if (strcmp(oper.toStdString().data(),"dechun") == 0){
            if (ptr->prev->dechun != NULL)
                ptr = ptr->prev->dechun;
        }
        if (strcmp(oper.toStdString().data(),"divmod") == 0){
            if (ptr->prev->divmod != NULL)
                ptr = ptr->prev->divmod;
        }
        if (strcmp(oper.toStdString().data(),"muldiv") == 0){
            if (ptr->prev->muldiv != NULL)
                ptr = ptr->prev->muldiv;
        }
        QString out2 = QString("Wrong swap node name");
        Logger::getInstance()->printWarning(out2);
    }

    template<typename T>
    void swapPrint(node<T>* &ptr,Ui_MainWindow *mainWindow){
        if (!snap){
            snap = new Snapshot(ptr->firstInput,ptr->firstResult,ptr->firstResult,ptr->secondResult);
        }
        else{
            snap->reclaim<T>(ptr);
        }
        assignSwap<T>(mainWindow->swapNode->toPlainText(),ptr);
        if (size == 4){
            mainWindow->firstInput->setText(QString::number(int(ptr->firstInput)));
            mainWindow->secondInput->setText(QString::number(int(ptr->secondInput)));
            mainWindow->firstResult->setText(QString::number(int(ptr->firstResult)));
            mainWindow->secondResult->setText(QString::number(int(ptr->secondResult)));
        }
        else{
            mainWindow->firstInput->setText(QString::number(ptr->firstInput));
            mainWindow->secondInput->setText(QString::number(ptr->secondInput));
            mainWindow->firstResult->setText(QString::number(ptr->firstResult));
            mainWindow->secondResult->setText(QString::number(ptr->secondResult));
        }
    }

    void swapNode(Ui_MainWindow *mainWindow){
        if (mainWindow->swapNode->toPlainText().isEmpty())
            return;
        if (currInt != NULL){
            swapPrint<int>(currInt,mainWindow);
        }
        if (currDouble != NULL){
            swapPrint<double>(currDouble,mainWindow);
        }
        if (currCord != NULL){
            swapPrint<cord>(currCord,mainWindow);
        }
    }

    void saveInFile(){
        QString buffer = "";
        if (currInt != NULL){
            Logger::getInstance()->getSimple()->assignSave<int>(currInt,buffer,"save.txt");
        }
        if (currDouble != NULL){
            Logger::getInstance()->getSimple()->assignSave<double>(currDouble,buffer,"save.txt");
        }
        if (currCord != NULL){
            Logger::getInstance()->getSimple()->assignSave<cord>(currCord,buffer,"save.txt");
        }
    }

    void saveInCache(){
        if (currInt != NULL){
            Logger::getInstance()->getCache()->SaveInfo<int>(currInt,my_buff);
        }
        if (currDouble != NULL){
            Logger::getInstance()->getCache()->SaveInfo<double>(currDouble,my_buff);
        }
        if (currCord != NULL){
            Logger::getInstance()->getCache()->SaveInfo<cord>(currCord,my_buff);
        }
    }

    template <typename T>
    void assignNew(Ui_MainWindow *mainWindow, node<T>* &ptr){
        QString oper = mainWindow->newOperation->toPlainText();
        if (oper.isEmpty()){
            QString out1 = QString("empty oper");
            Logger::getInstance()->printWarning(out1);
            return;
        }
        if (ptr->prev == NULL){
            QString out2 = QString("cant create start node");
            Logger::getInstance()->printCritical(out2);
            return;
        }
        node<T>* curr = new node<T>(ptr->prev);
        getPtr<T>(oper,curr);
        ptr = curr;
        ptr->firstInput = mainWindow->firstInput->toPlainText().toDouble();
        ptr->secondInput = mainWindow->secondInput->toPlainText().toDouble();
        reCount(ptr);
        if (size == 4){
            mainWindow->firstInput->setText(QString::number(int(ptr->firstInput)));
            mainWindow->secondInput->setText(QString::number(int(ptr->secondInput)));
            mainWindow->firstResult->setText(QString::number(int(ptr->firstResult)));
            mainWindow->secondResult->setText(QString::number(int(ptr->secondResult)));
        }
        else{
            mainWindow->firstInput->setText(QString::number(ptr->firstInput));
            mainWindow->secondInput->setText(QString::number(ptr->secondInput));
            mainWindow->firstResult->setText(QString::number(ptr->firstResult));
            mainWindow->secondResult->setText(QString::number(ptr->secondResult));
        }
    }

    void makeNewNode(Ui_MainWindow *mainWindow){
        y += 20;
        Node *node1 = new Node(widget);
        widget->my_scene->addItem(node1);
        widget->my_scene->addItem(new Edge(prev, node1));
        node1->setPos(x,y);
        curr = node1;
        if (currInt != NULL){
            assignNew<int>(mainWindow,currInt);
        }
        if (currDouble != NULL){
            assignNew<double>(mainWindow,currDouble);
        }
        if (currCord != NULL){
            assignNew<cord>(mainWindow,currCord);
        }
    }

    template <typename T>
    void countNeg(T* &tmp, double first){
        tmp->firstInput = first;
        tmp->secondInput = 0;
        tmp->firstResult = -first;
        tmp->secondResult = 0;
    }

    template <typename T>
    void countAbs(T* &tmp, double first){
        tmp->firstInput = first;
        tmp->secondInput = 0;
        tmp->firstResult = fabs(first);
        tmp->secondResult = 0;
    }

    template <typename T>
    void countAdd(T* &tmp, double first, double second){
        tmp->firstInput = first;
        tmp->secondInput = second;
        tmp->firstResult = first+second;
        tmp->secondResult = 0;
    }

    template <typename T>
    void countMul(T* &tmp,double first, double second){
        tmp->firstInput = first;
        tmp->secondInput = second;
        tmp->firstResult = first*second;
        tmp->secondResult = 0;
    }

    template <typename T>
    void countDiv(T* &tmp, double first){
        double i;
        double f;
        f = modf(first, &i);
        tmp->firstInput = first;
        tmp->secondInput = 0;
        tmp->firstResult = i;
        tmp->secondResult = f;
        if (size == 4)
            tmp->secondResult = 0.0;
    }

    template <typename T>
    void countDecHun(T* &tmp, double first){
        tmp->firstInput = first;
        tmp->secondInput = 0;
        tmp->firstResult = int(first/10);
        tmp->secondResult = int(first/100);
    }

    template <typename T>
    void countDivMod(T* &tmp, double first, double second){
        double i;
        double f;
        f = modf(first/second, &i);
        tmp->firstInput = first;
        tmp->secondInput = second;
        tmp->firstResult = i;
        tmp->secondResult = f;
        if (size == 4)
            tmp->secondResult = 0.0;
    }

    template <typename T>
    void countMulDiv(T* &tmp, double first, double second){
        tmp->firstInput = first;
        tmp->secondInput = second;
        tmp->firstResult = first*second;
        tmp->secondResult = first/second;
    }

    template <typename T>
    void getPtr(QString oper, node<T>* &ptr){
        if (strcmp(oper.toStdString().data(),"neg") == 0){
            if (ptr->prev->neg == ptr){
                QString out = QString("same operation");
                Logger::getInstance()->printWarning(out);
            }
            ptr->prev->neg = ptr;
        }
        if (strcmp(oper.toStdString().data(),"abs") == 0){
            ptr->prev->abs = ptr;
        }
        if (strcmp(oper.toStdString().data(),"add") == 0){
            ptr->prev->add = ptr;
        }
        if (strcmp(oper.toStdString().data(),"mul") == 0){
            ptr->prev->mul = ptr;
        }
        if (strcmp(oper.toStdString().data(),"div") == 0){
            ptr->prev->div = ptr;
        }
        if (strcmp(oper.toStdString().data(),"dechun") == 0){
            ptr->prev->dechun = ptr;
        }
        if (strcmp(oper.toStdString().data(),"divmod") == 0){
            ptr->prev->divmod = ptr;
        }
        if (strcmp(oper.toStdString().data(),"muldiv") == 0){
            ptr->prev->muldiv = ptr;
        }
    }

    template <typename T>
    void assignNext(node<T>* ptr, node<T>* &next){
        if (ptr->abs != NULL){
            next->abs = ptr->abs;
            next->abs->firstInput = next->firstResult;
            next->abs->prev = next;
        }
        if (ptr->add != NULL){
            next->add = ptr->add;
            next->add->firstInput = next->firstResult;
            next->add->prev = next;
        }
        if (ptr->neg != NULL){
            next->neg = ptr->neg;
            next->neg->firstInput = next->firstResult;
            next->neg->prev = next;
        }
        if (ptr->dechun != NULL){
            next->dechun = ptr->dechun;
            next->dechun->firstInput = next->firstResult;
            next->dechun->prev = next;
        }
        if (ptr->div != NULL){
            next->div = ptr->div;
            next->div->firstInput = next->firstResult;
            next->div->prev = next;
        }
        if (ptr->divmod != NULL){
            next->divmod = ptr->divmod;
            next->divmod->firstInput = next->firstResult;
            next->divmod->prev = next;
        }
        if (ptr->mul != NULL){
            next->mul = ptr->mul;
            next->mul->firstInput = next->firstResult;
            next->mul->prev = next;
        }
        if (ptr->muldiv != NULL){
            next->muldiv = ptr->muldiv;
            next->muldiv->prev = next;
        }
    }

    template<typename T>
    void assignNewNext(node<T>* &ptr,Ui_MainWindow *mainWindow){
        if (checkPtr<T>(ptr) == ptr){
            node<T>* next = new node<T>(ptr);
            next->firstInput = atof(mainWindow->firstInput->toPlainText().toStdString().data());
            next->secondInput = atof(mainWindow->secondInput->toPlainText().toStdString().data());
            reCount(next);
            QString oper = mainWindow->newOperation->toPlainText();
            getPtr<T>(oper,next);
        }

    }

    void makeNewNext(Ui_MainWindow *mainWindow){
        x += 25;
        y -= 10;
        Node *node1 = new Node(widget);
        widget->my_scene->addItem(node1);
        widget->my_scene->addItem(new Edge(curr, node1));
        node1->setPos(x,y);
        prev = curr;
        curr = node1;
        if (currInt != NULL){
            assignNewNext<int>(currInt,mainWindow);
        }
        if (currDouble != NULL){
            assignNewNext<double>(currDouble,mainWindow);
        }
        if (currCord != NULL){
            assignNewNext<cord>(currCord,mainWindow);
        }
    }

    void initFirst(Ui_MainWindow *mainWindow){
        widget = new GraphWidget();
        Node *node1 = new Node(widget);
        widget->my_scene->addItem(node1);
        node1->setPos(0,0);
        curr = node1;
        x = 0;
        y = 0;
        if (strcmp(mainWindow->newType->toPlainText().toStdString().data(),"int") == 0){
            currInt = new node<int>(NULL);
            return;
        }
        if (strcmp(mainWindow->newType->toPlainText().toStdString().data(),"double") == 0){
            currInt = new node<int>(NULL);
            return;
        }
        if (strcmp(mainWindow->newType->toPlainText().toStdString().data(),"cord") == 0){
            currInt = new node<int>(NULL);
            return;
        }
    }

    template<typename T>
    void nullMyPtr(node<T>* &ptr){
        if (ptr->prev->neg == ptr){
            ptr->prev->neg = NULL;
            return;
        }
        if (ptr->prev->muldiv == ptr){
            ptr->prev->muldiv = NULL;
            return;
        }
        if (ptr->prev->abs == ptr){
            ptr->prev->abs = NULL;
            return;
        }
        if (ptr->prev->add == ptr){
            ptr->prev->add = NULL;
            return;
        }
        if (ptr->prev->mul == ptr){
            ptr->prev->mul = NULL;
            return;
        }
        if (ptr->prev->dechun == ptr){
            ptr->prev->dechun = NULL;
            return;
        }
        if (ptr->prev->div == ptr){
            ptr->prev->div = NULL;
            return;
        }
        if (ptr->prev->divmod == ptr){
            ptr->prev->divmod = NULL;
            return;
        }
    }

    template <typename T>
    void getName(Ui_MainWindow *mainWindow, node<T>* &ptr){
        QString oper = mainWindow->newOperation->toPlainText();
        if (oper.isEmpty()){
            QString out1 = QString("no operation");
            Logger::getInstance()->printWarning(out1);
        }
        if (ptr->prev == NULL){
            QString out2 = QString("cant change start node");
            Logger::getInstance()->printCritical(out2);
            return;
        }
        node<T>* curr = new node<T>(ptr->prev);
        curr->firstInput = ptr->firstInput;
        curr->secondInput = ptr->secondInput;
        assignNext(ptr,curr);
        reCount(curr);
        nullMyPtr(ptr);
        delete ptr;
        ptr = curr;
        getPtr<T>(oper,ptr);
    }

    void changeMyNode(Ui_MainWindow *mainWindow){
        if (currInt != NULL){
            getName<int>(mainWindow,currInt);
        }
        if (currDouble != NULL){
            getName<double>(mainWindow,currDouble);
        }
        if (currCord != NULL){
            getName<cord>(mainWindow,currCord);
        }
    }

    template<typename T>
    void reCount(node<T>* &ptr){
        if (ptr->prev->neg == ptr){
            countNeg< node<T> >(ptr,ptr->firstInput);
            return;
        }
        if (ptr->prev->muldiv == ptr){
            countMulDiv< node<T> >(ptr,ptr->firstInput,ptr->secondInput);
            return;
        }
        if (ptr->prev->abs == ptr){
            countAbs< node<T> >(ptr,ptr->firstInput);
            return;
        }
        if (ptr->prev->add == ptr){
            countAdd< node<T> >(ptr,ptr->firstInput,ptr->secondInput);
            return;
        }
        if (ptr->prev->mul == ptr){
            countMul< node<T> >(ptr,ptr->firstInput,ptr->secondInput);
            return;
        }
        if (ptr->prev->dechun == ptr){
            countDecHun< node<T> >(ptr,ptr->firstInput);
            return;
        }
        if (ptr->prev->div == ptr){
            countDiv< node<T> >(ptr,ptr->firstInput);
            return;
        }
        if (ptr->prev->divmod == ptr){
            countDivMod< node<T> >(ptr,ptr->firstInput,ptr->secondInput);
            return;
        }
    }

    template<typename T>
    void CountPrev(node<T>* &ptr,Ui_MainWindow *mainWindow){
        if (ptr->prev != NULL){
            if (snap){
                snap->reclaim<T>(ptr);
                delete snap;
                snap = NULL;
                ptr = ptr->prev;
                if (size == 4){
                    mainWindow->firstInput->setText(QString::number(int(ptr->firstInput)));
                    mainWindow->secondInput->setText(QString::number(int(ptr->secondInput)));
                    mainWindow->firstResult->setText(QString::number(int(ptr->firstResult)));
                    mainWindow->secondResult->setText(QString::number(int(ptr->secondResult)));
                }
                else{
                    mainWindow->firstInput->setText(QString::number(ptr->firstInput));
                    mainWindow->secondInput->setText(QString::number(ptr->secondInput));
                    mainWindow->firstResult->setText(QString::number(ptr->firstResult));
                    mainWindow->secondResult->setText(QString::number(ptr->secondResult));
                }
            }
        }
    }

    void goBack(Ui_MainWindow *mainWindow){
        if (currInt != NULL){
            CountPrev<int>(currInt,mainWindow);
        }
        if (currDouble != NULL){
            CountPrev<double>(currDouble,mainWindow);
        }
        if (currCord != NULL){
            CountPrev<cord>(currCord,mainWindow);
        }
    }

    template<typename T>
    void CountNext(node<T>* &ptr,Ui_MainWindow *mainWindow){
        if (ptr == checkPtr<T>(ptr))
            return;
        if (!snap){
            snap = new Snapshot(ptr->firstInput,ptr->firstResult,ptr->firstResult,ptr->secondResult);
        }
        ptr = checkPtr<T>(ptr);
        if (ptr->firstInput != ptr->prev->firstResult && ptr->prev->prev != NULL){
            ptr->firstInput = ptr->prev->firstResult;
        }
        reCount(ptr);
        if (size == 4){
            mainWindow->firstInput->setText(QString::number(int(ptr->firstInput)));
            mainWindow->secondInput->setText(QString::number(int(ptr->secondInput)));
            mainWindow->firstResult->setText(QString::number(int(ptr->firstResult)));
            mainWindow->secondResult->setText(QString::number(int(ptr->secondResult)));
        }
        else{
            mainWindow->firstInput->setText(QString::number(ptr->firstInput));
            mainWindow->secondInput->setText(QString::number(ptr->secondInput));
            mainWindow->firstResult->setText(QString::number(ptr->firstResult));
            mainWindow->secondResult->setText(QString::number(ptr->secondResult));
        }
    }

    void goNext(Ui_MainWindow *mainWindow){
        if (currInt != NULL){
            CountNext<int>(currInt,mainWindow);
            return;
        }
        if (currDouble != NULL){
            CountNext<double>(currDouble,mainWindow);
            return;
        }
        if (currCord != NULL){
            CountNext<cord>(currCord,mainWindow);
            return;
        }
    }

    template <typename T>
    void checkOperation(char arr[4][10],T* &tmp,int size){
        QString out = QString(arr[0]) + " " + QString(arr[1]) + " " + QString(arr[2]) + " " + QString(arr[3]);
        Logger::getInstance()->printDebug(out);
        if (strcmp(arr[1],"neg") == 0){
            countNeg<T>(tmp,atof(arr[0]));
            tmp->prev->neg = tmp;
            return;
        }
        if (strcmp(arr[1],"abs") == 0){
            countAbs<T>(tmp,atof(arr[0]));
            tmp->prev->abs = tmp;
            return;
        }
        if (strcmp(arr[1],"div") == 0){
            countDiv<T>(tmp,atof(arr[0]));
            tmp->prev->div = tmp;
            return;
        }
        if (strcmp(arr[1],"dechun") == 0){
            countDecHun<T>(tmp,atof(arr[0]));
            tmp->prev->dechun = tmp;
            return;
        }
        if (strcmp(arr[2],"add") == 0){
            countAdd<T>(tmp,atof(arr[0]),atof(arr[1]));
            tmp->prev->add = tmp;
            return;
        }
        if (strcmp(arr[2],"mul") == 0){
            countMul<T>(tmp,atof(arr[0]),atof(arr[1]));
            tmp->prev->mul = tmp;
            return;
        }
        if (strcmp(arr[2],"divmod") == 0){
            countDivMod<T>(tmp,atof(arr[0]),atof(arr[1]));
            tmp->prev->divmod = tmp;
            return;
        }
        if (strcmp(arr[2],"muldiv") == 0){
            countMulDiv<T>(tmp,atof(arr[0]),atof(arr[1]));
            tmp->prev->muldiv = tmp;
            return;
        }
        throw MyExcept(oper_error,your_input + QString(arr[1]) + " " + QString(arr[2]));
    }

    template <typename T>
    void addNode(QString text,T* &prev,Node* begin,int x,int y){
        Node *node1 = new Node(widget);
        widget->my_scene->addItem(node1);
        widget->my_scene->addItem(new Edge(begin, node1));
        node1->setPos(x,y);
        char arr[4][10] = {'-'};
        char str[20];
        strcpy(str,text.toStdString().data());
        int i = 0;
        char* pch = strtok(str," ;\n");
        while (pch != NULL){
            strcpy(arr[i++],pch);
            pch = strtok(NULL," ;\n");
        }
        string str1 = ";";
        string str2 = ",";
        size_t found = string(text.toStdString().data()).find(str1);
        size_t found1 = string(text.toStdString().data()).find(str2);
        QString out = text + QString(" --- ") + found + " " + found1;
        Logger::getInstance()->printDebug(out);
        T* curr = new T(prev);
        if (found1 == string::npos){
            checkOperation<T>(arr,curr,4);
        }
        else if (found == string::npos){
            checkOperation<T>(arr,curr,8);
        }
             else{
                checkOperation<T>(arr,curr,12);
        }
        prev = curr;

    }

    template <typename T>
    void runFile(QString filename, QString &str,T* &start,Node* begin){
        int x = 0;
        int y = 0;
        QFile file(filename);
        if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
        {
        QString temp;
        while(!file.atEnd())
        {
            x+= 50;
            y-= 20;
            temp = file.readLine();
            addNode<T>(temp,start,begin,x,y);
            str=str+temp;
        }
        }
        file.close();
    }

    void initNode(QString filename, Ui_MainWindow *mainWindow){
        widget = new GraphWidget();
        Node *node1 = new Node(widget);
        widget->my_scene->addItem(node1);
        node1->setPos(0,0);
        QFile file(filename);
        if ((file.exists())&&(file.open(QIODevice::ReadOnly)))
        {
            QString temp = file.readLine();
            file.close();
            if (!temp.isEmpty()){
                QString str = "";
                size_t found = temp.toStdString().find(";");
                size_t found1 = temp.toStdString().find(",");
                if (found1 == string::npos){
                    node<int>* start1 = new node<int>(NULL);
                    currInt = start1;
                    size = 4;
                    runFile< node<int> >(filename,str,start1,node1);

                }
                else if (found == string::npos){
                    node<double>* start2 = new node<double>(NULL);
                    currDouble = start2;
                    size = 8;
                    runFile< node<double> >(filename,str,start2,node1);
                }
                     else{
                        node<cord>* start3 = new node<cord>(NULL);
                        currCord = start3;
                        size = 4;
                        runFile< node<cord> >(filename,str,start3,node1);
                     }
                mainWindow->status->setText(str);
            }
            else{
              throw MyExcept(file_open_error,empty_file + filename);
            }
        }
        else{
            throw MyExcept(empty_file_error,fail_to_open + filename);
        }
        file.close();
    }
};

Controller* Controller::instance = 0;

#endif // CONTROLLER_H
