# 📦 Huffman Encoding

**Huffman Encoding** is a greedy algorithm used for **lossless data compression**. It encodes characters using variable-length bit codes based on their frequencies — characters that appear more often get shorter codes.

---

## 📚 What is Huffman Encoding?

Huffman encoding converts a stream of characters into a compressed binary representation where:

- **Frequent characters** get **shorter codes**
- **Rare characters** get **longer codes**

This reduces the total number of bits required to represent the input.

---

## 🧠 Why It Works

Huffman encoding exploits redundancy in data:

- For instance, in English text, `'e'` is more common than `'z'`
- Encoding `'e'` as `10` and `'z'` as `111101001` helps reduce average bit length.

It constructs a **binary tree** (Huffman Tree) and assigns codes based on path from root:

- **Left = 0**
- **Right = 1**

---

## ⚙️ Algorithm Steps

### ✅ Compression (Encoding)

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

### 🔄 Decompression (Decoding)

1. **Read Huffman Tree from file**
2. **Read encoded bits** one-by-one
3. **Traverse Huffman Tree** using 0/1 until a leaf is found
4. **Output character**, repeat

---

## 📦 Example

### Input:

```
Text: "aaabbc"
Frequencies: a=3, b=2, c=1
```

### Tree:

```
        (*,6)
       /    \
   (*,3)    c(1)
   /   \
a(3)   b(2)
```

### Binary Codes:

```
a: 0
b: 10
c: 11
```

### Encoded Output:

```
"aaabbc" → 000101011
```

---

## 💡 Key Properties

| Concept             | Details                                |
| ------------------- | -------------------------------------- |
| Type                | Lossless Compression                   |
| Tree Used           | Binary Tree                            |
| Complexity (Build)  | O(n log n) using Min Heap              |
| Complexity (Encode) | O(n)                                   |
| Optimality          | Greedy & Optimal for prefix-free codes |

---

## 🛠️ Code Structure (in C++)

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

## 📁 Input/Output Format

- **Input**: Raw binary or text file
- **Output (Compressed)**: `.z` extension (binary)
- **Output (Decompressed)**: `.dec` extension (binary)

---

## 📊 Compression Rate

```
Compression rate = (Original Size - Compressed Size) / Original Size
```

Displayed in console after running the encoder.

---

## 🧪 Sample Usage

```bash
$ ./huffman_encoder input.txt
Compression rate = 42.37%
```

---

## ✅ Advantages

- Efficient for repetitive data
- Lossless (no data loss)
- Simple to implement

---

## ⚠️ Limitations

- Needs to store Huffman Tree in file (adds overhead)
- Not ideal for small or non-repetitive data
- Slower compared to dictionary-based methods (e.g., LZ77) for some inputs

---

## 📚 Applications

- ZIP File Compression
- JPEG Image Encoding (as entropy coder)
- MP3/MP4 Compression
- Data transmission (where bandwidth is expensive)

---

data compression techniques attempt to minimize the average code- word length by devising an optimal code

The construction of an optimal code was developed by David Huffman, who utilized a tree structure in this construction: a binary tree for a binary code. The algorithm is surprisingly simple and can be summarized as follows:

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
fig 11.1

createHuffmanTree(prob){
declare the probabilities p1, p2, and the Huffman tree Htree;
if (only two probabilities are left in prob){
return a tree with p1, p2 in the leaves and p1 + p2 in the root;}
else( remove the two smallest probabilities from prob and assign them to p1 and p2;){
insert p1 + p2 to prob;
Htree = CreateHuffmanTree(prob);
in Htree make the leaf with p1 + p2 the parent of two leaves with p1 and p2;
return Htree;
}
}
fig 11.4,11.5

Implementation of Huffman method with run-length encoding.
