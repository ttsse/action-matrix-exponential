#include <petscmat.h>
#include <petscvec.h>
#include <petscsystypes.h>
#include "../src/expmv.h"
#include <iostream>
#include <string>


int main(int argc, char **argv) {
    PetscInitialize(&argc, &argv, NULL, NULL);

    // Create a 2 by 2 matrix
    Mat A;
    MatCreate(PETSC_COMM_WORLD, &A);
    // MatSetSizes(A, PETSC_DECIDE, PETSC_DECIDE, 1000, 1000);
    MatSetFromOptions(A);
    MatSetUp(A);

    //create petscviewer object
    PetscViewer viewer;
    PetscViewerCreate(PETSC_COMM_WORLD,&viewer);
    PetscViewerSetType(viewer,PETSCVIEWERHDF5);
    PetscViewerFileSetMode(viewer,FILE_MODE_READ);

    std::string str = std::string("testmats/") + std::string(argv[2]);

    const char *matname = str.c_str();

    PetscViewerFileSetName(viewer,matname);

    // Create a 2 by 1 vector
    Vec b;
    VecCreate(PETSC_COMM_WORLD, &b);

    // Assemble the vector
    

    // Make a scaling value
    PetscReal t = std::atof(argv[1]);

    // initialize expmv class

    Vec expmvtAb, expmvtAbcomputed;
    VecCreate(PETSC_COMM_WORLD, &expmvtAb);
    VecCreate(PETSC_COMM_WORLD, &expmvtAbcomputed);

    PetscObjectSetName((PetscObject)A, "A");
    PetscObjectSetName((PetscObject)b, "b");
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
    expmvtAbcomputed = matexp.get_expmvtAb();
    
    //compute matrix exponential
    matexp.compute_action();

    PetscReal err;

    VecAXPY(expmvtAbcomputed, -1, expmvtAb);
    VecNorm(expmvtAbcomputed, NORM_2, &err);

    std::cout << "Error for " << argv[2] <<" = " err << "\n";

    PetscFinalize();
    return 0;
}
