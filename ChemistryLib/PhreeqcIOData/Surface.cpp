/**
 * \copyright
 * Copyright (c) 2012-2019, OpenGeoSys Community (http://www.opengeosys.org)
 *            Distributed under a Modified BSD License.
 *              See accompanying file LICENSE.txt or
 *              http://www.opengeosys.org/project/license
 *
 */

#include <ostream>

#include "Surface.h"

namespace ChemistryLib
{
std::ostream& operator<<(std::ostream& os, SurfaceSite const& surface_site)
{
    os << surface_site.name.c_str() << " " << surface_site.site_density << " "
       << surface_site.specific_area << " " << surface_site.mass << "\n";

    return os;
}
}  // namespace ChemistryLib
