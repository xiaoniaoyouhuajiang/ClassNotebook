#include "gamewindow.h"
#include "ui_gamewindow.h"

GameWindow::GameWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::GameWindow)
{
    ui->setupUi(this);

    facade = new GameFacade(this);


    chainOfResponsibilities = new StartGameHandler(facade);
    chainOfResponsibilities->setNext(new AddBaseHandler(facade))->setNext(new AddUnitHandler(facade))
            ->setNext(new MoveHandler(facade))->setNext(new AttackHandler(facade));

    ui->graphicsView->setComponents(chainOfResponsibilities, facade);
    ui->action_2->setEnabled(false);
    ui->action_3->setEnabled(false);
}

GameWindow::~GameWindow()
{
    delete facade;
    delete ui;
}

//IView implementation
void GameWindow::askForBasesPosition() {
    unsigned int playersAmount = facade->getPlayersAmount();
    unsigned int rowsAmount = facade->getRowsAmount();
    unsigned int columnsAmount = facade->getColumnsAmount();

    QMessageBox msgBox;

    msgBox.setWindowTitle("База");
    //msgBox.resize(600,600);
    //msgBox.setStyleSheet("QLabel{min-height: 10px; }");
    msgBox.setStyleSheet("QLabel{min-width:150 px; font-size: 20px;} QPushButton{ width:440px; height:30px; font-size: 18px; }");

    QLabel* title = new QLabel();
    title->setStyleSheet("QLabel{min-width:180 px; font-size: 20px;}");
    QLabel* zaglushka = new QLabel();

    QLabel* rowLabel = new QLabel("Строка:");
    QSpinBox* rowNumberInput = new QSpinBox();
    rowNumberInput->setRange(0, rowsAmount-1);

    QLabel* columnLabel = new QLabel("Столбец:");
    QSpinBox* columnNumberInput = new QSpinBox();


    columnNumberInput->setRange(0, columnsAmount-1);

    msgBox.layout()->addWidget(title);
    msgBox.layout()->addWidget(zaglushka);
    msgBox.layout()->addWidget(rowLabel);
    msgBox.layout()->addWidget(rowNumberInput);
    msgBox.layout()->addWidget(columnLabel);
    msgBox.layout()->addWidget(columnNumberInput);
    QPushButton *a1 = msgBox.addButton(tr("Создать базу"), QMessageBox::ActionRole);

    for(unsigned int i = 0; i < playersAmount; i++)
    {
        //title->setText("Создание базы\nигрока " + QString::number(i+1));

        msgBox.exec();

        AddBaseData* newBaseData = new AddBaseData(rowNumberInput->value(), columnNumberInput->value(), i);

        try {
            chainOfResponsibilities->handle(newBaseData);

        } catch (...) {
        }{}
    }

    ui->graphicsView->updateFieldPicture();
}

void GameWindow::update()
{
    ui->graphicsView->updateFieldPicture();
}

void GameWindow::setCurrentPlayerInfo(unsigned int currentPlayer)
{
    ui->currentPlayerLabel->setText("Очередность хода:\nХод " + QString::number(currentPlayer+1) + "-го игрока\n");
}

void GameWindow::showWinnerInfo(unsigned int winnerPlayer)
{

}
//end of IView impl

void GameWindow::on_action_triggered()
{
    ui->graphicsView->clear();

    QMessageBox msgBox;

    msgBox.setWindowTitle("Новая игра");
    QPushButton *a2 = msgBox.addButton(tr("Создать поле"), QMessageBox::ActionRole);

    QLabel* ss = new QLabel();
    ss->setText("Создать поле:\n");
    QLabel* text = new QLabel();
    text->setText("Размер n (строки):");
    QSpinBox* rowsInput = new QSpinBox();
    rowsInput->setRange(2, 100);

    QLabel* text1 = new QLabel();
    text1->setText("Размер m (столбцы):");
    QSpinBox* columnsInput = new QSpinBox();
    columnsInput->setRange(2, 100);

    QLabel* text2 = new QLabel();
    text2->setText("Ограничение существ на поле:");
    QSpinBox* maxEntitiesAmountInput = new QSpinBox();
    maxEntitiesAmountInput->setRange(0, 100);

    QLabel* text3 = new QLabel();
    text3->setText("Количество игроков:");
    QSpinBox* playersAmountInput = new QSpinBox();
    playersAmountInput->setRange(2, 4);

    msgBox.layout()->addWidget(text);
    msgBox.layout()->addWidget(rowsInput);
    msgBox.layout()->addWidget(text1);
    msgBox.layout()->addWidget(columnsInput);
    msgBox.layout()->addWidget(text2);
    msgBox.layout()->addWidget(maxEntitiesAmountInput);
    msgBox.layout()->addWidget(text3);
    msgBox.layout()->addWidget(playersAmountInput);
    msgBox.exec();

    StartNewGameData* newGameData = new StartNewGameData(rowsInput->value(), columnsInput->value(),
                                                         maxEntitiesAmountInput->value(),
                                                         playersAmountInput->value());

    chainOfResponsibilities->handle(newGameData);

    ui->graphicsView->updateFieldPicture(rowsInput->value(), columnsInput->value());


    ui->action_2->setEnabled(true);
    ui->action_3->setEnabled(true);
}

void GameWindow::on_action_2_triggered()
{
    unsigned int rowsAmount = facade->getRowsAmount();
    unsigned int columnsAmount = facade->getColumnsAmount();
    QMessageBox msgBox;

    msgBox.setWindowTitle("Добавление юнита");

    QLabel* text1 = new QLabel("Юнит:");
    QComboBox* unitTypesBox = new QComboBox();
    unitTypesBox->addItem("Лучник с крит. уроном");
    unitTypesBox->addItem("Конница с крит. уроном");
    unitTypesBox->addItem("Пехота с крит. уроном");
    unitTypesBox->addItem("Лучник с ув. здоровьем");
    unitTypesBox->addItem("Конница с ув. здоровьем");
    unitTypesBox->addItem("Пехота с ув. здоровьем");

    QLabel* text2 = new QLabel("Строка:");
    QSpinBox* rowInput = new QSpinBox();
    rowInput->setRange(0, rowsAmount-1);

    QLabel* text3 = new QLabel("Столбец:");
    QSpinBox* columnsInput = new QSpinBox();
    columnsInput->setRange(0, columnsAmount-1);

    msgBox.layout()->addWidget(text1);
    msgBox.layout()->addWidget(unitTypesBox);
    msgBox.layout()->addWidget(text2);
    msgBox.layout()->addWidget(rowInput);
    msgBox.layout()->addWidget(text3);
    msgBox.layout()->addWidget(columnsInput);
    msgBox.exec();

    AddUnitData* data;
    switch (unitTypesBox->currentIndex()) {
        case 0:
            data = new AddUnitData(rowInput->value(), columnsInput->value(), CRIT_ARCHER);
            break;
        case 1:
            data = new AddUnitData(rowInput->value(), columnsInput->value(), CRIT_CAVALRY);
            break;
        case 2:
            data = new AddUnitData(rowInput->value(), columnsInput->value(), CRIT_INFANTRY);
            break;
        case 3:
            data = new AddUnitData(rowInput->value(), columnsInput->value(), ABSORB_ARCHER);
            break;
        case 4:
            data = new AddUnitData(rowInput->value(), columnsInput->value(), ABSORB_CAVALRY);
            break;
        case 5:
            data = new AddUnitData(rowInput->value(), columnsInput->value(), ABSORB_INFANTRY);
            break;
    }

    chainOfResponsibilities->handle(data);

    ui->graphicsView->updateFieldPicture();
}

void GameWindow::on_action_3_triggered()
{
        QMessageBox msgBox;
        QLabel* text = new QLabel(facade->getBaseInfo());

        msgBox.setWindowTitle("Данные о базе");
        msgBox.layout()->addWidget(text);
        msgBox.exec();
}

void GameWindow::on_action_4_triggered()
{
    QMessageBox msgBox;

    msgBox.setWindowTitle("Настройки логирования");

    QLabel* text = new QLabel("Тип логирования:");
    QComboBox* loggingTypesBox = new QComboBox();
    loggingTypesBox->addItem("В файл");
    loggingTypesBox->addItem("В терминал");
    loggingTypesBox->addItem("Без логирования");

    QLabel* text1 = new QLabel("Формат логирования:");
    QComboBox* loggingFormatsBox = new QComboBox();
    loggingFormatsBox->addItem("Полная информация");
    loggingFormatsBox->addItem("Только действия");

    msgBox.layout()->addWidget(text);
    msgBox.layout()->addWidget(loggingTypesBox);
    msgBox.layout()->addWidget(text1);
    msgBox.layout()->addWidget(loggingFormatsBox);

    msgBox.exec();

    LoggingType logType;
    LogFormatType logFormat;

    switch (loggingTypesBox->currentIndex()) {
        case 0:
            logType = FILE_LOGGING;
            break;
        case 1:
            logType = TERMINAL_LOGGING;
            break;
        case 2:
            logType = NO_LOGGING;
            break;
    }

    switch (loggingFormatsBox->currentIndex()) {
        case 0:
            logFormat = FULL_INFO;
            break;
        case 1:
            logFormat = ACTIONS_ONLY;
            break;
    }

    facade->setLoggingProperties(logType, logFormat);
}

