#include "csr.h"
namespace ships::rules::csr::accelerations
{
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
  double roll_angle(double B, double k_r, double GM, bool has_bilge_keel, analysis_type type, design_load_scenario load_scenario){
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

    double roll_period = (2.3*_PI*k_r)/(sqrt(_grav * GM)); //k_r [s]
    return  9000*(1.25 - 0.025*roll_period)*f_p*f_BK/((B+75)*_PI);
  };
} // namespace ships::rules::csr:accelerations
