#include<iostream>
#include<string>
#include "csrlib.h"

// user input data e.g. from text file
const double _L_RULE = 175.15; //m
const double _B = 32.2;        //m
const double _T_SC = 13.3;     //m
const double _T_LC = 7.09;     //m
const double _D = 19.1;        //m
const double _V = 14.45;       //knots
const double _CB = 0.7883;     //[-]
const double _GM = 3.864;      //m
const double _Kr = 11.27;      //m
const bool _BilgeKeel = true;  // true, false
std::string _restriction = "R0";    //R0, R1, R2, R3, R4, RE
std::string _scenario = "extreme";  // extreme, ballast,  accidental, harbour
std::string _analysis = "strength"; //strength, fatigue
std::string _vessel = "tanker"; //tanker, bulk_carrier


//Helper functions for parsing input data from user
namespace csr = SHIP::RULES::CSR;

csr::CSR_SHIP::service_restriction parse_service_restriction(std::string r){ 
    if (r == "R0") return csr::CSR_SHIP::service_restriction::R0;
    else if (r == "R1") return csr::CSR_SHIP::service_restriction::R1;
    else if (r == "R2") return csr::CSR_SHIP::service_restriction::R2;
    else if (r == "R3") return csr::CSR_SHIP::service_restriction::R3;
    else if (r == "R4") return csr::CSR_SHIP::service_restriction::R4;
    else if (r == "RE") return csr::CSR_SHIP::service_restriction::RE;
    else return csr::CSR_SHIP::service_restriction::R0;
}

csr::CSR_SHIP::design_load_scenario parse_design_load_scenario(std::string s){

    if (s == "extreme") return csr::CSR_SHIP::design_load_scenario::extreme_sea;
    else if (s == "ballast") return csr::CSR_SHIP::design_load_scenario::ballast_water_exchange;
    else if (s == "accidental") return csr::CSR_SHIP::design_load_scenario::accidental_flooded;
    else if (s == "harbour") return csr::CSR_SHIP::design_load_scenario::harbour_or_sheltered;
    else return csr::CSR_SHIP::design_load_scenario::extreme_sea;
}

csr::CSR_SHIP::analysis_type parse_analysis_type(std::string a){
    if (a == "fatigue") return csr::CSR_SHIP::analysis_type::fatigue;
    else return csr::CSR_SHIP::analysis_type::strength;
}

csr::CSR_SHIP::vesel_type parse_vesel_type(std::string s){
    if (s == "tanker") return csr::CSR_SHIP::vesel_type::tanker;
    else return csr::CSR_SHIP::vesel_type::bulk_carrier;
}

int main()
{
    // const csr::service_restriction _restriction = csr::service_restriction::R0;
    // const csr::design_load_scenario _load_scenario = csr::design_load_scenario::extreme_sea;
    // const csr::analysis_type _analysis_type = csr::analysis_type::strength;

    std::cout << "*** Common Structural Rules ***\n";
    csr::CSR_SHIP ship( _L_RULE,  _B,  _T_SC, _T_LC,  _D,  _V,  _CB,  _GM,  _Kr, _BilgeKeel,
                  parse_design_load_scenario(_scenario), parse_analysis_type(_analysis), 
                  parse_service_restriction(_restriction), parse_vesel_type(_vessel));
   ship.print(); 

  return 0;
}
