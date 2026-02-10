// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2024 Second State INC

#include "driver/validate.h"
#include "common/configure.h"
#include "common/filesystem.h"
#include "loader/loader.h"
#include "po/option.h"
#include "validator/validator.h"
#include <iostream>

namespace WasmEdge {
namespace Driver {

using namespace std::literals;

int Validator(struct DriverValidateOptions &Opt) noexcept {
  spdlog::info("Starting validation on : {}"sv, Opt.WasmName.value());

  // using default configure for now, but this should be changed in week 4 when
  // configs args and other options are available.
  Configure Conf;
  Loader::Loader WasmLoader(Conf);
  Validator::Validator WasmValidator(Conf);

  std::vector<Byte> Data;

  if (auto Res = WasmLoader.loadFile(Opt.WasmName.value())) {
    Data = *Res;
  } else {
    spdlog::error("Load failed. Error code: {}"sv,
                  static_cast<uint32_t>(Res.error()));
    return 1;
  }

  auto Module = std::make_unique<AST::Module>();
  if (auto Res = WasmLoader.parseModule(Data)) {
    Module = std::move(*Res);
    spdlog::info(
        "File content check passed. Successfully parsed the module."sv);
  } else {
    spdlog::error("Parsing failed. Error code: {}"sv,
                  static_cast<uint32_t>(Res.error()));
    return 1;
  }

  if (auto Res = WasmValidator.validate(*Module)) {
    spdlog::info("Validation passed. The module is valid."sv);
  } else {
    spdlog::error("Validation failed. Error code: {}"sv,
                  static_cast<uint32_t>(Res.error()));
    return 1;
  }

  return 0;
}

} // namespace Driver
} // namespace WasmEdge
