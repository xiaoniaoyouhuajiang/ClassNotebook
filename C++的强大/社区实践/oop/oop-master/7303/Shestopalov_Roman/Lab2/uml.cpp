/*%2F%2F Cool Class Diagram,

[Shape]<>1*[Point| x : double; y : double]

[Shape| #struct rgb: unsigned char r; unsigned char g; unsigned char b;| virtual void move() =0;virtual void rotate() =0; virtual void scale() =0; void setColor(rgb color); int angle = 0; int id]

[Shape] ^public- [Trap | Trap(Point Point Point Point);|  #Point #Point #Point #Point| void move(const Point&); void rotate(int); void scale(double); friend ostream& operator\\<\\<(ostream& Trap&); ]

[Shape] ^public-[Triangle| Triangle(Point Point Point); |  #Point #Point #Point;  | void move(double double); void rotate(int); void scale(double);  friend ostream& operator\\<\\<(ostream& Triangle&); ]

[Shape] ^public-[Pentagon | Pentagon(Point double); Pentagon(const Pentagon&)| #Point #double | void move(double double); void rotate(int); void scale(double); friend ostream& operator\\<\\<(ostream&  Pentagon&); ]
*/
