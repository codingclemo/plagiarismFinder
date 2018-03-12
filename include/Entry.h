#pragma once

#include <set>
#include <ostream>
#include <iomanip>
#include <iterator>

template<typename K, typename V>
class Entry;

template<typename K, typename V>
std::ostream& operator << (std::ostream &os, const Entry<K,V> &e);

template<typename K, typename V>
class Entry {

private:
  K key;
  std::set<V> values;

public:
  Entry(K key) : key(key) {}
  virtual ~Entry() {}
  void addValue(V value) { values.insert(value); }
  bool operator < (const Entry &e) const { return key < e.key; }
  friend std::ostream& operator << <K, V>(std::ostream &os, const Entry<K,V> &e);
};

template<typename K, typename V>
std::ostream& operator << (std::ostream &os, const Entry<K,V> &e) {
  os << std::setw(15) << e.key << " (" << e.values.size() << "): ";
  copy(e.values.begin(), e.values.end(), std::ostream_iterator<V>(os, ","));
  return os;
}