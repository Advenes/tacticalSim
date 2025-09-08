#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild
  /usr/local/bin/cmake -E make_directory /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/CMakeFiles/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME
  /usr/local/bin/cmake -E touch /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/CMakeFiles/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/raylib_prebuilt-populate-complete
  /usr/local/bin/cmake -E touch /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/src/raylib_prebuilt-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/raylib_prebuilt-populate-done
fi

