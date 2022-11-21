#include <iostream>

#include "errors.hpp"

// General

void Y::outputs::Output::Show(Y::outputs::OUT outpt, std::string type) {
  std::cout << type << " : [" << outpt.line << "] " << outpt.message << " at : "
            << outpt.line[outpt.start_to_end[0], outpt.start_to_end[1]]
            << std::endl;
}

// Errors

Y::outputs::errors::Error::Error(int level) { error_level = level; }

Y::outputs::errors::SyntaxError::SyntaxError(std::string line, int line_number, int start_to_end[2], int error_level) : Error(error_level) {
  	Show(
      	{
			"Invalid syntax",
			line,
			line_number,
			*start_to_end
	  	},
	  	"SyntaxError"
	);
}

Y::outputs::errors::InvalidLitteralError::InvalidLitteralError(std::string line, int line_number, int start_to_end[2], int error_level) : Error(error_level) {
  	Show(
      	{
	        "Invalid litteral",
		  	line,
	        line_number,
	        *start_to_end
	  	},
		"InvalidLitteralError"
  	);
}

// Warnings

Y::outputs::warnings::Warning::Warning(int level) { warn_level = level; }

Y::outputs::warnings::UnusedValueWarning::UnusedValueWarning(std::string line, int line_number, int start_to_end[2], int warn_level) : Warning(warn_level) {
	Show(
	  	{
			"Value declared but never used",
			line,
			line_number,
			*start_to_end
	  	},
	  	"UnusedValueWarning"
  	);
}

// Informations

Y::outputs::informations::Information::Information() {}

Y::outputs::informations::UnusedFileImport::UnusedFileImport(std::string line, int line_number, int start_to_end[2]) {
	Show(
		{
			"File imported but never used",
			line,
			line_number,
			*start_to_end
		},
		"UnusedFileImport"
	);
}