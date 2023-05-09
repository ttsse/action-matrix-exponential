

#include<petscmat.h>
#include<petscvec.h>
#include<petscsystypes.h>
#include<petscerror.h>
#include<iostream>
#include "expmv.h"

expmv::expmv(PetscReal t, Mat A, Vec b,const char precision[], int mmax, int pmax, bool shift, bool balance)
{
    this->t = t;
    this->A = A;
    this->b =b;

    MatNorm(A, NORM_1, &(this->Anorm));

    this->mmax = mmax;
    this->pmax = pmax;

    std::string prec(precision);

    this->precision = prec;

    this->shift = shift;
    this->balance = balance;
};

void expmv::compute_action()
{
    std::cout << "I'm not doing much for now, come back later =/\n";
    this->find_params();
};

void expmv::get_expmvtAb(Vec *v)
{
    // PetscErrorCode ierr;
    VecDuplicate(this->expmvtAb, v); //CHKERRQ(ierr);
};

void expmv::find_params()
{
    std::vector<double> theta = this->get_theta();

    Vec thetaVec;
    Vec AnormVec;
    Vec Anormdivthetam;
    Vec mVec; //need a Petsc vector of m

    //create a bunch of vectors with various data
    PetscScalar* thetaPetsc = &theta[0]; //we need theta in a different type
    PetscInt allelem[this->mmax]; //we need a vector specifying all elements for out setvalues
    PetscScalar mPetscScalar[this->mmax]; //and another one with the same thing but different data type
    PetscScalar AnormPetsc[this->mmax]; //similarly need a vector all containing the same number
    for (int i = 0; i<this->mmax; i++) 
    {
        allelem[i] = i;
        mPetscScalar[this->mmax];
        AnormPetsc[i] = this->Anorm;
    }

    //create the vectors
    VecCreate(MPI_COMM_WORLD, &thetaVec);
    VecSetSizes(thetaVec, PETSC_DECIDE, this->mmax);
    VecSetFromOptions(thetaVec);
    VecCreate(MPI_COMM_WORLD, &Anormdivthetam);
    VecSetSizes(Anormdivthetam, PETSC_DECIDE, this->mmax);
    VecSetFromOptions(Anormdivthetam);

    VecAssemblyBegin(thetaVec);
    VecAssemblyEnd(thetaVec);
    VecAssemblyBegin(Anormdivthetam);
    VecAssemblyEnd(Anormdivthetam);

    //make thetaPetsc into a PetscVector
    VecSetValues(thetaVec, this->mmax, allelem, thetaPetsc, INSERT_VALUES);

    if (this->Anorm <= (4*theta[this->mmax]*this->pmax*(this->pmax+3))/(this->mmax) || true) //condition 3.13
    {
        VecCreate(MPI_COMM_WORLD, &AnormVec);
        VecSetSizes(AnormVec, PETSC_DECIDE, this->mmax);
        VecSetFromOptions(AnormVec);
        VecCreate(MPI_COMM_WORLD, &mVec);
        VecSetSizes(mVec, PETSC_DECIDE, this->mmax);
        VecSetFromOptions(mVec);

        VecSetValues(AnormVec, this->mmax, allelem, AnormPetsc, INSERT_VALUES);
        VecSetValues(mVec, this->mmax, allelem, mPetscScalar, INSERT_VALUES); //turns out our allelemvector can be reused for setting values of m

        VecPointwiseDivide(Anormdivthetam, AnormVec, mVec);
        VecPointwiseMult(thetaVec, mVec,Anormdivthetam); //let's reuse thetaVec

        VecMin(thetaVec, &(this->mstar), NULL); //get mstar according to line 2 in code fragment 3.1
        PetscScalar* sTemp;
        VecGetValues(thetaVec, 1, allelem+this->mstar-1, sTemp); //get s according to line 3
        this->s = (int)(*sTemp);
    }
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
