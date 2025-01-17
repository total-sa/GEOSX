/*
 * ------------------------------------------------------------------------------------------------------------
 * SPDX-License-Identifier: LGPL-2.1-only
 *
 * Copyright (c) 2018-2020 Lawrence Livermore National Security LLC
 * Copyright (c) 2018-2020 The Board of Trustees of the Leland Stanford Junior University
 * Copyright (c) 2018-2020 Total, S.A
 * Copyright (c) 2019-     GEOSX Contributors
 * All rights reserved
 *
 * See top level LICENSE, COPYRIGHT, CONTRIBUTORS, NOTICE, and ACKNOWLEDGEMENTS files for details.
 * ------------------------------------------------------------------------------------------------------------
 */

/**
 * @file ParMETISInterface.hpp
 */

#ifndef GEOSX_MESH_GENERATORS_PARMETISINTERFACE_HPP_
#define GEOSX_MESH_GENERATORS_PARMETISINTERFACE_HPP_

#include "common/DataTypes.hpp"
#include "common/MpiWrapper.hpp"

namespace geosx
{
namespace parmetis
{

/**
 * @brief Convert a element-node mesh map into a dual (element-element) graph
 * @param elemToNodes the input mesh represented by its elem-node map
 * @param elemDist the parallel distribution of elements: element index offset on each rank
 * @param comm the MPI communicator of processes to partition over
 * @param minCommonNodes minimum number of shared nodes to create an graph edge
 * @return a graph with an edge for every pair of elements that share at least @p minCommonNodes nodes;
 *         target element indices are global with respect to offsets in @p elemDist.
 * @note elemDist must be a comm-wide exclusive scan of elemToNodes.size();
 *       the user may compute it once and reuse in a subsequent call to partition().
 */
ArrayOfArrays< int64_t, int64_t >
meshToDual( ArrayOfArraysView< int64_t const, int64_t > const & elemToNodes,
            arrayView1d< int64_t const > const & elemDist,
            MPI_Comm comm,
            int const minCommonNodes );

/**
 * @brief Partition a mesh according to its dual graph.
 * @param graph the input graph (edges of locally owned nodes)
 * @param vertDist the parallel distribution of vertices: vertex index offset on each rank
 * @param numParts target number of partitions
 * @param comm the MPI communicator of processes to partition over
 * @param numRefinements number of partition refinement iterations
 * @return an array of target partitions for each element in local mesh
 */
array1d< int64_t >
partition( ArrayOfArraysView< int64_t const, int64_t > const & graph,
           arrayView1d< int64_t const > const & vertDist,
           int64_t const numParts,
           MPI_Comm comm,
           int const numRefinements );

} // namespace parmetis
} // namespace geosx

#endif //GEOSX_MESH_GENERATORS_PARMETISINTERFACE_HPP_
