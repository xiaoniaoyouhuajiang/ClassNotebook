#ifndef SAVE_H
#define SAVE_H

#include <QFile>
#include <QDebug>

class SimpleSave
{
  public:
    SimpleSave()
    {
    }
    ~SimpleSave()
    {
    }
    template <typename T>
    void assignSave(node<T>* tmp, QString res, char* filename){
        node<T>* ptr = tmp;
        while(ptr->prev != NULL){
            ptr = ptr->prev;
        }
        QFile fileOut(filename);
        if(fileOut.open(QIODevice::WriteOnly | QIODevice::Text)){
            QTextStream writeStream(&fileOut);
            int count = 1;
            if (res.isEmpty()){
                while (ptr != checkPtr<T>(ptr)){
                    ptr = checkPtr<T>(ptr);
                    writeStream << "node " << count << "\nfirstInp - " << ptr->firstInput << "\nsecondInp - " << ptr->secondInput << "\nfirst result "
                                << ptr->firstResult << "\nsecond result " << ptr->secondResult << "\n";
                    count++;
                }
                if (count == 1){
                    qDebug() << "no nodes";
                }
            }
            else{
                writeStream << res;
            }
            fileOut.close();
        }

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
};

class CacheSave
{
    SimpleSave *m_the_real_thing;
    int count;
  public:
    CacheSave()
    {
        count = 1;
        m_the_real_thing = 0;
    }
    ~CacheSave()
    {
        delete m_the_real_thing;
    }

    template<typename T>
    void SaveInfo(node<T>* tmp, QString &res)
    {
        if (!m_the_real_thing)
          m_the_real_thing = new SimpleSave();
        node<T>* ptr = tmp;
        while(ptr->prev != NULL){
            ptr = ptr->prev;
        }
        int tmpCounter = 1;
        while (ptr != m_the_real_thing->checkPtr<T>(ptr)){
            ptr = m_the_real_thing->checkPtr<T>(ptr);
            res = res + "node " + QString::number(count) + "\nfirstInp - " + QString::number(ptr->firstInput) + "\nsecondInp - " + QString::number(ptr->secondInput) + "\nfirst result " + QString::number(ptr->firstResult) + "\nsecond result " + QString::number(ptr->secondResult) + "\n";
            count++;
            tmpCounter++;
        }
        if (tmpCounter == 1){
            qDebug() << "no nodes";
        }
        if (count >= 10){
            m_the_real_thing->assignSave(ptr,res,"save.txt");
            res.clear();
            count = 1;
        }
    }
};

#endif // SAVE_H


