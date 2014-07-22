#ifndef __XPMLoader_hpp__
#define __XPMLoader_hpp__
#include <type_traits>

using std::add_pointer;
using std::remove_pointer;
using std::remove_const;
using std::is_same;
using std::is_scalar;

using std::is_const;
using std::is_pointer;

namespace Wand
{
	/*
template<typename T>
char **XPMLoadFromStaticCharArray(T xpm)
{
   static_assert(
      is_pointer<T>{},"not a pointer");

   static_assert(
      is_pointer<
         typename remove_pointer<T>::type
      >{},"not a pointer-pointer");

    static_assert(
      is_scalar<
         typename remove_pointer<
            typename remove_pointer<T>::type
         >::type
      >{},"not a pointer-pointer");

    static_assert(
      is_same<char,
			typename remove_const<
           typename remove_pointer<
             typename remove_pointer<T>::type
           >::type
         >::type
      >{},"not a pointer-pointer char");



		return
		  const_cast< //  const char ** -> char **
         typename add_pointer<
         typename add_pointer<
         typename remove_const<
         typename remove_pointer<
         typename remove_pointer<T>::type
         >::type
         >::type
         >::type
         >::type
      >(xpm);

}*/

};
#endif
