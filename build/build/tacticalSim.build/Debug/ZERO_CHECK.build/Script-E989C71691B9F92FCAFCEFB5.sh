#!/bin/sh
set -e
if test "$CONFIGURATION" = "Debug"; then :
  cd /Users/admin/Documents/tacticalSim/build
  make -f /Users/admin/Documents/tacticalSim/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "Release"; then :
  cd /Users/admin/Documents/tacticalSim/build
  make -f /Users/admin/Documents/tacticalSim/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "MinSizeRel"; then :
  cd /Users/admin/Documents/tacticalSim/build
  make -f /Users/admin/Documents/tacticalSim/build/CMakeScripts/ReRunCMake.make
fi
if test "$CONFIGURATION" = "RelWithDebInfo"; then :
  cd /Users/admin/Documents/tacticalSim/build
  make -f /Users/admin/Documents/tacticalSim/build/CMakeScripts/ReRunCMake.make
fi

