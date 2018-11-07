/* =================================================================================================

(c - GPLv3) T.W.J. de Geus (Tom) | tom@geus.me | www.geus.me | github.com/tdegeus/GooseFEM

================================================================================================= */

#ifndef XGOOSEFEM_MATRIXDIAGONAL_CPP
#define XGOOSEFEM_MATRIXDIAGONAL_CPP

// -------------------------------------------------------------------------------------------------

#include "MatrixDiagonal.h"

// =================================================================================================

namespace xGooseFEM {

// -------------------------------------------------------------------------------------------------

inline MatrixDiagonal::MatrixDiagonal(const xt::xtensor<size_t,2> &conn,
  const xt::xtensor<size_t,2> &dofs) : m_conn(conn), m_dofs(dofs)
{
  // mesh dimensions
  m_nelem = m_conn.shape()[0];
  m_nne   = m_conn.shape()[1];
  m_nnode = m_dofs.shape()[0];
  m_ndim  = m_dofs.shape()[1];

  // dimensions of the system
  m_ndof  = xt::amax(m_dofs)[0] + 1;

  // allocate matrix and its inverse
  m_data  = xt::empty<double>({m_ndof});
  m_inv   = xt::empty<double>({m_ndof});

  // check consistency
  assert( xt::amax(m_conn)[0] + 1 == m_nnode          );
  assert( m_ndof                  <= m_nnode * m_ndim );
}

// -------------------------------------------------------------------------------------------------

inline size_t MatrixDiagonal::nelem() const
{
  return m_nelem;
}

// -------------------------------------------------------------------------------------------------

inline size_t MatrixDiagonal::nne() const
{
  return m_nne;
}

// -------------------------------------------------------------------------------------------------

inline size_t MatrixDiagonal::nnode() const
{
  return m_nnode;
}

// -------------------------------------------------------------------------------------------------

inline size_t MatrixDiagonal::ndim() const
{
  return m_ndim;
}

// -------------------------------------------------------------------------------------------------

inline size_t MatrixDiagonal::ndof() const
{
  return m_ndof;
}

// -------------------------------------------------------------------------------------------------

inline xt::xtensor<size_t,2> MatrixDiagonal::dofs() const
{
  return m_dofs;
}

// -------------------------------------------------------------------------------------------------

inline xt::xtensor<double,1> MatrixDiagonal::dot(const xt::xtensor<double,1> &x) const
{
  // check input
  assert( x.size() == m_ndof );

  // compute product
  return m_data * x;
}

// -------------------------------------------------------------------------------------------------

inline void MatrixDiagonal::assemble(const xt::xtensor<double,3> &elemmat)
{
  // check input
  assert( elemmat.shape()[0] == m_nelem      );
  assert( elemmat.shape()[1] == m_nne*m_ndim );
  assert( elemmat.shape()[2] == m_nne*m_ndim );
  assert( Element::isDiagonal(elemmat) );

  // zero-initialize matrix
  m_data.fill(0.0);

  // assemble
  for ( size_t e = 0 ; e < m_nelem ; ++e )
    for ( size_t m = 0 ; m < m_nne ; ++m )
      for ( size_t i = 0 ; i < m_ndim ; ++i )
        m_data(m_dofs(m_conn(e,m),i)) += elemmat(e,m*m_ndim+i,m*m_ndim+i);

  // signal change
  m_change = true;
}

// -------------------------------------------------------------------------------------------------

inline void MatrixDiagonal::set(const xt::xtensor<double,1> &A)
{
  // check input
  assert( A.shape()[0] == m_ndof );

  // copy
  std::copy(A.begin(), A.end(), m_data.begin());

  // signal change
  m_change = true;
}

// -------------------------------------------------------------------------------------------------

inline void MatrixDiagonal::factorize()
{
  // skip for unchanged "m_data"
  if ( ! m_change ) return;

  // invert
  #pragma omp parallel for
  for ( size_t i = 0 ; i < m_ndof ; ++i )
    m_inv(i) = 1. / m_data(i);

  // reset signal
  m_change = false;
}

// -------------------------------------------------------------------------------------------------

inline xt::xtensor<double,1> MatrixDiagonal::solve(const xt::xtensor<double,1> &b)
{
  // check input
  assert( b.size() == m_ndof );

  // factorise (if needed)
  this->factorize();

  // solve
  xt::xtensor<double,1> x = m_inv * b;

  // return output
  return x;
}

// -------------------------------------------------------------------------------------------------

inline xt::xtensor<double,1> MatrixDiagonal::asDiagonal() const
{
  return m_data;
}

// -------------------------------------------------------------------------------------------------

} // namespace ...

// =================================================================================================

#endif
