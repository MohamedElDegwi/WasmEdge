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

namespace WasmEdge {
namespace Driver {

struct DriverValidateOptions {
  WasmEdge::PO::Option<std::string> WasmName{
      WasmEdge::PO::Description("the wasm file to validate")};

  WasmEdge::PO::List<std::string> Args{
      WasmEdge::PO::Description("arguments for the wasm file")};

  void add_option(PO::ArgumentParser &Parser) noexcept;
};

int Validator(struct DriverValidateOptions &Opt) noexcept;

} // namespace Driver
} // namespace WasmEdge
