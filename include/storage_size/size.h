#pragma once

#include <cstdint>
#include <ratio>

namespace sz {

using kib = std::ratio<1024, 1>;
using mib = std::ratio<1024 * 1024, 1>;
using gib = std::ratio<1024 * 1024 * 1024, 1>;
using tib = std::ratio<1024ll * 1024 * 1024 * 1024, 1>;

struct bytes
{
    using size_type = std::size_t;

    explicit bytes(size_type amount) : count(amount) { }
    bytes(bytes const& other) : count(other.count) { }

    operator size_type() { return count; }

    size_type count;
};

template <typename Ratio = std::ratio<1>>
class storage_size {

public:

    /*!
     * \brief Constructor setting the given size amount of units (ratio numerator) bytes.
     * \param size The amount of units.
     */
    storage_size(std::size_t size) : bytes_(size * Ratio::num) { }

    /*!
     * \brief Constructor for specified number of bytes.
     * \param bytes Number of bytes.
     */
    storage_size(bytes bytes) : bytes_(bytes) { }

    /*!
     * \brief Constructor to convert from storage_size with any ratio.
     */
    template <typename R>
    storage_size(storage_size<R>& other) : storage_size(static_cast<sz::bytes>(other)) { }

    /*!
     * \brief Copy assignment operator for storage_size with any ratio.
     */
    template <typename R>
    storage_size<Ratio>& operator=(storage_size<R> const& other) { this->bytes_ = sz::bytes(other.byte_count()); return *this; }

    /*!
     * \brief Conversion operator to \sa bytes.
     */
    operator bytes() { return bytes_; }

    /*!
     * \brief Number of bytes represented by this storage_size.
     * \return Integer representing the number of bytes.
     * \note This is the same as doing
     * \code
     * static_cast<sz::bytes>(storage).count
     * \endcode
     */
    bytes::size_type byte_count() const { return bytes_.count; }

    /*!
     * \brief Floating point representation of the amount of 'units' this storage_size represents.
     * \return Floating point number representing the units.
     *
     * \code
     * sz::kibibytes size = 512_KiB // size.units8) is 1.0
     * sz::mebibytes other = size; // other.units() is 0.5
     * \endcode
     */
    float units() const { return static_cast<float>(byte_count()) / Ratio::num; }

private:

    struct bytes bytes_;
};

using kibibytes = storage_size<kib>;
using mebibytes = storage_size<mib>;
using gibibytes = storage_size<gib>;
using tebibytes = storage_size<tib>;

kibibytes operator"" _KiB(unsigned long long val) {
    return kibibytes(sz::bytes(val * kib::num));
}

mebibytes operator"" _MiB(unsigned long long val) {
    return mebibytes(sz::bytes(val * mib::num));
}

gibibytes operator"" _GiB(unsigned long long val) {
    return gibibytes(sz::bytes(val * gib::num));
}

tebibytes operator"" _TiB(unsigned long long val) {
    return tebibytes(sz::bytes(val * tib::num));
}

}
