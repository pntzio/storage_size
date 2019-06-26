#include "catch.hpp"
#include "storage_size/size.h"

#include <limits>

TEST_CASE("fundamentals")
{
    using sz::operator""_KiB;
    using sz::operator""_MiB;
    using sz::operator""_GiB;

    SECTION("literals")
    {
        sz::kibibytes one_kib = 1_KiB;
        sz::mebibytes three_mib = 3_MiB;
        sz::gibibytes six_gib = 6_GiB;

        REQUIRE(one_kib.byte_count() == 1024);
        REQUIRE(three_mib.byte_count() == 3 * 1024 * 1024);
        REQUIRE(six_gib.byte_count() == 6ll * 1024 * 1024 * 1024);
    }

    SECTION("conversion")
    {
        {
            sz::kibibytes size = 100_KiB;
            sz::mebibytes other = size;

            REQUIRE(other.byte_count() == 100 * 1024);
        }

        {
            sz::kibibytes size = 1024_KiB;
            sz::mebibytes other = size;

            REQUIRE(other.byte_count() == 1024 * 1024);
            REQUIRE(other.units() == Approx(1.0));
            REQUIRE(size.units() == Approx(1024.0));
        }

        {
            sz::kibibytes size = sz::bytes(1024 * 1024 * 1024);
            sz::gibibytes other = size;

            REQUIRE(other.units() == Approx(1.0));
            REQUIRE(other.byte_count() == 1024 * 1024 * 1024);
            WARN(std::numeric_limits<std::intmax_t>::max());
        }
    }
}
