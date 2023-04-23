//
// Created by anton on 6/1/20.
//

#include "HandlerStuff.h"

#include "../Command/CommandSelect.h"
#include "../Command/CommandInteract.h"
#include "../Command/CommandSummon.h"
#include "../../Exeptions/SelectionOutOfBoundsExeption.h"
#include "../../Exeptions/ObjectLimitExceededException.h"
#include "../../Exeptions/NoTerrainException.h"


bool HandlerStuff::process(std::unique_ptr<AbstractCommand> command) {
    std::shared_ptr<AbstractCommand> sCmd = std::move(command);
    bool flag = false;

    if(auto fr = facadeReciever.lock()) {
        switch (sCmd->commandType){

            case CommandType::CommandExit:assert(0);break;//Not handleble
            case CommandType::CommandRestart:assert(0);break;////Not handleble
            case CommandType::CommandSelect:{
                try {
                    auto cmd = std::static_pointer_cast<CommandSelect>(sCmd);
                    if (cmd->AB) {
                        fr->setSelectionA({cmd->x, cmd->y});
                    } else {
                        fr->setSelectionB({cmd->x, cmd->y});
                    }
                }catch(SelectionOutOfBoundsExeption& e){
                    std::cerr<<e<<std::endl;
                    std::cerr<<"Selected by;"<<sCmd->actor.lock()->name<<std::endl;
                    return false;
                }
                flag= true;
                break;
            }
            case CommandType::CommandInteract:{
                auto cmd = std::static_pointer_cast<CommandInteract>(sCmd);
                if(auto wt = fr->whosTurn().lock()){
                    if(auto a = cmd->actor.lock()){
                        if(a==wt) {
                            if(cmd->actStep){
                                flag = fr->act();
                            }else{
                                try {
                                    flag = fr->step();
                                }catch (NoTerrainException&e){
                                    std::cerr<<e<<std::endl;
                                    std::cerr<<"Fatal";
                                    exit(1);
                                }
                            }
                        }
                        else
                            flag= false;//Not my turn
                    }else{
                        assert(0);//Cmd without actor
                    }

                }else{
                    assert(0);//Noones turn
                }
                break;
            }
            case CommandType::CommandSummon:{
                auto cmd = std::static_pointer_cast<CommandSummon>(sCmd);
                if(auto wt = fr->whosTurn().lock()){
                    if(auto a = cmd->actor.lock()){
                        if(a==wt) {
                            try {
                                fr->summon(cmd->x, cmd->y, cmd->unitClass);
                            }catch (SelectionOutOfBoundsExeption&e){
                                std::cerr<<e<<std::endl;
                                std::cerr<<"Selected by;"<<sCmd->actor.lock()->name<<std::endl;
                                return false;
                            }catch (ObjectLimitExceededException& e){
                                std::cerr<<e<<std::endl;
                                std::cerr<<"Summoned by by;"<<sCmd->actor.lock()->name<<std::endl;
                                return false;
                            }
                            flag = true;
                        }
                        else
                            flag= false;
                    }else{
                        assert(0);//Cmd without actor
                    }
                }else{
                    assert(0);//Noones turn
                }
                break;
            }
        }
    }
    return flag;
}

HandlerStuff::HandlerStuff(const std::weak_ptr<FacadeReciever> &facadeReciever) : AbstractHandler({CommandType ::CommandSummon, CommandType ::CommandInteract, CommandType ::CommandSelect},
                                                                                                  facadeReciever) {}
