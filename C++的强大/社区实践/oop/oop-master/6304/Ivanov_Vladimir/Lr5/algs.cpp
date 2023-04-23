#include "algs.hpp"

vector<shared_ptr<Shape>> create(){ //creating a vector of 1000 elements
    vector<shared_ptr<Shape>> a(1000);
    srand(time(nullptr));
    for(int i=0;i<1000;i++){
        int k=rand() % 3;
        if(!k)
            a[i]=shared_ptr<Shape>(new Rectangle(rand()%6,rand()%6,1+rand()%6,1+rand()%6));
        else if(k==1)
            a[i]=shared_ptr<Shape>(new Pentagon(rand()%6,rand()%6,6+rand()%6,6+rand()%6,12+rand()%6,12+rand()%6,-6+rand()%6,-6+rand()%6,-12+rand()%6,-12+rand()%6));
        else
            a[i]=shared_ptr<Shape>(new Ellipse(rand()%6,rand()%6,1+rand()%6,1+rand()%6));
    }
    return a;
}

void print(const vector<shared_ptr<Shape>>& mass){ //output of the contents of a vector
    for(auto i: mass)
        std::cout<<*(i.get());
}

bool allsquareless(const vector<shared_ptr<Shape>>& mass, int k){ //check of the squares of figures
    for(const auto& it: mass){
        if((*it).getSquare()<k) //If an element has a square less than the specified one, it returns false
            return false;
    }
    return true;
}

void copyBad(vector<shared_ptr<Shape>>& mass, int k){ //Copies elements whose square is larger than the specified
    int n=mass.size();
    for(int i=0;i<n;i++){
        if((*mass[i]).getSquare()>k){
            mass.insert(mass.begin()+i,mass[i]);
            i++;
            n++;
        }
    }
}