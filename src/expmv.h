#ifndef __EXPMV_H
#define __EXPMV_H


#include<petscmat.h>
#include<petscvec.h>
#include<petscsystypes.h>
#include<string>
#include<vector>


class expmv
{
    public:

    /// @brief empty constructor
    expmv() {};


    /// @brief destructor
    ~expmv() {};

    /// @brief constructor
    expmv(PetscReal t, Mat A, Vec b,const char precision[] = "double", int mmax = 55, int pmax = 15, bool shift = true, bool balance = true);

    /// @brief compute exp(t*A)b and save it in variable expmvtAb
    void compute_action();

    /// @brief get the computed action
    /// @param v a pointer to the vector you want to save the result in
    void get_expmvtAb(Vec *v);

    private:

    /// @brief finds the parameters m* and s according to code fragment 3.1 in https://epubs.siam.org/doi/pdf/10.1137/100788860
    /// @param mstar 
    /// @param s 
    void find_params();

    /// @brief finds an appropriate value of theta for each precision
    /// @param m 
    /// @return the value for theta
    std::vector<double> get_theta();

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

    void print_A();

    void print_b();

    void print_expmvtAb();

    int get_mstar();

    int get_s();

    private:

    PetscReal t;
    Mat A;
    Vec b;
    Vec expmvtAb;

    PetscInt n;

    double Anorm;
    double mu;
    int mmax;
    int pmax;
    std::string precision;
    double tol;

    int mstar;
    int s;

    bool shift;
    bool balance;
};

#endif
