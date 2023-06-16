

#include<petscmat.h>
#include<petscvec.h>
#include<petscsystypes.h>
#include<petscerror.h>
#include<iostream>
#include "expmv.h"

expmv::expmv(PetscReal t, Mat A, Vec b,const char precision[], int mmax, int pmax, bool shift, bool balance)
{
    this->set_t(t);
    this->set_A(A);
    this->set_b(b);
    this->set_mmax(mmax);
    this->set_pmax(pmax);
    this->set_precision(precision);

    this->set_shift(shift);
    this->set_balance(balance);
};

void expmv::compute_action()
{

    if (this->balance)
    {
        PetscPrintf(PETSC_COMM_WORLD, "Sorry kid, no balancing allowed yet, come back later >=(\n");
    }
    Vec muI;
    if (this->shift)
    {

        VecCreate(MPI_COMM_WORLD, &muI);
        VecSetSizes(muI, PETSC_DECIDE, this->n);
        VecSetFromOptions(muI);
        VecSet(muI,-1*(this->mu));
        VecAssemblyBegin(muI);
        VecAssemblyEnd(muI);        

        MatDiagonalSet(this->A, muI, ADD_VALUES); //line 6
    }

    if ((!(this->t) && !(this->Anorm)))
    {
        this->mstar = 0; this->s = 1; //line 8
    }
    else
    {
        this->find_params(); //line 10
    }

    PetscScalar eta;    

    VecCopy(this->b, this->expmvtAb); 
    eta = exp(this->t * this->mu/(this->s)); //line 12


    PetscScalar c1, c2, Fnorm;
    Vec btemp, ogb;

    VecDuplicate(this->b, &btemp);
    VecDuplicate(this->b, &ogb);
    VecCopy(this->b, ogb); //save a copy so we can still have the original b

    for (int i = 1; i <= this->s; i++)
    {
        VecNorm(this->b, NORM_INFINITY, &c1); //line 14

        for (int j = 1; j <= this->mstar; j++)
        {
            //line 16
            MatMult(this->A, this->b, btemp);
            VecScale(btemp, (PetscScalar)(this->t/(this->s * j)));
            VecCopy(btemp, this->b);
            VecNorm(this->b, NORM_INFINITY, &c2);

            VecAXPY(this->expmvtAb, 1, this->b); //line 17

            //line 18
            VecNorm(this->expmvtAb, NORM_INFINITY, &Fnorm);

            if (c1+c2 <= this->tol*Fnorm)
            {
                break;
            }

            c1 = c2; //line 19
        }

        VecScale(this->expmvtAb, eta);
        VecCopy(this->expmvtAb, this->b);
    }

    VecCopy(ogb, this->b);

    VecDestroy(&ogb);
    VecDestroy(&btemp);

    if (this->shift)
    {
        VecScale(muI, -1);
        MatDiagonalSet(this->A, muI, ADD_VALUES); //undo the shifting
        //this is important because the A in the class points to the same A outside the class
        //that is, changing this A changes the original one so we undo all changes
    }

    VecDestroy(&muI);

    if (this->balance)
    {
        //do some cool stuff
    }

    PetscObjectSetName((PetscObject)this->expmvtAb, "expmvtAb");
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
    for (int i = 0; i<this->mmax; i++) 
    {
        allelem[i] = i;
        mPetscScalar[i] = i+1;
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
    VecAssemblyBegin(thetaVec);
    VecAssemblyEnd(thetaVec);

    if (this->Anorm <= (4*theta[this->mmax]*this->pmax*(this->pmax+3))/(this->mmax) || true) //condition 3.13
    {
        VecCreate(MPI_COMM_WORLD, &AnormVec);
        VecSetSizes(AnormVec, PETSC_DECIDE, this->mmax);
        VecSetFromOptions(AnormVec);
        VecCreate(MPI_COMM_WORLD, &mVec);
        VecSetSizes(mVec, PETSC_DECIDE, this->mmax);
        VecSetFromOptions(mVec);

        VecAssemblyBegin(AnormVec);
        VecAssemblyEnd(AnormVec);
        VecAssemblyBegin(mVec);
        VecAssemblyEnd(mVec);

        VecSet(AnormVec, this->Anorm);
        VecAssemblyBegin(AnormVec);
        VecAssemblyEnd(AnormVec);

        VecSetValues(mVec, this->mmax, allelem, mPetscScalar, INSERT_VALUES);
        VecAssemblyBegin(mVec);
        VecAssemblyEnd(mVec);

        VecPointwiseDivide(Anormdivthetam, AnormVec, thetaVec);

        PetscScalar* Anormdivthetamceil;
        
        VecGetArray(Anormdivthetam, &Anormdivthetamceil);

        int rank;
        MPI_Comm_rank(PETSC_COMM_WORLD,&rank);

        Anormdivthetamceil[1] = (PetscScalar)ceil(Anormdivthetamceil[1]);
        Anormdivthetamceil[2] = (PetscScalar)ceil(Anormdivthetamceil[2]);
        Anormdivthetamceil[3] = (PetscScalar)ceil(Anormdivthetamceil[3]);
        Anormdivthetamceil[4] = (PetscScalar)ceil(Anormdivthetamceil[4]);
        Anormdivthetamceil[5] = (PetscScalar)ceil(Anormdivthetamceil[5]);
        Anormdivthetamceil[6] = (PetscScalar)ceil(Anormdivthetamceil[6]);
        Anormdivthetamceil[7] = (PetscScalar)ceil(Anormdivthetamceil[7]);
        Anormdivthetamceil[8] = (PetscScalar)ceil(Anormdivthetamceil[8]);
        Anormdivthetamceil[9] = (PetscScalar)ceil(Anormdivthetamceil[9]);
        Anormdivthetamceil[10] = (PetscScalar)ceil(Anormdivthetamceil[10]);
        Anormdivthetamceil[11] = (PetscScalar)ceil(Anormdivthetamceil[11]);
        Anormdivthetamceil[12] = (PetscScalar)ceil(Anormdivthetamceil[12]);
        Anormdivthetamceil[13] = (PetscScalar)ceil(Anormdivthetamceil[13]);
        Anormdivthetamceil[14] = (PetscScalar)ceil(Anormdivthetamceil[14]);
        Anormdivthetamceil[15] = (PetscScalar)ceil(Anormdivthetamceil[15]);
        Anormdivthetamceil[16] = (PetscScalar)ceil(Anormdivthetamceil[16]);
        Anormdivthetamceil[17] = (PetscScalar)ceil(Anormdivthetamceil[17]);
        Anormdivthetamceil[18] = (PetscScalar)ceil(Anormdivthetamceil[18]);
        Anormdivthetamceil[19] = (PetscScalar)ceil(Anormdivthetamceil[19]);
        Anormdivthetamceil[20] = (PetscScalar)ceil(Anormdivthetamceil[20]);
        Anormdivthetamceil[21] = (PetscScalar)ceil(Anormdivthetamceil[21]);
        Anormdivthetamceil[22] = (PetscScalar)ceil(Anormdivthetamceil[22]);
        Anormdivthetamceil[23] = (PetscScalar)ceil(Anormdivthetamceil[23]);
        Anormdivthetamceil[24] = (PetscScalar)ceil(Anormdivthetamceil[24]);
        Anormdivthetamceil[25] = (PetscScalar)ceil(Anormdivthetamceil[25]);
        Anormdivthetamceil[26] = (PetscScalar)ceil(Anormdivthetamceil[26]);
        Anormdivthetamceil[27] = (PetscScalar)ceil(Anormdivthetamceil[27]);
        Anormdivthetamceil[28] = (PetscScalar)ceil(Anormdivthetamceil[28]);
        Anormdivthetamceil[29] = (PetscScalar)ceil(Anormdivthetamceil[29]);
        Anormdivthetamceil[30] = (PetscScalar)ceil(Anormdivthetamceil[30]);
        Anormdivthetamceil[31] = (PetscScalar)ceil(Anormdivthetamceil[31]);
        Anormdivthetamceil[32] = (PetscScalar)ceil(Anormdivthetamceil[32]);
        Anormdivthetamceil[33] = (PetscScalar)ceil(Anormdivthetamceil[33]);
        Anormdivthetamceil[34] = (PetscScalar)ceil(Anormdivthetamceil[34]);
        Anormdivthetamceil[35] = (PetscScalar)ceil(Anormdivthetamceil[35]);
        Anormdivthetamceil[36] = (PetscScalar)ceil(Anormdivthetamceil[36]);
        Anormdivthetamceil[37] = (PetscScalar)ceil(Anormdivthetamceil[37]);
        Anormdivthetamceil[38] = (PetscScalar)ceil(Anormdivthetamceil[38]);
        Anormdivthetamceil[39] = (PetscScalar)ceil(Anormdivthetamceil[39]);
        Anormdivthetamceil[40] = (PetscScalar)ceil(Anormdivthetamceil[40]);
        Anormdivthetamceil[41] = (PetscScalar)ceil(Anormdivthetamceil[41]);
        Anormdivthetamceil[42] = (PetscScalar)ceil(Anormdivthetamceil[42]);
        Anormdivthetamceil[43] = (PetscScalar)ceil(Anormdivthetamceil[43]);
        Anormdivthetamceil[44] = (PetscScalar)ceil(Anormdivthetamceil[44]);
        Anormdivthetamceil[45] = (PetscScalar)ceil(Anormdivthetamceil[45]);
        Anormdivthetamceil[46] = (PetscScalar)ceil(Anormdivthetamceil[46]);
        Anormdivthetamceil[47] = (PetscScalar)ceil(Anormdivthetamceil[47]);
        Anormdivthetamceil[48] = (PetscScalar)ceil(Anormdivthetamceil[48]);
        Anormdivthetamceil[49] = (PetscScalar)ceil(Anormdivthetamceil[49]);
        Anormdivthetamceil[50] = (PetscScalar)ceil(Anormdivthetamceil[50]);
        Anormdivthetamceil[51] = (PetscScalar)ceil(Anormdivthetamceil[51]);
        Anormdivthetamceil[52] = (PetscScalar)ceil(Anormdivthetamceil[52]);
        Anormdivthetamceil[53] = (PetscScalar)ceil(Anormdivthetamceil[53]);
        Anormdivthetamceil[54] = (PetscScalar)ceil(Anormdivthetamceil[54]);

        if (rank == 0)
        {
            for (int i = 0; i<this->mmax; i++)
            {
                //Anormdivthetamceil[i] = (PetscScalar)ceil(Anormdivthetamceil[i]);
            }
        }

        MPI_Barrier(PETSC_COMM_WORLD);

	    VecRestoreArray(Anormdivthetam,&Anormdivthetamceil);

        VecPointwiseMult(thetaVec, mVec,Anormdivthetam); //let's reuse thetaVec

        PetscReal sTemp;
        VecMin(thetaVec, &(this->mstar), &sTemp); //get mstar according to line 2 in code fragment 3.1
        this->mstar += 1; //indexing is zero based but our m's are not
        this->s = sTemp/mstar;
    }
    else
    {
        //not implemented yet, i'm sure it will work...
    }

    VecDestroy(&thetaVec);
    VecDestroy(&AnormVec);
    VecDestroy(&Anormdivthetam);
    VecDestroy(&mVec);
};

///setter functions

void expmv::set_A(Mat A)
{
    this->A = A;

    PetscObjectSetName((PetscObject)this->A, "A");

    MatNorm(A, NORM_1, &(this->Anorm));
    this->Anorm *= abs(this->t); //this way avoids multiplying the entire matrix with a scalar
    MatGetTrace(this->A, &(this->mu));
    MatGetSize(A, &(this->n), NULL);
    this->mu = this->mu/(this->n);

    VecCreate(MPI_COMM_WORLD, &(this->expmvtAb));
    VecSetSizes(this->expmvtAb, PETSC_DECIDE, this->n);
    VecSetFromOptions(this->expmvtAb);
    VecAssemblyBegin(this->expmvtAb);
    VecAssemblyEnd(this->expmvtAb);
};

void expmv::set_b(Vec b)
{
    this->b = b;
    PetscObjectSetName((PetscObject)this->b, "b");
};

void expmv::set_t(PetscReal t)
{
    this->t = t;
};

void expmv::set_precision(std::string precision)
{
    std::string prec(precision);

    this->precision = prec;

    std::string half("half");
    std::string single("single");
    std::string doubles("double");

    if (this->precision == half)
    {
        this->tol = pow(2,-10);
    }
    else if (this->precision == single)
    {
        this->tol = pow(2,-24);
    }
    else if (this->precision == doubles)
    {
        this->tol = pow(2,-53);
    }
    else
    {
        throw std::exception();
    }
}

void expmv::set_mmax(int mmax)
{
    this->mmax = mmax;
}

void expmv::set_pmax(int pmax)
{
    this->pmax = pmax;
}

void expmv::set_shift(bool shift)
{
    this->shift = shift;
}

void expmv::set_balance(bool balance)
{
    this->balance = balance;
}

///getter functions

Mat expmv::get_A()
{
    return this->A;
}

double expmv::get_Anorm()
{
    return this->Anorm;
}

double expmv::get_mu()
{
    return this->mu;
}

PetscInt expmv::get_n()
{
    return this->n;
}

Vec expmv::get_b()
{
    return this->b;
}

Vec expmv::get_expmvtAb()
{
    return this->expmvtAb;
}

std::string expmv::get_precision()
{
    return this->precision;
}

int expmv::get_mstar()
{
    return this->mstar;
}

int expmv::get_s()
{
    return this->s;
}

PetscReal expmv::get_t()
{
    return this->t;
}

int expmv::get_mmax()
{
    return this->mmax;
}

int expmv::get_pmax()
{
    return this->pmax;
}

bool expmv::get_shift()
{
    return this->shift;
}

bool expmv::get_balance()
{
    return this->balance;
}

///printing functions

void expmv::print_A()
{
    MatView(this->A, PETSC_VIEWER_STDOUT_WORLD);
};

void expmv::print_b()
{
    VecView(this->b, PETSC_VIEWER_STDOUT_WORLD);
};

void expmv::print_expmvtAb()
{
    VecView(this->expmvtAb, PETSC_VIEWER_STDOUT_WORLD);
};
