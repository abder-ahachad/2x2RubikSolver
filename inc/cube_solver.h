//
// Created by abder on 20/05/24.
//

#ifndef CUBE_SOLVER
#define CUBE_SOLVER

#include "Cube.h"
#include "utils.h"

void solve(Cube& cube);

namespace top_layer {
    void solve(Cube& cube);
    namespace _1st_2nd_corner {
        void solve(Cube& cube);
        void action1(Cube& cube);
        void action2(Cube& cube);
        void action3(Cube& cube);
    }
    namespace _3rd_corner {
        void solve(Cube& cube);
        void action1(Cube& cube);
        void action2(Cube& cube);
        void action3(Cube& cube);
    }
    namespace _4th_corner {
        void solve(Cube& cube);
        void action1(Cube& cube);
        void action2(Cube& cube);
        void action3(Cube& cube);
    }
}
namespace second_layer {
    void solve(Cube& cube);
    bool action1(Cube& cube);
    void action2(Cube& cube);
}
namespace place_yellow_corners {
    void solve(Cube& cube);
    set<int> action1(Cube& cube);
    void action2(Cube& cube, set<int>&);
    void action3(Cube& cube);
}

#endif
