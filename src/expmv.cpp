

#include<petscmat.h>
#include<petscvec.h>
#include<petscsystypes.h>
#include<petscerror.h>
#include<iostream>
#include "expmv.h"

expmv::expmv(PetscReal t, Mat A, Vec b)
{
    this->t = t;
    this->A = A;
    this->b =b;
};

void expmv::compute_action()
{
    std::cout << "I'm not doing anything for now, come back later =/\n";
};

void expmv::get_expmvtAb(Vec *v)
{
    PetscErrorCode ierr;
    ierr = VecDuplicate(this->expmvtAb, v); //CHKERRQ(ierr);
};

void expmv::set_A(Mat A)
{
    this->A = A;
};

void expmv::set_t(PetscReal)
{
    this->t = t;
};

void expmv::set_b(Vec b)
{
    this->b = b;
};

PetscReal expmv::get_t()
{
    return this->t;
};
