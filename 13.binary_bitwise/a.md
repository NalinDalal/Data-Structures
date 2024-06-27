RAM has sort of threshold, above threshold stores data, below doesn't
stores in binary format

0->00
1->01
2->10
3->11
4->100
5->101
6->110

int a=5;
int is 4 byte, memory allocated for variable a -> 0000 0101 0000 0000 0000 0000 0000 0000

LSB on leftmost part, lower memeory address
MSB on rightmost part, higher memory address

bit shift left->shift 1 bit to left

0101 << 1
->
0101 + 1

---

    1010

bit shift right->shift 1 bit to right

0101 >> 1
->
0101 - 1

---

    0010

<< is left shift, doubles our number(ax2^n)

> > is right shift, halves our number(a/2^n)

& - AND
| - OR
^ - XOR
~ - NOT

0 & 0 -> 0
0 & 1 -> 0
1 & 0 -> 0
1 & 1 -> 1

0 | 1 -> 1
1 | 0 -> 1
1 | 1 -> 1
0 | 0 -> 0

0 ^ 1 -> 1
1 ^ 0 -> 1
1 ^ 1 -> 0
0 ^ 0 -> 0

~ 1-> 0
~ 0-> 1

say i want to check the 5th position from the rightmost bit
so just take a 5th bit mask keep it 1, rest all 0, and take the bitwise AND with our number ->

     10|1|00101

| $ 000 | 1   | 00000      |
| ----- | --- | ---------- |
| 000   | 1   | 00000 = 32 |

0
