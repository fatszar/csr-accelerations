#include<iostream>

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

const double _L_rule = 175.15; //m
const double _B = 32.2;        //m
const double _T_sc = 13.3;     //m
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



int main()
{
  std::cout << "Hello\n"; 
  return 0;
}
