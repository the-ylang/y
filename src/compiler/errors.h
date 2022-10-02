#ifndef __ERRORS_H__
#define __ERRORS_H__

#include <iostream>
#include <string>

namespace Y {
    namespace exceptions {
        namespace naming {
            // Exception called when a name is not valid because it is a keyword
            class InvalidNameKeyword : public std::exception
            {
                std::string m_msg;
            public:
                InvalidNameKeyword(const std::string name);
                virtual const char* what() const throw();
            };
        }
        namespace allocation {
            // Exception called when a number has an invalid litteral
            class InvalidNumberLitteral : public std::exception
            {
                std::string m_msg;
            public:
                InvalidNumberLitteral(const std::string num_buffer);
                virtual const char* what() const throw();
            };

            // Exception called when a boolean has a value that is not 0 or 1
            class InvalidBooleanValue : public std::exception
            {
                std::string m_msg;
            public:
                InvalidBooleanValue(const std::string num_buffer);
                virtual const char* what() const throw();
            };

            // Exception called when an integer is too big
            class IntegerOverflow : public std::exception
            {
                std::string m_msg;
            public:
                IntegerOverflow(const std::string value);
                virtual const char* what() const throw();
            };

            // Exception called when double is too big
            class DoubleOverflow : public std::exception
            {
                std::string m_msg;
            public:
                DoubleOverflow(const std::string value);
                virtual const char* what() const throw();
            };

            // Exception called when byte is too big
            class ByteOverflow : public std::exception
            {
                std::string m_msg;
            public:
                ByteOverflow(const std::string value);
                virtual const char* what() const throw();
            };

            // Exception called when char is too big
            class CharOverflow : public std::exception
            {
                std::string m_msg;
            public:
                CharOverflow(const std::string value);
                virtual const char* what() const throw();
            };

            // Exception called when there is a failure with the unallocation system
            class AllocationFatalError : public std::exception
            {
                std::string m_msg;
            public:
                AllocationFatalError();
                virtual const char* what() const throw();
            };
        }
    }
}

#endif // __ERRORS_H__