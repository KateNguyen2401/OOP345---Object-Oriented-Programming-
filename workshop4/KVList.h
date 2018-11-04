#pragma once
#ifndef KVLIST_H
#define KVLIST_H

#include <iostream>

template<typename K, typename V, int N>
class KVList {
	K k[N];
	V v[N];
	size_t count = 0;
public:
	KVList() : count(0) {}

	size_t size() const {
		return count;
	}
	const K& key(int i) const {
		if (i < N) {
			return k[i];
		}
	}

	const V& value(int i) const {
		if (i < N) {
			return v[i];
		}
	}
	KVList& add(const K& kk, const V& vv) {
		if (count < N) {
			k[count] = kk;
			v[count] = vv;
			count++;
		}
		return *this;
	}

	int find(const K& kk) const
	{
		for (size_t i = 0; i < count; i++) {
			if (k[i] == kk)
				return i;
		}
		return 0; //declares to 0 if kk is not finded
	}

	KVList& replace(int i, const K& kk, const V& vv) {
		if (i < N) {
			k[i] = kk;
			v[i] = vv;
		}
		return *this;
	}
};








#endif 
