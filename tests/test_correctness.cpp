#include <petscmat.h>
#include <petscvec.h>
#include <petscsystypes.h>
#include "../src/expmv.h"
#include <iostream>
#include <string>
#include<gtest/gtest.h>

double testmat(std::string name, int size, double t) {
    //PetscInitialize(&argc, &argv, NULL, NULL);

    // Create a 2 by 2 matrix
    Mat A;
    MatCreate(PETSC_COMM_WORLD, &A);
    MatSetSizes(A, PETSC_DECIDE, PETSC_DECIDE, size, size);
    MatSetFromOptions(A);
    MatSetUp(A);

    //create petscviewer object
    PetscViewer viewer;
    PetscViewerCreate(PETSC_COMM_WORLD,&viewer);
    PetscViewerSetType(viewer,PETSCVIEWERHDF5);
    PetscViewerFileSetMode(viewer,FILE_MODE_READ);

    std::string str = std::string("testmats/") + name;

    const char *matname = str.c_str();

    PetscViewerFileSetName(viewer,matname);

    // Create a 2 by 1 vector
    Vec b;
    VecCreate(PETSC_COMM_WORLD, &b);

    // Make a scaling value
    //PetscReal t = std::atof(t);

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

    //PetscPrintf(PETSC_COMM_WORLD,"Error for %s = %g\n",argv[2],err);
    //std::cout << "Error for " << argv[2] <<" = " <<err << "\n";

    //PetscFinalize();
    return err;
}

TEST(correctnesstest, Aidmat) { 
    EXPECT_LE(testmat("Aid.mat",2,-1),1e-10);
}

TEST(correctnesstest, Anormalmat) {
    EXPECT_LE(testmat("Anormal.mat",2,-1),1e-10);
}

TEST(correctnesstest, Atm50mat) {
    EXPECT_LE(testmat("Anormaltm50.mat",2,-50),1e-5);
}

TEST(correctnesstest, Abadcondmat) {
    EXPECT_LE(testmat("Abadcond.mat",2,-1),1e-10);
}

TEST(correctnesstest, Anegmat) {
    EXPECT_LE(testmat("Aneg.mat",2,1),1e-10);
}
