#pragma once
#include <cmath>
#include <vector>
namespace ships::rules::csr::accelerations
{

  const double _grav = 9.81; //mm/s2
  const double _PI = 3.14159265358979323846;

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


  //Acceleration parameter
  double a0(double L, double CB);
  double rot_centre(double D, double T_LC);
  double fT(double T_LC, double T_SC);
  double roll_period(double k_r, double GM);
  double calc_roll_angle(double B, double k_r, double GM, bool has_bilge_keel, analysis_type type, design_load_scenario load_scenario);
} // namespace ships::rules::csr:accelerations
