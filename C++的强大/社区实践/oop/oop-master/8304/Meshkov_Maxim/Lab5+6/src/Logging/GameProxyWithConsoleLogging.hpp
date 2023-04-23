#pragma once

#include "GameProxyWithLogging.hpp"
#include "PlainLoggerToOstreamAdapter.hpp"
#include "WithTimeLoggerToOstreamAdapter.hpp"

class GameProxyWithConsoleLogging : public GameProxyWithLogging {
public:
    GameProxyWithConsoleLogging(std::shared_ptr<GameInterface> game, bool withTime)
        : GameProxyWithLogging(std::move(game), static_cast<std::shared_ptr<Logger>>(withTime ?
            new WithTimeLoggerToOstreamAdapter(&std::cout) : new PlainLoggerToOstreamAdapter(&std::cout)))
    {}
};