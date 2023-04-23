#include "mainwindow.h"
#include <QApplication>
#include <QFile>
#include <QDir>
#include <QScopedPointer>
#include <QTextStream>
#include <QDateTime>
#include <QLoggingCategory>
#include <QtGui>
#include "graphwidget.h"
#include "node.h"

QScopedPointer<QFile>   m_logFile;

 void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg);

 void openmyActiv(GraphWidget widget){
     widget.show();
 }

 int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    GraphWidget widget;
    //openmyActiv(widget);
    //Node *node1 = new Node(&widget);
    //widget.my_scene->addItem(node1);
    //node1->setPos(-50, -50);
    //openmyActiv(widget);
    //widget.show();
    m_logFile.reset(new QFile("save.txt"));
    // Открываем файл логирования
    m_logFile.data()->open(QFile::Append | QFile::Text);
    // Устанавливаем обработчик
    qInstallMessageHandler(messageHandler);
    MainWindow w;
    w.show();

     return a.exec();
}

 void messageHandler(QtMsgType type, const QMessageLogContext &context, const QString &msg)
{
    // Открываем поток записи в файл
    QTextStream out(m_logFile.data());
    // Записываем дату записи
    out << QDateTime::currentDateTime().toString("yyyy-MM-dd hh:mm:ss.zzz ");
    // По типу определяем, к какому уровню относится сообщение
    switch (type)
    {
    case QtInfoMsg:     out << "INF "; break;
    case QtDebugMsg:    out << "DBG "; break;
    case QtWarningMsg:  out << "WRN "; break;
    case QtCriticalMsg: out << "CRT "; break;
    case QtFatalMsg:    out << "FTL "; break;
    }
    // Записываем в вывод категорию сообщения и само сообщение
    out << context.category << ": "
        << msg << endl;
    out.flush();    // Очищаем буферизированные данные
}
