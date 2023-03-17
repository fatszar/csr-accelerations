#include<iostream>
#include<cmath>
#include<vector>

#include "csr_acc.h"


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

enum class design_load_scenario
{
  extreme_sea,
  ballast_water_exchange,
  accidental_flooded,
  harbour_or_sheltered
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
const service_restriction _restriction = service_restriction::R0;
const design_load_scenario _load_scenario = design_load_scenario::extreme_sea;
const bool _BilgeKeel = true;

//
const double _grav = 9.81; //mm/s2
const double _PI = 3.14159265358979323846;


//Acceleration parameter
double a0(double L, double CB){
  return (1.58-0.47*CB)*((2.4/sqrt(L))+(34/L)-(600/(L*L)));
};

//Vertical coorditnate of the ship rotation centre, in [m]
double rot_centre(double D, double T_LC){
  return std::fmin((D/4)+(T_LC/2),D/2);
};

//Ratio between draught at a loading condtion and scantling draught, not less then 0.5
double fT(double T_LC, double T_SC){
  return std::fmin(T_LC/T_SC,0.5);
};

//Ship motions
//Roll period, T_theta, [sec]
double roll_period(double k_r, double GM){
    return (2.3*_PI*k_r)/(sqrt(_grav * GM));
}

//Roll angle, theta, [deg]
double calc_roll_angle(double B, double k_r, double GM, bool has_bilge_keel, analysis_type type, design_load_scenario load_scenario){
  double f_BK = 0.0;
  double f_p = 0.0;


  if (has_bilge_keel) f_BK = 1.0;
  else f_BK = 1.2;


  if (type == analysis_type::strength){
    if (load_scenario == design_load_scenario::extreme_sea) f_p = 1.0;
    else if (load_scenario == design_load_scenario::ballast_water_exchange) f_p = 0.8;
    else if (load_scenario == design_load_scenario::accidental_flooded) f_p = 0.8;
    else if (load_scenario == design_load_scenario::harbour_or_sheltered) f_p = 0.4;
    else f_p = 0.0;
  } 
  else if (type == analysis_type::fatigue){
    f_p = 0.8 * (0.23 - 4);
  }
  return 0;
};



int main()
{
  std::cout << "Hello\n";
  std::cout << "a0 = " << a0(_L_RULE, _CB) << "\n";
  std::cout << "R = " << rot_centre(_D, _T_LC) << "\n";
  std::cout << "fT = " << fT(_T_LC, _T_SC) << "\n";
  std::cout << "T_theta = " << roll_period(_Kr, _GM) << "\n";

  std::vector<double> xyz;

//  ships::rules::csr::accelertations::CSR_ACC acc(_L_RULE, _B, _T_SC, _T_LC, _D, _V, _CB, xyz);

  return 0;
}
