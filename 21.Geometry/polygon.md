# Algorithm on Polygon with Libraries

**Polygon** is a plane figure bounded by a closed path composed of a finite sequence of straight line segments. These segments are called edges or sides. The point where two edges meet is the polygon's vertex or corner.

## Polygon Representation

standard way: enumerate vertices in either clockwise or counter clockwise order, with the first vertex equal to the last vertex.

default vertex ordering is **counter clockwise**.

```cpp
// 6 points, entered in counter clockwise order, 0-based indexing
vector<point> P;
P.push_back(point(1, 1));   // P0
P.push_back(point(3, 3));   // P1
P.push_back(point(9, 1));   // P2
P.push_back(point(12, 4));  // P3
P.push_back(point(9, 7));   // P4
P.push_back(point(1, 7));   // P5
P.push_back(P[0]);          // important: loop back
```

## Perimeter of a Polygon

perimeter of a polygon (convex or concave) with $n$ vertices = sum of Euclidean distances of consecutive edges

```cpp
// returns the perimeter, which is the sum of Euclidian distances
// of consecutive line segments (polygon edges)
double perimeter(const vector<point> &P) {
  double result = 0.0;
  for (int i = 0; i < (int)P.size()-1; i++)  // remember that P[0] = P[n-1]
    result += dist(P[i], P[i+1]);
  return result; }
```

## Area of a Polygon

signed area $A$ of a polygon with $n$ vertices — compute the determinant of the matrix:

$$A = \frac{1}{2} \times (x_0 y_1 + x_1 y_2 + \ldots + x_{n-1} y_0 - x_1 y_0 - x_2 y_1 - \ldots - x_0 y_{n-1})$$

```cpp
// returns the area, which is half the determinant
double area(const vector<point> &P) {
  double result = 0.0, x1, y1, x2, y2;
  for (int i = 0; i < (int)P.size()-1; i++) {
    x1 = P[i].x; x2 = P[i+1].x;
    y1 = P[i].y; y2 = P[i+1].y;
    result += (x1 * y2 - x2 * y1);
  }
  return fabs(result) / 2.0; }
```

## Checking if a Polygon is Convex

polygon is **Convex** if any line segment drawn inside it does not intersect any edge. Otherwise the polygon is **Concave**.

computational check: all three consecutive vertices of the polygon form the same turns — all left turns/ccw if listed counter clockwise, all right turns/cw if listed clockwise. If at least one triple breaks this, the polygon is concave.

```cpp
bool isConvex(const vector<point> &P) {      // returns true if all three
  int sz = (int)P.size();  // consecutive vertices of P form the same turns
  if (sz <= 3) return false;   // a point/sz=2 or a line/sz=3 is not convex
  bool isLeft = ccw(P[0], P[1], P[2]);               // remember one result
  for (int i = 1; i < sz-1; i++)               // then compare with the others
    if ((ccw(P[i], P[i+1], P[(i+2) == sz ? 1 : i+2])) != isLeft)
      return false;              // different sign -> this polygon is concave
  return true; }                               // this polygon is convex
```

## Checking if a Point is Inside a Polygon

uses the **winding number algorithm** — works for both convex and concave polygons.

compute the sum of angles between three points $\{P[i],\ pt,\ P[i+1]\}$ where $P[i]$-$P[i+1]$ are consecutive sides. add angle for left turns, subtract for right turns. if final sum is $2\pi$ (360 degrees), then $pt$ is inside polygon $P$.

```cpp
// returns true if point p is in either convex/concave polygon P
bool inPolygon(point pt, const vector<point> &P) {
  if ((int)P.size() == 0) return false;
  double sum = 0;   // assume the first vertex is equal to the last vertex
  for (int i = 0; i < (int)P.size()-1; i++) {
    if (ccw(pt, P[i], P[i+1]))
      sum += angle(P[i], pt, P[i+1]);               // left turn/ccw
    else sum -= angle(P[i], pt, P[i+1]); }          // right turn/cw
  return fabs(fabs(sum) - 2*PI) < EPS; }
```

## Cutting Polygon with a Straight Line

cut a *convex* polygon $Q$ into two convex sub-polygons along a line defined by two points $a$ and $b$.

idea: iterate through vertices of $Q$. if line $ab$ and vertex $v$ form a left turn ($v$ is on left side of $ab$), put $v$ in new polygon $P$. when a polygon edge crosses line $ab$, add the intersection point to $P$.

```cpp
// line segment p-q intersect with line A-B.
point lineIntersectSeg(point p, point q, point A, point B) {
  double a = B.y - A.y;
  double b = A.x - B.x;
  double c = B.x * A.y - A.x * B.y;
  double u = fabs(a * p.x + b * p.y + c);
  double v = fabs(a * q.x + b * q.y + c);
  return point((p.x * v + q.x * u) / (u+v), (p.y * v + q.y * u) / (u+v)); }

// cuts polygon Q along the line formed by point a -> point b
// (note: the last point must be the same as the first point)
vector<point> cutPolygon(point a, point b, const vector<point> &Q) {
  vector<point> P;
  for (int i = 0; i < (int)Q.size(); i++) {
    double left1 = cross(toVec(a, b), toVec(a, Q[i])), left2 = 0;
    if (i != (int)Q.size()-1) left2 = cross(toVec(a, b), toVec(a, Q[i+1]));
    if (left1 > -EPS) P.push_back(Q[i]);       // Q[i] is on the left of ab
    if (left1 * left2 < -EPS)           // edge (Q[i], Q[i+1]) crosses line ab
      P.push_back(lineIntersectSeg(Q[i], Q[i+1], a, b));
  }
  if (!P.empty() && !(P.back() == P.front()))
    P.push_back(P.front());      // make P's first point = P's last point
  return P; }
```

note: `cutPolygon` returns only the left side. for the right side swap $a$ and $b$.

## Convex Hull

**Convex Hull** of a set of points $P$ is the smallest convex polygon $CH(P)$ such that each point in $P$ is either on the boundary of $CH(P)$ or in its interior.

analogy: points are nails on a flat plane, a rubber band released around them forms the convex hull.

algorithm used: **Graham's Scan** — $O(n \log n)$

### Graham's Scan

1. find pivot $P_0$ = point with lowest $y$ (break tie by rightmost $x$)
2. sort all other points by angle w.r.t. pivot $P_0$
3. maintain a stack $S$ — top three items must always make a left turn. push each point; if it causes a right turn, pop until left turn is restored.

```cpp
point pivot(0, 0);
bool angleCmp(point a, point b) {          // angle-sorting function
  if (collinear(pivot, a, b))                          // special case
    return dist(pivot, a) < dist(pivot, b);  // check which one is closer
  double d1x = a.x - pivot.x, d1y = a.y - pivot.y;
  double d2x = b.x - pivot.x, d2y = b.y - pivot.y;
  return (atan2(d1y, d1x) - atan2(d2y, d2x)) < 0; }  // compare two angles

vector<point> CH(vector<point> P) {     // the content of P may be reshuffled
  int i, j, n = (int)P.size();
  if (n <= 3) {
    if (!(P[0] == P[n-1])) P.push_back(P[0]); // safeguard from corner case
    return P; }                              // special case, the CH is P itself

  // first, find P0 = point with lowest Y and if tie: rightmost X
  int P0 = 0;
  for (i = 1; i < n; i++)
    if (P[i].y < P[P0].y || (P[i].y == P[P0].y && P[i].x > P[P0].x))
      P0 = i;

  point temp = P[0]; P[0] = P[P0]; P[P0] = temp;  // swap P[P0] with P[0]

  // second, sort points by angle w.r.t. pivot P0
  pivot = P[0];                   // use this global variable as reference
  sort(++P.begin(), P.end(), angleCmp);           // we do not sort P[0]

  // third, the ccw tests
  vector<point> S;
  S.push_back(P[n-1]); S.push_back(P[0]); S.push_back(P[1]); // initial S
  i = 2;                                          // then, we check the rest
  while (i < n) {            // note: N must be >= 3 for this method to work
    j = (int)S.size()-1;
    if (ccw(S[j-1], S[j], P[i])) S.push_back(P[i++]); // left turn, accept
    else S.pop_back(); }    // or pop the top of S until we have a left turn
  return S; }                                         // return the result
```

time complexity: $O(n \log n)$ — dominated by the angle sort step.

alternative: **Andrew's Monotone Chain** — same $O(n \log n)$ but sorts by x-coordinate instead of angle, avoids costly `atan2` comparisons. computes upper and lower hull separately.
