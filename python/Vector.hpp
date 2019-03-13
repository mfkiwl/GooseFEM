/* =================================================================================================

(c - GPLv3) T.W.J. de Geus (Tom) | tom@geus.me | www.geus.me | github.com/tdegeus/GooseFEM

================================================================================================= */

#include <Eigen/Eigen>

#include <pybind11/pybind11.h>
#include <pybind11/eigen.h>

#include <pyxtensor/pyxtensor.hpp>

#include "../include/GooseFEM/GooseFEM.h"

// =================================================================================================

namespace py = pybind11;

// =================================================================================================

void init_Vector(py::module &m)
{

py::class_<GooseFEM::Vector>(m, "Vector")

  .def(py::init<const xt::xtensor<size_t,2> &, const xt::xtensor<size_t,2> &>(), "Switch between dofval/nodevec/elemvec", py::arg("conn"), py::arg("dofs"))

  .def("nelem", &GooseFEM::Vector::nelem, "Return number of element")
  .def("nne"  , &GooseFEM::Vector::nne  , "Return number of nodes per element")
  .def("nnode", &GooseFEM::Vector::nnode, "Return number of nodes")
  .def("ndim" , &GooseFEM::Vector::ndim , "Return number of dimensions")
  .def("ndof" , &GooseFEM::Vector::ndof , "Return number of degrees-of-freedom")
  .def("dofs" , &GooseFEM::Vector::dofs , "Return degrees-of-freedom")

  .def("AsDofs", py::overload_cast<const xt::xtensor<double,2>&>(&GooseFEM::Vector::AsDofs, py::const_), "Set 'dofval", py::arg("nodevec"))
  .def("AsDofs", py::overload_cast<const xt::xtensor<double,3>&>(&GooseFEM::Vector::AsDofs, py::const_), "Set 'dofval", py::arg("elemvec"))

  .def("AsNode", py::overload_cast<const xt::xtensor<double,1>&>(&GooseFEM::Vector::AsNode, py::const_), "Set 'nodevec", py::arg("dofval"))
  .def("AsNode", py::overload_cast<const xt::xtensor<double,3>&>(&GooseFEM::Vector::AsNode, py::const_), "Set 'nodevec", py::arg("elemvec"))

  .def("AsElement", py::overload_cast<const xt::xtensor<double,1>&>(&GooseFEM::Vector::AsElement, py::const_), "Set 'elemvec", py::arg("dofval"))
  .def("AsElement", py::overload_cast<const xt::xtensor<double,2>&>(&GooseFEM::Vector::AsElement, py::const_), "Set 'elemvec", py::arg("nodevec"))

  .def("AssembleDofs", py::overload_cast<const xt::xtensor<double,2>&>(&GooseFEM::Vector::AssembleDofs, py::const_), "Assemble 'dofval'", py::arg("nodevec"))
  .def("AssembleDofs", py::overload_cast<const xt::xtensor<double,3>&>(&GooseFEM::Vector::AssembleDofs, py::const_), "Assemble 'dofval'", py::arg("elemvec"))

  .def("AssembleNode", py::overload_cast<const xt::xtensor<double,3>&>(&GooseFEM::Vector::AssembleNode, py::const_), "Assemble 'nodevec'", py::arg("elemvec"))

  .def("__repr__", [](const GooseFEM::Vector &){ return "<GooseFEM.Vector>"; });

}

// =================================================================================================
