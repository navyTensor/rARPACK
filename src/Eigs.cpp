#include "Eigs.h"

Eigs::Eigs(int n_, int nev_, int ncv_,
           const string & which_, int workmode_,
           double sigmar_, double sigmai_,
           char bmat_, double tol_, int maxitr_)
{
    n = n_;
    nev = nev_;
    ncv = ncv_;
    which = which_;
    workmode = workmode_;
    sigmar = sigmar_;
    sigmai = sigmai_;
    bmat = bmat_;
    tol = tol_;
    maxitr = maxitr_;

    ido = 0;
    info = 0;
    ierr = 0;

    matrix_linked = false;
    
    for(int i = 0; i < 11; i++)
        iparam[i] = 0;

    iparam[1 - 1] = 1;
    iparam[3 - 1] = maxitr;
    iparam[7 - 1] = workmode;

    for(int i = 0; i < 14; i++)
        ipntr[i] = 0;

    resid = new double[n]();
    workd = new double[3 * n]();
    // lworkl and workl are not initialized here since their
    // sizes are determined according to the problem.
    // Classes derived from Eigs should do this.
}

void Eigs::InitResid()
{
    // Create initial residual vector
    // info = 1 means using the residual vector we provide
    info = 1;
    double *initcoef = new double[n];
    for(int i = 0; i < n; i++)
        initcoef[i] = sin(i + 0.5);

    // resid = A * initcoef
    MultVector(initcoef, resid);
    delete [] initcoef;
}

Eigs::~Eigs()
{
    delete [] workd;
    delete [] resid;
}
