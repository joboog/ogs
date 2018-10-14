/**
 * \file
 * \copyright
 * Copyright (c) 2012-2019, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#pragma once

#include "ParameterLib/Parameter.h"

#include <memory>
#include <utility>

#include <Eigen/Dense>

namespace MaterialLib
{
namespace Solids
{
template <int DisplacementDim>
struct MechanicsBase;
}
}  // namespace MaterialLib
namespace ProcessLib
{
namespace ThermoHydroMechanics
{
template <int DisplacementDim>
struct ThermoHydroMechanicsProcessData
{
    ThermoHydroMechanicsProcessData(
        MeshLib::PropertyVector<int> const* const material_ids_,
        std::map<int,
                 std::unique_ptr<
                     MaterialLib::Solids::MechanicsBase<DisplacementDim>>>&&
            solid_materials_,
        ParameterLib::Parameter<double> const& intrinsic_permeability_,
        ParameterLib::Parameter<double> const& specific_storage_,
        ParameterLib::Parameter<double> const& fluid_viscosity_,
        ParameterLib::Parameter<double> const& fluid_density_,
        ParameterLib::Parameter<double> const& biot_coefficient_,
        ParameterLib::Parameter<double> const& porosity_,
        ParameterLib::Parameter<double> const& solid_density_,
        ParameterLib::Parameter<double> const&
            solid_linear_thermal_expansion_coefficient_,
        ParameterLib::Parameter<double> const&
            fluid_volumetric_thermal_expansion_coefficient_,
        ParameterLib::Parameter<double> const& solid_specific_heat_capacity_,
        ParameterLib::Parameter<double> const& fluid_specific_heat_capacity_,
        ParameterLib::Parameter<double> const& solid_thermal_conductivity_,
        ParameterLib::Parameter<double> const& fluid_thermal_conductivity_,
        ParameterLib::Parameter<double> const& reference_temperature_,
        Eigen::Matrix<double, DisplacementDim, 1>
            specific_body_force_)
        : material_ids(material_ids_),
          solid_materials{std::move(solid_materials_)},
          intrinsic_permeability(intrinsic_permeability_),
          specific_storage(specific_storage_),
          fluid_viscosity(fluid_viscosity_),
          fluid_density(fluid_density_),
          biot_coefficient(biot_coefficient_),
          porosity(porosity_),
          solid_density(solid_density_),
          solid_linear_thermal_expansion_coefficient(
              solid_linear_thermal_expansion_coefficient_),
          fluid_volumetric_thermal_expansion_coefficient(
              fluid_volumetric_thermal_expansion_coefficient_),
          solid_specific_heat_capacity(solid_specific_heat_capacity_),
          solid_thermal_conductivity(solid_thermal_conductivity_),
          fluid_specific_heat_capacity(fluid_specific_heat_capacity_),
          fluid_thermal_conductivity(fluid_thermal_conductivity_),
          reference_temperature(reference_temperature_),
          specific_body_force(std::move(specific_body_force_))
    {
    }

    ThermoHydroMechanicsProcessData(ThermoHydroMechanicsProcessData&& other) =
        default;

    //! Copies are forbidden.
    ThermoHydroMechanicsProcessData(ThermoHydroMechanicsProcessData const&) =
        delete;

    //! Assignments are not needed.
    void operator=(ThermoHydroMechanicsProcessData const&) = delete;

    //! Assignments are not needed.
    void operator=(ThermoHydroMechanicsProcessData&&) = delete;

    MeshLib::PropertyVector<int> const* const material_ids;

    /// The constitutive relation for the mechanical part.
    /// \note Linear elasticity is the only supported one in the moment.
    std::map<
        int,
        std::unique_ptr<MaterialLib::Solids::MechanicsBase<DisplacementDim>>>
        solid_materials;
    /// Permeability of the solid. A scalar quantity,
    ///	ParameterLib::Parameter<double>.
    ParameterLib::Parameter<double> const& intrinsic_permeability;
    /// Volumetric average specific storage of the solid and fluid phases.
    /// A scalar quantity, ParameterLib::Parameter<double>.
    ParameterLib::Parameter<double> const& specific_storage;
    /// Fluid's viscosity. A scalar quantity, ParameterLib::Parameter<double>.
    ParameterLib::Parameter<double> const& fluid_viscosity;
    /// Fluid's density. A scalar quantity, ParameterLib::Parameter<double>.
    ParameterLib::Parameter<double> const& fluid_density;
    /// Biot coefficient. A scalar quantity, ParameterLib::Parameter<double>.
    ParameterLib::Parameter<double> const& biot_coefficient;
    /// Porosity of the solid. A scalar quantity,
    /// ParameterLib::Parameter<double>.
    ParameterLib::Parameter<double> const& porosity;
    /// Solid's density. A scalar quantity, ParameterLib::Parameter<double>.
    ParameterLib::Parameter<double> const& solid_density;
    ParameterLib::Parameter<double> const&
        solid_linear_thermal_expansion_coefficient;
    ParameterLib::Parameter<double> const&
        fluid_volumetric_thermal_expansion_coefficient;
    ParameterLib::Parameter<double> const& solid_specific_heat_capacity;
    ParameterLib::Parameter<double> const& solid_thermal_conductivity;
    ParameterLib::Parameter<double> const& fluid_specific_heat_capacity;
    ParameterLib::Parameter<double> const& fluid_thermal_conductivity;
    ParameterLib::Parameter<double> const& reference_temperature;
    /// Specific body forces applied to solid and fluid.
    /// It is usually used to apply gravitational forces.
    /// A vector of displacement dimension's length.
    Eigen::Matrix<double, DisplacementDim, 1> const specific_body_force;
    double dt = 0.0;
    double t = 0.0;

    MeshLib::PropertyVector<double>* pressure_interpolated = nullptr;
    MeshLib::PropertyVector<double>* temperature_interpolated = nullptr;

    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
};

}  // namespace ThermoHydroMechanics
}  // namespace ProcessLib
