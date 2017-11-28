#include <stddef.h>
#include <stdint.h>

/// @{ Common types giving direct data access via member variable names
struct VectorTag; ///< vec[N]
struct CartesianTag; ///< x, [y, [z, [w]]]
struct RgbTag; ///< r, g, b, [a]
struct YuvTag; ///< y, [u, v]
/// @}

/// @{ Variable length vectors stack/allocator
/** Dynamic size vector with fixed capacity at compile time
*/
struct DynamicTag; ///< vec[1U..N]

/** Dynamic size vector with runtime allocated capacity
 * @remark Uses small-buffer optimisations to minimise allocation
 * @tparam  Count  Small-buffer capacity. When vector storage is less or 
 *  equal no dynamic allocation is used and data is directly stored.
 *   i.e. union{ Data* dynamic; Data smallBuffer[Count]; } 
 */
struct AllocatorTag; ///< ->vec[1U..N] (Custom allocator)
/// @}

/** Vector
 * @tparam  Data  Vector element data type
 * @tparam  Count Vector element capacity or count
 * @tparam  Tag   Vector specialisation identifier. [Default = CartesianTag]
 *                @see VectorTag, DynamicTag, AllocatorTag, CartesianTag, RgbTag, YuvTag, etc.
*/
template <typename Data, uint32_t Count, typename Tag = CartesianTag >
struct VectorT;

//TODO: doc etc
template <typename Data, typename Tag >
struct detail;
template <typename Data, uint32_t Count, typename Tag >
struct fixedDetail;

/** @} Default member */
template <typename Data, uint32_t Count, typename Tag >
struct VectorT : fixedDetail<Data,Count,Tag>
{
    typedef DynamicTag tag_type; ///< Custom tag interface

    Data vec[Count];

    /** @{ Performance container functions/operator
     * @remark Library functions may use .vec for zero cost array access as standard
     * @note These functions are less costly than CRTP (Recursive-Template) under debug builds.
     */
    Data& operator[] ( const size_t index ) { return vec[index]; }
    const Data& operator[] ( const size_t index ) const { return vec[index]; }
    Data* begin() { return &vec[0U]; }
    const Data* begin() const { return &vec[0U]; }
    const Data* cbegin() const { return &vec[0U]; }
    Data* end() { return &vec[Count]; }
    const Data* end() const { return &vec[Count]; }
    const Data* cend() const { return &vec[Count]; }
    /** @} End performance container functions/operators */
};
/** @} VectorTag */

/** @} DynamicTag */
template <typename Data, uint32_t Count>
struct VectorT<Data,Count,DynamicTag> : detail<Data,DynamicTag>
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

    /** @{ Performance container functions/operator
     * @remark Library functions may use .vec for zero cost array access as standard
     * @note These functions are less costly than CRTP (Recursive-Template) under debug builds.
     */
    Data& operator[] ( const size_t index ) { return vec[index]; }
    const Data& operator[] ( const size_t index ) const { return vec[index]; }
    Data* begin() { return &vec[0U]; }
    const Data* begin() const { return &vec[0U]; }
    const Data* cbegin() const { return &vec[0U]; }
    Data* end() { return &vec[Count]; }
    const Data* end() const { return &vec[Count]; }
    const Data* cend() const { return &vec[Count]; }
    /** @} End performance container functions/operators */
private:
    const uint_fast16_t size_; ///< Current size
};
/** @} DynamicTag */


/** @{ CartesianTag */
template <typename Data>
struct VectorT<Data,1U,CartesianTag> : fixedDetail<Data,1U,CartesianTag>
{
    union { struct { Data x; }; Data vec[1U]; };
    constexpr VectorT() : vec() {} ///< constexpr for static_assert tests!
    VectorT( const Data x ) 
    : x(x) {} 

    /** @{ Performance container functions/operator
     * @remark Library functions may use .vec for zero cost array access as standard
     * @note These functions are less costly than CRTP (Recursive-Template) under debug builds.
     */
    Data& operator[] ( const size_t index ) { return vec[index]; }
    const Data& operator[] ( const size_t index ) const { return vec[index]; }
    Data* begin() { return &vec[0U]; }
    const Data* begin() const { return &vec[0U]; }
    const Data* cbegin() const { return &vec[0U]; }
    Data* end() { return &vec[1U]; }
    const Data* end() const { return &vec[1U]; }
    const Data* cend() const { return &vec[1U]; }
    /** @} End performance container functions/operators */
};

template <typename Data>
struct VectorT<Data,2U,CartesianTag> : fixedDetail<Data,2U,CartesianTag>
{
    union { struct { Data x, y; }; Data vec[2U]; }; 
    constexpr VectorT() : vec() {} ///< constexpr for static_assert tests!
    VectorT( const Data x, const Data y ) 
    : x(x), y(y) {} 

    /** @{ Performance container functions/operator
     * @remark Library functions may use .vec for zero cost array access as standard
     * @note These functions are less costly than CRTP (Recursive-Template) under debug builds.
     */
    Data& operator[] ( const size_t index ) { return vec[index]; }
    const Data& operator[] ( const size_t index ) const { return vec[index]; }
    Data* begin() { return &vec[0U]; }
    const Data* begin() const { return &vec[0U]; }
    const Data* cbegin() const { return &vec[0U]; }
    Data* end() { return &vec[2U]; }
    const Data* end() const { return &vec[2U]; }
    const Data* cend() const { return &vec[2U]; }
    /** @} End performance container functions/operators */
};

template <typename Data>
struct VectorT<Data,3U,CartesianTag> : fixedDetail<Data,3U,CartesianTag>
{
    union { struct { Data x, y, z; }; Data vec[3U]; };
    constexpr VectorT() : vec() {} ///< constexpr for static_assert tests!
    VectorT( const Data x, const Data y, const Data z )
     : x(x), y(y), z(z) {} 

    /** @{ Performance container functions/operator
     * @remark Library functions may use .vec for zero cost array access as standard
     * @note These functions are less costly than CRTP (Recursive-Template) under debug builds.
     */
    Data& operator[] ( const size_t index ) { return vec[index]; }
    const Data& operator[] ( const size_t index ) const { return vec[index]; }
    Data* begin() { return &vec[0U]; }
    const Data* begin() const { return &vec[0U]; }
    const Data* cbegin() const { return &vec[0U]; }
    Data* end() { return &vec[3U]; }
    const Data* end() const { return &vec[3U]; }
    const Data* cend() const { return &vec[3U]; }
    /** @} End performance container functions/operators */
};

template <typename Data>
struct VectorT<Data,4U,CartesianTag> : fixedDetail<Data,4U,CartesianTag>
{
    union { struct { Data x, y, z, w; }; Data vec[4U]; }; 
    constexpr VectorT() : vec() {} ///< constexpr for static_assert tests!
    VectorT( const Data x, const Data y, const Data z, const Data w ) 
    : x(x), y(y), z(z), w(w) {} 

    /** @{ Performance container functions/operator
     * @remark Library functions may use .vec for zero cost array access as standard
     * @note These functions are less costly than CRTP (Recursive-Template) under debug builds.
     */
    Data& operator[] ( const size_t index ) { return vec[index]; }
    const Data& operator[] ( const size_t index ) const { return vec[index]; }
    Data* begin() { return &vec[0U]; }
    const Data* begin() const { return &vec[0U]; }
    const Data* cbegin() const { return &vec[0U]; }
    Data* end() { return &vec[4U]; }
    const Data* end() const { return &vec[4U]; }
    const Data* cend() const { return &vec[4U]; }
    /** @} End performance container functions/operators */
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

    /** @{ Performance container functions/operator
     * @remark Library functions may use .vec for zero cost array access as standard
     * @note These functions are less costly than CRTP (Recursive-Template) under debug builds.
     */
    Data& operator[] ( const size_t index ) { return vec[index]; }
    const Data& operator[] ( const size_t index ) const { return vec[index]; }
    Data* begin() { return &vec[0U]; }
    const Data* begin() const { return &vec[0U]; }
    const Data* cbegin() const { return &vec[0U]; }
    Data* end() { return &vec[3U]; }
    const Data* end() const { return &vec[3U]; }
    const Data* cend() const { return &vec[3U]; }
    /** @} End performance container functions/operators */
};

template <typename Data>
struct VectorT<Data,4U,RgbTag> : fixedDetail<Data,4U,RgbTag>
{
    union { struct { Data r, g, b, a; }; Data vec[4U]; };
    constexpr VectorT() {} ///< constexpr for static_assert tests!
    VectorT( const Data r, const Data g, const Data b, const Data a ) 
    : r(r), g(g), b(b), a(a) {} 

    /** @{ Performance container functions/operator
     * @remark Library functions may use .vec for zero cost array access as standard
     * @note These functions are less costly than CRTP (Recursive-Template) under debug builds.
     */
    Data& operator[] ( const size_t index ) { return vec[index]; }
    const Data& operator[] ( const size_t index ) const { return vec[index]; }
    Data* begin() { return &vec[0U]; }
    const Data* begin() const { return &vec[0U]; }
    const Data* cbegin() const { return &vec[0U]; }
    Data* end() { return &vec[4U]; }
    const Data* end() const { return &vec[4U]; }
    const Data* cend() const { return &vec[4U]; }
    /** @} End performance container functions/operators */
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

template <typename Data, typename Tag >
struct detail
{
    typedef Data value_type; ///< Interface for std container
    typedef CartesianTag tag_type; ///< Custom tag interface
};

template <typename Data, uint32_t Count, typename Tag >
struct fixedDetail : detail<Data,Tag>
{
    typedef VectorT<Data,Count,Tag> Vector;
    typedef Data value_type; ///< Interface for std container
    typedef CartesianTag tag_type; ///< Custom tag interface

    constexpr uint_fast16_t capacity() const { return Count; }
    constexpr uint_fast16_t size() const { return Count; }   
};

/**
 * @note Direct member access - Maximum debug performance
 */
template <typename Data, uint32_t Count, typename Tag>
inline VectorT<Data,Count,Tag> operator + ( const VectorT<Data,Count,Tag>& lhs, const VectorT<Data,Count,Tag>& rhs )
{
    VectorT<Data,Count,Tag> ret;
    for ( size_t i = 0U; i < Count; ++i )
        ret.vec[i] = lhs.vec[i] + rhs.vec[i];
    return ret;
}
/**
 * @note Direct member access - Maximum debug performance
 */
template <typename Data, uint32_t Count, typename Tag>
inline VectorT<Data,Count,Tag> operator - ( const VectorT<Data,Count,Tag>& lhs, const VectorT<Data,Count,Tag>& rhs )
{
    VectorT<Data,Count,Tag> ret;
    for ( size_t i = 0U; i < Count; ++i )
        ret.vec[i] = lhs.vec[i] - rhs.vec[i];
    return ret;
}

/**
 * @note Direct member access - Maximum debug performance
 */
template <typename Data, uint32_t Count, typename Tag>
inline VectorT<Data,Count,Tag> operator * ( const VectorT<Data,Count,Tag>& lhs, const VectorT<Data,Count,Tag>& rhs )
{
    VectorT<Data,Count,Tag> ret;
    for ( size_t i = 0U; i < Count; ++i )
        ret.vec[i] = lhs.vec[i] * rhs.vec[i];
    return ret;
}

/**
 * @note Direct member access - Maximum debug performance
 */
template <typename Data, uint32_t Count, typename Tag>
VectorT<Data,Count,Tag> operator / ( const VectorT<Data,Count,Tag>& lhs, const VectorT<Data,Count,Tag>& rhs )
{
    VectorT<Data,Count,Tag> ret;
    for ( size_t i = 0U; i < Count; ++i )
        ret.vec[i] = lhs.vec[i] / rhs.vec[i];
    return ret;
}

template <typename Data, uint32_t Count, typename Tag>
bool operator < ( const VectorT<Data,Count,Tag>& lhs, const VectorT<Data,Count,Tag>& rhs )
{
    ///TODO: not tested/verified/optimal?
    for ( size_t i = 0U; i < Count; ++i )
    {
        if ( lhs[i] < rhs[i] )
            return true;
        if ( rhs[i] < lhs[i] )
            return false;
    }
    return false;
}


/**
 * @remark Only 3D cross product implemented. 0, 1, 3, 7 technically valid (TBD)
 * @note Direct member access - Maximum debug performance
 */
template <typename Data>
VectorT<Data,3U,CartesianTag> cross( const VectorT<Data,3U,CartesianTag>& lhs, const VectorT<Data,3U,CartesianTag>& rhs )
{
    return VectorT<Data,3U,CartesianTag>( (lhs.y * rhs.z) - (lhs.z * rhs.y)
                                        , (lhs.z * rhs.x) - (lhs.x * rhs.z)
                                        , (lhs.x * rhs.y) - (lhs.y * rhs.x) ); 
}

/**
 * @note Direct member access - Maximum debug performance
 */
template <typename Data, uint32_t Count, typename Tag>
Data dot( const VectorT<Data,Count,Tag>& lhs, const VectorT<Data,Count,Tag>& rhs  )
{
    Data product = lhs.vec[0U] * lhs.vec[0U]; ///< @todo We don't specialise for Count==0!
    for ( size_t i = 1U; i < Count; ++i )
        product += lhs.vec[i] * lhs.vec[i]; 
    return product;		
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
Vector3f test() 
{
    Vector3f v;
    v.x = 1;
    v.vec[0] = 1; ///< Direct member access can be used for library functions
    v[1] = 2; ///< Must user overloaded operator
    v.z = 3;
    v.vec[2] = v.size();

    bool test = v < v;
    float t = dot(v,v);

    /// @note GCC 7.2 failes to optimise out the math at O3
    /// clang  oes optimise all code using constants
    return cross( v, v + Vector3f(2,3,4) * Vector3f(4,5,6) - Vector3f(4,5,6) / Vector3f(4,5,6) );
}
