/*
 > Code by Icy
 > Y Lang Project
 > Github : https://github.com/the-ylang/y
 > Errors Gestion System
*/

#include <iostream>
#include <string>

namespace Y {
	namespace exceptions {
		class Exception {
		private:
			std::string message;
			int action;
			/*
			0 -> Note
			1 -> Warning
			2 -> Error
			3 -> Fatal Error
			*/
		protected:
			void GetError() {
				/*
				 TODO : Add a log system
				 TODO : Add errors gestion (exit, continue, etc...)
				 TODO : Add line numbers
				*/
				if(this->action == 0) {
					std::cout << "Note " << " : " << this->message << std::endl;
				} else if(this->action == 1) {
					std::cout << "Warning " << " : " << this->message << std::endl;
				} else if(this->action == 2) {
					std::cout << "Error " << " : " << this->message << std::endl;
				} else if(this->action == 3) {
					std::cout << "Fatal Error " << " : " << this->message << std::endl;
				}
			}
		
		public:
			Exception(std::string message, int type) {
				this->message = message;
				this->action = type;
				GetError();
			}
		};

		namespace allocation {
			class InvalidNumberLitteral : public Exception {
			public:
				InvalidNumberLitteral(std::string num_buffer) : Exception("The number " + num_buffer + " has an invalid litteral", 2) {}
			};

			class InvalidBooleanValue : public Exception {
			public:
				InvalidBooleanValue(std::string buffer) : Exception("The boolean " + buffer + " has an invalid value", 2) {}
			};

			class IntegerOverflow : public Exception {
			public:
				IntegerOverflow(std::string value) : Exception("The value " + value + " is too big to be stored as an integer (8 bytes)", 2) {}
			};

			class DoubleOverflow : public Exception {
			public:
				DoubleOverflow(std::string value) : Exception("The value " + value + " is too big to be stored as a double (12 bytes)", 2) {}
			};

			class ByteOverflow : public Exception {
			public:
				ByteOverflow(std::string value) : Exception("The value " + value + " is too big to be stored as a byte (1 byte)", 2) {}
			};

			class CharOverflow : public Exception {
			public:
				CharOverflow(std::string value) : Exception("The value " + value + " is too big to be stored as a char (length 1)", 2) {}
			};

			class AllocationFatalError : public Exception {
			public:
				AllocationFatalError() : Exception("Allocation system failure", 3) {}
			};
		}
	}
}

int main() {
	Y::exceptions::allocation::InvalidNumberLitteral("test");
	Y::exceptions::allocation::InvalidBooleanValue("test");
	Y::exceptions::allocation::IntegerOverflow("test");
	Y::exceptions::allocation::DoubleOverflow("test");
	Y::exceptions::allocation::ByteOverflow("test");
	Y::exceptions::allocation::CharOverflow("test");
	Y::exceptions::allocation::AllocationFatalError();
	std::cout << "a" << std::endl;

	return 0;
}