# - Try to find FFTW3
# Once done, this will define
#
#  FFTW3_FOUND - system has FFTW3
#  FFTW3_INCLUDE_DIRS - the FFTW3 include directories
#  FFTW3_LIBRARIES - link these to use FFTW3

include(LibFindMacros.cmake)

# Dependencies
#libfind_package(FFTW3)

# Use pkg-config to get hints about paths
libfind_pkg_check_modules(FFTW3_PKGCONF FFTW3)

# Include dir
find_path(FFTW3_INCLUDE_DIR
  NAMES fftw3.h
  PATHS ${FFTW3_PKGCONF_INCLUDE_DIRS}
)

# Finally the library itself
find_library(FFTW3_LIBRARY
  NAMES fftw3
  PATHS ${FFTW3_PKGCONF_LIBRARY_DIRS}
)

find_library(FFTW3F_LIBRARY
  NAMES fftw3f
  PATHS ${FFTW3_PKGCONF_LIBRARY_DIRS}
)

# Set the include dir variables and the libraries and let libfind_process do the rest.
# NOTE: Singular variables for this library, plural for libraries this this lib depends on.
set(FFTW3_PROCESS_INCLUDES FFTW3_INCLUDE_DIR)
set(FFTW3_PROCESS_LIBS FFTW3_LIBRARY FFTW3F_LIBRARY)
libfind_process(FFTW3)
