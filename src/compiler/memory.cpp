/*
 > Code by Icy
 > Y Lang Project
 > Github : https://github.com/the-ylang/y
 > Memory Manager
*/

#include "errors.h"

#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <variant>


namespace Y {
    /*class MemoryManager {
    private:
        std::map<std::string, std::variant<data_types::Int*, data_types::Double*, data_types::Byte*, data_types::Char*, data_types::Bool*, data_types::Str*, data_types::Undefined*>> memory;
    public:
        MemoryManager() {
            memory = std::map<std::string, std::variant<data_types::Int*, data_types::Double*, data_types::Byte*, data_types::Char*, data_types::Bool*, data_types::Str*, data_types::Undefined*>>();
        }
        void Add(std::string name, std::variant<data_types::Int*, data_types::Double*, data_types::Byte*, data_types::Char*, data_types::Bool*, data_types::Str*, data_types::Undefined*> value) {
            memory[name] = value;
        }
        void Remove(std::string name) {
            memory.erase(name);
        }
        std::variant<data_types::Int*, data_types::Double*, data_types::Byte*, data_types::Char*, data_types::Bool*, data_types::Str*, data_types::Undefined*> Get(std::string name) {
            return memory[name];
        }
    };*/

    namespace data_types {
        class DataType {
        protected:
            std::string data_value;
            bool is_const;
            bool is_ptr;
        public:
            DataType(std::string value, bool is_constant, bool is_pointer) {
                data_value = value;
                is_const = is_constant;
                is_ptr = is_pointer;
            }
        };

        class Int : public DataType {
            std::variant<int*, long int*, long long int*> val;
        public:
            std::variant<int*, long int*, long long int*> a() {
                return val;
            } 
            Int(std::string value, bool is_constant, bool is_pointer) : DataType(value, is_constant, is_pointer) {
                try {
                    val = new int(std::stoi(value));
                }
                catch (...) {
                    try {
                        val = new long int(std::stol(value));
                    }
                    catch (...) {
                        try {
                            val = new long long int(std::stoll(value));
                        }
                        catch (std::range_error) {
                            throw exceptions::allocation::IntegerOverflow(value);
                        }
                        catch (...) {
                            throw exceptions::allocation::InvalidNumberLitteral(value);
                        }
                    }
                }
                is_const = is_constant;
                is_ptr = is_pointer;
            }
            Int(Int &obj) : DataType(obj.data_value, obj.is_const, obj.is_ptr) {
                val = new int(std::stoi(obj.data_value));
                is_const = obj.is_const;
                is_ptr = obj.is_ptr;
            }
            ~Int() {
                try {
                    delete std::get<int*>(val);
                }
                catch (std::bad_variant_access) {
                    try {
                        delete std::get<long int*>(val);
                    }
                    catch (std::bad_variant_access) {
                        try {
                            delete std::get<long long int*>(val);
                        }
                        catch (std::bad_variant_access) {
                            throw exceptions::allocation::AllocationFatalError();
                        }
                    }
                };
            }
        };

        class Double : public DataType {
            std::variant<double*, long double*> val;
            bool is_const;
            bool is_ptr;
        public:
            Double(std::string value, bool is_constant, bool is_pointer) : DataType(value, is_constant, is_pointer) {
                try {
                    val = new double(std::stoi(value));
                }
                catch (...) {
                    try {
                        val = new long double(std::stol(value));
                    }
                    catch (std::range_error) {
                        throw exceptions::allocation::DoubleOverflow(value);
                    }
                    catch (...) {
                        throw exceptions::allocation::InvalidNumberLitteral(value);
                    }
                }
                is_const = is_constant;
                is_ptr = is_pointer;
            }
            Double(Double &obj) : DataType(obj.data_value, obj.is_const, obj.is_ptr) {
                val = new double(std::stoi(obj.data_value));
                is_const = obj.is_const;
                is_ptr = obj.is_ptr;
            }
            ~Double() {
                try {
                    delete std::get<double*>(val);
                }
                catch (std::bad_variant_access) {
                    try {
                        delete std::get<long double*>(val);
                    }
                    catch (std::bad_variant_access) {
                        throw exceptions::allocation::AllocationFatalError();
                    }
                };
            }
        };

        class Byte : public DataType {
            int* val;
            bool is_const;
            bool is_ptr;
        public:
            Byte(std::string value, bool is_constant, bool is_pointer) : DataType(value, is_constant, is_pointer) {
                int* temp = new int(std::stoi(value));
                if (*temp > 255) {
                    delete(temp);
                    throw exceptions::allocation::ByteOverflow(value);
                }
                else {
                    val = temp;
                }
                is_const = is_constant;
                is_ptr = is_pointer;
            }
            Byte(Byte &obj) : DataType(obj.data_value, obj.is_const, obj.is_ptr) {
                int* val = new int(std::stoi(obj.data_value));
                is_const = obj.is_const;
                is_ptr = obj.is_ptr;
            }
            ~Byte() {
                try {
                    delete val;
                } catch (...) {
                    throw exceptions::allocation::AllocationFatalError();
                }
            }
        };

        class Char : public DataType {
            char* val;
            bool is_const;
            bool is_ptr;
        public:
            Char(std::string value, bool is_constant, bool is_pointer) : DataType(value, is_constant, is_pointer) {
                if(value.length() > 1) {
                    throw exceptions::allocation::CharOverflow(value);
                }
                else {
                    val = new char(value[0]);
                }
                is_const = is_constant;
                is_ptr = is_pointer;
            }
            Char(Char &obj) : DataType(obj.data_value, obj.is_const, obj.is_ptr) {
                val = new char(obj.data_value[0]);
                is_const = obj.is_const;
                is_ptr = obj.is_ptr;
            }
            ~Char() {
                try {
                    delete val;
                } catch (...) {
                    throw exceptions::allocation::AllocationFatalError();
                }
            }
        };

        class Bool : public DataType {
            bool* val;
            bool is_const;
            bool is_ptr;
        public:
            Bool(std::string value, bool is_constant, bool is_pointer) : DataType(value, is_constant, is_pointer) {
                if(value == "true" || value == "1") {
                    val = new bool(true);
                }
                else if(value == "false" || value == "0") {
                    val = new bool(false);
                }
                else {
                    throw exceptions::allocation::InvalidBooleanValue(value);
                }
                is_const = is_constant;
                is_ptr = is_pointer;
            }
            Bool(Bool &obj) : DataType(obj.data_value, obj.is_const, obj.is_ptr) {
                if(obj.data_value == "true" || obj.data_value == "1") {
                    val = new bool(true);
                }
                else {
                    val = new bool(false);
                }
                is_const = obj.is_const;
                is_ptr = obj.is_ptr;
            }
            ~Bool() {
                try {
                    delete val;
                } catch (...) {
                    throw exceptions::allocation::AllocationFatalError();
                }
            }
        };
        class Str : public DataType {
            std::string* val;
            bool is_const;
            bool is_ptr;
        public:
            Str(std::string value, bool is_constant, bool is_pointer) : DataType(value, is_constant, is_pointer) {
                val = new std::string(value);
                is_const = is_constant;
                is_ptr = is_pointer;
            }
            Str(Str &obj) : DataType(obj.data_value, obj.is_const, obj.is_ptr) {
                val = new std::string(obj.data_value);
                is_const = obj.is_const;
                is_ptr = obj.is_ptr;
            }
            ~Str() {
                try {
                    delete val;
                } catch (...) {
                    throw exceptions::allocation::AllocationFatalError();
                }
            }
        };
        class Undefined : public DataType {
            bool is_const;
            bool is_ptr;
        public:
            Undefined(std::string value, bool is_constant, bool is_pointer) : DataType(value, is_constant, is_pointer) {
                try {
                    Bool udf = Bool(value, is_constant, is_pointer);
                } catch (exceptions::allocation::InvalidBooleanValue) {
                    try {
                        Byte udf = Byte(value, is_constant, is_pointer);
                    } catch (exceptions::allocation::ByteOverflow) {
                        try {
                            Int udf = Int(value, is_constant, is_pointer);
                        } catch (exceptions::allocation::IntegerOverflow) {
                            try {
                                Double udf = Double(value, is_constant, is_pointer);
                            } catch (exceptions::allocation::DoubleOverflow) {
                                try {
                                    Char udf = Char(value, is_constant, is_pointer);
                                } catch (exceptions::allocation::CharOverflow) {
                                    Str udf = Str(value, is_constant, is_pointer);
                                }
                            }
                        }
                    }
                }
                is_const = is_constant;
                is_ptr = is_pointer;
            }
            Undefined(Undefined &obj) : DataType(obj.data_value, obj.is_const, obj.is_ptr) {
                try {
                    Bool udf = Bool(obj.data_value, obj.is_const, obj.is_ptr);
                } catch (exceptions::allocation::InvalidBooleanValue) {
                    try {
                        Byte udf = Byte(obj.data_value, obj.is_const, obj.is_ptr);
                    } catch (exceptions::allocation::ByteOverflow) {
                        try {
                            Int udf = Int(obj.data_value, obj.is_const, obj.is_ptr);
                        } catch (exceptions::allocation::IntegerOverflow) {
                            try {
                                Double udf = Double(obj.data_value, obj.is_const, obj.is_ptr);
                            } catch (exceptions::allocation::DoubleOverflow) {
                                try {
                                    Char udf = Char(obj.data_value, obj.is_const, obj.is_ptr);
                                } catch (exceptions::allocation::CharOverflow) {
                                    Str udf = Str(obj.data_value, obj.is_const, obj.is_ptr);
                                }
                            }
                        }
                    }
                }
                is_const = obj.is_const;
                is_ptr = obj.is_ptr;
            }
            ~Undefined() {
                // Do nothing
            }
        };
    }
}

int main() {
    Y::data_types::Int a = Y::data_types::Int("fadsf", false, false);
    std::variant<int*, long int*, long long int*> temp = a.a();
    try {
        std::cout << *std::get<int*>(temp) << std::endl;
    }
    catch (std::bad_variant_access) {
        try {
            std::cout << *std::get<long int*>(temp) << std::endl;
        }
        catch (std::bad_variant_access) {
            try {
                std::cout << *std::get<long long int*>(temp) << std::endl;
            }
            catch (std::bad_variant_access) {
                std::cout << "Error" << std::endl;
            }
        }
    };
    return 0;
}