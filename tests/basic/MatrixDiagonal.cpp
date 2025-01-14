#include <GooseFEM/ElementQuad4.h>
#include <GooseFEM/MatrixDiagonal.h>
#include <GooseFEM/MeshQuad4.h>
#include <GooseFEM/Vector.h>
#include <catch2/catch_all.hpp>
#include <xtensor/xrandom.hpp>

#define ISCLOSE(a, b) REQUIRE_THAT((a), Catch::Matchers::WithinAbs((b), 1.e-12));

TEST_CASE("GooseFEM::MatrixDiagonal", "MatrixDiagonal.h")
{
    SECTION("assemble")
    {
        GooseFEM::Mesh::Quad4::Regular mesh(2, 2);
        GooseFEM::Vector vector(mesh.conn(), mesh.dofs());
        GooseFEM::MatrixDiagonal A(mesh.conn(), mesh.dofs());

        GooseFEM::Element::Quad4::Quadrature quad(
            vector.AsElement(mesh.coor()),
            GooseFEM::Element::Quad4::Nodal::xi(),
            GooseFEM::Element::Quad4::Nodal::w());

        xt::xtensor<double, 2> val_quad = xt::empty<double>({mesh.nelem(), quad.nip()});
        for (size_t q = 0; q < quad.nip(); ++q) {
            xt::view(val_quad, xt::all(), q) = 1.0;
        }

        A.assemble(quad.Int_N_scalar_NT_dV(val_quad));

        xt::xtensor<double, 1> a = {
            0.25,
            0.25,
            0.5,
            0.5,
            0.25,
            0.25,
            0.5,
            0.5,
            1.0,
            1.0,
            0.5,
            0.5,
            0.25,
            0.25,
            0.5,
            0.5,
            0.25,
            0.25};

        REQUIRE(xt::allclose(A.data(), a));
    }

    SECTION("dot")
    {
        GooseFEM::Mesh::Quad4::Regular mesh(2, 2);

        xt::xtensor<double, 1> a = xt::random::rand<double>({mesh.nnode() * mesh.ndim()});
        xt::xtensor<double, 1> x = xt::random::rand<double>({mesh.nnode() * mesh.ndim()});
        xt::xtensor<double, 1> b = a * x;

        GooseFEM::MatrixDiagonal A(mesh.conn(), mesh.dofs());
        A.set(a);
        xt::xtensor<double, 1> B = A.Dot(x);

        REQUIRE(B.size() == b.size());
        REQUIRE(xt::allclose(B, b));
        REQUIRE(xt::allclose(A.data(), a));
    }

    SECTION("solve")
    {
        GooseFEM::Mesh::Quad4::Regular mesh(2, 2);

        xt::xtensor<double, 1> a = xt::random::rand<double>({mesh.nnode() * mesh.ndim()});
        xt::xtensor<double, 1> x = xt::random::rand<double>({mesh.nnode() * mesh.ndim()});
        xt::xtensor<double, 1> b = a * x;

        GooseFEM::MatrixDiagonal A(mesh.conn(), mesh.dofs());
        A.set(a);
        xt::xtensor<double, 1> B = A.Dot(x);
        xt::xtensor<double, 1> X = A.Solve(B);

        REQUIRE(B.size() == b.size());
        REQUIRE(X.size() == x.size());
        REQUIRE(xt::allclose(B, b));
        REQUIRE(xt::allclose(X, x));
    }
}
