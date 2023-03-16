
#include "csr_acc.h"

namespace ships::rules::csr
{
    namespace accelertations
    {
        
        CSR_ACC::CSR_ACC(const double L, const double B, const double T_SC, const double T_LC,const double D,const double SPEED, const double CB, std::vector<double> coord)
        {
            _L_RULE = L;
            _f_T = std::fmin(T_LC/T_SC,0.5);
        }
        
        CSR_ACC::~CSR_ACC()
        {
        }
        
        
    } // namespace accelertations
    
    
} // namespace ships::rules::csr
