# Distributed under the OSI-approved BSD 3-Clause License.  See accompanying
# file LICENSE.rst or https://cmake.org/licensing for details.

cmake_minimum_required(VERSION ${CMAKE_VERSION}) # this file comes with cmake

# If CMAKE_DISABLE_SOURCE_CHANGES is set to true and the source directory is an
# existing directory in our source tree, calling file(MAKE_DIRECTORY) on it
# would cause a fatal error, even though it would be a no-op.
if(NOT EXISTS "/Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-src")
  file(MAKE_DIRECTORY "/Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-src")
endif()
file(MAKE_DIRECTORY
  "/Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-build"
  "/Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix"
  "/Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/tmp"
  "/Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/src/raylib_prebuilt-populate-stamp"
  "/Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/src"
  "/Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/src/raylib_prebuilt-populate-stamp"
)

set(configSubDirs Debug)
foreach(subDir IN LISTS configSubDirs)
    file(MAKE_DIRECTORY "/Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/src/raylib_prebuilt-populate-stamp/${subDir}")
endforeach()
if(cfgdir)
  file(MAKE_DIRECTORY "/Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/src/raylib_prebuilt-populate-stamp${cfgdir}") # cfgdir has leading slash
endif()
