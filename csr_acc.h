#pragma once
#include <cmath>
#include <vector>
namespace ships::rules::csr
{

    namespace accelertations
    {
        class CSR_ACC
        {
        private:
            double _L_RULE;     //m
            double _B;          //m
            double _T_SC;       //m
            double _T_LC;       //m
            double _D;          //m
            double _V;          //knots
            double _CB;         //[-]
            double _f_T;
            double _f_p;
            double _f_fa;

const double _grav = 9.81; //mm/s2
const double _PI = 3.14159265358979323846;
        public:
            CSR_ACC(const double L, const double B, const double T_SC, const double T_LC,const double D,const double SPEED, const double CB, std::vector<double> coord);
            ~CSR_ACC();
        };
               
        
    } // namespace accelertations
    
    
} // namespace ships::rules::csr
