/**
 * \file
 * \copyright
 * Copyright (c) 2012-2020, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 */

#include "CreatePorosityFromMassBalance.h"

#include "BaseLib/ConfigTree.h"
#include "ParameterLib/Utils.h"
#include "PorosityFromMassBalance.h"

namespace MaterialPropertyLib
{
std::unique_ptr<PorosityFromMassBalance> createPorosityFromMassBalance(
    BaseLib::ConfigTree const& config,
    std::vector<std::unique_ptr<ParameterLib::ParameterBase>> const& parameters)
{
    //! \ogs_file_param{properties__property__type}
    config.checkConfigParameter("type", "PorosityFromMassBalance");
    DBUG("Create PorosityFromMassBalance medium property");

    std::string const& parameter_name =
        //! \ogs_file_param{properties__property__PorosityFromMassBalance__initial_porosity}
        config.getConfigParameter<std::string>("initial_porosity");
    auto const& initial_porosity = ParameterLib::findParameter<double>(
        parameter_name, parameters, 0, nullptr);

    return std::make_unique<PorosityFromMassBalance>(initial_porosity);
}
}  // namespace MaterialPropertyLib
