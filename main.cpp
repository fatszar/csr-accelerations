#include<iostream>
#include "csr.h"

namespace csr = ships::rules::csr::accelerations;
const double _L_RULE = 175.15; //m
const double _B = 32.2;        //m
const double _T_SC = 13.3;     //m
const double _T_LC = 7.09;     //m
const double _D = 19.1;        //m
const double _V = 14.45;       //knots
const double _CB = 0.7883;     //[-]
const double _GM = 3.864;      //m
const double _Kr = 11.27;      //m
const bool _BilgeKeel = true;
const csr::service_restriction _restriction = csr::service_restriction::R0;
const csr::design_load_scenario _load_scenario = csr::design_load_scenario::extreme_sea;
const csr::analysis_type _analysis_type = csr::analysis_type::strength;

int main()
{
  std::cout << "*** Common Structural Rules ***\n";
  std::cout << "a0 = " << csr::a0(_L_RULE, _CB) << "\n";
  std::cout << "R = " << csr::rot_centre(_D, _T_LC) << "\n";
  std::cout << "fT = " << csr::fT(_T_LC, _T_SC) << "\n";
  std::cout << "T_theta = " << csr::roll_period(_Kr, _GM) << "\n";

  return 0;
}
