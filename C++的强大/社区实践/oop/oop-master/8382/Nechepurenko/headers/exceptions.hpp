#pragma once
#include "base.hpp"
#include <exception>

class NoCurrentPlayerException : public std::exception {
    public:
        NoCurrentPlayerException(Base* base) : baseWithout(base) {}
        Base* getBase() {return baseWithout;}
        const char * what () const throw () {
            return "No players on this base to action!\n";
        }
    private:
        Base* baseWithout;
};

class FileErrorException : public std::exception {
    public:
        FileErrorException(std::string path, char flag) : path(path), flag(flag) {}
        std::string getPath() {return path;}
        char getFlag() {return flag;}
        const char * what() const throw () {
            return "Cannot open the file!\n";
        }
    private:
        std::string path;
        char flag;
};

class NoNextException : public std::exception {
public:
    NoNextException(Base* base) : base(base) {}
    Base* getBase() {return base;}
    const char * what() const throw () {
        return "No next player at this base!\n";
    }
private:
    Base* base;
};

class UnserializerException : public std::exception {
public:
    UnserializerException(char reason) : reason(reason) {}
    char getReason() {return reason;}
    const char * what() const throw () {
        return "Game load exception!\n";
    }
private:
    char reason;
};

class UnknownCommandException : public std::exception {
public:
    UnknownCommandException(char command = '.', char arg = '.') : command(command), arg(arg) {}
    char getCommand() {return command;}
    char getArg() {return arg;}
    const char * what() const throw () {
        return "Unknown command exception!\n";
    }
private:
    char command;
    char arg;
};