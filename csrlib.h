#ifndef CSRLIB_H
#define CSRLIB_H

#include <cmath>
#include <iostream>
#include <unordered_map>

namespace SHIP::RULES::CSR {
class CSR_SHIP {
public:
  enum class EDW {
    HSM_1,
    HSM_2,
    HSA_1,
    HSA_2,
    FSM_1,
    FSM_2,
    BSR_1P,
    BSR_2P,
    BSR_1S,
    BSR_2S,
    BSP_1P,
    BSP_2P,
    BSP_1S,
    BSP_2S,
    OST_1P,
    OST_2P,
    OST_1S,
    OST_2S,
    OSA_1P,
    OSA_2P,
    OSA_1S,
    OSA_2S
  };

  enum class service_restriction {
    R0 = 0,
    R1 = 1,
    R2 = 2,
    R3 = 3,
    R4 = 4,
    RE = 5
  };

  enum class analysis_type { strength, fatigue };

  enum class design_load_scenario {
    extreme_sea,
    ballast_water_exchange,
    accidental_flooded,
    harbour_or_sheltered
  };

  enum class vesel_type { bulk_carrier, tanker };
  CSR_SHIP(double L_RULE, double B, double T_SC, double T_LC, double D,
           double V, double CB, double GM, double Kr, bool BilgeKeel,
           design_load_scenario scenario, analysis_type analysis_type,
           service_restriction restriction, vesel_type vesel);
  // CSR_SHIP(CSR_SHIP &&) = default;
  // CSR_SHIP(const CSR_SHIP &) = default;
  // CSR_SHIP &operator=(CSR_SHIP &&) = default;
  // CSR_SHIP &operator=(const CSR_SHIP &) = default;
  ~CSR_SHIP();
  void print(double x, double y, double z);
  double a_x_env(double z);
  double a_y_env(double z);
  double a_z_env(double x, double y);
  bool GetEnvelopeAccelerations(double x, double y, double z, double out_ax_env,
                                double out_ay_env, double out_az_env);
  double a_x(double z, EDW edw);
  double a_y(double z);
  double a_z(double x, double y);

private:
  double _L_RULE;
  double _B;    // m
  double _T_SC; // m
  double _T_LC; // m
  double _D;    // m
  double _V;    // knots
  double _CB;   //[-]
  double _GM;   // m
  double _Kr;   // m
  bool _BilgeKeel;
  service_restriction _restriction;
  design_load_scenario _load_scenario;
  analysis_type _analysis_type;
  vesel_type _vesel_type;

  // calculated values base on  input data
  double
      _fT; // ratio between draught at a loading condition and scantling draught
  double _f_ps; // coefficient for strength assessment depandant  on design load
                // scenario
  double _f_fa; // fatigue coefficient , constant = 0.9
  double _a0;   // accelreation parameter
  double _RotCentre;   // vertical coordinate, in m, of the ship rotation centre
  double _rollPeriod;  // T_theta [s]
  double _rollAngle;   // Theta, [deg]
  double _pitchPeriod; // T_phi [s]
  double _pitchAngle;  // phi [deg]
  double _acc_surge;   // longitudinal acceleration due to surge, m/s2
  double _acc_sway;    // longitudinal acceleration due to surge, m/s2
  double _acc_heave;   // longitudinal acceleration due to surge, m/s2
  double _acc_roll;    // roll acceleration in rad/s2
  double _acc_pitch;   // pitch accemeration in rad/s2
  // constans
  const double _grav = 9.81; // mm/s2
  const double _PI = 3.14159265358979323846;

  void roll_motion();
  void pitch_motion();
  void surge_acceleration();
  void sway_acceleration();
  void heave_acceleration();
  void roll_acceleration();
  void pitch_acceleration();
};

} // namespace SHIP::RULES::CSR
#endif
