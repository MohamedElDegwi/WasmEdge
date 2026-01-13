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
