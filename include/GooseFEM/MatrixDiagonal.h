/* =================================================================================================

(c - GPLv3) T.W.J. de Geus (Tom) | tom@geus.me | www.geus.me | github.com/tdegeus/GooseFEM

================================================================================================= */

#ifndef GOOSEFEM_MATRIXDIAGONAL_H
#define GOOSEFEM_MATRIXDIAGONAL_H

// -------------------------------------------------------------------------------------------------

#include "config.h"

// =================================================================================================

namespace GooseFEM {

// -------------------------------------------------------------------------------------------------

class MatrixDiagonal
{
public:

  // constructors

  MatrixDiagonal() = default;
  MatrixDiagonal(const xt::xtensor<size_t,2> &conn, const xt::xtensor<size_t,2> &dofs);

  // dimensions

  size_t nelem() const; // number of elements
  size_t nne()   const; // number of nodes per element
  size_t nnode() const; // number of nodes
  size_t ndim()  const; // number of dimensions
  size_t ndof()  const; // number of DOFs

  // DOF lists

  xt::xtensor<size_t,2> dofs() const; // DOFs

  // set matrix components

  void set(const xt::xtensor<double,1> &A);

  // assemble from matrices stored per element [nelem, nne*ndim, nne*ndim]
  // WARNING: ignores any off-diagonal terms

  void assemble(const xt::xtensor<double,3> &elemmat);

  // product: b_i = A_ij * x_j

  void dot(const xt::xtensor<double,2> &x,
    xt::xtensor<double,2> &b) const;

  void dot(const xt::xtensor<double,1> &x,
    xt::xtensor<double,1> &b) const;

  // solve: x = A \ b

  void solve(const xt::xtensor<double,2> &b,
    xt::xtensor<double,2> &x);

  void solve(const xt::xtensor<double,1> &b,
    xt::xtensor<double,1> &x);

  // return matrix as diagonal matrix (column)

  xt::xtensor<double,1> asDiagonal() const;

  // auto allocation of the functions above

  xt::xtensor<double,2> dot(const xt::xtensor<double,2> &x) const;

  xt::xtensor<double,1> dot(const xt::xtensor<double,1> &x) const;

  xt::xtensor<double,2> solve(const xt::xtensor<double,2> &b);

  xt::xtensor<double,1> solve(const xt::xtensor<double,1> &b);

private:

  // the diagonal matrix, and its inverse (re-used to solve different RHS)
  xt::xtensor<double,1> m_data;
  xt::xtensor<double,1> m_inv;

  // signal changes to data compare to the last inverse
  bool m_change=false;

  // bookkeeping
  xt::xtensor<size_t,2> m_conn; // connectivity         [nelem, nne ]
  xt::xtensor<size_t,2> m_dofs; // DOF-numbers per node [nnode, ndim]

  // dimensions
  size_t m_nelem; // number of elements
  size_t m_nne;   // number of nodes per element
  size_t m_nnode; // number of nodes
  size_t m_ndim;  // number of dimensions
  size_t m_ndof;  // number of DOFs

  // compute inverse (automatically evaluated by "solve")
  void factorize();
};

// -------------------------------------------------------------------------------------------------

} // namespace ...

// =================================================================================================

#include "MatrixDiagonal.hpp"

// =================================================================================================

#endif