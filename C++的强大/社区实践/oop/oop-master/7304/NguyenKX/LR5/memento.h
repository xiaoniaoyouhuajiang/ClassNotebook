#ifndef COMMAND_H
#define COMMAND_H
class Memento{
    typedef unsigned char byte;
    template <typename T>
    friend class HandlerOutput;

private:
    byte *state;
public:
    std::size_t sizeInByte;

    Memento(byte *state, std::size_t sizeInByte): sizeInByte(sizeInByte){
        this->state = new byte[sizeInByte];
        std::copy(state, state+sizeInByte, this->state);
    }

    ~Memento(){
        delete[] state;
    }
};
#endif // COMMAND_H
