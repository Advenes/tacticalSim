#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/admin/Documents/tacticalSim/build/_deps
  /usr/local/bin/cmake -DCMAKE_MESSAGE_LOG_LEVEL=VERBOSE -P /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/src/raylib_prebuilt-populate-stamp/download-raylib_prebuilt-populate.cmake
  /usr/local/bin/cmake -DCMAKE_MESSAGE_LOG_LEVEL=VERBOSE -P /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/src/raylib_prebuilt-populate-stamp/verify-raylib_prebuilt-populate.cmake
  /usr/local/bin/cmake -DCMAKE_MESSAGE_LOG_LEVEL=VERBOSE -P /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/src/raylib_prebuilt-populate-stamp/extract-raylib_prebuilt-populate.cmake
  /usr/local/bin/cmake -E touch /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/raylib_prebuilt-populate-prefix/src/raylib_prebuilt-populate-stamp/$CONFIGURATION$EFFECTIVE_PLATFORM_NAME/raylib_prebuilt-populate-download
fi

