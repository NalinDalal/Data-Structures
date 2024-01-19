/*
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
*/

#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;
#include "HuffmanCoding.h"
int main(int argc, char* argv[]) {
    char fileName[30];
    HuffmanCoding Huffman;
    if (argc != 2) {
        cout << "Enter a file name: ";
        cin  >> fileName;
    }
    else strcpy(fileName,argv[1]);
    ifstream fIn(fileName,ios::binary);
    if (fIn.fail()) {
        cerr << "Cannot open " << fileName << endl;
return 0; }
    Huffman.decompress(fileName,fIn);
    fIn.close();
    return 0;
}