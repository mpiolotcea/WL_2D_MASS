/**
 * @file Tools/ShearInversions.h
 * @date 11/27/15
 * @author user
 */

#ifndef _TOOLS_SHEARINVERSIONS_H
#define _TOOLS_SHEARINVERSIONS_H

#include <fftw3.h>

namespace Tools {

/**
 * @class ShearInversions
 * @brief
 *
 */
class ShearInversions
{

public:
  ShearInversions(int NZeroPadded);
  /**
   * @brief Destructor
   */
  virtual ~ShearInversions();

  //  void gamma2kappa(dblarray &gamma1, dblarray &gamma2, dblarray &kappa);
  void gamma2kappa(double *gamma1, double *gamma2, double *kappa, int Nx, int Ny, int Nz);

  //  void flexion2kappa(double pixel_size, dblarray &F1, dblarray &F2, dblarray &kappa);
  void flexion2kappa(double pixel_size, double *F1, double *F2, double *kappa, int Nx, int Ny, int Nz);

  //  void kappa2gamma(dblarray &kappa, dblarray &gamma1, dblarray &gamma2);
  void kappa2gamma(double *kappa,double *gamma1, double *gamma2,  int Nx, int Ny, int Nz);

  //  void kappa2flexion(double pixel_size, dblarray &kappa, dblarray &F1, dblarray &F2);
  void kappa2flexion(double pixel_size, double *kappa,double *F1, double *F2,  int Nx, int Ny, int Nz);

  //  void gamma_flexion2kappa(double pixel_size, dblarray &gamma1, dblarray &gamma2, dblarray &F1, dblarray &F2, dblarray &kappa);
  void gamma_flexion2kappa(double pixel_size, double sigma_g, double sigma_f, double* gamma1, double* gamma2, double* F1, double* F2, double* kappa, int Nx, int Ny, int Nz);

private:

  int NpixFFT;
  double fftFactor;
  fftw_complex* fftFrame1;
  fftw_complex* fftFrame2;
  fftw_complex* fftFrame3;
  fftw_complex* fftFrame4;
  fftw_plan plan_forward1, plan_backward1,plan_forward2, plan_backward2,plan_forward3,plan_forward4;

}; /* End of ShearInversions class */

} /* namespace Tools */

#endif
