# What is a Koch Snowflake?

- Start with an **equilateral triangle**
- At each step, divide each side into 3 equal segments
- Replace the middle segment with two segments that form a **"bump" (60° spike)**
- Recur on every segment
- The shape grows more intricate with each level

---

## Code Structure Breakdown

###  `vonKoch` Class

This class handles drawing the snowflake:

#### Constructor:

```cpp
vonKoch(int s,int lvl, CDC *pDC)
```

- `s`: length of the triangle's side
- `lvl`: recursion depth
- `pDC`: pointer to the device context used for drawing (GDI)

---

###  Core Recursive Logic — `drawFourLines`

```cpp
void vonKoch::drawFourLines(double side,int level)
```

####  Algorithm:

```plaintext
If level == 0:
    Draw straight line from current point to next point using angle
Else:
    1. Recur on first 1/3 segment
    2. Turn left 60° and recur (creates upper spike)
    3. Turn right 120° and recur (back to bottom path)
    4. Turn left 60° again and recur on final segment
```

```mermaid
graph TD
    Start[Start Point] --> A1[drawFourLines(s, lvl)]
    A1 --> A2[break into 4 segments]
    A2 --> A3[left 60° and draw]
    A3 --> A4[right 120° and draw]
    A4 --> A5[left 60° and draw]
    A5 --> NextSide[Rotate 120° for next triangle edge]

```

This recursively builds the Koch edge.

---

###  Angle Handling

```cpp
void left(double x)  → angle -= x;
void right(double x) → angle += x;
```

You're adjusting `angle` globally in the object and using `cos(angle)` / `sin(angle)` to compute new points.

---

###  `LineTo`

```cpp
pen->LineTo(pt);
```

Draws a line from `currPt` to `pt` on the device context `pDC`. After drawing, it updates `currPt`.

---

###  `snowflake()`

This draws **3 Koch edges** to form a full triangle (the base of the snowflake):

```cpp
for (int i = 1; i <= 3; i++) {
    drawFourLines(side, level);  // Draw one edge
    right(120);                  // Turn for the next edge
}
```

---

##  What is `onDraw` doing?

```cpp
vonKoch(200, 4, pDC).snowflake();
```

- It creates a Koch Snowflake of side `200`, recursion `level = 4`
- Calls `snowflake()` which draws the full 3-edge recursive snowflake
- All drawing happens on the passed `CDC*` object (`pDC` from MFC framework)

---

##  TL;DR Summary

- `drawFourLines()` is the recursive part
- `snowflake()` draws 3 sides to form the base triangle
- You use `angle`, `cos`, `sin` to move directions like a turtle (turtle graphics logic)
- Depth of recursion (`level`) controls the detail
