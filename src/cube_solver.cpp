//
// Created by abder on 20/05/24.
//
#include "../inc/cube_solver.h"
void solve(Cube& cube) {
    top_layer::solve(cube);
    second_layer::solve(cube);
    place_yellow_corners::solve(cube);
}

// solving the top layer :
void top_layer::solve(Cube& cube) {
    _1st_2nd_corner::solve(cube);
    _3rd_corner::solve(cube);
    _4th_corner::solve(cube);
}
void top_layer::_1st_2nd_corner::solve(Cube& cube) {
    auto corner = cube.find_corner_combination(make_tuple('w','r','b'));
    cube.fix_cube_orientation_and_track(corner['w'],cube.U, &corner['b']);
    cube.fix_cube_orientation_and_preserve(corner['b'], cube.R, corner['w']);
    action1(cube);
}
void top_layer::_1st_2nd_corner::action1(Cube& cube) {
    if(cube.U[1] == 'w' && cube.R[1] == 'b') {
        return;
    }
    auto corner = cube.find_corner_combination(make_tuple('w','o','b'));
    if(cube.is_up(corner)) {
        if(corner['o'] == cube.U) {
            cube.fix_cube_orientation_and_preserve(corner['w'], cube.F, cube.U);
        } else if(corner['w'] == cube.U) {
            cube.fix_cube_orientation_and_preserve(corner['b'], cube.F, cube.U);
        } else {
            cube.fix_cube_orientation_and_preserve(corner['o'], cube.F, cube.U);
        }
        action2(cube);
    }
    corner = cube.find_corner_combination(make_tuple('w','r','b'));
    cube.fix_cube_orientation_and_track(corner['w'],cube.U, &corner['b']);
    cube.fix_cube_orientation_and_preserve(corner['b'], cube.F, cube.U);
    action3(cube);
}
void top_layer::_1st_2nd_corner::action2(Cube &cube) {
    cube.rot_rev_R();
    cube.rot_rev_D();
    cube.rot_R();
}
void top_layer::_1st_2nd_corner::action3(Cube &cube) {
    while(1) {
        if(cube.F[2] == 'w' && cube.D[3] == 'b' && cube.R[3] == 'o') {
            cube.rot_R();
            return;
        } else if(cube.F[2] == 'b' && cube.D[3] == 'o' && cube.R[3] == 'w') {
            cube.rot_rev_R();
            cube.rot_rev_D();
            cube.rot_R();
            return;
        } else if(cube.F[2] == 'o' && cube.D[3] == 'w' && cube.R[3] == 'b') {
            cube.rot_D();
            cube.rot_R();
            cube.rot_R();
            return;
        }
        cube.rot_D();
    }
}

void top_layer::_3rd_corner::solve(Cube &cube) {
    auto corner = cube.find_corner_combination(make_tuple('o','w','b'));
    cube.fix_cube_orientation_and_track(corner['w'], cube.U, &corner['b']);
    cube.fix_cube_orientation_and_preserve(corner['b'], cube.L, cube.U);
    action1(cube);
}

void top_layer::_3rd_corner::action1(Cube &cube) {
    if(cube.F[1] == 'o' && cube.U[2] == 'w') {
        return;
    }
    auto corner = cube.find_corner_combination(make_tuple('w','o', 'g'));
    if(cube.is_up(corner)) {
        if(cube.U[1] == 'o' && cube.R[1] == 'g') {
            cube.rot_rev_R();
            return;
        }
        action2(cube);
    }
    action3(cube);
}
void top_layer::_3rd_corner::action2(Cube &cube) {
    if((cube.R[1] == 'w' && cube.U[1] == 'g') || (cube.R[1] == 'o' && cube.U[1] == 'w')) {
        cube.rot_R();
        cube.rot_rev_D();
    } else {
        cube.rot_R();
        cube.rot_R();
        cube.rot_rev_D();
    }
}
void top_layer::_3rd_corner::action3(Cube &cube) {
    while(true) {
        if(cube.F[2] == 'w' && cube.D[3] == 'o' && cube.R[3] == 'g') {
            cube.rot_R();
            return;
        } else if(cube.F[2] == 'o' && cube.D[3] == 'g' && cube.R[3] == 'w') {
            cube.rot_rev_R();
            cube.rot_rev_D();
            cube.rot_R();
            return;
        } else if(cube.F[2] == 'g' && cube.D[3] == 'w' && cube.R[3] == 'o') {
            cube.rot_D();
            cube.rot_R();
            cube.rot_R();
            return;
        }
        cube.rot_D();
    }
}

void top_layer::_4th_corner::solve(Cube &cube) {
    auto corner = cube.find_corner_combination(make_tuple('g','o','w'));
    cube.fix_cube_orientation_and_track(corner['w'], cube.U, &corner['g']);
    cube.fix_cube_orientation_and_preserve(corner['g'], cube.F, cube.U);
    action1(cube);
}

void top_layer::_4th_corner::action1(Cube &cube) {
    if(cube.F[2] == 'w' && cube.F[1] == 'g') {
        return;
    }
    auto corner = cube.find_corner_combination(make_tuple('g', 'w', 'r'));
    if(cube.is_up(corner)) {
        action2(cube);
    }
    action3(cube);
}

void top_layer::_4th_corner::action2(Cube &cube) {
    cube.rot_rev_R();
    cube.rot_rev_D();
    cube.rot_R();
}

void top_layer::_4th_corner::action3(Cube &cube) {
    while(true) {
        if(cube.F[2] == 'r' && cube.R[3] == 'g' && cube.D[3] == 'w') {
            cube.rot_F();
            cube.rot_rev_D();
            cube.rot_rev_F();
            cube.rot_D();
            cube.rot_D();

        }
        if(cube.F[2] == 'w' && cube.R[3] == 'r' && cube.D[3] == 'g') {
            cube.rot_rev_D();
            cube.rot_rev_R();
            cube.rot_D();
            cube.rot_R();
            return;
        } else if(cube.F[2] == 'g' && cube.R[3] == 'w' && cube.D[3] == 'r') {
            cube.rot_rev_R();
            cube.rot_rev_D();
            cube.rot_R();
            return;
        }
        cube.rot_D();
    }
    
}
// solving the second layer :
void second_layer::solve(Cube& cube) {
    cube.rotate_cube_X();
    cube.rotate_cube_X();
    while(!action1(cube))
        action2(cube);
}

bool second_layer::action1(Cube &cube) {
    int count_yellow = cube.color_count_in_face(cube.U, 'y');
    if(count_yellow == 4)
        return true;
    if(count_yellow == 0)
        while(cube.L[1]!='y')
            cube.rotate_cube_Z();
    else if(count_yellow == 1)
        while(cube.U[3]!='y')
            cube.rotate_cube_Z();
    else
        while(!(cube.F[0]=='y' &&
        ((cube.U[0]=='y' && cube.U[1]=='y') || (cube.U[1]=='y' && cube.U[2]=='y') || (cube.U[0]=='y' && cube.U[2]=='y'))))
            cube.rotate_cube_Z();
    return false;
}

void second_layer::action2(Cube &cube) {
    cube.rot_R();
    cube.rot_U();
    cube.rot_rev_R();
    cube.rot_U();
    cube.rot_R();
    cube.rot_U();
    cube.rot_U();
    cube.rot_rev_R();
}

// place yellow corners correctly
void place_yellow_corners::solve(Cube &cube) {
    set<int> incorrect_corners = action1(cube);
    while(!incorrect_corners.empty()) {
        action2(cube, incorrect_corners);
        action3(cube);
        incorrect_corners = action1(cube);
    }
}

set<int> place_yellow_corners::action1(Cube& cube) {
    int opposite_squares[4] = {1, 0, 3, 2};
    set<int> incorrect_corners;
    while(true) {
        for(int i = 0; i<4; ++i) {
            auto up_corner = reverse_map(cube.get_square_periphery(cube.U, i));
            auto down_corner = reverse_map(cube.get_square_periphery(cube.D, opposite_squares[i]));
            for(auto p:up_corner) {
                if(p.second != down_corner[p.first]) {
                    incorrect_corners.insert(i);
                }
            }
        }
        if(incorrect_corners.size() <= 2)
            return incorrect_corners;
        else {
            cube.rot_U();
            incorrect_corners.clear();
        }
    }
}

void place_yellow_corners::action2(Cube &cube, set<int>& incorrect_corners) {
    if(incorrect_corners.empty())
        return;
    auto _null = incorrect_corners.end();
    if(incorrect_corners.find(0)!=_null && incorrect_corners.find(1)!=_null) {
        cube.rotate_cube_Z();
        cube.rotate_cube_Z();
    } else if(incorrect_corners.find(0)!=_null && incorrect_corners.find(3)!=_null) {
        cube.rotate_cube_Z();
        cube.rotate_cube_Z();
        cube.rotate_cube_Z();
    } else if((incorrect_corners.find(1)!=_null && incorrect_corners.find(2)!=_null) ||
              (incorrect_corners.find(0)!=_null && incorrect_corners.find(2)!=_null)) {
        cube.rotate_cube_Z();
    }
}

void place_yellow_corners::action3(Cube &cube) {
    cube.rot_rev_R();
    cube.rot_F();
    cube.rot_rev_R();
    cube.rot_B();
    cube.rot_B();
    cube.rot_R();
    cube.rot_rev_F();
    cube.rot_rev_R();
    cube.rot_B();
    cube.rot_B();
    cube.rot_R();
    cube.rot_R();
    cube.rot_rev_U();
}