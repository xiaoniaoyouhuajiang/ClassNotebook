#include "logwriter.h"

LogWriter* LogWriter::instance = nullptr;

LogWriter::LogWriter(int mode){
    changeMode(mode);
}
LogWriter& LogWriter::getInstance(){
    if(instance==nullptr){
        instance = new LogWriter(0);
    }
    return *instance;
}
void LogWriter::changeMode(int mode){
    switch(mode){
    case NO_LOG:
        writer.reset(nullptr);
        break;
    case BUFFERED_LOG:
        writer.reset(new BufferedWriter(new TxtWriter("log.txt",true))) ;
        break;
    case REALTIME_LOG:
        writer.reset(new TxtWriter("log.txt"));
    default:
        break;
    }
}
void LogWriter::log(std::string message){
    if(writer!=nullptr){
        std::stringstream ss;
        std::time_t now = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
        ss<<"["<<std::ctime(&now)<<"] "<<message;
        writer->write(ss.str());
    }
}
LogWriter::~LogWriter(){
}
