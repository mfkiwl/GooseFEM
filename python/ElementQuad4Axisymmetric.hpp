/**
\file
\copyright Copyright 2017. Tom de Geus. All rights reserved.
\license This project is released under the GNU Public License (GPLv3).
*/

#ifndef PYGOOSEFEM_ELEMENTQUAD4AXISYMMETRIC_H
#define PYGOOSEFEM_ELEMENTQUAD4AXISYMMETRIC_H

#include <GooseFEM/ElementQuad4Axisymmetric.h>
#include <pybind11/pybind11.h>
#include <xtensor-python/pytensor.hpp>

#include "Element.hpp"

namespace py = pybind11;

void init_ElementQuad4Axisymmetric(py::module& m)
{
    py::class_<GooseFEM::Element::Quad4::QuadratureAxisymmetric> cls(m, "QuadratureAxisymmetric");

    cls.def(
        py::init<const xt::pytensor<double, 3>&>(),
        "See :cpp:class:`GooseFEM::Element::Quad4::QuadratureAxisymmetric`.",
        py::arg("x"));

    cls.def(
        py::init<
            const xt::pytensor<double, 3>&,
            const xt::pytensor<double, 2>&,
            const xt::pytensor<double, 1>&>(),
        "See :cpp:class:`GooseFEM::Element::Quad4::QuadratureAxisymmetric`.",
        py::arg("x"),
        py::arg("xi"),
        py::arg("w"));

    register_Mesh_QuadratureBase<GooseFEM::Element::Quad4::QuadratureAxisymmetric>(cls);
    register_Mesh_QuadratureBaseCartesian<GooseFEM::Element::Quad4::QuadratureAxisymmetric>(cls);

    cls.def_property_readonly(
        "B",
        &GooseFEM::Element::Quad4::QuadratureAxisymmetric::B,
        "B-matrix (shape function gradients) [nelem, nne, tdim, tdim, tdim]");

    cls.def("__repr__", [](const GooseFEM::Element::Quad4::QuadratureAxisymmetric&) {
        return "<GooseFEM.Element.Quad4.QuadratureAxisymmetric>";
    });
}

#endif
