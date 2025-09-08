#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild
  make -f /Users/admin/Documents/tacticalSim/build/_deps/raylib_prebuilt-subbuild/CMakeScripts/ReRunCMake.make
fi

