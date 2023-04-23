//
// Created by user on 31.03.19.
//

#ifndef OOP_2_COLOR_H
#define OOP_2_COLOR_H
class Color{
    unsigned int R,G,B;
public:
    Color(unsigned int R,unsigned int G,unsigned int B): R(R%256),G(G%256),B(B%256){};
    unsigned int get_R(){
        return R;
    }
    unsigned int get_G(){
        return G;
    }
    unsigned int get_B(){
        return B;
    }
};
#endif //OOP_2_COLOR_H
