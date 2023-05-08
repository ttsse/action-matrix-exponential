#ifndef __EXPMV_H
#define __EXPMV_H


#include<petscmat.h>
#include<petscvec.h>
#include<petscsystypes.h>
#include<string.h>


class expmv
{
    public:

    /// @brief empty constructor
    expmv() {};


    /// @brief destructor
    ~expmv() {};

    /// @brief constructor
    expmv(PetscReal t, Mat A, Vec b,string precision = 'double', int mmax = 55, int pmax = 15, bool shift = true, bool balance = false);

    /// @brief compute exp(t*A)b and save it in variable expmvtAb
    void compute_action();

    /// @brief get the computed action
    /// @param v a pointer to the vector you want to save the result in
    void get_expmvtAb(Vec *v);

    private:

    /// @brief finds the parameters m* and s according to code fragment 3.1 in https://epubs.siam.org/doi/pdf/10.1137/100788860
    /// @param mstar 
    /// @param s 
    void find_params(double& mstar, int& s);

    /// @brief finds an appropriate value of theta for double precision
    /// @param m 
    /// @return the value for theta
    double theta_double_prec(int m);

    double theta_single_prec(int m);

    double theta_half_prec(int m);

    public:

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

    double Anorm;
    int mmax;
    int pmax;
    string precision;

    bool shift;
    bool balance;
};

#endif
