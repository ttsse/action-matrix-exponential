#ifndef __EXPMV_H
#define __EXPMV_H


#include<petsc/petscmat.h>
#include<petsc/petscvec.h>
#include<petsc/petscsystypes.h>


class expmv
{
    public:

    /// @brief empty constructor
    expmv() {};


    /// @brief destructor
    ~expmv() {};

    /// @brief constructor
    expmv(PETSC_REAL t, Mat A, Vec b);

    /// @brief compute exp(t*A)b and save it in variable expmvtAb
    void compute_action();

    /// @brief get the computed action
    /// @return the computed action as a shared_ptr<Vec>
    std::shared_ptr<Vec> get_expmvtAb();

    /// @brief set the matrix
    /// @param A the matrix to be set as the matrix to take the exponential of
    void set_A(Mat A);

    /// @brief set the scaling value t
    /// @param t the scaling value
    void set_t(PETSC_REAL t);

    /// @brief set the Vector
    /// @param b the vector to be multiplied by the exponential
    void set_b(Vec b);

    private:

    PETSC_REAL t;
    Mat A;
    Vec b;
    Vec expmvtAb
}

#endif