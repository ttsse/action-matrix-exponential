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

    /// setter functions 
    void set_A(Mat A);

    void set_b(Vec b);

    void set_t(PetscReal t);

    void set_precision(std::string precision);

    void set_mmax(int mmax);

    void set_pmax(int pmax);

    void set_shift(bool shift);

    void set_balance(bool balance);

    ///getter functions
    Mat get_A();

    double get_Anorm();

    double get_mu();

    PetscInt get_n();

    Vec get_b();

    Vec get_expmvtAb();

    std::string get_precision();

    int get_mstar();

    int get_s();

    PetscReal get_t();

    int get_mmax();

    int get_pmax();

    bool get_shift();

    bool get_balance();

    //printing functions
    void print_A();

    void print_b();

    void print_expmvtAb();

    private:
    Mat A;
    double Anorm;
    double mu;
    PetscInt n;

    Vec b;

    Vec expmvtAb;
    
    std::string precision;
    double tol;

    int mstar;
    int s;

    public:

    PetscReal t;

    int mmax;
    int pmax;

    bool shift;
    bool balance;

    MPI_Comm comm;    
};

#endif
