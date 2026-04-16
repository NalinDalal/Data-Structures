# 2D Objects: Triangles

**Triangle** (three angles) is a polygon with three vertices and three edges.

Types of triangles:
- **Equilateral**: Three equal-length edges and all interior angles are 60 degrees.
- **Isosceles**: Two edges have the same length and two interior angles are the same.
- **Scalene**: All edges have different length.
- **Right**: One of its interior angles is 90 degrees (a **right angle**).

## Area

triangle with base $b$ and height $h$ has area $A = 0.5 \times b \times h$

## Perimeter and Semi-Perimeter

triangle with three sides $a$, $b$, $c$ has **perimeter** $p = a + b + c$

**semi-perimeter** $s = 0.5 \times p$

## Heron's Formula

triangle with 3 sides $a$, $b$, $c$ and semi-perimeter $s$ has area:

$$A = \sqrt{s \times (s-a) \times (s-b) \times (s-c)}$$

## Incircle

triangle with area $A$ and semi-perimeter $s$ has an **inscribed circle (incircle)** with radius $r = A/s$

```cpp
double rInCircle(double ab, double bc, double ca) {
  return area(ab, bc, ca) / (0.5 * perimeter(ab, bc, ca)); }

double rInCircle(point a, point b, point c) {
  return rInCircle(dist(a, b), dist(b, c), dist(c, a)); }
```

center of incircle is the meeting point between the triangle's *angle bisectors*
get the center by finding intersection of two angle bisectors

```cpp
// returns 1 if there is an inCircle center, returns 0 otherwise
// if this function returns 1, ctr will be the inCircle center
// and r is the same as rInCircle
int inCircle(point p1, point p2, point p3, point &ctr, double &r) {
  r = rInCircle(p1, p2, p3);
  if (fabs(r) < EPS) return 0;          // no inCircle center

  line l1, l2;                           // compute two angle bisectors
  double ratio = dist(p1, p2) / dist(p1, p3);
  point p = translate(p2, scale(toVec(p2, p3), ratio / (1 + ratio)));
  pointsToLine(p1, p, l1);

  ratio = dist(p2, p1) / dist(p2, p3);
  p = translate(p1, scale(toVec(p1, p3), ratio / (1 + ratio)));
  pointsToLine(p2, p, l2);

  areIntersect(l1, l2, ctr);             // get their intersection point
  return 1; }
```

## Circumcircle

triangle with 3 sides $a$, $b$, $c$ and area $A$ has a **circumscribed circle (circumcircle)** with radius:

$$R = \frac{a \times b \times c}{4 \times A}$$

```cpp
double rCircumCircle(double ab, double bc, double ca) {
  return ab * bc * ca / (4.0 * area(ab, bc, ca)); }

double rCircumCircle(point a, point b, point c) {
  return rCircumCircle(dist(a, b), dist(b, c), dist(c, a)); }
```

center of circumcircle is the meeting point between the triangle's *perpendicular bisectors*

## Triangle Inequality

to check if three line segments of length $a$, $b$, $c$ can form a triangle:

$(a + b > c)$ && $(a + c > b)$ && $(b + c > a)$

if lengths are sorted with $a$ smallest and $c$ largest, simplifies to just $(a + b > c)$

## Trigonometry

**Law of Cosines** (Cosine Rule): relates the lengths of sides to the cosine of one angle.

$$c^2 = a^2 + b^2 - 2 \times a \times b \times \cos(\gamma)$$

$$\gamma = \arccos\left(\frac{a^2 + b^2 - c^2}{2 \times a \times b}\right)$$

**Law of Sines** (Sine Rule): relates side lengths to the sines of opposite angles.

$$\frac{a}{\sin(\alpha)} = \frac{b}{\sin(\beta)} = \frac{c}{\sin(\gamma)} = 2R$$

where $R$ is the radius of the circumcircle.

**Pythagorean Theorem**: specializes the Law of Cosines for right triangles (angle $\gamma = 90°$, so $\cos(\gamma) = 0$):

$$c^2 = a^2 + b^2$$

## Pythagorean Triple

a triple $(a, b, c)$ of positive integers such that $a^2 + b^2 = c^2$

well-known example: $(3, 4, 5)$

if $(a, b, c)$ is a Pythagorean triple, so is $(ka, kb, kc)$ for any positive integer $k$

each primitive triple is of form $({n}^{2} - {m}^{2},\ 2nm,\ {n}^{2} + {m}^{2})$
where $0 < m < n$, $n$ and $m$ are coprime and at least one of $n$, $m$ is even
