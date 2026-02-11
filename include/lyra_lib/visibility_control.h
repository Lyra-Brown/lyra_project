#ifndef LYRA_LIB__VISIBILITY_CONTROL_H_
#define LYRA_LIB__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define LYRA_LIB_EXPORT __attribute__ ((dllexport))
    #define LYRA_LIB_IMPORT __attribute__ ((dllimport))
  #else
    #define LYRA_LIB_EXPORT __declspec(dllexport)
    #define LYRA_LIB_IMPORT __declspec(dllimport)
  #endif
  #ifdef LYRA_LIB_BUILDING_LIBRARY
    #define LYRA_LIB_PUBLIC LYRA_LIB_EXPORT
  #else
    #define LYRA_LIB_PUBLIC LYRA_LIB_IMPORT
  #endif
  #define LYRA_LIB_PUBLIC_TYPE LYRA_LIB_PUBLIC
  #define LYRA_LIB_LOCAL
#else
  #define LYRA_LIB_EXPORT __attribute__ ((visibility("default")))
  #define LYRA_LIB_IMPORT
  #if __GNUC__ >= 4
    #define LYRA_LIB_PUBLIC __attribute__ ((visibility("default")))
    #define LYRA_LIB_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define LYRA_LIB_PUBLIC
    #define LYRA_LIB_LOCAL
  #endif
  #define LYRA_LIB_PUBLIC_TYPE
#endif

#endif  // LYRA_LIB__VISIBILITY_CONTROL_H_
