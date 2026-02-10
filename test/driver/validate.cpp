// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2024 Second State INC

//===-- wasmedge/test/driver/validate.cpp - Validate CLI tests --===//
//
// Part of the WasmEdge Project.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contains tests for the WasmEdge CLI validate subcommand.
///
//===----------------------------------------------------------------------===//

#include "driver/validate.h"
#include "common/configure.h"
#include "common/filesystem.h"

#include <gtest/gtest.h>

#include <fstream>
#include <vector>

namespace {

using namespace WasmEdge;
using namespace std::literals;

// create a minimal valid wasm module
std::filesystem::path createValidWasmFile() {
  auto TempPath = std::filesystem::temp_directory_path() / "valid_test.wasm";
  std::ofstream Ofs(TempPath, std::ios::binary);
  const unsigned char ValidWasm[] = {0x00, 0x61, 0x73, 0x6D,
                                     0x01, 0x00, 0x00, 0x00};
  Ofs.write(reinterpret_cast<const char *>(ValidWasm), sizeof(ValidWasm));
  Ofs.close();
  return TempPath;
}

// Please note those tests kept minimal for the poc purpose.
// More tests should be added in week 4 when fully implementing the validate.

TEST(ValidateTest, ValidModule) {
  auto WasmPath = createValidWasmFile();

  Driver::DriverValidateOptions Opt;
  Opt.WasmName.value() = WasmPath.string();

  int Result = Driver::Validator(Opt);
  EXPECT_EQ(Result, 0) << "should pass validation";

  std::filesystem::remove(WasmPath);
}

TEST(ValidateTest, NonExistFile) {
  Driver::DriverValidateOptions Opt;
  Opt.WasmName.value() = "/non/existent/path/to/file.wasm";

  int Result = Driver::Validator(Opt);
  EXPECT_NE(Result, 0) << "should fail validation";
}

} // namespace
