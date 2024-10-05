#!/bin/bash
cd builddir || exit $?
meson compile -C meson-src || exit $?
./meson-src/app || exit $?