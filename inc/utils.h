//
// Created by abder on 21/05/24.
//

#ifndef UTILS
#define UTILS
#include <tuple>
#include <array>
#include <utility>
#include <unordered_map>
#include <set>
#include <cassert>
#include <functional>
#include <algorithm>
using namespace std;
template<typename T>
using triplet = tuple<T,T,T>;

typedef char* Face;

unordered_map<Face,char> reverse_map(unordered_map<char,Face> map);



#endif
