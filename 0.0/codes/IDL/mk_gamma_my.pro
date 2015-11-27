;+
; NAME: 
;       MK_GAMMA_MY
;
; PURPOSE: 
;      to make a pixelised map from shear catalog
;       
; CALLING:
;
;       mk_gamma_my, gcat, gamma, delta=delta
;
; INPUTS:
;       		gcat --- shear catalog
; 					delta --- map pixel size [amin]
;
; OUTPUTS:
;           gamma --- shear map structure
;
; HISTORY:
;
; 			Written by A.Refregier, Dec 2003
; 			Changed by S. PIRES, Jan 2005
;      
;-
;-------------------------------------------------------------------------------
pro mk_gamma_my,gcat,gamma,delta=delta,radec=radec, weight=weight, square=square

; declarations
gamma_max=2.                                  ; max gamma to include
n_g=n_elements(gcat.gamma1)
print,'n_g',n_g


if not keyword_set(delta) then delta=1.       ; map cell size [amin] 
delta1=delta/60.                                 ; map cell size [deg]
delta2=delta1
if not keyword_set(radec) then begin
    xran=[min(gcat.x),max(gcat.x)]*gcat.pixscale ; exact range [deg]
    yran=[min(gcat.y),max(gcat.y)]*gcat.pixscale
endif else begin
    xran=[min(gcat.ra),max(gcat.ra)] ; exact range [deg]
    yran=[min(gcat.dec),max(gcat.dec)]
 ;   xran=[min(gcat.dec),max(gcat.dec)] ; exact range [deg]
 ;   yran=[min(gcat.ra),max(gcat.ra)]
endelse

print,'xran',xran
print,'yran',yran

n_x=fix((xran(1)-xran(0))/delta1)+1
print, 'nb de pixels/x =',n_x
n_y=fix((yran(1)-yran(0))/delta2)+1
print, 'nb de pixels/y =',n_y
if keyword_set(square) then begin
  px = fix(alog(n_x)/alog(2.))
  n_x = 2^(px+1.)
  py = fix(alog(n_y)/alog(2.))
  n_y = 2^(py+1.)
endif

theta1=float(n_x)*delta1              
theta2=float(n_y)*delta2
x_ran=xran(0)+[0.,theta1]                   ; map range [deg]
y_ran=yran(0)+[0.,theta2]
x_l=x_ran(0)+findgen(n_x)*delta1            ; pixel limits (low, middle, high)
y_l=y_ran(0)+findgen(n_y)*delta2
x_h=x_l+delta1 & y_h=y_l+delta2
x_m=x_l+.5*delta1 & y_m=y_l+.5*delta2

; build map
gamma1=fltarr(n_x,n_y)
gamma2=fltarr(n_x,n_y)
gamma1_noise=fltarr(n_g)
gamma2_noise=fltarr(n_g)
wtot=fltarr(n_x,n_y)
w2tot=fltarr(n_x,n_y)
ng=intarr(n_x,n_y)
compt=0
print, 'nb total de galaxies =',n_g
compt = 0l
for i=0l,n_g-1 do begin
  if not keyword_set(radec) then begin
    if (gcat.gamma1(i)^2+gcat.gamma2(i)^2) le gamma_max^2 then begin
      compt=compt+1
      i_x=fix((gcat.x(i)*gcat.pixscale-x_ran(0))/delta1)
      i_y=fix((gcat.y(i)*gcat.pixscale-y_ran(0))/delta2)
      gamma1(i_x,i_y)=gamma1(i_x,i_y)+gcat.gamma1(i)*gcat.weight(i)
      gamma2(i_x,i_y)=gamma2(i_x,i_y)+gcat.gamma2(i)*gcat.weight(i)
      wtot(i_x,i_y)=wtot(i_x,i_y)+gcat.weight(i)
      w2tot(i_x,i_y)=w2tot(i_x,i_y)+gcat.weight(i)^2
      ng(i_x,i_y)=ng(i_x,i_y)+1
    endif
  endif else begin
    if (gcat.gamma1(i)^2+gcat.gamma2(i)^2) le gamma_max^2 then begin
      compt=compt+1
      i_x=fix((gcat.ra(i)-x_ran(0))/delta1)
      i_y=fix((gcat.dec(i)-y_ran(0))/delta2)
      ;i_x=fix((gcat.dec(i)-x_ran(0))/delta1)
      ;i_y=fix((gcat.ra(i)-y_ran(0))/delta2)
      gamma1(i_x,i_y)=gamma1(i_x,i_y)+gcat.gamma1(i)*gcat.weight(i)
      gamma2(i_x,i_y)=gamma2(i_x,i_y)+gcat.gamma2(i)*gcat.weight(i)
      wtot(i_x,i_y)=wtot(i_x,i_y)+gcat.weight(i)
      w2tot(i_x,i_y)=w2tot(i_x,i_y)+gcat.weight(i)^2
      ng(i_x,i_y)=ng(i_x,i_y)+1
    endif
  endelse
endfor

print,'nb total de galaxies après seuillage =',compt    
gd=where(wtot gt 0.)
gamma1(gd)=gamma1(gd)/wtot(gd)
gamma2(gd)=gamma2(gd)/wtot(gd)

for i=0l,n_g-1 do begin
  if not keyword_set(radec) then begin
    if (((gcat.gamma1(i)^2+gcat.gamma2(i)^2) le gamma_max^2)) then begin
      compt=compt+1
      i_x=fix((abs(gcat.x(i)*gcat.pixscale-xran(0))/delta1))
      i_y=fix((abs(gcat.y(i)*gcat.pixscale-yran(0))/delta2))
      gamma1_noise(i) = gcat.gamma1(i) - gamma1(i_x,i_y)
      gamma2_noise(i) = gcat.gamma2(i) - gamma2(i_x,i_y)
    endif 
  endif else begin
    if (((gcat.gamma1(i)^2+gcat.gamma2(i)^2) le gamma_max^2)) then begin
      compt=compt+1
      i_x=fix((abs(gcat.ra(i)-x_ran(0))/delta1))
      i_y=fix((abs(gcat.dec(i)-y_ran(0))/delta2))
      gamma1_noise(i) = gcat.gamma1(i) - gamma1(i_x,i_y)
      gamma2_noise(i) = gcat.gamma2(i) - gamma2(i_x,i_y)
    endif
  endelse
endfor

;compute noise variance
ind1 = where(abs(gamma1_noise) gt 0)
ind2 = where(abs(gamma2_noise) gt 0)
gd=where((gcat.gamma1^2+gcat.gamma2^2)le gamma_max^2)
;error in gamma1 per galaxy :
sigma_gamma1=sqrt(asigma(gamma1_noise(ind1))^2)
print, 'sigma_gamma1 =', sigma_gamma1
;error in gamma2 per galaxy :
sigma_gamma2=sqrt(asigma(gamma2_noise(ind2))^2)
print, 'sigma_gamma2 =', sigma_gamma2
;error in gamma per galaxy :
sigma_gamma=sqrt(asigma(gamma1_noise(ind1))^2+asigma(gamma2_noise(ind2))^2)
print, 'sigma_gamma =', sigma_gamma  
      
; construct mask and noise map
mask=intarr(n_x,n_y)
gd =where(ng ge 1)
mask(gd)=1


gamma_err=fltarr(n_x,n_y)
kappa_err=fltarr(n_x,n_y)
gd=where(ng gt 0.)
print, 'nb moyen de galaxies/pixel =', mean(ng(gd))

val=sigma_gamma/sqrt(mean(ng(gd)))
;print, 'rms moyen =', val
gamma_err=replicate(val,n_x,n_y)
gamma_err(gd)=sigma_gamma/sqrt(ng(gd))
kappa_err=gamma_err/sqrt(2.)

if keyword_set(weight) then begin  
gamma_err(gd)=sigma_gamma*sqrt(w2tot(gd))/wtot(gd)  
; rms error in gamma i.e. sqrt(2)*rms error in gamma1 or gamma2
ng_eff=fltarr(n_x,n_y)
ng_eff(gd)=wtot(gd)^2/w2tot(gd)  ; effective number of galaxies
print, 'nb moyen effectif de galaxies/pixel =', mean(ng_eff(gd))
; store in structure
gamma={n1:n_x,n2:n_y,delta1:delta1,delta2:delta2,$
       theta1:theta1,theta2:theta2,$
       gamma1:gamma1,gamma2:gamma2,$
       mask:mask,$
       ng:ng,wtot:wtot,gamma_err:gamma_err,$
       ng_eff:ng_eff,sigma_gamma:sigma_gamma,$
       x1_ran:x_ran,x2_ran:y_ran,$
       x1_l:x_l,x2_l:y_l,x1_m:x_m,x2_m:y_m,x1_h:x_h,x2_h:y_h}
endif

gamma={n1:n_x,n2:n_y,delta1:delta1,delta2:delta2,$
       theta1:theta1,theta2:theta2,$
       gamma1:gamma1,gamma2:gamma2,$
       mask:mask,$
       ng:ng,gamma_err:gamma_err,$
			 kappa_err:kappa_err,$
       sigma_gamma:sigma_gamma,$
       x1_ran:x_ran,x2_ran:y_ran,$
       x1_l:x_l,x2_l:y_l,x1_m:x_m,x2_m:y_m,x1_h:x_h,x2_h:y_h}

end
