/*
 * ------------------------------------------------------------------------------------------------------------
 * SPDX-License-Identifier: LGPL-2.1-only
 *
 * Copyright (c) 2018-2020 Lawrence Livermore National Security LLC
 * Copyright (c) 2018-2020 The Board of Trustees of the Leland Stanford Junior University
 * Copyright (c) 2018-2020 TotalEnergies
 * Copyright (c) 2019-     GEOSX Contributors
 * All rights reserved
 *
 * See top level LICENSE, COPYRIGHT, CONTRIBUTORS, NOTICE, and ACKNOWLEDGEMENTS files for details.
 * ------------------------------------------------------------------------------------------------------------
 */

/**
 * @file ThermalConductivityExtrinsicData.hpp
 */

#ifndef GEOSX_CONSTITUTIVE_THERMALCONDUCTIVITY_THERMALCONDUCTIVITYEXTRINSICDATA_HPP_
#define GEOSX_CONSTITUTIVE_THERMALCONDUCTIVITY_THERMALCONDUCTIVITYEXTRINSICDATA_HPP_

#include "constitutive/relativePermeability/layouts.hpp"
#include "mesh/ExtrinsicMeshData.hpp"

namespace geosx
{

namespace extrinsicMeshData
{

namespace thermalconductivity
{

EXTRINSIC_MESH_DATA_TRAIT( effectiveConductivity,
                           "effectiveConductivity",
                           array3d< real64 >,
                           0,
                           LEVEL_0,
                           WRITE_AND_READ,
                           "Effective conductivity" );

EXTRINSIC_MESH_DATA_TRAIT( rockThermalConductivity,
                           "rockThermalConductivity",
                           array3d< real64 >,
                           0,
                           LEVEL_0,
                           WRITE_AND_READ,
                           "Rock thermal conductivity" );

}

}

}

#endif // GEOSX_CONSTITUTIVE_THERMALCONDUCTIVITY_THERMALCONDUCTIVITYEXTRINSICDATA_HPP_
