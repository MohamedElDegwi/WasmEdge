// SPDX-License-Identifier: Apache-2.0
// SPDX-FileCopyrightText: 2019-2024 Second State INC

//===-- wasmedge/driver/validate.h - Validate entrypoint ------------------===//
//
// Part of the WasmEdge Project.
//
//===----------------------------------------------------------------------===//
///
/// \file
/// This file contents the entrypoint for the validate executable.
///
//===----------------------------------------------------------------------===//
#pragma once
#include "po/argument_parser.h"
#include <string_view>

namespace WasmEdge {
namespace Driver {

using namespace std::literals;

struct DriverValidateOptions {
  DriverValidateOptions()
      : WasmName(PO::Description("Wasm file"sv), PO::MetaVar("WASM"sv)),

        // this should not be one argument rather than a list of arguments
        // according to the supported args in the c api, but for the sake of
        // simplicity and poc purpose i will just use one argument to represent
        // all the arguments passed to the module, and this should be changed in
        // week 4 when fully implementing this file in the mentorship.
        Args(PO::Description("Arguments passed to the module"sv),
             PO::MetaVar("ARG"sv)) {}

  PO::Option<std::string> WasmName;
  PO::List<std::string> Args;

  void add_option(PO::ArgumentParser &Parser) noexcept {
    Parser.add_option("wasm-file", WasmName).add_option("args", Args);
  }
};

int Validator(struct DriverValidateOptions &Opt) noexcept;

} // namespace Driver
} // namespace WasmEdge
