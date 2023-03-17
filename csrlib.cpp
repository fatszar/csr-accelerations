#include "csrlib.h"

using namespace SHIP::RULES::CSR;

CSR_SHIP::CSR_SHIP(double L_RULE, double B, double T_SC, double T_LC, double D, double V, 
                   double CB, double GM, double Kr, bool BilgeKeel, design_load_scenario scenario, 
                   analysis_type analysis_type, service_restriction restriction, vesel_type vesel){
    _L_RULE = L_RULE;
    _B = B;
    _T_SC = T_SC;
    _T_LC = T_LC;
    _D = D;
    _V = V;
    _CB = CB;
    _GM = GM;
    _Kr = Kr;
    _BilgeKeel = BilgeKeel;
    _restriction = restriction;
    _analysis_type = analysis_type;
    _load_scenario = scenario;
    _vesel_type = vesel;

    _fT =  std::fmin(_T_LC/_T_SC,0.5);
    _a0 =  (1.58-0.47*_CB)*((2.4/sqrt(_L_RULE))+(34/_L_RULE)-(600/(_L_RULE*_L_RULE)));
    _RotCentre = std::fmin((_D/4)+(_T_LC/2),_D/2);
    _rollPeriod =  (2.3*_PI*_Kr)/(sqrt(_grav * _GM));

    if (_BilgeKeel) _f_BK = 1.0;
    else _f_BK = 1.2;

    if (_analysis_type == analysis_type::strength){
        if (_load_scenario == design_load_scenario::extreme_sea) _f_p = 1.0;
        else if (_load_scenario == design_load_scenario::ballast_water_exchange) _f_p = 0.8;
        else if (_load_scenario == design_load_scenario::accidental_flooded) _f_p = 0.8;
        else if (_load_scenario == design_load_scenario::harbour_or_sheltered) _f_p = 0.4;
        else _f_p = 0.0;
    }
    else if (_analysis_type == analysis_type::fatigue){
      _f_p = 0.8 * (0.23 - 4);
    }
    _rollAngle =   9000*(1.25 - 0.025*_rollPeriod)*_f_p*_f_BK/((_B+75)*_PI);
}

    CSR_SHIP::~CSR_SHIP()
    {
    }

    void CSR_SHIP::print(){
        std::cout <<"Data from  class\n";
        std::cout << "a0 = " << _a0 << "\n";
        std::cout << "R = " << _RotCentre << "\n";
        std::cout << "fT = " << _fT << "\n";
        std::cout << "T_theta = " << _rollPeriod << "\n";
        std::cout << "Theta = " << _rollAngle << "\n";
    }
