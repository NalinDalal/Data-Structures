# Circle

Circle centered at (a,b) and radius `r` is set of all points (x,y) such that $(x-a)^2 + (y-b)^2 = r^2$

to check if point lies inside, outside or on the circle:
```cpp
int insideCircle(point_i p, point_i c,int r){
    int dx=p.x-c.x, dy=p.y-c.y;

    int Euc=dx*dx+dy*dy, rSq=r*r;
    return Euc<rSq?0:Euc==rSq?1:2;
}
```

Pi: ratio of circumeference to diameter
`pi=acos(-1.0)` or `pi=2*acos(0.0)`

radius: `r`
Diameter: `d=2*r`
circumeference: `c=2*pi*r`
Area: `A=pi*pow(r,2)`

length of Arc(alpha is angle): $\frac{\alpha}{360} * c$

length of chord(line segment joining 2 points on circumeference): sqrt(2*pow(r,2)*(1-cos /alpha)) or 2*r*sin(\frac{/alpha }{2})


