#include <petscmat.h>
#include <petscvec.h>
#include <petscsystypes.h>
#include "../src/expmv.h"
#include <iostream>

#include <chrono>


int main(int argc, char **argv) {
    PetscInitialize(&argc, &argv, NULL, NULL);

    // Create a 2 by 2 matrix
    Mat A;
    PetscInt Asz = 2*5*7*8*9;
    MatCreateDense(PETSC_COMM_WORLD,PETSC_DECIDE,PETSC_DECIDE, Asz,Asz, &A);
    MatSetRandom(A,NULL);
    MatSetFromOptions(A);
    MatSetUp(A);

    // Assemble the matrix
    MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);

    // Create a Asz by 1 vector
    Vec b;
    VecCreate(PETSC_COMM_WORLD, &b);
    VecSetSizes(b, PETSC_DECIDE, Asz);
    VecSetRandom(b, NULL);
    VecAssemblyBegin(b);
    VecAssemblyEnd(b);

    // Make a scaling value
    PetscReal t = -1;

    PetscObjectSetName((PetscObject)A, "A");
    PetscObjectSetName((PetscObject)b, "b");

    expmv matexp(t, A, b);
    
    //compute matrix exponential
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    matexp.compute_action();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;

    PetscFinalize();
    return 0;
}
