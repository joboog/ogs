/**
 * \copyright
 * Copyright (c) 2012-2019, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#include "BaseLib/ConfigTree.h"
#include "UserPunch.h"
#include "MeshLib/Mesh.h"

namespace ChemistryLib
{
std::unique_ptr<UserPunch> createUserPunch(
    //std::size_t const& num_chemical_systems,
    MeshLib::Mesh const& mesh,
    boost::optional<BaseLib::ConfigTree> const& config)
{
    if (!config)
        return {};

    auto secondary_variable_names =
        config->getConfigParameter<std::vector<std::string>>("headline");

    std::vector<SecondaryVariable> secondary_variables;
    for (auto& variable_name : secondary_variable_names)
    {
        auto value = MeshLib::getOrCreateMeshProperty<double>(
            const_cast<MeshLib::Mesh&>(mesh),
            variable_name,
            MeshLib::MeshItemType::Node,
            1);
        std::fill(std::begin(*value), std::end(*value), 0);

        secondary_variables.emplace_back(std::move(variable_name),
                                         value);

    }
    //std::vector<std::vector<SecondaryVariable>> secondary_variables(
    //    num_chemical_systems, secondary_variables_per_chem_sys);


    std::vector<std::string> statements;
    auto const statements_config =
        //! \ogs_file_param{prj__chemical_system__user_punch__statements}
        config->getConfigSubtree("statements");
    for (
        auto const& statement :
        //! \ogs_file_param{prj__chemical_system__user_punch__statements__statement}
        statements_config.getConfigParameterList<std::string>("statement"))
        statements.push_back(statement);

    return std::make_unique<UserPunch>(std::move(secondary_variables),
                                       std::move(statements));
}
}  // namespace ChemistryLib
