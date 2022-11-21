#include <iostream>
#include <string>

#ifndef __ERRORS_HPP__
	#define __ERRORS_HPP__

	namespace Y {
		namespace outputs {
			struct OUT {
				std::string message;
				std::string line;
				int line_number;
				int start_to_end[2];
			};
			class Output {
			public:
				Output();
				void Show(OUT outpt, std::string type);
			};
			namespace errors {
				class Error : public Output {
				private:
					int error_level;
				public:
					Error(int level);
				};
				class SyntaxError : public Error {
				public:
					SyntaxError(
						std::string line,
						int line_number,
						int start_to_end[2],
						int error_level
					);
				};
				class InvalidLitteralError : public Error {
				public:
					InvalidLitteralError(
						std::string line,
						int line_number,
						int start_to_end[2],
						int error_level
					);
				};
			}
			namespace warnings {
				class Warning : public Output {
				private:
					int warn_level;
				public:
					Warning(int level);
				};
				class UnusedValueWarning : public Warning {
					UnusedValueWarning(
						std::string line,
						int line_number,
						int start_to_end[2],
						int warn_level
					);
				};
			}
			namespace informations {
				class Information : public Output {
				public:
					Information();
				};
				class UnusedFileImport : public Information {
					UnusedFileImport(
						std::string line,
						int line_number,
						int start_to_end[2]
					);
				};
			}
		}
	}
#endif