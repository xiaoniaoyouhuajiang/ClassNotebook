#include <nodes/NodeData>
#include <nodes/FlowScene>
#include <nodes/FlowView>
#include <nodes/ConnectionStyle>
#include <nodes/TypeConverter>

#include <QtWidgets/QApplication>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QMenuBar>
#include <Qtwidgets/QPushButton>

#include <nodes/DataModelRegistry>

#include "NumberSourceDataModel.hpp"
#include "NumberDisplayDataModel.hpp"
#include "TextSourceDataModel.hpp"
#include "TextDisplayDataModel.hpp"
#include "AdditionModel.hpp"
#include "SubtractionModel.hpp"
#include "MultiplicationModel.hpp"
#include "DivisionModel.hpp"
#include "ModuloModel.hpp"
#include "Converters.hpp"

#include <QAction>
#include "GraphWindow.hpp"

using QtNodes::DataModelRegistry;
using QtNodes::FlowScene;
using QtNodes::FlowView;
using QtNodes::ConnectionStyle;
using QtNodes::TypeConverter;
using QtNodes::TypeConverterId;

static std::shared_ptr<DataModelRegistry> registerDataModels() {
  auto ret = std::make_shared<DataModelRegistry>();
  ret->registerModel<NumberSourceDataModel>("Sources");

  ret->registerModel<TextSourceDataModel>("Sources");

  ret->registerModel<NumberDisplayDataModel>("RESULT");

  ret->registerModel<INIT_NUMBER>("INIT");
  ret->registerModel<StringInitDataModel>("INIT");

  ret->registerModel<TextDisplayDataModel>("RESULT");

  ret->registerModel<AdditionModel>("Number Operators");

  ret->registerModel<SubtractionModel>("Number Operators");

  ret->registerModel<MultiplicationModel>("Number Operators");

  ret->registerModel<DivisionModel>("Number Operators");

  ret->registerModel<ModuloModel>("Number Operators");

  ret->registerModel<AdditionStringModel>("String Operators");

  ret->registerModel<ReverseStringModel>("String Operators");

  ret->registerModel<RmSymbolStringModel>("String Operators");

  ret->registerTypeConverter(std::make_pair(DecimalData().type(), IntegerData().type()), TypeConverter{DecimalToIntegerConverter()});

  ret->registerTypeConverter(std::make_pair(IntegerData().type(), DecimalData().type()), TypeConverter{IntegerToDecimalConverter()});

  return ret;
}


static void setStyle() {
  ConnectionStyle::setConnectionStyle(
  R"(
  {
    "ConnectionStyle": {
      "ConstructionColor": "gray",
      "NormalColor": "black",
      "SelectedColor": "gray",
      "SelectedHaloColor": "deepskyblue",
      "HoveredColor": "deepskyblue",

      "LineWidth": 3.0,
      "ConstructionLineWidth": 2.0,
      "PointDiameter": 10.0,

      "UseDataDefinedColors": true
    }
  }
  )");
}


int main(int argc, char *argv[]) {
  QApplication app(argc, argv);

  setStyle();

  QWidget mainWidget;

  auto menuBar    = new QMenu();
  auto saveAction = menuBar->addAction("Сохранить");
  auto loadAction = menuBar->addAction("Загрузить");
  auto backAction = menuBar->addAction("Назад");
  auto openLogsBtn = menuBar->addAction("Посмотреть логи");

  auto menuBtn    = new QPushButton();
  menuBtn->setText("Действия");
  menuBtn->setMenu(menuBar);

  auto launchBtn  = new QPushButton();
  launchBtn->setText("Старт");

  QVBoxLayout *l = new QVBoxLayout(&mainWidget);

  l->addWidget(menuBtn);

  FlowScene * scene = new FlowScene(registerDataModels(), &mainWidget);
  l->addWidget(new FlowView(scene));
  l->setContentsMargins(0, 0, 0, 0);
  l->setSpacing(0);

  l->addWidget(launchBtn);

  QObject::connect(saveAction, &QAction::triggered, scene, &FlowScene::save);
  QObject::connect(loadAction, &QAction::triggered, scene, &FlowScene::load);
  QObject::connect(backAction, &QAction::triggered, scene, &FlowScene::back);
  QObject::connect(openLogsBtn, &QAction::triggered, scene, &FlowScene::openLogs);
  QObject::connect(launchBtn, &QPushButton::clicked, scene, &FlowScene::runProject);

  mainWidget.setWindowTitle("Обработчик Последовательности");
  mainWidget.resize(1000, 700);
  mainWidget.showNormal();

  return app.exec();
}
