
# Huffman Codes

Binary codes assigned for each character of a string as a *codeword* consisting of bits. You can compress a string by replacing each character with its corresponding codeword.

| char | codeword |
|------|----------|
| A | 00 |
| B | 01 |
| C | 10 |
| D | 11 |

This is a **fixed-length** code — every codeword has the same length.
`AABACDACA` → `000001001011001000` → 18 bits.

**More optimisation:** use a **variable-length** code — give short codewords to frequent characters, long ones to rare characters.

| char | codeword |
|------|----------|
| A | 0 |
| B | 110 |
| C | 10 |
| D | 111 |

New optimal encoding: `AABACDACA` → `001100101110100` → 15 bits.

> ⚠️ **Prefix-free constraint:** No codeword may be a prefix of another. The table below violates this — `A=10` is a prefix of `C=1011`:
>
> | char | codeword |
> |------|----------|
> | A | 10 |
> | B | 11 |
> | C | 1011 |
> | D | 111 |

---

## Huffman Coding

A greedy algorithm that constructs an **optimal prefix-free code** for compressing a given string.
It is used for **lossless data compression**
The algorithm builds a **full binary tree** (a *trie*) based on character frequencies. Each character's codeword is the path from root to its leaf:
- Left child / left move → bit `0`
- Right child / right move → bit `1`

The cost of a tree T is defined as:

$$B(T) = \sum_{c \in C} f(c) \cdot d_T(c)$$

where $f(c)$ is frequency and $d_T(c)$ is depth of character $c$'s leaf.

 It encodes characters using variable-length bit codes based on their frequencies — characters that appear more often get shorter codes.

- **Frequent characters** get **shorter codes**
- **Rare characters** get **longer codes**

- For instance, in English text, `'e'` is more common than `'z'`
- Encoding `'e'` as `10` and `'z'` as `111101001` helps reduce average bit length.


This reduces the total number of bits required to represent the input.

**Algorithm:** Repeatedly merge the two least-frequent nodes.

`Compression rate = (Original Size - Compressed Size) / Original Size`


```
Huffman(){
for(){ each symbol create a tree with a single root node and order all trees
according to the probability of symbol occurrence;}
while(more than one tree is left){
take the two trees t1, t2 with the lowest probabilities p1, p2 (p1 ≤ p2)
and create a tree with t1 and t2 as its children and with
the probability in the new root equal to p1 + p2;}

    associate 0 with each left branch and 1 with each right branch;
    create a unique codeword for each symbol by traversing the tree from the root
        to the leaf containing the probability corresponding to this
        symbol and by putting all encountered 0s and 1s together;

}

createHuffmanTree(prob){
    declare the probabilities p1, p2, and the Huffman tree Htree;
    if (only two probabilities are left in prob){
        return a tree with p1, p2 in the leaves and p1 + p2 in the root;
    }
    else(remove the two smallest probabilities from prob and assign them to p1 and p2;){
        insert p1 + p2 to prob;
        Htree = CreateHuffmanTree(prob);
        in Htree make the leaf with p1 + p2 the parent of two leaves with p1 and p2;
        return Htree;
    }
}
```

---

**HUFFMAN(C)**
```
Huffman(C):
    n ← |C|
    Q ← C                          // initialize min-priority queue
    for i ← 1 to n-1:
        allocate new node z
        left[z]  ← x ← ExtractMin(Q)
        right[z] ← y ← ExtractMin(Q)
        f[z] ← f[x] + f[y]
        Insert(Q, z)
    return ExtractMin(Q)            // return root of the tree
```

> **Time complexity:** O(n log n) — the queue is a binary min-heap, each of the n−1 iterations does O(log n) heap operations.

---

**BuildHuffman**
```
BuildHuffman(f[1..n]):
    for i ← 1 to n:
        L[i] ← 0
        R[i] ← 0
        Insert(i, f[i])
    for i ← n to 2n-1:
        x ← ExtractMin()
        y ← ExtractMin()
        f[i] ← f[x] + f[y]
        Insert(i, f[i])
        L[i] ← x;  P[x] ← i
        R[i] ← y;  P[y] ← i
    P[2n-1] ← 0
```

**HuffmanEncode**

1. **Frequency Analysis**: Count frequency of each character (optionally with run-length for efficiency)
2. **Build Min-Heap**: Each character is a node in a priority queue (sorted by frequency)
3. **Construct Tree**:

   - Repeatedly remove two lowest frequency nodes
   - Merge into a new node with their combined frequency
   - Push back into heap

4. **Generate Codes**:

   - Traverse from root to leaves
   - Assign binary codes (left=0, right=1)

5. **Encode File**:

   - Replace each character with its binary code
   - Write compressed data to file



```
HuffmanEncode(A[1..k]):
    m ← 1
    for i ← 1 to k:
        HuffmanEncodeOne(A[i])

HuffmanEncodeOne(x):
    if x < 2n-1:
        HuffmanEncodeOne(P[x])
        if x == L[P[x]]:
            B[m] ← 0
        else:
            B[m] ← 1
        m ← m + 1
```

**HuffmanDecode**

1. **Read Huffman Tree from file**
2. **Read encoded bits** one-by-one
3. **Traverse Huffman Tree** using 0/1 until a leaf is found
4. **Output character**, repeat



```
HuffmanDecode(B[1..m]):
    k ← 1
    v ← 2n-1
    for i ← 1 to m:
        if B[i] == 0:
            v ← L[v]
        else:
            v ← R[v]
        if L[v] == 0:
            A[k] ← v
            k ← k + 1
            v ← 2n-1
```



```cpp
class HuffmanNode {
  char symbol;
  unsigned long freq;
  unsigned long codeword;
  HuffmanNode *left, *right;
};
```

```cpp
class HuffmanCoding {
  void compress(char *filename, ifstream &fIn);
  void decompress(char *filename, ifstream &fIn);

  // Core steps
  void garnerData(ifstream &);
  void createHuffmanTree();
  void createCodewords(HuffmanNode *, unsigned long codeword, int level);
  void encode(ifstream &);
  void decode(ifstream &);
};
```


---

## CLRS Example — 100,000 character file

Characters a–f with frequencies (in thousands):

| char | a | b | c | d | e | f |
|------|---|---|---|---|---|---|
| frequency | 45 | 13 | 12 | 16 | 9 | 5 |
| fixed-length | 000 | 001 | 010 | 011 | 100 | 101 |
| variable-length | 0 | 101 | 100 | 111 | 1101 | 1100 |

Fixed-length needs 300,000 bits. Variable-length needs:
$(45·1 + 13·3 + 12·3 + 16·3 + 9·4 + 5·4) · 1000 = 224,000$ bits — a **~25% saving**.

**Stage (a) — Initial 6 nodes (queue sorted by frequency)**
```mermaid
graph TD
    F("f (5)")
    E("e (9)")
    C("c (12)")
    B("b (13)")
    D("d (16)")
    A("a (45)")
```

**Stage (b) — Merge f(5) and e(9)**
```mermaid
graph TD
    C("c (12)")
    B("b (13)")
    D("d (16)")
    A("a (45)")
    FE("14") --0--> F("f (5)")
    FE("14") --1--> E("e (9)")
```

**Stage (c) — Merge c(12) and b(13)**
```mermaid
graph TD
    D("d (16)")
    A("a (45)")
    FE("14") --0--> F("f (5)")
    FE("14") --1--> E("e (9)")
    CB("25") --0--> C("c (12)")
    CB("25") --1--> B("b (13)")
```

**Stage (d) — Merge d(16) and FE(14)**
```mermaid
graph TD
    A("a (45)")
    CB("25") --0--> C("c (12)")
    CB("25") --1--> B("b (13)")
    DFE("30") --0--> FE("14")
    DFE("30") --1--> D("d (16)")
    FE --0--> F("f (5)")
    FE --1--> E("e (9)")
```

**Stage (e) — Merge CB(25) and DFE(30)**
```mermaid
graph TD
    A("a (45)")
    N55("55") --0--> CB("25")
    N55("55") --1--> DFE("30")
    CB --0--> C("c (12)")
    CB --1--> B("b (13)")
    DFE --0--> FE("14")
    DFE --1--> D("d (16)")
    FE --0--> F("f (5)")
    FE --1--> E("e (9)")
```

**Stage (f) — Final tree: merge a(45) and N55**
```mermaid
graph TD
    Root("100") --0--> A("a (45)")
    Root("100") --1--> N55("55")
    N55 --0--> CB("25")
    N55 --1--> DFE("30")
    CB --0--> C("c (12)")
    CB --1--> B("b (13)")
    DFE --0--> FE("14")
    DFE --1--> D("d (16)")
    FE --0--> F("f (5)")
    FE --1--> E("e (9)")
```

Final codewords (path from root to leaf):

| char | codeword |
|------|----------|
| a | 0 |
| b | 101 |
| c | 100 |
| d | 111 |
| e | 1101 |
| f | 1100 |

---

## Advantages

- Efficient for repetitive data
- Lossless (no data loss)
- Simple to implement


## Limitations

- Needs to store Huffman Tree in file (adds overhead)
- Not ideal for small or non-repetitive data
- Slower compared to dictionary-based methods (e.g., LZ77) for some inputs

## Applications

- ZIP File Compression
- JPEG Image Encoding (as entropy coder)
- MP3/MP4 Compression
- Data transmission (where bandwidth is expensive)


