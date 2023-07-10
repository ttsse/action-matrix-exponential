# Purpose
A PETSc implementation of the action of the matrix exponential on a vector.
Solves problems of the form $x=e^{tA}b$ where $x,b\in \mathbb{R}^N$, $A\in\mathbb{R}^{N\times N}$, and $t\in\mathbb{R}$ without explicitly computing $e^{tA}$, which in general is a dense $N\times N$ matrix, even if $A$ is sparse.
