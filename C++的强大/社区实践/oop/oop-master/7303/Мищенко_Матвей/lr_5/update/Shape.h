
int id1=0;
class Shape
{public:
    Shape (){};
    virtual ~Shape(){};
    virtual void move_by_coordinates(int x,int y)=0;
    virtual void turn_by_corner(int corner)=0;
    virtual void inscrease_by_cf(int cf)=0;
    
   
    
    std::pair<int,int>centr;
    int color[3];
    int id;
};
class Rectangle:public Shape
{  public:
    Rectangle(double width,double height,std::pair<int,int>centr)
    {   basis1=std::make_pair(std::make_pair(centr.first-(width/2),centr.second+(height/2)),
                              std::make_pair(centr.first+(width/2),centr.second+(height/2)));
        basis2=std::make_pair(std::make_pair(centr.first-(width/2),centr.second-(height/2)),
                              std::make_pair(centr.first+(width/2),centr.second-(height/2)));
        this->centr=centr;
        this->id=id1;
        id1++;
    this->color[0]=rand()%255; this->color[1]=rand()%255; this->color[2]=rand()%255;
    }
    void move_by_coordinates(int x,int y);
    void turn_by_corner(int corner);
    void inscrease_by_cf(int cf);
    friend std::ostream& operator <<(std::ostream &out,const Rectangle &rec);
    ~Rectangle(){};
private:
    std::pair<std::pair<double ,double >, std::pair<double,double >> basis1;
    std::pair<std::pair<double ,double > , std::pair<double ,double >> basis2;
    
};

class Trapeze:public Shape
{public:
    Trapeze(double height,double size_basis1,double size_basis2,double corner1,std::pair<int,int>centr)
    {
        if (corner1==90){
            basis1=std::make_pair(std::make_pair(centr.first-(size_basis2/2),centr.second+(height/2)),
                                  std::make_pair(centr.first-(size_basis2/2)+size_basis1,centr.second+(height/2)));
            basis2=std::make_pair(std::make_pair(centr.first-(size_basis2/2),centr.second-(height/2)),
                                  std::make_pair(centr.first+(size_basis2/2),centr.second-(height/2)));
        }
        else{
            basis1=std::make_pair(std::make_pair(centr.first-(size_basis2/2)+(height/tan((corner1*Pi)/180)),
                                                 centr.second+height/2),
                                  std::make_pair(centr.first-(size_basis2/2)+(height/tan((corner1*Pi)/180))+size_basis1,centr.second+(height/2)));
            
            basis2=std::make_pair(std::make_pair(centr.first-(size_basis2/2),centr.second-(height/2)),
                                  std::make_pair(centr.first+(size_basis2/2),centr.second-(height/2)));}
        this->id=id1;
        id1++;
        this->centr=centr;
        this->color[0]=rand()%255; this->color[1]=rand()%255; this->color[2]=rand()%255;

    }
    void move_by_coordinates(int x,int y);
    void turn_by_corner(int corner);
    void inscrease_by_cf(int cf);
    friend std::ostream& operator <<(std::ostream &out,const  Trapeze &tr);
    ~Trapeze(){};
private:
    
    std::pair<std::pair<double ,double >, std::pair<double,double >> basis1;
    std::pair<std::pair<double ,double > , std::pair<double ,double >> basis2;
};

class Lsosceles_trapeze:public Shape
{ public:
    Lsosceles_trapeze(double height,double size_basis1,double size_basis2,std::pair<int,int>centr)
    {
        basis1=std::make_pair(std::make_pair(centr.first-(size_basis1/2),centr.second+(height/2)),
                              std::make_pair(centr.first+(size_basis1/2),centr.second+(height/2)));
        basis2=std::make_pair(std::make_pair(centr.first-(size_basis2/2),centr.second-(height/2)),
                              std::make_pair(centr.first+(size_basis2/2),centr.second-(height/2)));
        this->id=id1;
        id1++;
        this->centr=centr;
        this->color[0]=rand()%255; this->color[1]=rand()%255; this->color[2]=rand()%255;

    }
    void move_by_coordinates(int x,int y);
    void turn_by_corner(int corner);
    void inscrease_by_cf(int cf);
    friend std::ostream& operator <<(std::ostream &out,const Lsosceles_trapeze &Lr_tr);
    ~ Lsosceles_trapeze(){};
private:
    
    
    std::pair<std::pair<double ,double >, std::pair<double ,double>> basis1;
    std::pair<std::pair<double ,double > , std::pair<double ,double >> basis2;
};
