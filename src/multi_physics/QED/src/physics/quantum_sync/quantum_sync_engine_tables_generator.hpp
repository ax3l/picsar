#ifndef PICSAR_MULTIPHYSICS_QUANTUM_SYNC_ENGINE_TABLES_GENERATOR
#define PICSAR_MULTIPHYSICS_QUANTUM_SYNC_ENGINE_TABLES_GENERATOR

//Should be included by all the src files of the library
#include "../../qed_commons.h"

//Implements methods of BW lookup tables
#include "quantum_sync_engine_tables.hpp"
//Uses BW tabulated functions
#include "quantum_sync_engine_tabulated_functions.hpp"
//Uses progress bar
#include "../../math/cmath_overloads.hpp"
//Uses progress bar
#include "../../utils/progress_bar.hpp"

#include <omp.h>

#include <vector>
#include <chrono>
#include <iostream>
#include <type_traits>

namespace picsar{
namespace multi_physics{
namespace phys{
namespace quantum_sync{

    template<typename RealType, typename VectorType>
    PXRMP_INTERNAL_FORCE_INLINE_DECORATOR
    RealType dndt_lookup_table<RealType, VectorType>::
    aux_generate_double(RealType x)
    {
        return static_cast<RealType>(
            compute_G_function<double>(x));
    }

    template<typename RealType, typename VectorType>
    template<generation_policy Policy>
    void dndt_lookup_table<RealType, VectorType>::generate(
        const bool show_progress)
    {
        constexpr bool use_internal_double =
            (Policy == generation_policy::force_internal_double) &&
            !std::is_same<RealType,double>();

        auto t_start =  std::chrono::system_clock::now();

        const auto all_coords = get_all_coordinates();
        auto all_vals = std::vector<RealType>(all_coords.size());

        int count = 0;
        #pragma omp parallel for
        for (int i = 0; i < all_coords.size(); ++i){
            PXRMP_INTERNAL_CONSTEXPR_IF (use_internal_double){
                all_vals[i] = aux_generate_double(all_coords[i]);
            }
            else {
                all_vals[i] = compute_G_function(all_coords[i]);
            }

            #pragma omp critical
            {
                count++;
                utils::draw_progress(count,
                    all_vals.size(), "Quantum sync dN/dt", 1);
            }
        }
        set_all_vals(all_vals);

        auto t_end =  std::chrono::system_clock::now();
        utils::draw_progress(
            count, all_vals.size(), "Quantum sync dN/dt", 1, true);
        std::cout << " Done in " <<
            std::chrono::duration_cast<std::chrono::milliseconds>(
                t_end - t_start).count()/1000.0 << " seconds. \n" << std::endl;

        m_init_flag = true;
    }

    //__________________________________________________________

    template<typename RealType, typename VectorType>
    PXRMP_INTERNAL_FORCE_INLINE_DECORATOR
    std::vector<RealType>
    photon_emission_lookup_table_logchi_logfrac<RealType, VectorType>::
    aux_generate_double(const RealType x, const std::vector<RealType>& y)
    {
        auto dtemp = std::vector<double>(y.size());
        std::transform(y.begin(), y.end(), dtemp.begin(),
            [](RealType yy){ return static_cast<double>(yy); });
        const auto dres = compute_cumulative_prob<
            double, std::vector<double>>(x,dtemp);
        auto res = std::vector<RealType>(y.size());
        std::transform(dres.begin(), dres.end(), res.begin(),
            [](double rr){ return static_cast<RealType>(rr); });
        return res;
    }

    template<typename RealType, typename VectorType>
    template<generation_policy Policy>
    void photon_emission_lookup_table_logchi_logfrac<RealType, VectorType>::generate(
        const bool show_progress)
    {
        constexpr bool use_internal_double =
            (Policy == generation_policy::force_internal_double) &&
            !std::is_same<RealType,double>();

        auto t_start =  std::chrono::system_clock::now();

        const int chi_size = m_params.chi_part_how_many;
        const int frac_size = m_params.how_many_frac;

        const auto all_coords = get_all_coordinates();
        auto all_vals = std::vector<RealType>(all_coords.size());

        auto fracs = std::vector<RealType>(frac_size);
        for(int j = 0; j < frac_size; ++j){
            fracs[j] = all_coords[j][1];
        }

        int count = 0;
        #pragma omp parallel for
        for (int i = 0; i < chi_size; ++i){
            std::vector<RealType> temp;
            PXRMP_INTERNAL_CONSTEXPR_IF (use_internal_double){
                temp = aux_generate_double(
                    all_coords[i*frac_size][0],fracs);
            } else {
                temp = compute_cumulative_prob(
                    all_coords[i*frac_size][0],fracs);
            }

            std::copy(temp.begin(), temp.end(), all_vals.begin()+i*frac_size);

            #pragma omp critical
            {
                count++;
                utils::draw_progress(count, chi_size, "QS photon emission", 1);
            }
        }

        set_all_vals(all_vals);
        auto t_end =  std::chrono::system_clock::now();
        utils::draw_progress(
            count, chi_size, "QS photon emission", 1, true);
        std::cout << " Done in " <<
            std::chrono::duration_cast<std::chrono::milliseconds>(
                t_end - t_start).count()/1000.0 << " seconds. \n" << std::endl;

        m_init_flag = true;
    }
}
}
}
}

#endif // PICSAR_MULTIPHYSICS_QUANTUM_SYNC_ENGINE_TABLES_GENERATOR
