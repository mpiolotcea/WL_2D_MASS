;+
; NAME: CAT2MAP
;
;
; PURPOSE: to change a .cat file in a .fits file
;     Catalogue with gamma1 and gamma2 values
;
; CALLING: txt2fits, catsextxt=catsextxt, catsexfits
;
; INPUTS: 
;       Ncol --- number of columns in the catalogue
;       
; KEYWORDS:
;       cat  --- input catalogue
;       delta  ---   map pixel size [amin]
;       decl --- the declination in degrees
;	square ---  the input image is square and power of two
;	
; OUTPUT: 
;       mask --- mask of the data
;       g --- the shear structure
;       
; HISTORY:
;	Written: Sandrine Pires 2012.
;-
;-------------------------------------------------------------------------------
pro cat2map, i, delta = delta, mask, g, square=square
  ; i from 0 to 63.
  path = '../Millennium/'
  i0 = floor(i / 8.)
  i1 = floor(i - i0*8.)
  cat =  mrdfits(path+'ms_ia_lightcone_'+strtrim(i0, 1)+ '_' + strtrim(i1, 1) +'.fits', 1)
  n_lin = n_elements(cat)
  ra = cat.x_pos
  dec = cat.ypos
  gamma1 = cat.shear_1
  gamma2 = cat.shear_2
  
  weight = dblarr(n_lin)
  weight(*) = 1

  gcat = {ra : ra, dec : dec, gamma1:gamma1, gamma2:gamma2, weight:weight}
  mk_gamma_my, gcat, g, delta = delta, /radec, weight = weight, square=square
  mask = g.mask

end
