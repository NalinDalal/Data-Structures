# Lines
set of points whose coordinates satisfy a given linear equation: `ax+by+c=0`.
```cpp
struct line{
    double a,b,c;
}
```

If 2 points are given through which the line passes then:
```cpp
//ans is stored in 3rd parameter(pass by reference)
void pointsToLine(point p1,point p2, line &l){
    if (fabs(p1.x - p2.x) < EPS) { // vertical line is fine 
        l.a = 1.0;
        l.b = 0.0;
        l.c = -p1.x; // default values
    } else {
        l.a = -(double)(p1.y - p2.y) / (p1.x - p2.x); 
        l.b=1.0;// IMPORTANT: we fix the value of b to 1.0
        l.c = -(double)(l.a * p1.x) - p1.y; 
    }
}
```

If 2 lines are parallel by checking whether the coefficients are same or not.
```cpp
bool areParallel(line l1,lin l2){   //check coefficients of a & b
    return (fabs(l1.a-l2.a)<EPS) && (fabs(l1.b-l2,b)<EPS);
}

bool areSame(line l1,line l2){  //check coefficients of c
    return areParallel(l1,l2) && (fabs(l1.c-l2.c)<EPS);
}
```

If 2 lines are not parallel, they will intersect at a point
```cpp
//return true(+intersect point) if 2 lines intersect
bool areIntersect(line l1,line l2, point &p){
    if(areParallel(l1,l2))return false; //no intersect

    //solve system of equation
    p.x=(l2.b*l1.c-l1.b*l2.c)/(l2.a*l1.b-l1.a*l2.b);

    //spcl case: test for vertical line to avoid division by zero
    if(fabs(l1.b)>EPS) p.y= -(l1.a*p.x + l1.c);
    else p.y= -(l2.a*p.x+l2.c);

    return true;
}
```

# Vectors
Lie segment with a direction.

translate a point w.r.t, a vector as a vector describes displacmeent magnitude in x and y axis.

```cpp
struct vec{
    double x,y;
    vec(double _x,double _y):x(_x),y(_y) {}
};

vec toVec(point a,point b){     //cpnvert 2 points to vector a->b
    return vec(b.x-a.x,b.y-a.y);
}

vec scale(vec v,double s){
    return vec(v.x*s,v.y*s);
}

point translate(point p,vec v){ //translate p according to v
    return point(p.x+v.x,p.y+v.y);
}
```

# Minimum distance b/w point `p` and line `l`.
compute `c` that closes to point `p`; `c` lies on `l`

compute euclidean distance b/w `p` and `c`

`c=a+u*ab`


```
double dot(vec a,vec b){
    return (a.x+b.x+a.y*b.y);
}

double norm_sq(vec v) { return v.x * v.x + v.y * v.y; }


// returns the distance from p to the line defined by 
// two points a and b (a and b must be different) 
// the closest point is stored in the 4th parameter (byref) 

double distToLine(point p, point a, point b, point &c) {
// formula: c = a + u * ab 
vec ap = toVec(a, p), ab = toVec(a, b); 
double u = dot(ap, ab) / norm_sq(ab); 
c = translate(a, scale(ab, u)); // translate a to c 
return dist(p, c); } // Euclidean distance between p and c
```

# instead of line there is line segment

```cpp
// returns the distance from p to the line segment ab defined by 
// two points a and b (still OK if a == b) 
// the closest point is stored in the 4th parameter (byref) 

double distToLineSegment(point p, point a, point b, point &c) {
    vec ap = toVec(a, p), ab = toVec(a, b); 
    double u = dot(ap, ab) / norm_sq(ab);    

    if (u < 0.0) { 
        c = point(a.x, a.y); // closer to a
        return dist(p, a);  // Euclidean distance between p and a 
    }

    if (u > 1.0) {
        c = point(b.x, b.y); // closer to b
        return dist(p, b);  // Euclidean distance between p and b 
    }

    return distToLine(p, a, b, c);
} // run distToLine as above
```

# compute angle aob
```cpp
double angle(point a,point o,point b){
    vec oa=toVec(o,a), ob=toVec(o,b);
    return acos(dot(oa,ob)/sqrt(norm_sq(oa)*norm_sq(ob)));
}
```


