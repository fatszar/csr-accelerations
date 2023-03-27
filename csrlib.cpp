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

    _fT =  std::fmax(_T_LC/_T_SC,0.5);
    _a0 =  (1.58-0.47*_CB)*((2.4/sqrtf(_L_RULE))+(34/_L_RULE)-(600/(_L_RULE*_L_RULE)));
    _RotCentre = std::fmin((_D/4)+(_T_LC/2),_D/2);

    if (_load_scenario == design_load_scenario::extreme_sea) _f_ps = 1.0;
    else if (_load_scenario == design_load_scenario::ballast_water_exchange) _f_ps = 0.8;
    else if (_load_scenario == design_load_scenario::accidental_flooded) _f_ps = 0.8;
    else if (_load_scenario == design_load_scenario::harbour_or_sheltered) _f_ps = 0.4;
    else _f_ps = 0.0;

    _f_fa = 0.9; 

    roll_motion();  
    pitch_motion();
    surge_acceleration();
    sway_acceleration();
    heave_acceleration();
    roll_acceleration();
    pitch_acceleration();

}

    CSR_SHIP::~CSR_SHIP()
    {
    }

    void CSR_SHIP:: roll_motion(){
        double f_p = 0.0;
        double f_BK =0.0;
        if (_BilgeKeel) f_BK = 1.0;
        else f_BK = 1.2;

        if (_analysis_type == analysis_type::strength){
            f_p = _f_ps;
        }
        else if (_analysis_type == analysis_type::fatigue){
            f_p = _f_fa * (0.23 - 4*_fT*powf(_B,-4));
        }
        _rollPeriod =  (2.3*_PI*_Kr)/(sqrtf(_grav * _GM));
        _rollAngle =   9000*(1.25 - 0.025*_rollPeriod)*f_p*f_BK/((_B+75)*_PI);
    }

    void CSR_SHIP::pitch_motion(){
        double f_p = 0.0;

        if (_analysis_type == analysis_type::strength){
            f_p = _f_ps;
        }
        else if (_analysis_type == analysis_type::fatigue){
            f_p = _f_fa * (0.23 - 4*_fT*powf(_B,-4));
        }
        _pitchPeriod = sqrtf((2*_PI*(0.6*(1+_fT)*_L_RULE))/_grav);
        _pitchAngle = (1350*f_p*(powf(_L_RULE, -0.94)))*(1.0 + powf((2.57/(sqrtf(_grav*_L_RULE))), 1.2));
    }

    void CSR_SHIP::surge_acceleration(){
        double f_p = 0.0;

        if (_analysis_type == analysis_type::strength){
            f_p = _f_ps;
        }
        else if (_analysis_type == analysis_type::fatigue){
            f_p = _f_fa * (0.27 - (15 + 4*_fT)*(_L_RULE* 0.00001));
        }
       _acc_surge = 0.2 * f_p * _a0 * _grav; 
    }
    void CSR_SHIP::sway_acceleration(){
        double f_p = 0.0;

        if (_analysis_type == analysis_type::strength){
            f_p = _f_ps;
        }
        else if (_analysis_type == analysis_type::fatigue){
            f_p = _f_fa * (0.24 - (6 - 2*_fT)*(_B* 0.0001));
        }
        _acc_sway = 0.3 * f_p * _a0 * _grav;
    }
    void CSR_SHIP::heave_acceleration(){
        double f_p = 0.0;

        if (_analysis_type == analysis_type::strength){
            f_p = _f_ps;
        }
        else if (_analysis_type == analysis_type::fatigue){
            f_p = _f_fa * ((0.27 + 0.02*_fT)-(17.0 * _L_RULE* 0.00001));
        }
       _acc_heave = f_p * _a0 * _grav; 
    }
        
    void CSR_SHIP::roll_acceleration(){
        double f_p;
        double roll_period;
        double roll_angle;
        double f_BK;

        if (_analysis_type == analysis_type::strength){
            f_p = _f_ps;
        }
        else if (_analysis_type == analysis_type::fatigue){
            f_p = _f_fa * (0.23 - (4.0*_fT*_B* 0.0001));
        }

        if (_BilgeKeel) f_BK = 1.0;
        else f_BK = 1.2;

        roll_period =  (2.3*_PI*_Kr)/(sqrtf(_grav * _GM));
        roll_angle =   9000*(1.25 - 0.025*roll_period)*1.0*f_BK/((_B+75)*_PI); //roll angle using f_p = 1.0


        _acc_roll = f_p * roll_angle * (_PI/180) * pow((2*_PI/roll_period),2);
    }

    void CSR_SHIP::pitch_acceleration(){
        double f_p;
        double pitch_angle;
        double pitch_period;
        
        if (_analysis_type == analysis_type::strength){
            f_p = _f_ps;
        }
        else if (_analysis_type == analysis_type::fatigue){
            f_p = _f_fa * (0.28 - (5 + 4*_fT) * _L_RULE * 0.00001);
        }
        pitch_period = sqrtf((2*_PI*(0.6*(1+_fT)*_L_RULE))/_grav);
        //Pitch angle using f_p = 1.0
        pitch_angle = 1350*1.0*powf(_L_RULE, -0.94)*(1.0 + powf(2.57/(sqrtf(_grav*_L_RULE)),1.2));
        _acc_pitch = f_p * ((3.1/sqrtf(_grav * _L_RULE)) + 1.0) * pitch_angle * (_PI/180)* powf((2*_PI/pitch_period),2);
    }

    double CSR_SHIP::a_x_env(double z){
        return 0.7*sqrtf(std::pow(_acc_surge,2) + std::pow((_L_RULE/325)*(_grav*std::sin(_pitchAngle*_PI/180)+(_acc_pitch*(z- _RotCentre))),2));
    }

    double CSR_SHIP::a_y_env(double z){
        return sqrtf(std::pow(_acc_sway,2) + std::pow(_grav*std::sin(_rollAngle*_PI/180)+_acc_roll*(z- _RotCentre),2));
    }

    double CSR_SHIP::a_z_env(double x, double y){
        return sqrtf(std::pow(_acc_heave, 2) + std::pow((0.3 + (_L_RULE/325))*(_acc_pitch*(x - 0.45 * _L_RULE)), 2) + std::pow(1.2*_acc_roll * y, 2));
    }
    bool CSR_SHIP::GetEnvelopeAccelerations(double x, double y, double z, double out_ax_env, double out_ay_env, double out_az_env){
        out_ax_env = a_x_env(z);
        out_ax_env = a_y_env(z);
        out_ax_env = a_z_env(x,y);
        return true; // TODO: not checking anything but ther is a need to implement at least division by zero check!!!
    }

    double CSR_SHIP::a_x(double z, EDW edw){
        double C_XS;
        double C_XP;
        double C_XG;
        if (_analysis_type == analysis_type::strength){
            switch(edw)
            {
                case EDW::HSM_1:
                    C_XG = 0.6;
                    C_XS = 0.3-0.2*_fT;
                    C_XP = -0.7;

            }
        }
        else if (_analysis_type == analysis_type::fatigue){

        }
        else { return 0.0;}


    void CSR_SHIP::print(double x, double y, double z){
        std::cout <<"Data from  class\n";
        std::cout << "a0 = " << _a0 << "\n";
        std::cout << "R = " << _RotCentre << "\n";
        std::cout << "fT = " << _fT << "\n";
        std::cout << "T_theta = " << _rollPeriod << "\n";
        std::cout << "Theta = " << _rollAngle << "\n";
        std::cout << "T_phi = " << _pitchPeriod << "\n";
        std::cout << "Phi = " << _pitchAngle << "\n";
        std::cout << "acc_surge = " << _acc_surge << "\n";
        std::cout << "acc_sway = " << _acc_sway << "\n";
        std::cout << "acc_heave = " << _acc_heave << "\n";
        std::cout << "acc_roll = " << _acc_roll << "\n";
        std::cout << "acc_pitch = " << _acc_pitch << "\n";
        std::cout << "acc_pitch = " << _acc_pitch << "\n";
        std::cout << "a_x_env = " << a_x_env(z) << "\n";
        std::cout << "a_y_env = " << a_y_env(z) << "\n";
        std::cout << "a_z_env = " << a_z_env(x,y) << "\n";
    }
