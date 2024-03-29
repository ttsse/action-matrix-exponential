# Installation #
Petsc is required and can be installed with\\

```
git clone -b release https://gitlab.com/petsc/petsc.git petsc  
git pull
```

Once downloaded, Petsc can be configured with

```
./configure --with-cc=gcc --with-cxx=g++ --download-mpich --download-f2cblaslapack --download-hdf5 --with-fc=0
```

and built according to the message given when the configuration is set up.

Note: Depending on what is already available on the system, it may not be necessary to download everything during the configuration. Further, hdf5 is only required for the tests or if you want to read in Matlab matrices to Petsc.

You may also follow the installation guidelines given on Petsc's website (https://petsc.org/release/install/install_tutorial/) but it is worth noting that this code does not require Fortran for anything and leaving it out during configuration may speed up build times.

# Usage #
This package solves problems of the form $x=e^{tA}b$ for known $t,A,b$ where $x,b\in \mathbb{R}^N$, $A\in\mathbb{R}^{N\times N}$, and $t\in\mathbb{R}$ using the method by Al-Mohy and Higham [[1](https://epubs.siam.org/doi/pdf/10.1137/100788860)]. This computation is performed without explicitly computing $e^{tA}$, which in general is a dense $N\times N$ matrix, even if $A$ is sparse.

## Main functions ##
```
expmv(PetscReal t, Mat A, Vec b,const char precision[], int mmax, int pmax, bool shift, bool balance)
```
Constructor for the expmv class
### Arguments ###
```t,A,b``` are their counterparts in the expression $x=e^{tA}b$

```precision``` should be one of 'half', 'single', or 'double'. Default is 'double'.

```mmax``` is the largest m allowed, as described in [[1](https://epubs.siam.org/doi/pdf/10.1137/100788860)]. Default is 55.

```shift``` decides if the matrix $A$ should be shifted before computations by subtracting trace(A) from the diagonal, resulting in a more well conditioned matrix. Default is true.

```balance``` decides if the matrix should be balanced before computations. Deafult is false.

```
void compute_action()
```

Computes the action ```x``` using the given instance variables. It is then possible to get ```x``` using ```Vec get_x()```.

# References #

[1] Al-Mohy, A.H. and Higham, N.J., 2011. Computing the action of the matrix exponential, with an application to exponential integrators. SIAM journal on scientific computing, 33(2), pp.488-511.
