//
// Created by abder on 15/05/24.
//
#ifndef CUBE
#define CUBE
#include "utils.h"

struct Cube {
    Face F;
    Face B;
    Face L;
    Face R;
    Face U;
    Face D;

    Cube();
    void apply_random_operations(int N);
    void print_faces();

    void rot_F();
    void rot_rev_F();
    void rot_B();
    void rot_rev_B();
    void rot_L();
    void rot_rev_L();
    void rot_R();
    void rot_rev_R();
    void rot_U();
    void rot_rev_U();
    void rot_D();
    void rot_rev_D();

    unordered_map<char,Face> find_corner_combination(triplet<char>);
    bool is_up(unordered_map<char, Face>& corner);
    int color_count_in_face(Face face, char color);
    unordered_map<char,Face> get_square_periphery(Face, int);

    void fix_cube_orientation_and_track(Face& face, Face goal, Face* tracked_face);
    void fix_cube_orientation_and_preserve(Face& face, Face goal, Face preserved_face);

    void rotate_cube_X();
    void rotate_cube_Y();
    void rotate_cube_Z();

private :
    array<char*, 8> get_face_periphery(Face);
    void rotate_face(Face face);
    void rotate_face_rev(Face face);
    void twist_colors(Face);
    void twist_colors_rev(Face);

    Face rotate_X(Face face);
    Face rotate_Y(Face face);
    Face rotate_Z(Face face);
};

#endif
