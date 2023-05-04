

#include<petsc/petscmat.h>
#include<petsc/petscvec.h>
#include<petsc/petscsystypes.h>
#include<petsc/petscerror.h>

#include "expmv.h"

expmv::expmv(PETSC_REAL t, Mat A, Vec b)
{
    this->t = t;
    this->A = A;
    this->b =b;
}

void expmv::compute_action();
{
    std::cout << "I'm not doing anything for now, come back later =/\n";
}

void get_expmvtAb(Vec *v);
{
    PetscErrorCode ierr;
    ierr = VecDuplicate(this->expmvtAb, v); CHKERRQ(ierr);
}

void expmv::set_A(Mat A)
{
    this->A = A;
}

void expmv::set_t(PETSC_REAL)
{
    this->t = t;
}

void expmv::set_b(Vec b)
{
    this->b = b;
}

