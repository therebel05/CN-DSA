#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

int maxFrequency(vector<int>& arr, int n) {
  unordered_map<int, int> umap;
  int maxFreq = -1;
  for(int i = 0; i < n; i++) {
    umap[arr[i]]++;
    maxFreq = max(maxFreq, umap[arr[i]]);
  }
  for(int i = 0; i < n; i++) {
    if(umap[arr[i]] == maxFreq) {
      return arr[i];
    }
  }
  return maxFreq;
}

int main() {
  int n;
  cin >> n;
  vector<int> arr(n);
  for(int i = 0; i < n; i++) {
    cin >> arr[i];
  }

  cout << maxFrequency(arr, n) << endl;

  return 0;
}
