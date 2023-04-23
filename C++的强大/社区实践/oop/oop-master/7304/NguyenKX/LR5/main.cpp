#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[] )
{

    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    return a.exec();


    // Simple chain (2 handlers)

//    CoordinateBreakUpHandler h1;
//    SumHandler h2;
//    h2.isOutput = true;

//    h1.setNext(0,&h2);
//    h1.setNext(1,&h2);


//    h1.handle(coordinate);

//    std::cout<<h1<<h2;
//    LogWriter::getInstance().changeMode(LogWriter::BUFFERED_LOG);
//    Controller controller;
//    for(std::string s : controller.getInfo()){
//        std::cout<<s;
//    }
//    // Model
//    Model<Coordinate,double> myModel;

//    auto h1 =  myModel.add(new CoordinateBreakUpHandler);
//    auto h2 = myModel.add(new SumHandler);
//    auto h3 = myModel.add(new SumHandler);
//    auto h4 = myModel.add(new DistributeHandler);


//    h1->setNext(0,h2);
//    h1->setNext(1,h2);

//    myModel.setInput(h1.get());
//    myModel.setOutput(h2.get());

//    std::cout<<"Model initiated"<<std::endl;
//    std::cout<< myModel;
//    std::cout<<*h1<<*h2<<*h3;

//    std::cout<<"Replacing"<<std::endl;
//    try{
//        myModel.replace(h2.get(),h3.get());
//        std::cout<< myModel;
//        std::cout<<*h1<<*h2<<*h3;
//    }catch(HandlerStructureException &e){
//        std::cout<<e.what()<<std::endl;
//    }
//    std::cout<<"Backing up..."<<std::endl;
//    myModel.backup();
//    myModel.backup();

//    std::cout<<"Handling input"<<std::endl;
//    myModel.handle(coordinate);

//    myModel.saveToFile<TxtWriter>("state_internal_.txt");

//    myModel.saveToFile<BinaryWriter>("state_internal_.bin");

//    std::cout<<"Result:"<<std::endl;
//    std::cout<<myModel;
//    std::cout<<*h1<<*h2<<*h3;

//    std::cout<<"Restoring..."<<std::endl;
//    myModel.undo();
//    std::cout<<myModel;
//    std::cout<<*h1<<*h2<<*h3;
//    std::cout<<"Reading from txt file..." <<std::endl;

//    myModel.loadFromFile<TxtReader>("state_internal_.txt");

//    std::cout<<myModel;
//    std::cout<<*h1<<*h2<<*h3;

//    std::cout<<"Restoring..."<<std::endl;
//    myModel.undo();
//    std::cout<<myModel;
//    std::cout<<*h1<<*h2<<*h3;

//    std::cout<<"Reading from binary file..." <<std::endl;

//    myModel.loadFromFile<BinaryReader>("state_internal_.bin");

//    std::cout<<myModel;
//    std::cout<<*h1<<*h2<<*h3;
    system("pause");
    return 0;
}
