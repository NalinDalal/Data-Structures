/* 7.Hashing with Buckets
1. **Collision Handling:**
   - The program handles collisions in a hash table using an outfile as a hash
table.
   - If a hash bucket is full, items are stored in the overflow file.
   - Deleted records in overflow may be replaced with new items.

2. **Initialization of Hash Table:**
   - The program initializes the hash table (outfile) by filling it with empty
records.
   - Each record corresponds to a certain number of bytes.

3. **Insertion Function:**
   - The `insertion` function transfers entries from the names file to outfile
based on the hash function.
   - If a bucket in outfile is full, the function looks for available positions
in the overflow file.
   - If a deleted record position is found in overflow, the new item replaces
it; otherwise, the item is added to the end of overflow.

4. **User Interaction:**
   - The program displays a menu for users to insert a new record, delete an old
one, or exit.

5. **Deletion Function:**
   - Deletion is performed by accessing the corresponding hash bucket and
linearly searching for the item.
   - If found, a deletion marker is applied; otherwise, the search continues in
overflow.

6. **Exiting the Program:**
   - Upon choosing to exit, undeleted entries in overflow are transferred to
outfile.

7. **Sorting for External Sort:**
   - The program performs an external sort by applying quicksort to both the
outfile and an array called `pointers`.
   - Pointers contain addresses of entries in outfile.

8. **Indirect Sorting:**
   - Sorting is performed indirectly, meaning the elements in pointers are
moved, not the elements in outfile.

9. **Alphabetical Order:**
   - After sorting, the data in outfile needs to be put in alphabetical order.

10. **Transfer to Sorted File:**
    - Entries from outfile are transferred to a sorted file (sorted) based on
the order indicated in the pointers array.

11. **File Renaming:**
    - The original file (`names`) is deleted, and the sorted file is renamed to
replace it.

12. **Example Modification:**
    - An example scenario involves inserting "Carol 654-6543" and deleting
"Brenda 345-5352" and "Jeremiah 789-4563."

13. **File Contents Illustration:**
    - The example shows the contents of outfile and overflow before and after
modifications.

14. **Subsequent Insertion and Deletion:**
    - Subsequent operations involve inserting "Maggie 733-0983" and deleting
"Brendon 983-7373."

15. **Final Outcome:**
    - After choosing to exit, undeleted records from overflow are transferred to
outfile, and the combined file is sorted, resulting in the final alphabetical
order of records.
    */
#include <cctype>
#include <cstdio>
#include <cstring>
#include <fstream>
#include <iomanip>
#include <iostream>

const int bucketSize = 2, tableSize = 3, strLen = 20;
const int recordLen = strLen;

class File {
public:
  File() : empty('*'), delMarker('#') {}
  void processFile(char *fileName);

private:
  const char empty, delMarker;
  long *pointers;
  std::fstream outfile, overflow, sorted;

  unsigned long hash(char *s);
  void getName(char *line);
  void insertion(char *line);
  void excise(char *line);
  void partition(int low, int high, int &pivotLoc);
  void QSort(int low, int high);
  void sortFile();
  void combineFiles();
  ////////////////////////////////////////////////////////////////////
  void swap(long &i, long &j) {
    long tmp = i;
    i = j;
    j = tmp;
  }

  void insert(char line[]) {
    getName(line);
    insertion(line);
  }
  ////////////////////////////////////////////////////////////////////
};

unsigned long File::hash(char *s) {
  unsigned long xorValue = 0, pack;
  int i, j, slength;

  for (slength = strlen(s); isspace(s[slength - 1]); slength--)
    ;

  for (i = 0; i < slength;) {
    for (pack = 0, j = 0;; j++, i++) {
      pack |= (unsigned long)s[i];
      if (j == 3 || i == slength - 1) {
        break;
      }
    }
    pack <<= 8;
    xorValue ^= pack;
  }
  return (xorValue % tableSize) * bucketSize * recordLen;
}

void File::getName(char line[]) {
  std::cout << "Enter a name: ";
  std::cin.getline(line, recordLen + 1);
  for (int i = strlen(line); i < recordLen; i++)
    line[i] = ' ';
  line[recordLen] = '\0';
}

void File::insertion(char line[]) {
  int address = hash(line), counter = 0;
  char name[recordLen + 1];
  bool done = false, inserted = false;

  outfile.clear();
  outfile.seekg(address, std::ios::beg);

  while (!done && outfile.get(name, recordLen + 1)) {
    if (name[0] == empty || name[0] == delMarker) {
      outfile.clear();
      outfile.seekg(address + counter * recordLen, std::ios::beg);
      outfile << line << std::setw(strlen(line) - recordLen);
      done = inserted = true;
    } else if (!strcmp(name, line)) {
      std::cout << line << " is already in the file\n";
      return;
    } else {
      counter++;
    }

    if (counter == bucketSize) {
      done = true;
    } else {
      outfile.seekg(address + counter * recordLen, std::ios::beg);
    }
  }

  if (!inserted) {
    done = false;
    counter = 0;
    overflow.clear();
    overflow.seekg(0, std::ios::beg);

    while (!done && overflow.get(name, recordLen + 1)) {
      if (name[0] == delMarker) {
        done = true;
      } else if (!strcmp(name, line)) {
        std::cout << line << " is already in the file\n";
        return;
      } else {
        counter++;
      }
    }

    overflow.clear();

    if (done) {
      overflow.seekg(counter * recordLen, std::ios::beg);
    } else {
      overflow.seekg(0, std::ios::end);
    }
    overflow << line << std::setw(strlen(line) - recordLen);
  }
}

void File::excise(char line[]) {
  getName(line);
  int address = hash(line), counter = 0;
  bool done = false, removed = false;
  char name2[recordLen + 1];

  outfile.clear();
  outfile.seekg(address, std::ios::beg);

  while (!done && outfile.get(name2, recordLen + 1)) {
    if (!strcmp(line, name2)) {
      outfile.clear();
      outfile.seekg(address + counter * recordLen, std::ios::beg);
      outfile.put(delMarker);
      done = removed = true;
    } else {
      counter++;
    }

    if (counter == bucketSize) {
      done = true;
    } else {
      outfile.seekg(address + counter * recordLen, std::ios::beg);
    }
  }

  if (!removed) {
    done = false;
    counter = 0;
    overflow.clear();
    overflow.seekg(0, std::ios::beg);

    while (!done && overflow.get(name2, recordLen + 1)) {
      if (!strcmp(line, name2)) {
        overflow.clear();
        overflow.seekg(counter * recordLen, std::ios::beg);
        overflow.put(delMarker);
        done = removed = true;
      } else {
        counter++;
      }

      overflow.seekg(counter * recordLen, std::ios::beg);
    }
  }

  if (!removed) {
    std::cout << line << " is not in the database\n";
  }
}

void File::partition(int low, int high, int &pivotLoc) {
  char rec[recordLen + 1], pivot[recordLen + 1];
  register int i, lastSmall;

  swap(pointers[low], pointers[(low + high) / 2]);

  outfile.seekg(pointers[low] * recordLen, std::ios::beg);
  outfile.clear();
  outfile.get(pivot, recordLen + 1);

  for (lastSmall = low, i = low + 1; i <= high; i++) {
    outfile.clear();
    outfile.seekg(pointers[i] * recordLen, std::ios::beg);
    outfile.get(rec, recordLen + 1);

    if (strcmp(rec, pivot) < 0) {
      lastSmall++;
      swap(pointers[lastSmall], pointers[i]);
    }
  }

  swap(pointers[low], pointers[lastSmall]);
  pivotLoc = lastSmall;
}

void File::QSort(int low, int high) {
  int pivotLoc;

  if (low < high) {
    partition(low, high, pivotLoc);
    QSort(low, pivotLoc - 1);
    QSort(pivotLoc + 1, high);
  }
}

void File::sortFile() {
  char rec[recordLen + 1];
  QSort(1, pointers[0]);
  rec[recordLen] = '\0';

  for (int i = 1; i <= pointers[0]; i++) {
    outfile.clear();
    outfile.seekg(pointers[i] * recordLen, std::ios::beg);
    outfile.get(rec, recordLen + 1);
    sorted << rec << std::setw(strlen(rec) - recordLen);
  }
}

void File::combineFiles() {
  int counter = bucketSize * tableSize;
  char rec[recordLen + 1];

  outfile.clear();
  overflow.clear();
  outfile.seekg(0, std::ios::end);
  overflow.seekg(0, std::ios::beg);

  while (overflow.get(rec, recordLen + 1)) {
    if (rec[0] != delMarker) {
      counter++;
      outfile << rec << std::setw(strlen(rec) - recordLen);
    }
  }

  pointers = new long[counter + 1];
  int arrCnt = 1;

  for (int i = 0; i < counter; i++) {
    outfile.clear();
    outfile.seekg(i * recordLen, std::ios::beg);
    outfile.get(rec, recordLen + 1);

    if (rec[0] != empty && rec[0] != delMarker) {
      pointers[arrCnt++] = i;
    }
  }

  pointers[0] = --arrCnt;
}

void File::processFile(char *fileName) {
  std::ifstream fIn(fileName);

  if (fIn.fail()) {
    std::cerr << "Cannot open " << fileName << std::endl;
    return;
  }

  char command[strLen + 1] = " ";

  outfile.open("outfile", std::ios::in | std::ios::out | std::ios::trunc);
  sorted.open("sorted", std::ios::in | std::ios::out | std::ios::trunc);
  overflow.open("overflow", std::ios::in | std::ios::out | std::ios::trunc);

  for (int i = 1; i <= tableSize * bucketSize * recordLen; i++) {
    outfile << empty;
  }

  char line[recordLen + 1];

  while (fIn.get(line, recordLen + 1)) {
    insertion(line);
  }

  while (strcmp(command, "exit")) {
    std::cout << "Enter a command (insert, remove, or exit): ";
    std::cin.getline(command, strLen + 1);

    if (!strcmp(command, "insert")) {
      insert(line);
    } else if (!strcmp(command, "remove")) {
      excise(line);
    } else if (strcmp(command, "exit")) {
      std::cout << "Wrong command entered, please retry.\n";
    }
  }

  combineFiles();
  sortFile();

  outfile.close();
  sorted.close();
  overflow.close();
  fIn.close();

  remove(fileName);
  rename("sorted", fileName);
}

int main(int argc, char *argv[]) {
  char fileName[30];

  if (argc != 2) {
    std::cout << "Enter a file name: ";
    std::cin.getline(fileName, 30);
  } else {
    std::strcpy(fileName, argv[1]);
  }

  File fClass;
  fClass.processFile(fileName);

  return 0;
}
