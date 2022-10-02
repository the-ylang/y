#include "errors.h"

#include <iostream>
#include <string>

namespace Y {
    namespace exceptions {
        namespace naming {
            InvalidNameKeyword::InvalidNameKeyword(const std::string name)
                : m_msg("The name " + name + " is not valid because it is a keyword")
            {}

            const char* InvalidNameKeyword::what() const throw() {
                return m_msg.c_str();
            }
        }
        namespace allocation {
            InvalidNumberLitteral::InvalidNumberLitteral(const std::string num_buffer)
                : m_msg("The number " + num_buffer + " has an invalid litteral")
            {}

            const char* InvalidNumberLitteral::what() const throw() {
                return m_msg.c_str();
            }

            InvalidBooleanValue::InvalidBooleanValue(const std::string num_buffer)
                : m_msg("The boolean " + num_buffer + " has an invalid value")
            {}

            const char* InvalidBooleanValue::what() const throw() {
                return m_msg.c_str();
            }

            IntegerOverflow::IntegerOverflow(const std::string value)
                : m_msg("The value " + value + " is too big to be stored as an integer (8 bytes)")
            {}

            const char* IntegerOverflow::what() const throw() {
                return m_msg.c_str();
            }
            
            DoubleOverflow::DoubleOverflow(const std::string value)
                : m_msg("The value " + value + " is too big to be stored as a double (12 bytes)")
            {}

            const char* DoubleOverflow::what() const throw() {
                return m_msg.c_str();
            }

            ByteOverflow::ByteOverflow(const std::string value)
                : m_msg("The value " + value + " is too big to be stored as a byte (1 byte)")
            {}

            const char* ByteOverflow::what() const throw() {
                return m_msg.c_str();
            }

            CharOverflow::CharOverflow(const std::string value)
                : m_msg("The value " + value + " is too big to be stored as a char (length 1)")
            {}

            const char* CharOverflow::what() const throw() {
                return m_msg.c_str();
            }

            AllocationFatalError::AllocationFatalError()
                : m_msg("Fatal error with the allocation system")
            {}

            const char* AllocationFatalError::what() const throw() {
                return m_msg.c_str();
            }
        }
    }
}