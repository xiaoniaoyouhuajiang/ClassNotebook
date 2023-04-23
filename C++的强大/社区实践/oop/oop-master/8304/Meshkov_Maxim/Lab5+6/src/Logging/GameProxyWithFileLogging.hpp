#pragma once

#include <fstream>

#include "GameProxyWithLogging.hpp"
#include "PlainLoggerToOstreamAdapter.hpp"
#include "WithTimeLoggerToOstreamAdapter.hpp"

class GameProxyWithFileLogging : public GameProxyWithLogging {
public:
    GameProxyWithFileLogging(std::shared_ptr<GameInterface> game, const std::string &fileName, bool withTime)
            : m_fout(fileName), GameProxyWithLogging(std::move(game),
                static_cast<std::shared_ptr<Logger>>(withTime ?
                new WithTimeLoggerToOstreamAdapter(&m_fout) : new PlainLoggerToOstreamAdapter(&m_fout)))
    {}
    ~GameProxyWithFileLogging() {
        m_fout.close();
    }

private:
    std::ofstream m_fout;
};