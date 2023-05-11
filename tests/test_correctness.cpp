#include <petscmat.h>
#include <petscvec.h>
#include <petscsystypes.h>
#include "../src/expmv.h"
#include <iostream>
int main(int argc, char **argv) {
    PetscInitialize(&argc, &argv, NULL, NULL);

    // Create a 2 by 2 matrix
    Mat A;
    MatCreate(PETSC_COMM_WORLD, &A);
    MatSetSizes(A, PETSC_DECIDE, PETSC_DECIDE, 10, 10);
    MatSetFromOptions(A);
    MatSetUp(A);

    //create petscviewer object
    PetscViewer viewer;
    PetscViewerCreate(PETSC_COMM_WORLD,&viewer);
    PetscViewerSetType(viewer,PETSCVIEWERHDF5);
    PetscViewerFileSetMode(viewer,FILE_MODE_READ);
    PetscViewerFileSetName(viewer,"matdensefiles/matdense10.mat");

    // Create a 2 by 1 vector
    Vec b;
    VecCreate(PETSC_COMM_WORLD, &b);

    // Assemble the vector
    

    // Make a scaling value
    PetscReal t = -1;

    // initialize expmv class

    Vec expmvtAb;
    VecCreate(PETSC_COMM_WORLD, &expmvtAb);

    PetscObjectSetName((PetscObject)A, "A10");
    PetscObjectSetName((PetscObject)b, "b10");
    // PetscObjectSetName(t, "t");
    PetscObjectSetName((PetscObject)expmvtAb, "expmvtAb");

    MatLoad(A, viewer);
    VecLoad(b, viewer);
    VecLoad(expmvtAb, viewer);

    // Assemble the matrix
    MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);

    VecAssemblyBegin(b);
    VecAssemblyEnd(b);

    VecAssemblyBegin(expmvtAb);
    VecAssemblyEnd(expmvtAb);

    expmv matexp(t, A, b);
    
    //compute matrix exponential
    matexp.compute_action();

    //print the result
    matexp.print_expmvtAb();

    //print the original arrays to see they are unchanged
    MatView(A, PETSC_VIEWER_STDOUT_WORLD);
    VecView(b, PETSC_VIEWER_STDOUT_WORLD);
   
    PetscFinalize();
    return 0;
}
