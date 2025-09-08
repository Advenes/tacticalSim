#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-build
  /usr/local/bin/cmake -E echo_append
  /usr/local/bin/cmake -E touch /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/src/raylib_prebuilt-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/raylib_prebuilt-populate-build
fi

