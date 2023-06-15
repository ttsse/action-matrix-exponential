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
    MatCreate(PETSC_COMM_WORLD, &A);
    MatSetSizes(A, PETSC_DECIDE, PETSC_DECIDE, 400000, 400000);
    MatSetFromOptions(A);
    MatSetUp(A);

    Vec b;
    VecCreate(PETSC_COMM_WORLD, &b);

    PetscViewer viewer;
    PetscViewerCreate(PETSC_COMM_WORLD,&viewer);
    PetscViewerSetType(viewer,PETSCVIEWERHDF5);
    PetscViewerFileSetMode(viewer,FILE_MODE_READ);

    PetscViewerFileSetName(viewer,"testmats/Arandsparse.mat");

    // Make a scaling value
    PetscReal t = -1;

    PetscObjectSetName((PetscObject)A, "A");
    PetscObjectSetName((PetscObject)b, "b");

    MatLoad(A, viewer);
    VecLoad(b, viewer);

    MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);

    VecAssemblyBegin(b);
    VecAssemblyEnd(b);

    expmv matexp(t, A, b);
    
    //compute matrix exponential
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    matexp.compute_action();

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();

    PetscPrintf(PETSC_COMM_WORLD, "Time difference = ");
    PetscPrintf(PETSC_COMM_WORLD, "%d",std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count());
    PetscPrintf(PETSC_COMM_WORLD, "[µs]\n");

    PetscFinalize();
    return 0;
}
