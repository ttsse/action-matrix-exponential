#ifndef __EXPMV_H
#define __EXPMV_H


#include<petscmat.h>
#include<petscvec.h>
#include<petscsystypes.h>


class expmv
{
    public:

    /// @brief empty constructor
    expmv() {};


    /// @brief destructor
    ~expmv() {};

    /// @brief constructor
    expmv(PetscReal t, Mat A, Vec b);

    /// @brief compute exp(t*A)b and save it in variable expmvtAb
    void compute_action();

    /// @brief get the computed action
    /// @param v a pointer to the vector you want to save the result in
    void get_expmvtAb(Vec *v);

    /// @brief set the matrix
    /// @param A the matrix to be set as the matrix to take the exponential of
    void set_A(Mat A);

    /// @brief set the scaling value t
    /// @param t the scaling value
    void set_t(PetscReal t);

    /// @brief set the Vector
    /// @param b the vector to be multiplied by the exponential
    void set_b(Vec b);

    ///@brief get the current value for t
    ///@return the value for t
    PetscReal get_t();

    private:

    PetscReal t;
    Mat A;
    Vec b;
    Vec expmvtAb;
};

#endif
