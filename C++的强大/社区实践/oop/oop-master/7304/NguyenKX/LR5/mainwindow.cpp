#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include "coordinate.h"
#include "logwriter.h"
#include <QGraphicsScene>
#include <QGraphicsView>
#include "unitgraphics.h"
#include "arrowgraphics.h"

#include <QKeyEvent>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    std::srand(std::time(nullptr));

    connect(ui->btnReplace,SIGNAL(clicked(bool)),this,SLOT(btnReplace_clicked()));
    connect(ui->btnHandle,SIGNAL(clicked(bool)),this,SLOT(btnHandle_clicked()));
    connect(ui->btnUndo,SIGNAL(clicked(bool)),this,SLOT(btnUndo_clicked()));
    connect(ui->actionSave,SIGNAL(triggered(bool)),this,SLOT(actionSave_triggered()));
    connect(ui->actionLoad,SIGNAL(triggered(bool)),this,SLOT(actionLoad_triggered()));

    connect(ui->btnDelete,SIGNAL(clicked(bool)),this,SLOT(btnDelete_clicked()));
    connect(ui->btnAdd,SIGNAL(clicked(bool)),this,SLOT(btnAdd_clicked()));
    connect(ui->btnSetIn,SIGNAL(clicked(bool)),this,SLOT(btnSetInp_clicked()));
    connect(ui->btnSetOut,SIGNAL(clicked(bool)),this,SLOT(btnSetOut_clicked()));
    connect(ui->btnConnect,SIGNAL(clicked(bool)),this,SLOT(btnConnect_clicked()));
    connect(ui->cbAddType,SIGNAL(currentIndexChanged(int)), this, SLOT(cdAddType_currentIndexChanged(int)));

    QStringList types;
    types   <<"Sum"
            <<"Distribute"
            <<"Squared"
            <<"DivMod"
            <<"Round2"
            <<"Distance"
            <<"CoordinateMaking"
            <<"CoordinateBreakup"
            <<"Round1"
            <<"Distribute";

    ui->cbAddType->addItems(types);

    this->scene = new QGraphicsScene(ui->graphicsView);
    ui->graphicsView->setScene(this->scene);
    ui->graphicsView->setCacheMode(QGraphicsView::CacheNone);
    ui->graphicsView->setViewportUpdateMode(QGraphicsView::BoundingRectViewportUpdate);
    ui->graphicsView->setRenderHint(QPainter::Antialiasing);
    ui->graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    ui->graphicsView->scale(qreal(0.8), qreal(0.8));

    this->drawBg();

    this->loadInfo();

    LogWriter::getInstance().changeMode(LogWriter::BUFFERED_LOG);
    LogWriter::getInstance().log("Program initialization completed");

}

void MainWindow::cdAddType_currentIndexChanged(int index){
    ui->lblHandlerType->setText(QString::fromStdString(HandlerRegistry::getInstance().getTypeDescription(index)));
}
void MainWindow::drawBg(){
//    scene->addLine(600,200,600,-200,QPen(Qt::black));

//    QFont font;
//    font.setPixelSize(30);
//    font.setBold(false);
//    font.setFamily("Calibri");

//    QGraphicsTextItem *title = new QGraphicsTextItem;
//    title->setPlainText("Unused Handler In Model");
//    title->setFont(font);
//    title->setPos(600,-250);
//    scene->addItem(title);

}
void MainWindow::focusItem(std::size_t id){
    ui->lstHandlers->item(map_row_id[id])->setSelected(true);
    ui->lstHandlers->setFocus();
}
void MainWindow::loadInfo(){
    ui->lstHandlers->clear();
    map_row_id.clear();
    int i = 0;
    for(auto pair : this->controller.getHandlersInfo()){

        ui->lstHandlers->addItem(QString::fromStdString(pair.second)); ;
        map_row_id.insert(std::pair<std::size_t,std::size_t>(pair.first,i));
        i++;
    }
    ui->lblModelState->setText(QString::fromStdString(controller.getModelState()));


    std::map<std::size_t, bool> map_used;

    // create node
    for(auto &id : controller.getUnitIds()){
        if(units.find(id)==units.end()){
            UnitGraphics *u = new UnitGraphics(id,(id-10)*70,std::sin(id/1.5*3.14)*200, this);
            units[id]=u;
            scene->addItem(u);
        }
        map_used[id] = false;
    }

    // remove all connection
    for(QGraphicsItem *item : scene->items()){
        if(dynamic_cast<ArrowGraphics*>(item)!=nullptr){
            scene->removeItem(item);
        }
    }
    // draw new connection
    for(std::pair<std::size_t,std::size_t> &connection : controller.getConnections()){
        scene->addItem(new ArrowGraphics(units[connection.first],units[connection.second]));
        // mark as used
        map_used[connection.first] = true;
        map_used[connection.second] = true;

    }

    for(std::pair<std::size_t,bool> const& used : map_used){
        if(used.second==false){
            std::size_t id = used.first;
            units[id]->setX(std::rand()%200+650);
            //units[id]->setY(pos_unused);
            //pos_unused-=50;

        }
    }


}
void MainWindow::btnUndo_clicked(){
    this->controller.undo();
    this->loadInfo();
}
void MainWindow::btnReplace_clicked(){
    try{
        controller.replace(ui->txtRepId1->text().toUInt(),ui->txtRepId2->text().toUInt());
        this->loadInfo();
        LogWriter::getInstance().log("Replaced handler ("+ui->txtRepId1->text().toStdString()
                                     +") with ("+ui->txtRepId2->text().toStdString()+")");
    }catch(const std::exception& e){
        LogWriter::getInstance().log(" Error: "+std::string(e.what()));
        QMessageBox::critical(this,QString("Error"),QString(e.what()));
    }
}
void MainWindow::btnHandle_clicked(){
    try{
        //Coordinate c = Coordinate::fromString(ui->txtValue0->text().toStdString());
        double c1 = ui->txtValue0->text().toDouble();
        double c2 = ui->txtValue1->text().toDouble();

        controller.handle(c1,c2);
        this->loadInfo();

        LogWriter::getInstance().log("Handled input: "+ui->txtValue0->text().toStdString()
                                     +" "+ui->txtValue1->text().toStdString());
    }catch(const std::exception& e){
        LogWriter::getInstance().log(" Error: "+std::string(e.what()));
        QMessageBox::critical(this,QString("Error"),QString(e.what()));
    }
}

void MainWindow::actionSave_triggered(){
    QString fileName = QFileDialog::getSaveFileName(this,
        tr("Save state"), "",
        tr("Text File (*.txt);;Binary File (*.bin)"));

    if((fileName.toStdString().compare("")!=0))
    {
        QFileInfo fi(fileName);
        QString ext = fi.suffix();
        if(ext.toStdString().compare("bin")==0){
            controller.saveToBinFile(fileName.toStdString());
        }else if(ext.toStdString().compare("txt")==0){
            controller.saveToTextFile(fileName.toStdString());
        }
    }

}
void MainWindow::actionLoad_triggered(){
    QString fileName = QFileDialog::getOpenFileName(this,
        tr("Load state"), "",
        tr("Text File (*.txt);;Binary File (*.bin)"));
    if((fileName.toStdString().compare("")!=0))
    {
        QFileInfo fi(fileName);
        QString ext = fi.suffix();
        if(ext.toStdString().compare("bin")==0){
            controller.loadFromBinFile(fileName.toStdString());
        }else if(ext.toStdString().compare("txt")==0){
            controller.loadFromTextFile(fileName.toStdString());
        }
        scene->clear();
        units.clear();
        this->drawBg();
        this->loadInfo();
    }
}

void MainWindow::btnAdd_clicked(){
    try{
        std::size_t typeId = ui->cbAddType->currentIndex();
        controller.addHandler(typeId);
        loadInfo();
    }catch(const std::exception& e){
        LogWriter::getInstance().log(" Error: "+std::string(e.what()));
        QMessageBox::critical(this,QString("Error"),QString(e.what()));
    }

}
void MainWindow::btnDelete_clicked(){
    try{
        std::size_t id = ui->txtDel->text().toUInt();
        controller.deleteHandler(id);

        //remove the node
        if(units.find(id)!=units.end()){
            UnitGraphics *u = units[id];
            scene->removeItem(u);
            units.erase(id);
        }

        loadInfo();
    }catch(const std::exception& e){
        LogWriter::getInstance().log(" Error: "+std::string(e.what()));
        QMessageBox::critical(this,QString("Error"),QString(e.what()));
    }
}
void MainWindow::btnConnect_clicked(){
    try{
        std::size_t id1 = ui->txtCon1->text().toUInt();
        std::size_t id2 = ui->txtCon2->text().toUInt();
        std::size_t slot = ui->txtConSlot->text().toUInt();
        controller.connect(id1,slot,id2);
        loadInfo();
    }catch(const std::exception& e){
        LogWriter::getInstance().log(" Error: "+std::string(e.what()));
        QMessageBox::critical(this,QString("Error"),QString(e.what()));
    }
}
void MainWindow::btnSetInp_clicked(){
    try{
        std::size_t id = ui->txtIn->text().toUInt();
        controller.setInput(id);
        loadInfo();
    }catch(const std::exception& e){
        LogWriter::getInstance().log(" Error: "+std::string(e.what()));
        QMessageBox::critical(this,QString("Error"),QString(e.what()));
    }
}
void MainWindow::btnSetOut_clicked(){
    try{
        std::size_t id = ui->txtOut->text().toUInt();
        controller.setOutput(id);
        loadInfo();
    }catch(const std::exception& e){
        LogWriter::getInstance().log(" Error: "+std::string(e.what()));
        QMessageBox::critical(this,QString("Error"),QString(e.what()));
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
