# Points
we know what points are ; it is most basic building block of all higher dimensional geometry objects.

so we reprenst points with coordinates {x,y} with respect to origin {0,0}.
use the data type as defined in problem.
```cpp
struct point{
    int x,y;    
    point_i(){  //default constructor
        x=y=0;
    }

    point_i(int _x,int _y): x(_x),y(_y) {}      //user defined points
};
```

you can use double instead of int when precision is needed.

To sort the points, we will overload the `less than operator` inside `point`
```cpp
struct point{
    double x, y;
    point() { x = y = 0.0; }
    point(double _x, double _y) : x(_x), y(_y) {} 
    bool operator < (point other) const { // override less than operator 
        if (fabs(x - other.x) > EPS) // useful for sorting 
            return x < other.x; // first criteria , by x-coordinate 
            return y < other.y; } }; // second criteria, by y-coordinate

// in int main(), assuming we already have a populated vector<point> P 
sort(P.begin(), P.end()); // comparison operator is defined above
```

To test if two points are equal, do via overloading equal operator inside struct `point`.
```cpp
struct point { 
    double x, y;
    point() { x = y = 0.0; } 
    point(double _x, double _y) : x(_x), y(_y) {} 
    // use EPS (1e-9) when testing equality of two floating points 

    bool operator == (point other) const { 
        return (fabs(x - other.x) < EPS && (fabs(y - other.y) < EPS)); 
    }    
};

// in int main()
point P1(0, 0), P2(0, 0), P3(0, 1); //true
printf("%d\n", P1 == P2); printf("%d\n", P1 == P3);  // false
```

Euclidean Distance
```cpp
double dist(point p1,point p2){
    //hypot(dx,dy) returns sqrt(dx*dx+dy*dy)
    return hypot(p1.x-p2.x,p1.y-p2.y);
}
```

Rotate point by \theta angle counter clockwise around orign(0,0)
```cpp
point rotate(point p,double theta){
    double rad=DEG_TO_RAD(theta);
    return point(p.x * cos(rad)- p.y * sin(rad),p.x*sin(rad)+p.y*cos(rad));
}
```


