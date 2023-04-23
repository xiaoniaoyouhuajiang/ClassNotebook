//
// Created by anton on 6/1/20.
//

#include "Sender.h"

#include "../Command/everything.h"
void Sender::setAndSend(std::unique_ptr<AbstractCommand> command) {
    set(std::move(command));
    if(auto gl = gameLoop.lock()){
        gl->loop();
    }
}

void Sender::set(std::unique_ptr<AbstractCommand> command) {
    
    AbstractCommand* cmd = &(*command);
    std::string n;;
    if(auto ac = cmd->actor.lock()){
        n = ac->name;
    } else{
        assert(0);
    }
    switch (cmd->commandType){

        case CommandType::CommandExit:{
            logger<<("Player "+n+" exited");
            break;
        }
        case CommandType::CommandRestart:{
            logger<<("Player "+n+" restarted");
            break;
        }
        case CommandType::CommandSelect:{
            CommandSelect* nCmd = static_cast<CommandSelect*>(cmd);
            logger<<("Player "+n+" selected "+(nCmd->AB?"A":"B")+" "+std::to_string(nCmd->x)+":"+std::to_string(nCmd->y));
            break;
        }
        case CommandType::CommandInteract:{
            CommandInteract* nCmd = static_cast<CommandInteract*>(cmd);
            logger<<("Player "+n+" "+(nCmd->actStep?"acted":"stepped"));  
            break;
        }
        case CommandType::CommandSummon:{
            CommandSummon* nCmd = static_cast<CommandSummon*>(cmd);
            logger<<("Player "+n+" "+"summoned unit class "+std::to_string(int(nCmd->unitClass))+" at "+std::to_string(nCmd->x)+":"+std::to_string(nCmd->y));
            break;
        }
    }

    buffer=std::move(command);
}

bool Sender::sendIfSet() {
    if(buffer){
        sbuffer=std::move(buffer);
        buffer.reset();
        firstHandler->check(std::move(sbuffer));
        sbuffer.reset();
        return true;
    }else{
        return false;
    }
}

Sender::Sender(const std::shared_ptr<AbstractHandler> &firstHandler) : firstHandler(firstHandler) {
    buffer=std::unique_ptr<AbstractCommand>(nullptr);
}

void Sender::setLogger(const std::shared_ptr<AbstractLogger> &logger) {
    Sender::logger = logger;
}
