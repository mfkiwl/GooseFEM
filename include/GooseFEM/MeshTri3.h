/**
Generate simple meshes of 3-noded triangular elements in 2d (GooseFEM::Mesh::ElementType::Tri3).

\file MeshTri3.h
\copyright Copyright 2017. Tom de Geus. All rights reserved.
\license This project is released under the GNU Public License (GPLv3).
*/

#ifndef GOOSEFEM_MESHTRI3_H
#define GOOSEFEM_MESHTRI3_H

#include "config.h"
#include "Mesh.h"

namespace GooseFEM {
namespace Mesh {

/**
Simple meshes of triangular elements of type ElementType::Tri3.
*/
namespace Tri3 {

/**
Regular grid of squares, with each square cut into two triangular elements.
*/
class Regular : public RegularBase2d {
public:

    /**
    Constructor.

    \param nelx Number of elements in x-direction.
    \param nely Number of elements in y-direction.
    \param h Edge-size (of the squares, and thus of two of three element-edges).
    */
    Regular(size_t nelx, size_t nely, double h = 1.);

    ElementType getElementType() const override;
    xt::xtensor<double, 2> coor() const override;
    xt::xtensor<size_t, 2> conn() const override;
    xt::xtensor<size_t, 1> nodesBottomEdge() const override;
    xt::xtensor<size_t, 1> nodesTopEdge() const override;
    xt::xtensor<size_t, 1> nodesLeftEdge() const override;
    xt::xtensor<size_t, 1> nodesRightEdge() const override;
    xt::xtensor<size_t, 1> nodesBottomOpenEdge() const override;
    xt::xtensor<size_t, 1> nodesTopOpenEdge() const override;
    xt::xtensor<size_t, 1> nodesLeftOpenEdge() const override;
    xt::xtensor<size_t, 1> nodesRightOpenEdge() const override;
    size_t nodesBottomLeftCorner() const override;
    size_t nodesBottomRightCorner() const override;
    size_t nodesTopLeftCorner() const override;
    size_t nodesTopRightCorner() const override;
};

// read / set the orientation (-1/+1) of all triangles
inline xt::xtensor<int, 1> getOrientation(
    const xt::xtensor<double, 2>& coor, const xt::xtensor<size_t, 2>& conn);

inline xt::xtensor<size_t, 2> setOrientation(
    const xt::xtensor<double, 2>& coor, const xt::xtensor<size_t, 2>& conn, int orientation = -1);

inline xt::xtensor<size_t, 2> setOrientation(
    const xt::xtensor<double, 2>& coor,
    const xt::xtensor<size_t, 2>& conn,
    const xt::xtensor<int, 1>& current, // (output of "getOrientation")
    int orientation = -1);

} // namespace Tri3
} // namespace Mesh
} // namespace GooseFEM

#include "MeshTri3.hpp"

#endif
