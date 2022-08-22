#ifndef KEYVALUEPAIR_H
#define KEYVALUEPAIR_H

template <class K, class V>
struct KeyValuePair {
    KeyValuePair(K key, V value) {
        this->key = key;
        this->value = value;
    }

    K key;
    V value;
};

#endif