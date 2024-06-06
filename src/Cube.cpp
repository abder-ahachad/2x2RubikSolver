//
// Created by abder on 15/05/24.
//
#include <ctime>
#include <iostream>
#include "../inc/Cube.h"


void Cube::rot_F() {
    rotate_face(F);
}
void Cube::rot_rev_F() {
    rotate_face_rev(F);
}

void Cube::rot_B() {
    rotate_face(B);
}
void Cube::rot_rev_B() {
    rotate_face_rev(B);
}

void Cube::rot_R() {
    rotate_face(R);
}
void Cube::rot_rev_R() {
    rotate_face_rev(R);
}

void Cube::rot_L() {
    rotate_face(L);
}
void Cube::rot_rev_L() {
    rotate_face_rev(L);
}

void Cube::rot_U() {
    rotate_face(U);
}
void Cube::rot_rev_U() {
    rotate_face_rev(U);
}

void Cube::rot_D() {
    rotate_face(D);
}
void Cube::rot_rev_D() {
    rotate_face_rev(D);
}

unordered_map<char, Face> Cube::find_corner_combination(triplet<char> color_combination) {
    char color1 = get<0>(color_combination);
    char color2 = get<1>(color_combination);
    char color3 = get<2>(color_combination);
    unordered_map<char,Face> corner;

    for(int i = 0; i<4; ++i) {
        corner = get_square_periphery(U, i);
        corner[U[i]] = U;
        if(corner.find(color1)!=corner.end() && corner.find(color2)!=corner.end() &&
           corner.find(color3)!=corner.end()) {
            return corner;
        }
        corner.clear();
    }
    for(int i = 0; i<4; ++i) {
        corner = get_square_periphery(D, i);
        corner[D[i]] = D;
        if(corner.find(color1)!=corner.end() && corner.find(color2)!=corner.end() &&
           corner.find(color3)!=corner.end()) {
            return corner;
        }
        corner.clear();
    }
}

bool Cube::is_up(unordered_map<char, Face> &corner) {
    for(auto p:corner) {
        if(p.second == U)
            return true;
    }
    return false;
}

int Cube::color_count_in_face(Face face, char color) {
    int count = 0;
    for (int i = 0; i<4; ++i) {
        if(face[i] == color)
            count++;
    }
    return count;
}

unordered_map<char, Face> Cube::get_square_periphery(Face face, int i) {
    if(face == F) {
        if(i == 0)
            return {{U[3],U}, {L[1], L}};
        if(i == 1)
            return {{U[2], U}, {R[0], R}};
        if(i == 2)
            return {{D[3],D}, {R[3],R}};
        if(i == 3)
            return {{D[2],D}, {L[2],L}};
    }
    if(face == B) {
        if(i == 0)
            return {{R[1],R}, {U[1],U}};
        if(i == 1)
            return {{U[0],U}, {L[0],L}};
        if(i == 2)
            return {{L[3], L}, {D[1], D}};
        if(i == 3)
            return {{R[2],R},{D[0],D}};
    }
    if(face == L) {
        if(i == 0)
            return {{U[0], U}, {B[1], B}};
        if(i == 1)
            return {{F[0],F}, {U[3], U}};
        if(i == 2)
            return {{F[3],F}, {D[2],D}};
        if(i == 3)
            return {{B[2], B}, {D[1], D}};
    }
    if(face == R) {
        if(i == 0)
            return {{F[1],F}, {U[2],U}};
        if(i == 1)
            return {{B[0],B}, {U[1],U}};
        if(i == 2)
            return {{B[3],B}, {D[0],D}};
        if (i == 3)
            return {{F[2],F}, {D[3], D}};
    }
    if(face == U) {
        if(i == 0)
            return {{B[1], B}, {L[0], L}};
        if(i == 1)
            return {{B[0], B}, {R[1], R}};
        if(i == 2)
            return {{R[0],R}, {F[1],F}};
        if(i == 3)
            return {{F[0], F}, {L[1],L}};
    }
    if(face == D) {
        if(i == 0)
            return {{B[3],B}, {R[2], R}};
        if(i == 1)
            return {{B[2], B}, {L[3],L}};
        if(i == 2)
            return {{F[3], F}, {L[2],L}};
        if(i == 3)
            return {{F[2], F}, {R[3], R}};
    }
    return unordered_map<char,Face>();
}

void Cube::fix_cube_orientation_and_track(Face &face, Face goal, Face* tracked_face = nullptr) {
    // x:0 , y:1, z:2
    void(Cube::*cube_operations[3])() = {&Cube::rotate_cube_X,
                                         &Cube::rotate_cube_Y,
                                         &Cube::rotate_cube_Z};
    Face(Cube::*face_operations[3])(Face) = {&Cube::rotate_X,
                                             &Cube::rotate_Y,
                                             &Cube::rotate_Z};
    int rotation_fct;
    if(face == F || face == B) {
        if(goal == R || goal == L){
            rotation_fct = 2;
        } else if(goal == U || goal == D) {
            rotation_fct = 1;
        } else {
            rotation_fct = 1;
        }
    } else if(face == L || face == R) {
        if(goal == F || goal == B){
            rotation_fct = 2;
        } else if(goal == U || goal == D) {
            rotation_fct = 0;
        } else {
            rotation_fct = 2;
        }
    } else if(face == U || face == D) {
        if(goal == F || goal == B){
            rotation_fct = 1;
        } else if(goal == R || goal == L) {
            rotation_fct = 0;
        } else {
            rotation_fct = 0;
        }
    }

    while(face != goal) {
        face = (this->*face_operations[rotation_fct])(face);
        *tracked_face = (this->*face_operations[rotation_fct])(*tracked_face);
        (this->*cube_operations[rotation_fct])();
    }
}

void Cube::fix_cube_orientation_and_preserve(Face &face, Face goal, Face preserved_face) {
    // x:0 , y:1, z:2
    void(Cube::*cube_operations[3])() = {&Cube::rotate_cube_X,
                                         &Cube::rotate_cube_Y,
                                         &Cube::rotate_cube_Z};
    Face(Cube::*face_operations[3])(Face) = {&Cube::rotate_X,
                                             &Cube::rotate_Y,
                                             &Cube::rotate_Z};
    vector<int> rotation_fct;
    if(face == F || face == B) {
        if(goal == R || goal == L){
            rotation_fct = {2};
        } else if(goal == U || goal == D) {
            rotation_fct = {1};
        } else {
            rotation_fct = {1, 2};
        }
    } else if(face == L || face == R) {
        if(goal == F || goal == B){
            rotation_fct = {2};
        } else if(goal == U || goal == D) {
            rotation_fct = {0};
        } else {
            rotation_fct = {0, 2};
        }
    } else if(face == U || face == D) {
        if(goal == F || goal == B){
            rotation_fct = {1};
        } else if(goal == R || goal == L) {
            rotation_fct = {0};
        } else {
            rotation_fct = {0, 1};
        }
    }
    void (Cube::*cube_rotation_lambda)();
    Face (Cube::*face_rotation_lambda)(Face);
    if(rotation_fct.size() == 1) {
        cube_rotation_lambda = cube_operations[rotation_fct[0]];
        face_rotation_lambda = face_operations[rotation_fct[0]];
    }
    else {
        if((this->*face_operations[rotation_fct[0]])(preserved_face) == preserved_face) {
            cube_rotation_lambda = cube_operations[rotation_fct[0]];
            face_rotation_lambda = face_operations[rotation_fct[0]];
        }
        else {
            cube_rotation_lambda = cube_operations[rotation_fct[1]];
            face_rotation_lambda = face_operations[rotation_fct[1]];
        }

    }
    while(face != goal) {
        face = (this->*face_rotation_lambda)(face);
        (this->*cube_rotation_lambda)();
    }
}

void Cube::rotate_cube_X() {
    char buffer[4];
    copy(U,U+4, buffer);

    U[0] = L[3];
    U[1] = L[0];
    U[3] = L[2];
    U[2] = L[1];

    L[0] = D[1];
    L[1] = D[2];
    L[2] = D[3];
    L[3] = D[0];

    D[0] = R[1];
    D[1] = R[2];
    D[2] = R[3];
    D[3] = R[0];

    R[0] = buffer[3];
    R[1] = buffer[0];
    R[2] = buffer[1];
    R[3] = buffer[2];

    twist_colors(F);
    twist_colors_rev(B);
}

void Cube::rotate_cube_Y() {
    char buffer[4];
    copy(U,U+4, buffer);
    copy(F,F+4,U);
    F[0] = D[2];
    F[1] = D[3];
    F[2] = D[0];
    F[3] = D[1];
    copy(B,B+4,D);
    B[0] = buffer[2];
    B[1] = buffer[3];
    B[2] = buffer[0];
    B[3] = buffer[1];

    twist_colors(R);
    twist_colors_rev(L);
}

void Cube::rotate_cube_Z() {
    Face cpy = F;
    F = R;
    R = B;
    B = L;
    L = cpy;

    twist_colors(U);
    twist_colors_rev(D);
}

Face Cube::rotate_X(Face face) {
    if(face == F || face == B)
        return face;
    if(face == U)
        return R;
    if(face == R)
        return D;
    if(face == D)
        return L;
    if(face == L)
        return U;
}

Face Cube::rotate_Y(Face face) {
    if(face == R || face == L)
        return face;
    if(face == U)
        return B;
    if(face == B)
        return D;
    if(face == D)
        return F;
    if(face == F)
        return U;
}

Face Cube::rotate_Z(Face face) {
    if(face == U || face == D)
        return face;
    if(face == F)
        return L;
    if(face == L)
        return B;
    if(face == B)
        return R;
    if(face == R)
        return F;
}

array<char *, 8> Cube::get_face_periphery(Face face) {
    if(face  == F)
        return {&U[3], &U[2], &R[0], &R[3], &D[3], &D[2], &L[2], &L[1]};
    if(face == R)
        return {&U[2], &U[1], &B[0], &B[3], &D[0], &D[3], &F[2], &F[1]};
    if(face == B)
        return {&U[1], &U[0], &L[0], &L[3], &D[1], &D[0], &R[2], &R[1]};
    if(face == L)
        return {&U[0], &U[3], &F[0], &F[3], &D[2], &D[1], &B[2], &B[1]};
    if(face == U)
        return {&B[1], &B[0], &R[1], &R[0], &F[1], &F[0], &L[1], &L[0]};
    if(face == D)
        return {&F[3], &F[2], &R[3], &R[2], &B[3], &B[2], &L[3], &L[2]};
    return {nullptr};
}

void Cube::rotate_face(Face face) {
    twist_colors(face);
    auto periphery = get_face_periphery(face);
    char buff[2] = {*periphery[6],*periphery[7]};
    for(int  i=7; i>2; i-=2) {
        *periphery[i] = *periphery[i-2];
        *periphery[i-1] = *periphery[i-3];
    }
    *periphery[0] = buff[0];
    *periphery[1] = buff[1];
}

void Cube::rotate_face_rev(Face face) {
    twist_colors_rev(face);
    auto periphery  = get_face_periphery(face);
    char buff[2] = {*periphery[0], *periphery[1]};
    for(int i = 0; i<5; i+=2) {
        *periphery[i] = *periphery[i+2];
        *periphery[i+1] = *periphery[i+3];
    }
    *periphery[6] = buff[0];
    *periphery[7] = buff[1];
}

Cube::Cube(): F(new char[4]),
              B(new char[4]),
              L(new char[4]),
              R(new char[4]),
              U(new char[4]),
              D(new char[4]){
    fill(F, F+4, 'r');
    fill(B, B+4, 'o');
    fill(U, U+4, 'w');
    fill(D, D+4, 'y');
    fill(R, R+4, 'b');
    fill(L, L+4, 'g');
}
void Cube::apply_random_operations(int N) {
    void(Cube::*operation[12])() = {
            &Cube::rot_U,
            &Cube::rot_rev_U,
            &Cube::rot_D,
            &Cube::rot_rev_D,
            &Cube::rot_L,
            &Cube::rot_rev_L,
            &Cube::rot_R,
            &Cube::rot_rev_R,
            &Cube::rot_F,
            &Cube::rot_rev_F,
            &Cube::rot_B,
            &Cube::rot_rev_B
    };

    std::srand(static_cast<unsigned int>(std::time(0)));
    int random_operation;
    for(int i = 0; i< N; ++i){
        random_operation = rand() % 12;
        (this->*operation[random_operation])();
    }
    cout<<"\n>>> Applied "<<N<<" random operations on the Cube";
}
void Cube::print_faces() {
    cout<<endl<<"Front       Back"<<endl;
    cout<<F[0]<<"  "<<F[1]<<"        "<<B[0]<<"  "<<B[1]<<endl;
    cout<<F[3]<<"  "<<F[2]<<"        "<<B[3]<<"  "<<B[2]<<endl;

    cout<<"Left        Right"<<endl;
    cout<<L[0]<<"  "<<L[1]<<"        "<<R[0]<<"  "<<R[1]<<endl;
    cout<<L[3]<<"  "<<L[2]<<"        "<<R[3]<<"  "<<R[2]<<endl;

    cout<<"Up          Down"<<endl;
    cout<<U[0]<<"  "<<U[1]<<"        "<<D[0]<<"  "<<D[1]<<endl;
    cout<<U[3]<<"  "<<U[2]<<"        "<<D[3]<<"  "<<D[2]<<endl;
}

void Cube::twist_colors(Face face) {
    char buff = face[3];
    face[3] = face[2];
    face[2] = face[1];
    face[1] = face[0];
    face[0] = buff;
}

void Cube::twist_colors_rev(Face face) {
    char buff  = face[0];
    face[0] = face[1];
    face[1] = face[2];
    face[2] = face[3];
    face[3] = buff;
}
