#           __        _
#  ________/ /  ___ _(_)__  ___
# / __/ __/ _ \/ _ `/ / _ \/ -_)
# \__/\__/_//_/\_,_/_/_//_/\__/
# 
# Copyright (C) Clément Chain
# This file is part of ECAP5-DWBMMSC <https://github.com/ecap5/ECAP5-DWBMMSC>
# 
# ECAP5-DWBMMSC is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
# 
# ECAP5-DWBMMSC is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with ECAP5-DWBMMSC.  If not, see <http://www.gnu.org/licenses/>.

# Bench parent directory
set(BENCH_DIR ${CMAKE_CURRENT_SOURCE_DIR}/benches/)
# C++ bench include directory
set(TEST_INCLUDE_DIRS ${ecap5_ecap5_dtestlib_SOURCE_DIR}/include)
# Bench CSV output directory
set(TESTDATA_DIR ${CMAKE_CURRENT_BINARY_DIR}/)

# Lint
add_lint_target(
  TARGET lint
  LIB    ecap5_dwbmmsc
)

# Add testbenches
add_testbench(
  MODULE            ecap5_dwbmmsc
  LIBS              ecap5_dwbmmsc
  BENCH_DIR         ${BENCH_DIR}
  TESTDATA_DIR      ${TESTDATA_DIR}
  TEST_INCLUDE_DIRS ${TEST_INCLUDE_DIRS}
)

# Main targets
add_custom_target(build DEPENDS ${TEST_BINARIES})
add_custom_target(tests DEPENDS ${TEST_TARGETS})
