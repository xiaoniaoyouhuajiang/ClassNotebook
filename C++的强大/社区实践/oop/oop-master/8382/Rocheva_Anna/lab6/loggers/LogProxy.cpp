#include "LogProxy.hpp"

LogProxy::LogProxy(LoggerType loggerType) {
    switch (loggerType){
        case FILE_LOG: {
            std::cout << "File name:" << std::endl;
            std::string name;
            std::cin >> name;
            logger = new FileLogger(name);
            break;
        }
        case TERMINAL_LOG:
            logger = new TerminalLogger;
            break;
        case NO_LOG:
            logger = new NoLogger;
            break;
    }
}
