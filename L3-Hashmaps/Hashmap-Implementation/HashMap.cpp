#include <iostream>
#include "HashMap.h"
using namespace std;

int main() {
  HashMap<int> hmap;
  for(int i = 0; i < 10; i++) {
    char c = '0' + i;
    string key = "abc";
    key += c;
    int value = i + 1;
    hmap.insert(key, value);
    cout << hmap.getLoadFactor() << endl;
  }

  cout << hmap.size() << endl;
  hmap.remove("abc0");
  hmap.remove("abc6");
  hmap.remove("abc40");
  cout << hmap.size() << endl;

  for(int i = 0; i < 10; i++) {
    char c = '0' + i;
    string key = "abc";
    key += c;
    cout << key << ": " << hmap.getValue(key) << endl;
  }

  cout << hmap.size() << endl;

  return 0;
}
