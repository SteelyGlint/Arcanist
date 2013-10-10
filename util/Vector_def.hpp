#ifndef __Vector_def_hpp__
#define __Vector_def_hpp__

#include "Vector.hpp"


#define VECTOR_PP_DEF(OP)           \
   template<typename T>             \
	template<typename T2,typename>        \
	inline                       \
	Vector2D<T>&                 \
	Vector2D<T>::                \
	operator OP##=               \
	( const Vector2D<T2>&         \
        rhs                     \
   )                            \
   { x OP##= rhs.x;         \
     y OP##= rhs.y;         \
    return  *this;                \
	}


#define SCALAR_PP_DEF(OP)       \
   template<typename T>        \
   template<typename S, typename>      \
   inline                       \
	Vector2D<T>&                 \
	Vector2D<T>::                \
   operator OP##=  \
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




VECTOR_PP_DEF(+)
VECTOR_PP_DEF(-)

SCALAR_PP_DEF(*)
SCALAR_PP_DEF(/)
SCALAR_PP_DEF(+)
SCALAR_PP_DEF(-)


NEW_VECTOR_PP_DEF2(+)
NEW_VECTOR_PP_DEF(+)
NEW_VECTOR_PP_DEF2(-)
NEW_VECTOR_PP_DEF(-)

NEW_SCALAR_PP_DEF(*)
NEW_SCALAR_PP_DEF(/)
NEW_SCALAR_PP_DEF(+)
NEW_SCALAR_PP_DEF(-)


/*
template<typename T>
template<typename>
inline void Vector2D<T>::normalize()
{
//	static_assert(std::is_integral<T>::value,"Cannot normalize an integral Vector");
	T l = length();
	if( l > 0 )
	{
		(*this) *= 1 / l;
	}
}*/

template<typename T>
  template<typename RT>
inline RT Vector2D<T>::length()
{  
	return std::sqrt(x * x + y * y);
}



#undef SCALAR_PP_DEC
#undef VECTOR_PP_DEC

#undef SCALAR_PP_DEF
#undef VECTOR_PP_DEF
#undef NEW_SCALAR_PP_DEF
#undef NEW_SCALAR_PP_DEF2
#undef NEW_VECTOR_PP_DEF
#undef NEW_VECTOR_PP_DEF2

#endif
