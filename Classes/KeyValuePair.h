#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H

#include <ostream>

template <class K, class V>
struct KeyValuePair {  
    K key;
    V value;

    KeyValuePair() {}

    KeyValuePair(K key) {
        this->key = key;
    }

    KeyValuePair(K key, V value) {
        this->key = key;
        this->value = value;
    }

    KeyValuePair(const KeyValuePair<K,V>& kvPair) {
        this->key = kvPair.key;
        this->value = kvPair.value;
    }

    friend bool operator<(const KeyValuePair<K,V>& p1, const KeyValuePair<K,V>& p2) {
        return p1.key < p2.key;
    }

    friend bool operator>(const KeyValuePair<K,V>& p1, const KeyValuePair<K,V>& p2) {
        return p1.key > p2.key;
    }

    friend bool operator==(const KeyValuePair<K,V>& p1, const KeyValuePair<K,V>& p2) {
        return p1.key == p2.key;
    }

    friend bool operator!=(const KeyValuePair<K,V>& p1, const KeyValuePair<K,V>& p2) {
        return !(p1.key == p2.key);
    }

    friend std::ostream& operator<<(std::ostream& os, const KeyValuePair<K,V>& kv) {
        os << kv.value << std::endl;

        return os;
    }
};

#endif