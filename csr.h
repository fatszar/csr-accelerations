#pragma once
#include <cmath>
#include <vector>
namespace ships::rules::csr
{

  const double _grav = 9.81; //mm/s2
  const double _PI = 3.14159265358979323846;



  //Acceleration parameter
  double a0(double L, double CB);
  double rot_centre(double D, double T_LC);
  double fT(double T_LC, double T_SC);
  double roll_period(double k_r, double GM);
  double roll_angle(double B, double k_r, double GM, bool has_bilge_keel, analysis_type type, design_load_scenario load_scenario);
} // namespace ships::rules::csr:accelerations
