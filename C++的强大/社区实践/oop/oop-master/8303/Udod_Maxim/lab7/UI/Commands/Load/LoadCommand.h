//
// Created by shenk on 02.04.2020.
//

#ifndef UNTITLED13_LOADCOMMAND_H
#define UNTITLED13_LOADCOMMAND_H

#include "../../LoadCommandInterpreter.h"
#include "../../../Utils/utils.h"
#include "../../../Exceptions/InvalidFileLoaddingException.h"
#include "../../../Exceptions/DoublePlacingOnFieldException.h"
#include "../../../Exceptions/GameFieldOutOfRangeException.h"
#include "../../../Exceptions/ImpossibleMoveException.h"

class LoadCommand: public Command {

private:

    std::ifstream fs;
    LoadCommandInterpreter interpreter;

public:

    explicit LoadCommand(std::string &filename): fs(filename){}
    void execute(GameInfo &gameInfo) override{

        gameInfo.newGame();

        std::string cmd;

        std::hash<std::string> hashFunc;
        unsigned long int calculatedHash = 0;
        unsigned long int fileHash = 0;

        std::string fileHashStr;
        std::getline(fs, fileHashStr);

        fileHash = utils::StrToInt(fileHashStr);

        while (std::getline(fs, cmd)){

            CommandPtr command = interpreter.handle(cmd);
            try {
                command->execute(gameInfo);
            } catch(DoubleBasePlacingException &exception) {
                game::log << "[FileLoader]" << "Player " << exception.playerIndex << " trying to place base second time." << game::logend;
            } catch (DoublePlacingOnFieldException &exception){
                game::log << "[FileLoader]" << "This cell is busy by other object." << game::logend;
            } catch (GameFieldOutOfRangeException &exception){
                game::log << "[FileLoader]" << "Out of range. Cell " << exception.x << " " << exception.y << " is not exist." << game::logend;
            } catch (ImpossibleMoveException &exception){
                game::log << "[FileLoader]" << "Can't move to this cell. They busy by other object." << game::logend;
            } catch (...){
                game::log << "[FileLoader]" << "Undefined error." << game::logend;
            }
            auto memento = command->getMemento();
            gameInfo.addToHistory(memento);
            calculatedHash += memento->getHash(hashFunc);
            gameInfo.nextUser();

        }

        game::log << "String hash from file: " << fileHashStr << game::logend;
        game::log << "Int hash from file: " << fileHash << game::logend;
        game::log << "Calculated hash: " << calculatedHash << game::logend;
        game::log << "Read commands count: " << gameInfo.getHistory().size() << game::logend;

        if (fileHash != calculatedHash){
            game::log << "Wrong file format. The correctness of the loaded field is not guaranteed." << game::logend;
            throw InvalidFileLoaddingException();
        }

    }

    ~LoadCommand() override{

        fs.close();

    }

};

class LoadCommandHandler: public CommandHandler{

public:

    bool canHandle(std::vector<std::string> &cmd) override{

        return cmd.size() == 2 && cmd[0] == "load";

    }

    CommandPtr handle(std::vector<std::string> &cmd) override{

        if (canHandle(cmd)){
            return CommandPtr(new LoadCommand(cmd[1]));
        }

        if (next) return next->handle(cmd);

        return std::make_unique<Command>();

    }

};


#endif //UNTITLED13_LOADCOMMAND_H
