#include <cstring>
#include <fstream>
#include <iostream>
#include "HuffmanCoding.h"

using namespace std;

int main(int argc, char *argv[]) {
  char fileName[30];
  HuffmanCoding Huffman;
  if (argc != 2) {
    cout << "Enter a file name: ";
    cin >> fileName;
  } else
    strcpy(fileName, argv[1]);
  ifstream fIn(fileName, ios::binary);
  if (fIn.fail()) {
    cerr << "Cannot open " << fileName << endl;
    return 0;
  }
  Huffman.decompress(fileName, fIn);
  fIn.close();
  return 0;
}
