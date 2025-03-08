#include <string>
using namespace std;

// we will have key as string type only but value can be any type
template <typename V>
class MapNode {
  public:
    string key;
    V value;
    MapNode* next;

    MapNode(string key, V value) {
      this->key = key;
      this->value = value;
      next = NULL;
    }

    ~MapNode() {
      delete next;
    }
};

template <typename V>
class HashMap {
  MapNode<V>** buckets;
  int count;
  int numBuckets;

  int getBucketIndex(string key) {
    int hashcode = 0;
    int coefficient = 1;
    for(int i = key.length() - 1; i >= 0; i--) {
      hashcode += key[i] * coefficient;
      hashcode = hashcode % numBuckets;
      coefficient *= 37;
      coefficient = coefficient % numBuckets; // (a*b) % n === ((a % n) * (b % n)) % n   // This will keep the values inside int range
    }

    return hashcode % numBuckets;
  }

  void rehash() {
    MapNode<V>** temp = buckets;
    buckets = new MapNode<V>*[2 * numBuckets];
    for(int i = 0; i < 2 * numBuckets; i++) {
      buckets[i] = NULL;
    }

    int oldBucketCount = numBuckets;
    numBuckets *= 2;
    count = 0; //now buckets will behave like empty map

    //traverse on the temp map and take every value and insert in buckets map
    for(int i = 0; i < oldBucketCount; i++) {
      MapNode<V>* head = temp[i]; //taking each entry from temp map
      while(head != NULL) {
        string key = head->key;
        V value = head->value;
        insert(key, value);
        head = head->next; //this one while loop will copy one of the bucket to the new buckets map
      }
    }

    //delete the temp map
    for(int i = 0; i < oldBucketCount; i++) {
      MapNode<V>* head = temp[i];
      delete head;
    }
    delete [] temp;
  }

  public:
    HashMap() {
      count = 0;
      numBuckets = 5;
      buckets = new MapNode<V>*[numBuckets];
      for(int i = 0; i < numBuckets; i++) {
        buckets[i] = NULL;
      }
    }

    ~HashMap() {
      for(int i = 0; i < numBuckets; i++) {
        delete buckets[i];
      }
      delete [] buckets;
    }

    //get size of the hashmap
    int size() {
      return count;
    }

    //to see changes to load factor in console
    double getLoadFactor() {
      return (1.0 * count)/numBuckets;
    }

    //inserting into hashmap
    void insert(string key, V value) {
      //we have to get index using hash function where we will insert
      int bucketIndex = getBucketIndex(key);
      MapNode<V>* head = buckets[bucketIndex]; //head pointer at the bucketIndex
      while(head != NULL) {  // check if key already present, if yes then update value
        if(head->key == key) {
          head->value = value;
          return;
        }
        head = head->next;
      }
      head = buckets[bucketIndex]; // reinitialize head to the same index
      MapNode<V>* newNode = new MapNode<V>(key, value); //create node for the new key to be inserted
      newNode->next = head;
      buckets[bucketIndex] = newNode; //make this element as the new head for this bucketIndex
      count++; //increase count to keep track of number of elements inserted till now

      //calculate load factor to see if rehashing is needed
      double loadFactor = (1.0 * count)/numBuckets;
      if(loadFactor > 0.7) {
        rehash();
      }
    }

    //get value from key
    V getValue(string key) {
      int bucketIndex = getBucketIndex(key);
      MapNode<V>* head = buckets[bucketIndex];
      while(head != NULL) {
        if(head->key == key) {
          return head->value;
        }
        head = head->next;
      }
      return 0;
    }

    //delete key and return the value for which key was deleted
    V remove(string key) {
      int bucketIndex = getBucketIndex(key);
      MapNode<V>* head = buckets[bucketIndex];
      MapNode<V>* prev = NULL; //prev pointer to help with deletion when head reaches the key to be removed
      while(head != NULL) {
        if(head-> key == key) {
          if(prev == NULL) { //means the first node itself needs to be removed
            buckets[bucketIndex] = head->next;
          } else {
            prev->next = head->next;
          }
          V value = head->value; //storing the value to return
          head->next = NULL;
          delete head; //doing the extra step in the above line otherwise recursively all nodes will get deleted
          count--;
          return value;
        }
        prev = head;
        head = head->next;
      }
      return 0; //signifies that the key was not found
    }


};
