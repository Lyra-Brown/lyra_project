#ifndef ARAMR_LIB__VISIBILITY_CONTROL_H_
#define ARAMR_LIB__VISIBILITY_CONTROL_H_

// This logic was borrowed (then namespaced) from the examples on the gcc wiki:
//     https://gcc.gnu.org/wiki/Visibility

#if defined _WIN32 || defined __CYGWIN__
  #ifdef __GNUC__
    #define ARAMR_LIB_EXPORT __attribute__ ((dllexport))
    #define ARAMR_LIB_IMPORT __attribute__ ((dllimport))
  #else
    #define ARAMR_LIB_EXPORT __declspec(dllexport)
    #define ARAMR_LIB_IMPORT __declspec(dllimport)
  #endif
  #ifdef ARAMR_LIB_BUILDING_LIBRARY
    #define ARAMR_LIB_PUBLIC ARAMR_LIB_EXPORT
  #else
    #define ARAMR_LIB_PUBLIC ARAMR_LIB_IMPORT
  #endif
  #define ARAMR_LIB_PUBLIC_TYPE ARAMR_LIB_PUBLIC
  #define ARAMR_LIB_LOCAL
#else
  #define ARAMR_LIB_EXPORT __attribute__ ((visibility("default")))
  #define ARAMR_LIB_IMPORT
  #if __GNUC__ >= 4
    #define ARAMR_LIB_PUBLIC __attribute__ ((visibility("default")))
    #define ARAMR_LIB_LOCAL  __attribute__ ((visibility("hidden")))
  #else
    #define ARAMR_LIB_PUBLIC
    #define ARAMR_LIB_LOCAL
  #endif
  #define ARAMR_LIB_PUBLIC_TYPE
#endif

#endif  // ARAMR_LIB__VISIBILITY_CONTROL_H_
