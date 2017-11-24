#include <stdint.h>
#include <array>

struct VectorTag; ///< vec[N]
struct DynamicTag; ///< vec[1U..N]
struct AllocatorTag; ///< ->vec[1U..N]
struct CartesianTag; ///< x, [y, [z, [w]]]
struct RgbTag; ///< r, g, b, [a]
struct YuvTag; ///< y, [u, v]

/** Vector
 * @tparam  Data  Vector element data type
 * @tparam  Count Vector element capacity or count
 * @tparam  Tag   Vector specialisation identifier. [Default = CartesianTag]
 *                @see VectorTag, DynamicTag, AllocatorTag, CartesianTag, RgbTag, YuvTag, etc.
*/
template <typename Data, uint32_t Count, typename Tag = CartesianTag >
struct VectorT;

/** @} Default member */
template <typename Data, uint32_t Count, typename Tag >
struct VectorT : std::array<Data,Count>
{
    typedef DynamicTag tag_type; ///< Custom tag interface

#if 0 ///< C++03
    Data vec[Count];
    Data& operator[] ( const size_t index ) { return vec[index]; }
    const Data& operator[] ( const size_t index ) const { return vec[index]; }
#endif
};
/** @} VectorTag */

/** @} DynamicTag */
template <typename Data, uint32_t Count>
struct VectorT<Data,Count,DynamicTag>
{ 
    typedef Data value_type; ///< Interface for std container
    typedef DynamicTag tag_type; ///< Custom tag interface

    static const uint_fast16_t cCapacity = Count; ///< Capacity constant
    static uint_fast16_t capacity() { return cCapacity; }

    Data vec[Count];

    constexpr uint_fast16_t size() const
    { return size_; }

    constexpr VectorT( const uint_fast16_t size )  ///< constexpr for static_assert tests!
    : vec(), size_(size) {}

private:
    const uint_fast16_t size_; ///< Current size
};
/** @} DynamicTag */

template <typename Data, uint32_t Count, typename Tag >
struct fixedDetail;

/** @{ CartesianTag */
template <typename Data>
struct VectorT<Data,1U,CartesianTag> : fixedDetail<Data,1U,CartesianTag>
{
    union { struct { Data x; }; Data vec[1U]; };
    constexpr VectorT() : vec() {} ///< constexpr for static_assert tests!
    VectorT( const Data x ) 
    : x(x) {} 
};

template <typename Data>
struct VectorT<Data,2U,CartesianTag> : fixedDetail<Data,2U,CartesianTag>
{
    union { struct { Data x, y; }; Data vec[2U]; }; 
    constexpr VectorT() : vec() {} ///< constexpr for static_assert tests!
    VectorT( const Data x, const Data y ) 
    : x(x), y(y) {} 
};

template <typename Data>
struct VectorT<Data,3U,CartesianTag> : fixedDetail<Data,3U,CartesianTag>
{
    union { struct { Data x, y, z; }; Data vec[3U]; };
    constexpr VectorT() : vec() {} ///< constexpr for static_assert tests!
    VectorT( const Data x, const Data y, const Data z )
     : x(x), y(y), z(z) {} 
};

template <typename Data>
struct VectorT<Data,4U,CartesianTag> : fixedDetail<Data,4U,CartesianTag>
{
    union { struct { Data x, y, z, w; }; Data vec[4U]; }; 
    constexpr VectorT() : vec() {} ///< constexpr for static_assert tests!
    VectorT( const Data x, const Data y, const Data z, const Data w ) 
    : x(x), y(y), z(z), w(w) {} 
};
/** @} CartesianTag */

/** @{ RgbTag */
template <typename Data>
struct VectorT<Data,3U,RgbTag> : fixedDetail<Data,3U,RgbTag>
{
    union { struct { Data r, g, b; }; Data vec[3U]; };
    constexpr VectorT() {} ///< constexpr for static_assert tests!
    VectorT( const Data r, const Data g, const Data b ) 
    : r(r), g(g), b(b) {}  
};

template <typename Data>
struct VectorT<Data,4U,RgbTag> : fixedDetail<Data,4U,RgbTag>
{
    union { struct { Data r, g, b, a; }; Data vec[4U]; };
    constexpr VectorT() {} ///< constexpr for static_assert tests!
    VectorT( const Data r, const Data g, const Data b, const Data a ) 
    : r(r), g(g), b(b), a(a) {} 
};
/** @} RgbTag */

/** @{ YuvTag */
template <typename Data>
struct VectorT<Data,1U,YuvTag> : fixedDetail<Data,1U,YuvTag>
{
    union { struct { Data y; }; Data vec[1U]; };
    constexpr VectorT() {} ///< constexpr for static_assert tests!
    VectorT( const Data y  ) 
    : y(y) {}  
}; 

template <typename Data>
struct VectorT<Data,3U,YuvTag> : fixedDetail<Data,3U,YuvTag>
{
    union { struct { Data y, u, v; }; Data vec[3U]; }; 
    constexpr VectorT() {} ///< constexpr for static_assert tests!
    VectorT( const Data y, const Data u, const Data v ) 
    : y(y), u(u), v(v) {}  
};
/** @} YuvTag */

template <typename Data, uint32_t Count, typename Tag >
struct fixedDetail
{
    typedef VectorT<Data,Count,Tag> Vector;
    typedef Data value_type; ///< Interface for std container
    typedef CartesianTag tag_type; ///< Custom tag interface
    static constexpr uint_fast16_t cCapacity = Count;

    constexpr uint_fast16_t capacity() const { return cCapacity; }
    constexpr uint_fast16_t size() const { return cCapacity; }
    
    /// @note CRTP performance needs check
    // !Looks to not compile out until O3 :(
    const value_type& __attribute((optimize("O3"))) operator[] ( const uint_fast16_t index ) const
    { return static_cast<const Vector&>(*this).vec[index]; }

    value_type& __attribute((optimize("O3"))) operator[] ( const uint_fast16_t index )
    { return static_cast<Vector&>(*this).vec[index]; }
};

template <typename Data, uint32_t Count, typename Tag>
VectorT<Data,Count,Tag> operator + ( const VectorT<Data,Count,Tag>& lhs, const VectorT<Data,Count,Tag>& rhs )
{
    VectorT<Data,Count,Tag> ret;
    for ( size_t i = 0U; i < Count; ++i )
        ret.vec[i] = lhs.vec[i] + rhs.vec[i];
    return ret;
}

typedef VectorT<float,1U,CartesianTag> Vector1f; ///< x
typedef VectorT<float,2U,CartesianTag> Vector2f; ///< x, y
typedef VectorT<float,3U,CartesianTag> Vector3f; ///< x, y, z

typedef VectorT<float,10U> Vector10f; ///< vec[10]
typedef VectorT<float,10U,DynamicTag> VectorX10f; ///< vec[1..10]

typedef VectorT<float,3U,RgbTag> Rgb;
typedef VectorT<float,3U,YuvTag> Yuv;

static_assert( sizeof(Vector1f) == sizeof(float) * 1U, "Design error" );
static_assert( sizeof(Vector2f) == sizeof(float) * 2U, "Design error" );
static_assert( sizeof(Vector3f) == sizeof(float) * 3U, "Design error" );
static_assert( sizeof(Vector10f) == sizeof(float) * 10U, "Design error" );
static_assert( sizeof(VectorX10f) == sizeof(Vector10f) + sizeof(uint_fast16_t), "Design error" );

static_assert( Vector1f().size() == 1U, "Design error" );
static_assert( Vector2f().size() == 2U, "Design error" );
static_assert( Vector3f().size() == 3U, "Design error" );
static_assert( Vector10f().size() == 10U, "Design error" );
static_assert( VectorX10f(1U).size() == 1U, "Design error" );
static_assert( VectorX10f(5U).size() == 5U, "Design error" );

// Type your code here, or load an example.
Yuv test() 
{
    Yuv yuv(1,2,3);
    yuv.y = 4;
    yuv.u = 5;
    yuv.v = 6;


    return yuv + Yuv(2,3,4);
}
