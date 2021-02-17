
#include <catch2/catch.hpp>
#include <xtensor/xrandom.hpp>
#include <xtensor/xmath.hpp>
#include <GooseFEM/GooseFEM.h>

#define ISCLOSE(a,b) REQUIRE_THAT((a), Catch::WithinAbs((b), 1.e-12));

TEST_CASE("GooseFEM::Element", "Element.h")
{

    SECTION("QuadratureBase - AsTensor - e.g. Quad4")
    {
        size_t nelem = 3;
        size_t nip = 4;
        GooseFEM::Element::QuadratureBase<4, 2, 2> quad(nelem, nip);

        xt::xtensor<double, 2> qscalar = xt::random::rand<double>({nelem, nip});
        auto qtensor = quad.AsTensor<2>(qscalar);

        REQUIRE(xt::has_shape(quad.AllocateQscalar(), qscalar.shape()));
        REQUIRE(xt::has_shape(quad.AllocateQscalar(0.0), qscalar.shape()));
        REQUIRE(xt::has_shape(quad.AllocateQtensor<2>(), qtensor.shape()));
        REQUIRE(xt::has_shape(quad.AllocateQtensor<2>(0.0), qtensor.shape()));
        REQUIRE(xt::has_shape(quad.AllocateQtensor(2), qtensor.shape()));
        REQUIRE(xt::has_shape(quad.AllocateQtensor(2, 0.0), qtensor.shape()));

        for (size_t e = 0; e < nelem; ++e) {
            for (size_t q = 0; q < nip; ++q) {
                REQUIRE(xt::allclose(xt::view(qtensor, xt::keep(e), xt::keep(q)), qscalar(e, q)));
            }
        }
    }

    SECTION("QuadratureBase - AsTensor - e.g. Hex8")
    {
        size_t nelem = 6;
        size_t nip = 8;
        GooseFEM::Element::QuadratureBase<8, 3, 3> quad(nelem, nip);

        xt::xtensor<double, 2> qscalar = xt::random::rand<double>({nelem, nip});
        auto qtensor = quad.AsTensor<2>(qscalar);

        REQUIRE(xt::has_shape(quad.AllocateQscalar(), qscalar.shape()));
        REQUIRE(xt::has_shape(quad.AllocateQscalar(0.0), qscalar.shape()));
        REQUIRE(xt::has_shape(quad.AllocateQtensor<2>(), qtensor.shape()));
        REQUIRE(xt::has_shape(quad.AllocateQtensor<2>(0.0), qtensor.shape()));
        REQUIRE(xt::has_shape(quad.AllocateQtensor(2), qtensor.shape()));
        REQUIRE(xt::has_shape(quad.AllocateQtensor(2, 0.0), qtensor.shape()));

        for (size_t e = 0; e < nelem; ++e) {
            for (size_t q = 0; q < nip; ++q) {
                REQUIRE(xt::allclose(xt::view(qtensor, xt::keep(e), xt::keep(q)), qscalar(e, q)));
            }
        }
    }
}