/**
\file
\copyright Copyright 2017. Tom de Geus. All rights reserved.
\license This project is released under the GNU Public License (GPLv3).
*/

#include <GooseFEM/GooseFEM.h>
#include <pybind11/pybind11.h>
#include <xtensor-python/pyarray.hpp>
#include <xtensor-python/pytensor.hpp>

namespace py = pybind11;

void init_VectorPartitionedTyings(py::module& m)
{

    py::class_<GooseFEM::VectorPartitionedTyings, GooseFEM::Vector>(m, "VectorPartitionedTyings")

        .def(
            py::init<
                const xt::xtensor<size_t, 2>&,
                const xt::xtensor<size_t, 2>&,
                const Eigen::SparseMatrix<double>&,
                const Eigen::SparseMatrix<double>&,
                const Eigen::SparseMatrix<double>&>(),
            "See :cpp:class:`GooseFEM::VectorPartitionedTyings`.",
            py::arg("conn"),
            py::arg("dofs"),
            py::arg("Cdu"),
            py::arg("Cdp"),
            py::arg("Cdi"))

        .def("nnu", &GooseFEM::VectorPartitionedTyings::nnu)
        .def("nnp", &GooseFEM::VectorPartitionedTyings::nnp)
        .def("nni", &GooseFEM::VectorPartitionedTyings::nni)
        .def("nnd", &GooseFEM::VectorPartitionedTyings::nnd)
        .def("iiu", &GooseFEM::VectorPartitionedTyings::iiu)
        .def("iip", &GooseFEM::VectorPartitionedTyings::iip)
        .def("iii", &GooseFEM::VectorPartitionedTyings::iii)
        .def("iid", &GooseFEM::VectorPartitionedTyings::iid)

        .def(
            "AsDofs_i",
            &GooseFEM::VectorPartitionedTyings::AsDofs_i<xt::xtensor<double, 2>>,
            py::arg("nodevec"))

        .def("__repr__", [](const GooseFEM::VectorPartitionedTyings&) {
            return "<GooseFEM.VectorPartitionedTyings>";
        });
}
