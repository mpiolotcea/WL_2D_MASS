/**
 * @file src/lib/kg.cpp
 * @date 12/18/15
 * @author user
 */

#include "Tools/kg.h"

namespace Tools {

void kg::real2complex(double *real, fftw_complex *complex, int Nx, int Ny)
{
  // copy real into complex
  for (int x = 0; x < Nx; x++) {
    for (int y = 0; y < Ny; y++) {
      complex[x*Ny+y][0] = real[x*Ny+y];
      complex[x*Ny+y][1] = 0;
    }
  }
}

void kg::complex2real(fftw_complex *complex, double *real, int Nx, int Ny)
{
  // copy complex into real
  for (int x = 0; x < Nx; x++) {
    for (int y = 0; y < Ny; y++) {
      real[x*Ny+y] = complex[x*Ny+y][0];
    }
  }
}

void kg::realandimag2complex(double *real, double *imag, fftw_complex *complex, int Nx, int Ny)
{
  // copy real and imag into complex
  for (int x = 0; x < Nx; x++) {
    for (int y = 0; y < Ny; y++) {
      complex[x*Ny+y][0] = real[x*Ny+y];
      complex[x*Ny+y][1] = imag[x*Ny+y];
    }
  }
}

void kg::complex2realandimag(fftw_complex *complex, double *real, double *imag, int Nx, int Ny)
{
  // copy complex into real and imag
  for (int x = 0; x < Nx; x++) {
    for (int y = 0; y < Ny; y++) {
      real[x*Ny+y] = complex[x*Ny+y][0];
      imag[x*Ny+y] = complex[x*Ny+y][1];
    }
  }
}

void kg::fftw_forward(fftw_complex *complex, fftw_complex *circumflex, int Nx, int Ny)
{
  fftw_plan plan = fftw_plan_dft_2d(Nx, Ny, complex, circumflex, FFTW_FORWARD, FFTW_MEASURE);
  fftw_execute(plan);
  fftw_destroy_plan(plan);
}

void kg::fftw_backward(fftw_complex *circumflex, fftw_complex *complex, int Nx, int Ny)
{
  fftw_plan plan = fftw_plan_dft_2d(Nx, Ny, circumflex, complex, FFTW_BACKWARD, FFTW_MEASURE);
  fftw_execute(plan);
  fftw_destroy_plan(plan);
}

void kg::gammacircumflex2kappacircumflex(fftw_complex *gamma_real_circumflex, fftw_complex *gamma_imag_circumflex, fftw_complex *kappaE_circumflex, fftw_complex *kappaB_circumflex, int Nx, int Ny)
{
  // compute the multiplication in Fourier space
  for (int x = 0; x < Nx; x++) {
    for (int y = 0; y < Ny; y++) {
      double C1, C2;
      if (x == 0 && y == 0) {
        C1 = 0;
        C2 = 0;
      } else {
        C1 = (x*x-y*y)/(x*x+y*y);
        C2 = 2.0*x*y/(x*x+y*y);
      }
      long pos = x*Ny+y;
      kappaE_circumflex[pos][0] = C1*gamma_real_circumflex[pos][0]+C2*gamma_imag_circumflex[pos][0];
      kappaE_circumflex[pos][1] = C1*gamma_real_circumflex[pos][1]+C2*gamma_imag_circumflex[pos][1];
      kappaB_circumflex[pos][0] = C2*gamma_real_circumflex[pos][0]-C1*gamma_imag_circumflex[pos][0];
      kappaB_circumflex[pos][1] = C2*gamma_real_circumflex[pos][1]-C1*gamma_imag_circumflex[pos][1];
    }
  }
}

void kg::kappacircumflex2gammacircumflex(fftw_complex *kappaE_circumflex, fftw_complex *kappaB_circumflex, fftw_complex *gamma_real_circumflex, fftw_complex *gamma_imag_circumflex, int Nx, int Ny)
{
  // compute the multiplication in Fourier space
  for (int x = 0; x < Nx; x++) {
    for (int y = 0; y < Ny; y++) {
      double C1 = (x*x-y*y)/(x*x+y*y);
      double C2 = 2.0*x*y/(x*x+y*y);
      long pos = x*Ny+y;
      if (x == 0 && y == 0) {
        gamma_real_circumflex[pos][0] = gamma_real_circumflex[pos][1] = 0;
        gamma_imag_circumflex[pos][0] = gamma_imag_circumflex[pos][1] = 0;
        continue;
      }
      double denom = C1*C1+C2*C2;
      gamma_real_circumflex[pos][0] = (C1*kappaE_circumflex[pos][0]+C2*kappaB_circumflex[pos][0])/denom;
      gamma_real_circumflex[pos][1] = (C1*kappaE_circumflex[pos][1]+C2*kappaB_circumflex[pos][1])/denom;
      gamma_imag_circumflex[pos][0] = (C2*kappaE_circumflex[pos][0]-C1*kappaB_circumflex[pos][0])/denom;
      gamma_imag_circumflex[pos][1] = (C2*kappaE_circumflex[pos][1]-C1*kappaB_circumflex[pos][1])/denom;
    }
  }
}

void kg::gamma2kappa(double *gamma_real, double *gamma_imag, double *kappaE, double *kappaB, int Nx, int Ny)
{
  // allocate and initialize arrays in Fourier space
  fftw_complex *gamma_real_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  fftw_complex *gamma_imag_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  real2complex(gamma_real, gamma_real_complex, Nx, Ny);
  real2complex(gamma_imag, gamma_imag_complex, Nx, Ny);

  // compute the FFT on gamma
  fftw_complex *gamma_real_circumflex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  fftw_complex *gamma_imag_circumflex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  fftw_forward(gamma_real_complex, gamma_real_circumflex, Nx, Ny);
  fftw_forward(gamma_imag_complex, gamma_imag_circumflex, Nx, Ny);

  // compute the multiplication in Fourier space
  fftw_complex *kappaE_circumflex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  fftw_complex *kappaB_circumflex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  gammacircumflex2kappacircumflex(gamma_real_circumflex, gamma_imag_circumflex, kappaE_circumflex, kappaB_circumflex, Nx, Ny);

  // compute the backward FFT
  fftw_complex *kappaE_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  fftw_complex *kappaB_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  fftw_backward(kappaE_circumflex, kappaE_complex, Nx, Ny);
  fftw_backward(kappaB_circumflex, kappaB_complex, Nx, Ny);

  // get real part of the result of the backward FFT
  complex2real(kappaE_complex, kappaE, Nx, Ny);
  complex2real(kappaB_complex, kappaB, Nx, Ny);

  // free arrays
  fftw_free(kappaB_complex);
  fftw_free(kappaE_complex);
  fftw_free(kappaB_circumflex);
  fftw_free(kappaE_circumflex);
  fftw_free(gamma_imag_circumflex);
  fftw_free(gamma_real_circumflex);
  fftw_free(gamma_imag_complex);
  fftw_free(gamma_real_complex);
}

void kg::kappa2gamma(double *kappaE, double *kappaB, double *gamma_real, double *gamma_imag, int Nx, int Ny)
{
  // allocate and initialize arrays in Fourier space
  fftw_complex *kappaE_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  fftw_complex *kappaB_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  real2complex(kappaE, kappaE_complex, Nx, Ny);
  real2complex(kappaB, kappaB_complex, Nx, Ny);

  // compute the FFT on kappa
  fftw_complex *kappaE_circumflex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  fftw_complex *kappaB_circumflex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  fftw_forward(kappaE_complex, kappaE_circumflex, Nx, Ny);
  fftw_forward(kappaE_complex, kappaE_circumflex, Nx, Ny);

  // compute the multiplication in Fourier space
  fftw_complex *gamma_real_circumflex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  fftw_complex *gamma_imag_circumflex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  kappacircumflex2gammacircumflex(kappaE_circumflex, kappaB_circumflex, gamma_real_circumflex, gamma_imag_circumflex, Nx, Ny);

  // compute the backward FFT
  fftw_complex *gamma_real_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  fftw_complex *gamma_imag_complex = (fftw_complex*)fftw_malloc(sizeof(fftw_complex)*Nx*Ny);
  fftw_backward(gamma_real_circumflex, gamma_real_complex, Nx, Ny);
  fftw_backward(gamma_imag_circumflex, gamma_imag_complex, Nx, Ny);

  // get real part of the result of the backward FFT
  complex2real(gamma_real_complex, gamma_real, Nx, Ny);
  complex2real(gamma_imag_complex, gamma_imag, Nx, Ny);

  // free arrays
  fftw_free(gamma_imag_complex);
  fftw_free(gamma_real_complex);
  fftw_free(gamma_imag_circumflex);
  fftw_free(gamma_real_circumflex);
  fftw_free(kappaB_circumflex);
  fftw_free(kappaE_circumflex);
  fftw_free(kappaB_complex);
  fftw_free(kappaE_complex);
}

} // Tools namespace
