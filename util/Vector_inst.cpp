
#include "Vector.hpp"



template double Vector2D<int>::length();
template float Vector2D<float>::length();
template double Vector2D<double>::length();
template long double Vector2D<long double>::length();

template Vector2D<float>::Vector2D<int>(Vector2D<int> const &);

#define INSTANTIATE_VEC_OPT_SCALAR(OP)													\
template Vector2D<int> operator OP (Vector2D<int> const&, int const &);       \
template Vector2D<int> operator OP (Vector2D<int> const&, float const &);     \
template Vector2D<float> operator OP(Vector2D<float> const&, int const &);   \
template Vector2D<float> operator OP(Vector2D<float> const&, float const &); \
template Vector2D<double> operator OP(Vector2D<double> const&, int const &);  \
template Vector2D<double> operator OP(Vector2D<double> const&, float const &); \
template Vector2D<double> operator OP(Vector2D<double> const&, double const &);

INSTANTIATE_VEC_OPT_SCALAR(*)
INSTANTIATE_VEC_OPT_SCALAR(/)
INSTANTIATE_VEC_OPT_SCALAR(+)
INSTANTIATE_VEC_OPT_SCALAR(-)

#define INSTANTIATE_INLINE_VEC_OPT_SCALAR(OP)                                  \
template Vector2D<int>& Vector2D<int>::operator OP##=(int const &);             \
template Vector2D<float>& Vector2D<float>::operator OP##=(float const &);       \
template Vector2D<double>& Vector2D<double>::operator OP##=(float const &);   \
template Vector2D<double>& Vector2D<double>::operator OP##=(double const &); 


INSTANTIATE_INLINE_VEC_OPT_SCALAR(*)
INSTANTIATE_INLINE_VEC_OPT_SCALAR(/)
INSTANTIATE_INLINE_VEC_OPT_SCALAR(-)
INSTANTIATE_INLINE_VEC_OPT_SCALAR(+)

#define INSTANTIATE_INLINE_VEC_OPT_VEC(OP)                                  \
template Vector2D<int>& Vector2D<int>::operator OP##=(Vector2D<int> const &);             \
template Vector2D<float>& Vector2D<float>::operator OP##=(Vector2D<int> const &);             \
template Vector2D<float>& Vector2D<float>::operator OP##=(Vector2D<float> const &);             \
template Vector2D<double>& Vector2D<double>::operator OP##=(Vector2D<int> const &);             \
template Vector2D<double>& Vector2D<double>::operator OP##=(Vector2D<float> const &);             \
template Vector2D<double>& Vector2D<double>::operator OP##=(Vector2D<double> const &);             

INSTANTIATE_INLINE_VEC_OPT_VEC(-)
INSTANTIATE_INLINE_VEC_OPT_VEC(+)


#define INSTANTIATE_VEC_OPT_VEC(OP) \
template Vector2D<int> operator OP (Vector2D<int> const&, Vector2D<int> const &);       \
template Vector2D<float> operator OP (Vector2D<float> const&, Vector2D<int> const &); \
template Vector2D<double> operator OP (Vector2D<double> const&, Vector2D<float> const &); \
template Vector2D<double> operator OP (Vector2D<double> const&, Vector2D<int> const &); \
template Vector2D<double> operator OP (Vector2D<double> const&, Vector2D<double> const &); \


INSTANTIATE_VEC_OPT_VEC(+)
INSTANTIATE_VEC_OPT_VEC(-)



template class Vector2D<int>;
template class Vector2D<double>;
template class Vector2D<float>;



