#ifndef PICSAR_MULTIPHYSICS_PHYS_CONSTANTS
#define PICSAR_MULTIPHYSICS_PHYS_CONSTANTS

//Should be included by all the src files of the library
#include "picsar_qed/qed_commons.h"

//Uses some mathematical constants
#include "picsar_qed/math/math_constants.h"

namespace picsar{
namespace multi_physics{
namespace phys{

    // Some useful physical constants in SI units
    template<typename RealType = double>
    constexpr auto electron_mass = RealType(9.1093837015e-31);

    template<typename RealType = double>
    constexpr auto elementary_charge = RealType(1.602176634e-19);

    template<typename RealType = double>
    constexpr auto light_speed = RealType(299792458.);

    template<typename RealType = double>
    constexpr auto reduced_plank = RealType(1.054571817e-34);

    template<typename RealType = double>
    constexpr auto vacuum_permittivity = RealType(8.8541878128e-12);

    template<typename RealType = double>
    constexpr auto vacuum_permeability = RealType(1.25663706212e-6);

    template<typename RealType = double>
    constexpr auto fine_structure =  RealType(0.0072973525693);

    template<typename RealType = double>
    constexpr auto eV = RealType(1.602176634e-19);

    template<typename RealType = double>
    constexpr auto KeV = RealType(1.602176634e-16);

    template<typename RealType = double>
    constexpr auto MeV = RealType(1.602176634e-13);

    template<typename RealType = double>
    constexpr auto GeV = RealType(1.602176634e-10);

    //This constant is used for the Heaviside Lorentz unit system
    //(unfortunately, sqrt is not constexpr)
    template<typename RealType = double>
    constexpr auto sqrt_4_pi_fine_structure =
        RealType(0.302822120872089);

    //Intermediate calculations of the following quantities are performed with
    //double precision to avoid numerical issues
    template<typename RealType = double>
    constexpr auto classical_electron_radius = RealType(
        elementary_charge<>*elementary_charge<> /
        (4.0*math::pi<> * vacuum_permittivity<> *
        electron_mass<> * light_speed<> * light_speed<>));

    template<typename RealType = double>
    constexpr auto schwinger_field = RealType(
        electron_mass<>*electron_mass<>*(light_speed<>*light_speed<>*light_speed<>)/
        (elementary_charge<>*reduced_plank<>));

    template<typename RealType = double>
    constexpr auto tau_e = RealType(classical_electron_radius<>/light_speed<>);
    //_______________________________________________________________________
}
}
}

#endif //PICSAR_MULTIPHYSICS_MATH_CONSTANTS
