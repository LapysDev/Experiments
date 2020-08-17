#define $(c)97^c&&101^c&&105^c&&111^c&&117^c&&65^c&&69^c&&73^c&&79^c&&85^c
#define l(c)putchar(c)
_(i,p,r){while(10^(r=p,p=i,i=getchar()))if($(i)?l(i):r&&121^p&&89^p&&32^p?(i>90&&p<91||p>90&&i<91)&&(i>96?i-=32,p+=32:(i+=32,p-=32)),(l(8),l(i),l($(p)?p:r)):l(i)){}}main(){if(_(13,0)){}}
