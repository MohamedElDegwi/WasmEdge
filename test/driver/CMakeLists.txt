# SPDX-License-Identifier: Apache-2.0
# SPDX-FileCopyrightText: 2019-2024 Second State INC

wasmedge_add_executable(wasmedgeSubCommandsTests
  validate.cpp
)

add_test(wasmedgeSubCommandsTests wasmedgeSubCommandsTests)
target_link_libraries(wasmedgeSubCommandsTests
  PRIVATE
  wasmedgeDriver
  ${GTEST_BOTH_LIBRARIES}
)

target_include_directories(wasmedgeSubCommandsTests
  PRIVATE
  ${PROJECT_SOURCE_DIR}/include
)
