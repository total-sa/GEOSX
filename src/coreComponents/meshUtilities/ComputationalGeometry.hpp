/*
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 * Copyright (c) 2019, Lawrence Livermore National Security, LLC.
 *
 * Produced at the Lawrence Livermore National Laboratory
 *
 * LLNL-CODE-746361
 *
 * All rights reserved. See COPYRIGHT for details.
 *
 * This file is part of the GEOSX Simulation Framework.
 *
 * GEOSX is a free software; you can redistribute it and/or modify it under
 * the terms of the GNU Lesser General Public License (as published by the
 * Free Software Foundation) version 2.1 dated February 1999.
 *~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
 */

/**
 * @file ComputationalGeometry.hpp
 */

#ifndef SRC_COMPONENTS_CORE_SRC_MESHUTILITIES_COMPUTATIONALGEOMETRY_HPP_
#define SRC_COMPONENTS_CORE_SRC_MESHUTILITIES_COMPUTATIONALGEOMETRY_HPP_

#include "common/DataTypes.hpp"

namespace geosx
{
namespace computationalGeometry
{

/**
 * Calculates the centroid of a convex 3D polygon as well as the normal
 * @param[in] pointIndices list of index references for the points array in
 * order (CW or CCW) about the polygon loop
 * @param [in] numPoints the number of points in the polygon
 * @param[in] points 3D point list
 * @param[out] center 3D center of the given ordered polygon point list
 * @param[out] normal Normal to the face
 * @return area of the convex 3D polygon
 */
real64 Centroid_3DPolygon( localIndex const * const pointsIndices,
                           localIndex const numPoints,
                           arrayView1d<R1Tensor const> const & points,
                           R1Tensor & center,
                           R1Tensor & normal,
                           real64 areaTolerance = 0.0 );

/**
 * @author settgast
 * Calculates the centroid of a convex 3D polygon as well as the normal
 * @param[in] pointIndices list of index references for the points array in
 * order (CW or CCW) about the polygon loop
 * @param[in] points 3D point list
 * @param[out] center 3D center of the given ordered polygon point list
 * @param[out] normal Normal to the face
 * @return area of the convex 3D polygon
 */
real64 Centroid_3DPolygon( arrayView1d<localIndex const> const & pointsIndices,
                           arrayView1d<R1Tensor const> const & points,
                           R1Tensor & center,
                           R1Tensor & normal,
                           real64 areaTolerance = 0.0 );

/**
 * Calculates the centroid of a convex 3D polygon as well as the normal
 * @param[in] pointIndices list of index references for the points array in
 * order (CW or CCW) about the polygon loop
 * @param[in] numPoints the numberof points in the polygon
 * @param[in] pointReferences 3D reference point list
 * @param[in] pointDisplacements 3D displacement list
 * @param[out] center 3D center of the given ordered polygon point list
 * @param[out] normal Normal to the face
 * @return area of the convex 3D polygon
 */
real64 Centroid_3DPolygon( localIndex const * const pointsIndices,
                           localIndex const numPoints,
                           arrayView1d<R1Tensor const> const & pointReferences,
                           arrayView1d<R1Tensor const> const & pointDisplacements,
                           R1Tensor & center,
                           R1Tensor & normal );

/**
 * @author settgast
 * Calculates the centroid of a convex 3D polygon as well as the normal
 * @param[in] pointIndices list of index references for the points array in
 * order (CW or CCW) about the polygon loop
 * @param[in] pointReferences 3D reference point list
 * @param[in] pointDisplacements 3D displacement list
 * @param[out] center 3D center of the given ordered polygon point list
 * @param[out] normal Normal to the face
 * @return area of the convex 3D polygon
 */
real64 Centroid_3DPolygon( arrayView1d<localIndex const> const & pointsIndices,
                           arrayView1d<R1Tensor const> const & pointReferences,
                           arrayView1d<R1Tensor const> const & pointDisplacements,
                           R1Tensor & center,
                           R1Tensor & normal );

/**
 * @brief Check if a point is inside a convex polyhedron (3D polygon)
 * @param[in] nodeCoordinates a global array of nodal coordinates
 * @param[in] faceNodeIndicies ordered lists of node indices for each face of the polyhedron
 * @param[in] point coordinates of the query point
 * @param[in] areaTolerance same as in Centroid_3DPolygon
 * @return whether the point is inside
 *
 * @note Face nodes must all be ordered the same way (i.e. CW or CCW),
 * resulting in all face normals pointing either outside or inside the polyhendron
 *
 * @note For faces with n>3 nodes that are non-planar, average normal is used
 */
bool IsPointInsidePolyhedron( arrayView1d<R1Tensor const> const & nodeCoordinates,
                              array1d<array1d<localIndex>> const & faceNodeIndicies,
                              R1Tensor const & point,
                              real64 const areaTolerance = 0.0 );

real64 HexVolume( R1Tensor const * const points );

real64 TetVolume( R1Tensor const * const points );

real64 WedgeVolume( R1Tensor const * const points );

real64 PyramidVolume( R1Tensor const * const points );

inline void VectorDifference( array1d< R1Tensor > const & X,
                              localIndex const index0,
                              localIndex const index1,
                              R1Tensor & vec )
{
  vec = X[index1];
  vec -= X[index0];
}

template< int N >
inline void VectorMean( array1d< R1Tensor > const & X,
                        arrayView1d<localIndex> const indices,
                        R1Tensor & vec )
{
  vec = 0;
  for( int a=0 ; a<N ; ++a )
  {
    vec += X[indices[a]];
  }
  vec /= N;
}

}
} /* namespace geosx */

#endif /* SRC_COMPONENTS_CORE_SRC_MESHUTILITIES_COMPUTATIONALGEOMETRY_HPP_ */
