#include "Adapter.hpp"

void Adapter::setLog(std::string logString) {
    if (!logger)
        return;
    logger->setLog(logString);
    std::string log = "\nField status:\nCells without units: " + std::to_string(field->getHeight()*field->getWidth() - field->getNumUnits()) + "\n";
    logger->addLog(log);
}

void Adapter::addLog(std::string logString) {
    if (!logger)
        return;
    logger->addLog(logString);
}
