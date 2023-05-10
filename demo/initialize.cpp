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
    MatSetSizes(A, PETSC_DECIDE, PETSC_DECIDE, 2, 2);
    MatSetFromOptions(A);
    MatSetUp(A);

    // Set values in the matrix
    PetscInt rows[2] = {0, 1};
    PetscInt cols[2] = {0, 1};
    PetscScalar values[4] = {1.0, 2.0, 3.0, 4.0};
    MatSetValues(A, 2, rows, 2, cols, values, INSERT_VALUES);

    // Assemble the matrix
    MatAssemblyBegin(A, MAT_FINAL_ASSEMBLY);
    MatAssemblyEnd(A, MAT_FINAL_ASSEMBLY);

    // Create a 2 by 1 vector
    Vec b;
    VecCreate(PETSC_COMM_WORLD, &b);
    VecSetSizes(b, PETSC_DECIDE, 2);
    VecSetFromOptions(b);
    VecSetUp(b);

    // Set values in the vector
    PetscScalar b_values[2] = {5.0, 6.0};
    VecSetValues(b, 2, rows, b_values, INSERT_VALUES);

    // Assemble the vector
    VecAssemblyBegin(b);
    VecAssemblyEnd(b);

    // Make a scaling value
    PetscReal t = 1;

    expmv matexp(t, A, b);
    matexp.compute_action();
    std::cout << "\nt is currently set to " << matexp.get_t() << "\n";
    std::cout << "\nmstar is currently set to " << matexp.get_mstar() << "\n";
    std::cout << "\ns is currently set to " << matexp.get_s() << "\n";

    matexp.print_expmvtAb();

    MatView(A, PETSC_VIEWER_STDOUT_WORLD);
    VecView(b, PETSC_VIEWER_STDOUT_WORLD);

    PetscFinalize();
    return 0;
}
