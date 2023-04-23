//
// Created by anton on 6/1/20.
//

#ifndef OOPROJECT_SENDER_H
#define OOPROJECT_SENDER_H

#include <memory>

#include "../Handler/AbstractHandler.h"

#include "ISender.h"

#include "../../GameLoop.h"

#include "../../Logger/AbstractLogger.h"

class Sender : public ISender {
public:
    Sender(const std::shared_ptr<AbstractHandler> &firstHandler);

    void setAndSend(std::unique_ptr<AbstractCommand> command) override;

    void set(std::unique_ptr<AbstractCommand> command) override;

    bool sendIfSet() override;

private:
    std::shared_ptr<AbstractHandler> firstHandler;
    std::unique_ptr<AbstractCommand> buffer;
    std::unique_ptr<AbstractCommand> sbuffer;
    std::weak_ptr<GameLoop> gameLoop;

    std::shared_ptr<AbstractLogger> logger;
public:
    void setLogger(const std::shared_ptr<AbstractLogger> &logger);
};


#endif //OOPROJECT_SENDER_H
