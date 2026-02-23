/* Code implementation with ordered map
std::map maintains its elements in sorted manner based on the keys. It is
implemented as a self balanced trees. Just like Red black trees. Search, insert
and delete operations are perform in O(logn) time.
*/
#include <iostream>
#include <map>
#include <string>

using namespace std;

int main() {

  std::map<std::string, int> OrderedMap;

  OrderedMap["Squares"] = 10;
  OrderedMap["Circles"] = 5;
  OrderedMap["Triangles"] = 8;

  std::cout << "There are  " << OrderedMap["Squares"] << " Squares"
            << std::endl;
  std::cout << "There are  " << OrderedMap["Circles"] << " Circles"
            << std::endl;
  std::cout << "There are  " << OrderedMap["Triangles"] << " Triangles"
            << std::endl;

  // Iterate over all key-value pairs in the map
  for (const auto &pair : OrderedMap) {
    std::cout << pair.first << ": " << pair.second << std::endl;
  }

  return 0;
}
