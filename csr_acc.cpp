#include<iostream>
#include<cmath>

enum class service_restriction
{
  R0 = 0,
  R1 = 1,
  R2 = 2,
  R3 = 3,
  R4 = 4,
  RE = 5,
};

enum class analysis_type
{
  strength,
  fatigue
};

const double _L_RULE = 175.15; //m
const double _B = 32.2;        //m
const double _T_SC = 13.3;     //m
const double _T_LC = 7.09;     //m
const double _D = 19.1;        //m
const double _V = 14.45;       //knots
const double _CB = 0.7883;     //[-]
const double _GM = 3.864;      //m
const double _Kr = 11.27;      //m
const service_restriction _Restriction = service_restriction::R0;
const bool _BilgeKeel = true;

//
const double _grav = 9.81; //mm/s2
const double _PI = 3.14159265358979323846;

//Acceleration parameter
double calc_a0(double L, double CB){
  return (1.58-0.47*CB)*((2.4/sqrt(L))+(34/L)-(600/(L*L)));
};

//Vertical coorditnate of the ship rotation centre, in [m]
double calc_rot_centre(double D, double T_LC){
  return std::fmin((D/4)+(T_LC/2),D/2);
};

//Ratio between draught at a loading condtion and scantling draught, not less then 0.5
double calc_fT(double T_LC, double T_SC){
  return std::fmin(T_LC/T_SC,0.5);
};



int main()
{
  std::cout << "Hello\n";
  std::cout << "a0 = " << calc_a0(_L_RULE, _CB) << "\n";
  std::cout << "R = " << calc_rot_centre(_D, _T_LC) << "\n";
  std::cout << "fT = " << calc_fT(_T_LC, _T_SC) << "\n";
  return 0;
}
