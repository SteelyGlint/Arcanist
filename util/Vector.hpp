#include <cmath>
#include <type_traits>


/*
#define VECTOR_PP_DEC(OP)		  \
	Vector2D<T>& operator OP##=  \
	( const Vector2D<T>& rhs );

#define SCALAR_PP_DEC(OP)		  \
	template<typename S, typename T2 = void >       \
	Vector2D<T>& operator OP##=  \
	( const S& rhs );
*/

#define INLINE_VECTOR_PP_DEF(OP)		  \
	template<typename T2,            \
		typename = typename std::enable_if<  \
			std::is_convertible<T2,T  \
         >::value                   \
      >::type                    \
   >                            \
	Vector2D<T>&                 \
	operator OP##=               \
	( const Vector2D<T2>&         \
        rhs                     \
   )                            \
   { x OP##= rhs.x;         \
     y OP##= rhs.y;         \
    return  *this;                \
	}


#define INLINE_SCALAR_PP_DEF(OP)		  \
    template<typename S,        \
      typename = typename std::enable_if< \
                 std::is_arithmetic<S \
                 >::value        \
               >::type          \
       >                        \
	Vector2D<T>& operator OP##=  \
	(const S&					     \
        rhs                     \
   )                            \
   { x OP##= rhs;           \
     y OP##= rhs;           \
    return *this;           \
	}

#define NEW_VECTOR_PP_DEF(OP)	  \
	template<typename T>	        \
	Vector2D<T> operator OP      \
	( const Vector2D<T>& lhs,    \
	 const Vector2D<T>& rhs )   \
   { return Vector2D<T>			  \
     (lhs.x OP rhs.x,				  \
      lhs.y OP rhs.y); }

#define NEW_VECTOR_PP_DEF2(OP)	  \
	template<typename T,typename T2>	        \
	Vector2D<T> operator OP      \
	( const Vector2D<T>& lhs,    \
	  const Vector2D<T2>& rhs )   \
   { return Vector2D<T>			  \
     (lhs.x OP rhs.x,				  \
      lhs.y OP rhs.y); }



#define NEW_SCALAR_PP_DEF(OP)	  \
	template<                    \
       typename T,              \
       typename S,              \
       typename = typename std::enable_if< \
          std::is_arithmetic<S>::value  \
       >::type                 \
   >         \
	Vector2D<T> operator OP     \
	(                            \
	  const Vector2D<T>& lhs,    \
	  const S& rhs )             \
   { return Vector2D<T>			  \
		(lhs.x OP rhs,				  \
		lhs.y OP rhs); }


template<typename T>
struct Vector2D
{
	T x,y;

	Vector2D() = default;
	Vector2D(T _x, T _y) : x(_x), y(_y) {}


	INLINE_VECTOR_PP_DEF(+)
	INLINE_VECTOR_PP_DEF(-)

	INLINE_SCALAR_PP_DEF(*)
	INLINE_SCALAR_PP_DEF(/)
	INLINE_SCALAR_PP_DEF(+)
	INLINE_SCALAR_PP_DEF(-)


	template<typename RT = typename 
		std::conditional<
          std::is_floating_point<T>::value,
			 T,
          double
      >::type
   >
	RT length()
   {  
      return std::sqrt(x * x + y * y);
	}

	void normalize();
};


NEW_VECTOR_PP_DEF2(+)
NEW_VECTOR_PP_DEF(+)
NEW_VECTOR_PP_DEF2(-)
NEW_VECTOR_PP_DEF(-)

NEW_SCALAR_PP_DEF(*)
NEW_SCALAR_PP_DEF(/)
NEW_SCALAR_PP_DEF(+)
NEW_SCALAR_PP_DEF(-)

template<typename T>
inline void Vector2D<T>::normalize()
{
	static_assert(std::is_integral<T>::value,"Cannot normalize an integral Vector");
	T l = length();
	if( l > 0 )
	{
		(*this) *= 1 / l;
	}
}

#undef INLINE_SCALAR_PP_DEF
#undef INLINE_VECTOR_PP_DEF
#undef NEW_SCALAR_PP_DEF
#undef NEW_SCALAR_PP_DEF2
#undef NEW_VECTOR_PP_DEF
#undef NEW_VECTOR_PP_DEF2
