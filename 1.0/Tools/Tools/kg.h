/**
 * @file Tools/kg.h
 * @date 12/18/15
 * @author user
 */

#ifndef _TOOLS_KG_H
#define _TOOLS_KG_H

#include <fftw3.h>

namespace Tools {

/**
 * @class kg
 * @brief
 *
 */
class kg
{

public:

  /**
   * @brief Destructor
   */
  virtual ~kg() = default;

  /**
   *
   * @param real
   * @param complex
   * @param Nx
   * @param Ny
   */
  static void real2complex(float *real, fftw_complex *complex, int Nx, int Ny);

  /**
   *
   * @param complex
   * @param real
   * @param Nx
   * @param Ny
   */
  static void complex2real(fftw_complex *complex, float *real, int Nx, int Ny);

  /**
   *
   * @param real
   * @param imag
   * @param complex
   * @param Nx
   * @param Ny
   */
  static void realandimag2complex(float *real, float *imag, fftw_complex *complex, int Nx, int Ny);

  /**
   *
   * @param complex
   * @param real
   * @param imag
   * @param Nx
   * @param Ny
   */
  static void complex2realandimag(fftw_complex *complex, float *real, float *imag, int Nx, int Ny);

  /**
   *
   * @param complex
   * @param circumflex
   * @param Nx
   * @param Ny
   */
  static void fftw_forward(fftw_complex *complex, fftw_complex *circumflex, int Nx, int Ny);

  /**
   *
   * @param circumflex
   * @param complex
   * @param Nx
   * @param Ny
   */
  static void fftw_backward(fftw_complex *circumflex, fftw_complex *complex, int Nx, int Ny);

  /**
   *
   * @param gamma_real_circumflex
   * @param gamma_imag_circumflex
   * @param kappaE_circumflex
   * @param kappaB_circumflex
   * @param Nx
   * @param Ny
   */
  static void gammacircumflex2kappacircumflex(fftw_complex *gamma_real_circumflex, fftw_complex *gamma_imag_circumflex, fftw_complex *kappaE_circumflex, fftw_complex *kappaB_circumflex, int Nx, int Ny);

  /**
   *
   * @param kappaE_circumflex
   * @param kappaB_circumflex
   * @param gamma_real_circumflex
   * @param gamma_imag_circumflex
   * @param Nx
   * @param Ny
   */
  static void kappacircumflex2gammacircumflex(fftw_complex *kappaE_circumflex, fftw_complex *kappaB_circumflex, fftw_complex *gamma_real_circumflex, fftw_complex *gamma_imag_circumflex, int Nx, int Ny);

  /**
   *
   * @param gamma_real
   * @param gamma_imag
   * @param kappaE
   * @param kappaB
   * @param Nx
   * @param Ny
   */
  static void gamma2kappa(float *gamma_real, float *gamma_imag, float *kappaE, float *kappaB, int Nx, int Ny);

  /**
   *
   * @param kappaE
   * @param kappaB
   * @param gamma_real
   * @param gamma_imag
   * @param Nx
   * @param Ny
   */
  static void kappa2gamma(float *kappaE, float *kappaB, float *gamma_real, float *gamma_imag, int Nx, int Ny);


private:

}; /* End of kg class */

} /* namespace Tools */

#endif
