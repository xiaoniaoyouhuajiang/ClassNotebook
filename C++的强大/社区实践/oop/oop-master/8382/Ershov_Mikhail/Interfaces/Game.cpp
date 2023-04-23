#include "Game.h"

template <typename T>
Game<T>::Game(int numOfOrcs, int numOfMens, int numOfElfs, int G, T rule) {
    string st; // Через эту переменную происходит считывание данных пользователя

    int howToLog = 0;	// Выбор логирования
    logger = new LoggerProxy();
    cout << "Выберите формат логирования:\n";
    cout << "1 - Логирование в файл\n2 - Логирование в терминал\n3 - Без логирования\n";
    cin >> howToLog;

    switch (howToLog) {
        case 1:
            setLogger(new LoggingFile("log.txt"));
            break;

        case 2:
            setLogger(new LoggingTerminal());
            break;

        case 3:
            setLogger(new NoLogging());
            break;

        default:
            cout << "Так как был выбран неверный формат логирования, то логи вестись не будут\n";
            setLogger(new NoLogging());
            break;
    }
    setLogFormatter(new FormatterTime());

    *logger << "GAME: Создана игра с размером поля " << G << "; количество орков - " << numOfOrcs << "; количество людей - " << numOfMens << Logger::Endl();

    MEb = new Base(G, 'm', logger);
    bool isMEbaseExist = false;     // Чтобы не создавать базу повторно
    bases.push_back(MEb);
    b = new Base(G, 'o', logger);
    bool isObaseExist = false;     // Чтобы не создавать базу повторно
    bases.push_back(b);

    f1 = new Field(G, numOfOrcs, logger);
    f1->init(numOfOrcs, numOfElfs, numOfMens);

    Iterator* it = new Iterator(f1->getCell(), G, G);
    do {
        st.clear();
        f1->print(rule.maxNumOfBases);
        int forAddAndDel = 0;

        if (states.getState() == 0) {
            cout << "1-й игрок, ваш ход:\n";
            cout << "Введите персонажа из эльфов или людей:\n";
            cin >> st;

            if (st == "exit") break;

            else if (st == "add") {
                forAddAndDel = 1;
                if (!addUnit(*f1)) continue;
            }

            else if (st == "del") {
                delUnit(*f1);
                forAddAndDel = 1;
            }

            else if (st == "base" && rule.maxNumOfBases == 2) {
                forAddAndDel = 1;
                cout << "Введите \"create\", чтобы создать базу, либо \"add\", чтобы добавить юнита в базу" << endl;
                cin >> st;

                if (st == "create" && !isMEbaseExist) {
                    isMEbaseExist = true;
                    CommandBase cb(f1, MEb, "createME");
                    string tmp = "";
                    cb.execute(tmp);
                    f1->createBase(G - 1, 0, MEb);
                }

                else if (st == "add") {
                    cout << "Введите обозначение юнита, которого вы хотите добавить:\n";
                    string character;
                    cin >> character;
                    if (character != "MS" && character != "MW" && character != "EA" && character != "EI") {
                        cout << "Неправильное обозначение персонажа. Вы пропускаете ход!\n";
                        system("pause");
                    }
                    else {
                        CommandBase cb(f1, MEb, "addInME");
                        cb.execute(character);
                    }
                }
            }

            else if (st == "save") {
                forAddAndDel = 1;
                saveGame("saving.txt", states.getState());
            }

            else if (st == "load") {
                forAddAndDel = 1;
                int turn = 0;
                loadGame("saving.txt", G, turn);
                states.setState(turn);
                it = new Iterator(f1->getCell(), f1->getSizeOfField(), f1->getSizeOfField());
            }

            else {
                while (!states.handle(st)) {
                    cout << "Неверно! Вы играете за эльфов и людей!\n";
                    cin >> st;
                }
            }
        } else {
            cout << "2-й игрок, ваш ход:\n";
            cout << "Введите персонажа из орков:\n";
            cin >> st;
            if (st == "exit") break;
            else if (st == "add") {
                forAddAndDel = 1;
                if (!addUnit(*f1)) continue;
            }
            else if (st == "del") {
                forAddAndDel = 1;
                delUnit(*f1);
            }
            else if (st == "base" && rule.maxNumOfBases == 2) {
                forAddAndDel = 1;
                cout << "Введите \"create\", чтобы создать базу, либо \"add\", чтобы добавить юнита в базу" << endl;
                cin >> st;
                if (st == "create" && !isObaseExist) {
                    isObaseExist = true;
                    CommandBase cb(f1, b, "createO");
                    string tmp = "";
                    cb.execute(tmp);
                    f1->createBase(G - 1, G - 1, b);
                }
                else if (st == "add") {
                    cout << "Введите обозначение персонажа, которого вы хотите добавить:\n";
                    string character;
                    cin >> character;
                    if (character != "OD" && character != "OR") {
                        cout << "Неправильное обозначение персонажа. Вы пропускаете ход!\n";
                        system("pause");
                    }
                    else {
                        CommandBase cb(f1, b, "addInO");
                        cb.execute(character);
                    }
                }
            }

            else if (st == "save") {
                forAddAndDel = 1;
                saveGame("saving.txt", states.getState());
            }

            else if (st == "load") {
                forAddAndDel = 1;
                int turn = 0;
                loadGame("saving.txt", G, turn);
                states.setState(turn);
                it = new Iterator(f1->getCell(), f1->getSizeOfField(), f1->getSizeOfField());
            }

            else
                while (!states.handle(st)) {
                    cout << "Неверно! Вы играете за орков!\n";
                    cin >> st;
                }
        }

        //       ХОД ЗА ЮНИТА

        if (forAddAndDel == 0) {
            unitMove(*f1, st);

            int numOfMoves = f1->howManyMoves(st);
            for (int l = 0; l < numOfMoves; l++) {
                f1->landscapeEffect();
                f1->neutObjEffect();
                cout << "Вы можете сделать еще один ход за своего персонажа\n";
                string ch;
                cin >> ch;
                while (!states.handle(ch)) {
                    cout << "Неверно введен персонаж!\n";
                    cin >> ch;
                }
                unitMove(*f1, ch);
            }
        }
        f1->landscapeEffect();
        f1->neutObjEffect();

        //k++;
        states.nextState();

        cout << "\nВведите \"info\", чтобы вывести информацию о юнитах и базе. Введите что угодно, чтобы ничего не выводить\n";
        cin >> st;
        if (st == "info") {
            it->displayUnitData(*f1);
            cout << endl;
            if (rule.maxNumOfBases == 2) {
                MEb->printBaseCondition();
                b->printBaseCondition();
            }
            system("pause");
        }

        bool win1st = true;
        bool win2nd = true;
        it->checkWin(*f1, win1st, win2nd);
        if (win1st && win2nd) {
            *logger << "#GAME: Ничья" << Logger::Endl();
            cout << "Ничья!!!\n";
            break;
        }
        else if (win1st) {
            *logger << "#GAME: Победа 1-го игрока" << Logger::Endl();
            cout << "Победил 1-й игрок!!!\n";
            break;
        }
        else if (win2nd) {
            *logger << "#GAME: Победа 2-го игрока" << Logger::Endl();
            cout << "Победил 2-й игрок!!!\n";
            break;
        }
    } while (st != "exit");
    *logger << "#GAME: Game over!" << Logger::Endl() << Logger::Endl();

    delete logger;
}

template <typename T>
void Game<T>::unitMove(Field& f, string character) {
    int direction = 0;
    getchar();
    cout << "Введите направление:\n";
    string opportunity = f.check(character);

    cin >> direction;

    char tmp = direction + '0';
    int checker = 0;
    for (int i = 0; i < (int)opportunity.length(); i++) {
        if (opportunity[i] == tmp) checker = 1;
    }

    if (checker == 1) {
        CommandField cf(&f, "move");
        string forMove = character + tmp;
        cf.execute(forMove);
        *logger << "#GAME: Попытка передвижения юнита \"" << character << "\" по направлению " << direction << Logger::Endl();
    }
    else {
        cout << "Такого направления нет! Вы пропускаете ход!\n";
    }
}

template <typename T>
bool Game<T>::addUnit(Field& f) {
    cout << "Введите обозначение персонажа, которого вы хотите добавить:\n";
    string character;
    cin >> character;
    getchar();
    if (character != "OD" && character != "OR" && character != "MS" && character != "MW" && character != "EA" && character != "EI") {
        cout << "Неправильное обозначение персонажа. Вы пропускаете ход!\n";
        system("pause");
        return false;
    }
    else {
        //f.add(character, -30, 0);
        CommandField cf(&f, "add");
        cf.execute(character);
        *logger << "#GAME: Добавление юнита \" " << character << "\"" << Logger::Endl();
    }

    return true;
}

template <typename T>
void Game<T>::delUnit(Field& f) {
    cout << "Введите обозначение персонажа, которого вы хотите удалить:\n";
    string character;
    cin >> character;
    //f.del(character);
    CommandField cf(&f, "del");
    cf.execute(character);
    *logger << "#GAME: Удаление юнита \" " << character << "\"" << Logger::Endl();
}

template <typename T>
void Game<T>::setLogger(Logger* logger_) {
    logger->setLogger(logger_);
}

template <typename T>
void Game<T>::setLogFormatter(LogFormatter* formatter) {
    logger->setFormat(formatter);
}

template <typename T>
void Game<T>::saveGame(string name, int turn) {
    *logger << "#GAME: попытка сохранения игры" << Logger::Endl();
    try {
        readMemento(name, turn);
    }
    catch (std::runtime_error a) {
        *logger << "#GAME: во время сохранения игры произошла ошибка" << Logger::Endl();
        std::cout << "Runtime error во время сохранения игры!\n";
    }
}

template <typename T>
void Game<T>::loadGame(string name, int& G, int& turn) {
    *logger << "#GAME: попытка загрузки игры" << Logger::Endl();
    try {
        GameMemento* memento = new GameMemento(name);
        restoreMemento(memento, G, turn);
    }
    catch (std::runtime_error a) {
        *logger << "#GAME: во время загрузки игры произошла ошибка" << Logger::Endl();
        cout << "Runtime error во время загрузки игры\n";
    }
    catch (std::logic_error a) {
        *logger << "#GAME: во время загрузки игры произошла ошибка" << Logger::Endl();
        cout << "Logic error во время загрузки игры\n";
    }
}

template <typename T>
void Game<T>::restoreMemento(CommandMemento* memento, int &G, int& turn) {
    SnapshotGame* snapGame = memento->loadFromFile();
    f1 = nullptr;
    for (Base* base : bases) {
        base = nullptr;
    }
    bases.clear();
    MEb = new Base(snapGame->getSize(), 'm', logger);
    b = new Base(snapGame->getSize(), 'o', logger);

    int numOfUnits = 0;
    for (unsigned i = 0; i < snapGame->getSize(); i++) {
        for (unsigned j = 0; j < snapGame->getSize(); j++) {
            if (snapGame->getField()->getCell()[i][j].getUnit().GetValue()[0] == 'M' || snapGame->getField()->getCell()[i][j].getUnit().GetValue()[0] == 'E'
                || snapGame->getField()->getCell()[i][j].getUnit().GetValue()[0] == 'O')
                numOfUnits++;
        }
    }

    f1 = new Field(snapGame->getSize(), numOfUnits, logger);
    f1->mas();
    f1->setNewField(snapGame->getField()->getCell());

    for (SnapshotBase* base : snapGame->getBases()) {
        vector <Warrior> orcs;
        vector <Warrior> mensAndElfs;

        for (SnapshotUnit* u : base->getUnits()) {
            Warrior tmp;
            tmp.SetValue(u->getName());
            tmp.SetArmor(u->getArmor());
            tmp.SetHealth(u->getHealth());
            tmp.SetDamage(u->getDamage());
            tmp.SetPlaceX(u->getX());
            tmp.SetPlaceY(u->getY());

            if (u->getName()[0] == 'M' || u->getName()[0] == 'E')
                mensAndElfs.push_back(tmp);
            else if (u->getName()[0] == 'O')
                orcs.push_back(tmp);
        }

        if (base->getTypeOfBase() == 'm') {
            MEb->setMEUnits(mensAndElfs);
            MEb->setOrcsUnits(orcs);
            MEb->setHealth(base->getHealth());
            f1->createBase(snapGame->getSize() - 1, 0, MEb);
        }
        else if (base->getTypeOfBase() == 'o') {
            b->setMEUnits(mensAndElfs);
            b->setOrcsUnits(orcs);
            b->setHealth(base->getHealth());
            f1->createBase(snapGame->getSize() - 1, snapGame->getSize() - 1, b);
        }
    }

    if (MEb->getBaseHealth() > 0)
        bases.push_back(MEb);
    if (b->getBaseHealth() > 0)
        bases.push_back(b);

    G = snapGame->getSize();
    turn = snapGame->getField()->getWhoseTurn();
    turn--;
}

template <typename T>
GameMemento* Game<T>::readMemento(string name, int turn) {
    SnapshotField* fieldSnap = new SnapshotField(f1->getSizeOfField(), f1->getCell(), turn);
    vector<SnapshotBase*> baseSnap;

    for (Base* base : bases) {
        char typeOfB = base->getTypeOfBase();
        int currentOrcsNum = base->getCurrentOrcsNum();
        int currentMEnum = base->getCurrentMEnum();
        int health = base->getBaseHealth();
        vector <Warrior> orcsUnits = base->getOrcsUnits();
        vector <Warrior> MEUnits = base->getMEUnits();

        vector<SnapshotUnit*> unitsSnap;
        for (Warrior w : orcsUnits) {
            string name = w.GetValue();
            int health = w.GetHealth();
            int armor = w.GetArmor();
            int damage = w.GetDamage();
            SnapshotUnit* unitSnap = new SnapshotUnit(name, damage, health, armor, w.GetPlaceX(), w.GetPlaceY());
            unitsSnap.push_back(unitSnap);
        }
        for (Warrior w : MEUnits) {
            string name = w.GetValue();
            int health = w.GetHealth();
            int armor = w.GetArmor();
            int damage = w.GetDamage();
            SnapshotUnit* unitSnap = new SnapshotUnit(name, damage, health, armor, w.GetPlaceX(), w.GetPlaceY());
            unitsSnap.push_back(unitSnap);
        }
        SnapshotBase* tmpSnapBase = new SnapshotBase(typeOfB, health, currentOrcsNum, currentMEnum, unitsSnap);
        baseSnap.push_back(tmpSnapBase);
    }
    SnapshotGame* gameSnap = new SnapshotGame(f1->getSizeOfField(), baseSnap, fieldSnap);
    return new GameMemento(name, gameSnap);
}
