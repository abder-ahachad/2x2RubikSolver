#include <iostream>
#include "inc/cube_solver.h"
int main() {
    cout<<">>> Initializing the cube at the correct state :";
    Cube cube;
    cube.print_faces();
    cube.apply_random_operations(100);
    cube.print_faces();

    cout<<"\n>>> Solving the cube ....";
    solve(cube);
    cube.print_faces();

}
