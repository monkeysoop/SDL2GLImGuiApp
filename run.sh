#!/bin/bash
cd builddir
meson compile -C meson-src
valgrind ./meson-src/app