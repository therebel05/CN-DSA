#include <iostream>
#include <unordered_map>
#include <string>
#include <vector>

int main() {
  unordered_map<string, int> umap;
  umap.insert("abc", 2);
  umap["def"] = 3;
  umap["pqr"] = 3;
  umap["ghi"] = 3;
  umap["xyz"] = 3;

  //iterator to iterate over an unordered map
  unordered_map<string, int>::iterator it = umap.begin();
  while(it != umap.end()) {
    cout << "key: " << it->first << " value: " << it->second << endl;
    it++;
  }

  vector<int> vec;
  vec.push_back(2);
  vec.push_back(3);
  vec.push_back(4);
  vec.push_back(5);
  vec.push_back(1);

  //iterator to iterate over a vector
  vector<int>::iterator it2 = vec.begin();
  while(it2 != vec.end()) {
    cout << *it << " ";
    it2++;
  }

  //find an element
  unordered_map<string, int>::iterator findIt = umap.find("abc");
  //erase using the iterator
  umap.erase(findIt);
  //erase a range of values
  umap.erase(findIt, findIt + 2); // this will delete element at "findIt" and "findIt + 1"
                                  // erasing a  range is usually good for vector as it doesn't make sense for 
                                  // unordered maps

  return 0;
}
