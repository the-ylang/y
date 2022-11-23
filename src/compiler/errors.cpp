#include <iostream>

#include "errors.hpp"

// General

Y::outputs::Output::Output() { return; }

void Y::outputs::Output::Show(Y::outputs::OUT outpt, std::string type) {
  std::cout << type << " : [" << outpt.line_number << "] " << outpt.message
            << " at : "
            << outpt.line.substr(outpt.start_to_end[0], outpt.start_to_end[1] - outpt.start_to_end[0])
            << std::endl;
}

// Errors

Y::outputs::errors::Error::Error(int level) : Output() { error_level = level; }

Y::outputs::errors::SyntaxError::SyntaxError(std::string line, int line_number,
                                             int start_to_end[2],
                                             int error_level)
    : Error(error_level) {
  Show({"Invalid syntax", line, line_number, *start_to_end}, "SyntaxError");
}

Y::outputs::errors::InvalidLitteralError::InvalidLitteralError(
    std::string line, int line_number, int start_to_end[2], int error_level)
    : Error(error_level) {
  Show({"Invalid litteral", line, line_number, *start_to_end},
       "InvalidLitteralError");
}

// Warnings

Y::outputs::warnings::Warning::Warning(int level) : Output() {
  warn_level = level;
}

Y::outputs::warnings::UnusedValueWarning::UnusedValueWarning(
    std::string line, int line_number, int start_to_end[2], int warn_level)
    : Warning(warn_level) {
  Show({"Value declared but never used", line, line_number, *start_to_end},
       "UnusedValueWarning");
}

// Informations

Y::outputs::informations::Information::Information() : Output() {}

Y::outputs::informations::UnusedFileImport::UnusedFileImport(
    std::string line, int line_number, int start_to_end[2]) {
  Show({"File imported but never used", line, line_number, *start_to_end},
       "UnusedFileImport");
}