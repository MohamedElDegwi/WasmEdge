#include "driver/validate.h"
#include "common/configure.h"
#include "common/filesystem.h"
#include "loader/loader.h"
#include "po/option.h"
#include "validator/validator.h"
#include <iostream>

namespace WasmEdge {
namespace Driver {

void DriverValidateOptions::add_option(PO::ArgumentParser &Parser) noexcept {

  Parser.add_option("wasm-file", WasmName);

  Parser.add_option("args", Args);
}

int Validator(struct DriverValidateOptions &Opt) noexcept {
  std::cout << "running validation on: " << Opt.WasmName.value()
            << " let's see what's gonna happen!" << std::endl;

  Configure Conf;
  Loader::Loader WasmLoader(Conf);
  Validator::Validator WasmValidator(Conf);

  std::vector<Byte> Data;

  if (auto Res = WasmLoader.loadFile(Opt.WasmName.value())) {
    Data = *Res;
  } else {
    std::cerr << "check on your file it's not found or maybe inaccessible."
              << std::endl;
    return 1;
  }

  auto Module = std::make_unique<AST::Module>();
  if (auto Res = WasmLoader.parseModule(Data)) {
    Module = std::move(*Res);
    std::cout << "parsing successfull. good till now :)" << std::endl;
  } else {
    std::cerr << "check on file content. thats not pure web asm" << std::endl;
    return 1;
  }

  if (auto Res = WasmValidator.validate(*Module)) {
    std::cout << "Congratulations! Validation is successfull :) " << std::endl;
  } else {
    std::cerr << "validation went wrong :(" << std::endl;
    return 1;
  }

  return 0;
}

} // namespace Driver
} // namespace WasmEdge
