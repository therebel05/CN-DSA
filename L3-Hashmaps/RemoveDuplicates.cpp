#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

// arr - [1, 2, 3, 2, 1, 5]   output - [1, 2, 3, 5] order should be maintained
vector<int> removeDuplicates(vector<int>& arr, int n) {
  vector<int> ans;
  unordered_map<int, bool> visited;

  for(int i = 0; i < n; i++) {
    if(visited.count(arr[i]) > 0) {
      continue;
    }
    visited[arr[i]] = true;
    ans.push_back(arr[i]);
  }

  return ans;
}

int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for(int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  vector<int> ans = removeDuplicates(arr, n);
  for(int elem : ans) {
    cout << elem << " ";
  }
  cout << endl;

  return 0;

}
