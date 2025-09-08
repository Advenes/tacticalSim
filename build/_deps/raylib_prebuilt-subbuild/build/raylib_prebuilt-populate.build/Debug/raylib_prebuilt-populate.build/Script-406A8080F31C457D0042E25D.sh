#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild
  /usr/local/bin/cmake -Dcfgdir=/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME -P /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/tmp/raylib_prebuilt-populate-mkdirs.cmake
  /usr/local/bin/cmake -E touch /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/src/raylib_prebuilt-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/raylib_prebuilt-populate-mkdir
fi

