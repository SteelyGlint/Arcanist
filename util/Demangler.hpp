
#ifndef __Demangler_hpp__
#define __Demangler_hpp__
#include <typeinfo>
#include <iostream>
#include <cxxabi.h>


std::ostream& operator<<(std::ostream& stream, const std::type_info& ti) {
  char buf[1024];
  size_t size=1024;
  int status;
  char* res = abi::__cxa_demangle (ti.name(),
                                   buf,
                                   &size,
                                   &status);
  return stream << res;
}

#endif
