#pragma once
#include <cmath>
#include <vector>

namespace ships::rules::csr
{
  class CSR_SHIP
  {
  public:
    CSR_SHIP();
    CSR_SHIP(CSR_SHIP &&) = default;
    CSR_SHIP(const CSR_SHIP &) = default;
    CSR_SHIP &operator=(CSR_SHIP &&) = default;
    CSR_SHIP &operator=(const CSR_SHIP &) = default;
    ~CSR_SHIP();

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
  private:
    double _L_RULE;
    double _B;        //m
    double _T_SC;     //m
    double _T_LC;     //m
    double _D;        //m
    double _V;       //knots
    double _CB;     //[-]
    double _GM;      //m
    double _Kr;      //m
    bool _BilgeKeel;
    service_restriction _restriction;
    design_load_scenario _load_scenario;
    analysis_type _analysis_type;

    const double _grav = 9.81; //mm/s2
    const double _PI = 3.14159265358979323846;


    double a0();
    double rot_centre();
    double fT();
    double roll_period();
    double roll_angle();
  };




  CSR_SHIP::CSR_SHIP()
  {
  }

  CSR_SHIP::~CSR_SHIP()
  {
  }



  class CSR_ACC : CSR_SHIP_DATA
  {
  public:
    CSR_ACC();
    CSR_ACC(CSR_ACC &&) = default;
    CSR_ACC(const CSR_ACC &) = default;
    CSR_ACC &operator=(CSR_ACC &&) = default;
    CSR_ACC &operator=(const CSR_ACC &) = default;
    ~CSR_ACC();

  private:
  };

  CSR_ACC::CSR_ACC()
  {
  }

  CSR_ACC::~CSR_ACC()
  {
  }




  //Acceleration parameter
} // namespace ships::rules::csr:accelerations
