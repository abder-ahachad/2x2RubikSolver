//
// Created by abder on 21/05/24.
//

#include "../inc/utils.h"

unordered_map<Face,char> reverse_map(unordered_map<char,Face> map) {
    unordered_map<Face,char> reversed_map;
    for(auto p:map) {
        reversed_map[p.second] = p.first;
    }
    return reversed_map;
}