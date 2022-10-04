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
    namespace memory {
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
                bool is_const;
                bool is_ptr;
            public:
                Int(std::string value, bool is_constant, bool is_pointer) : DataType(value, is_constant, is_pointer) {
                    try {
                        val = new int(std::stoi(value));
                        if(std::to_string(*std::get<int*>(val)) != value) {
                            throw exceptions::allocation::IntegerOverflow(value); // TODO : Add new error management system AND add new error type
                            delete std::get<int*>(val);
                        }
                    }
                    catch (...) {
                        try {
                            val = new long int(std::stol(value));
                            if(std::to_string(*std::get<long int*>(val)) != value) {
                                throw exceptions::allocation::IntegerOverflow(value); // TODO : Add new error management system AND add new error type
                                delete std::get<long int*>(val);
                            }
                        }
                        catch (...) {
                            try {
                                val = new long long int(std::stoll(value));
                                if(std::to_string(*std::get<long long int*>(val)) != value) {
                                    throw exceptions::allocation::IntegerOverflow(value); // TODO : Add new error management system AND add new error type
                                    delete std::get<long long int*>(val);
                                }
                            }
                            catch (std::range_error) {
                                throw exceptions::allocation::IntegerOverflow(value); // TODO : Add new error management system
                            }
                            catch (...) {
                                throw exceptions::allocation::InvalidNumberLitteral(value); // TODO : Add new error management system
                            }
                        }
                    }
                    is_const = is_constant;
                    is_ptr = is_pointer;
                }
                // TODO : Update stoi to all others
                Int(Int &obj) : DataType(obj.data_value, obj.is_const, obj.is_ptr) {
                    val = new int(std::stoi(obj.data_value));
                    is_const = obj.is_const;
                    is_ptr = obj.is_ptr;
                }
                std::variant<int*, long int*, long long int*> GetValue() {
                    return val;
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
                                throw exceptions::allocation::AllocationFatalError(); // TODO : Add new error management system
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
                        val = new double(std::stod(value));
                    }
                    catch (...) {
                        try {
                            val = new long double(std::stold(value));
                        }
                        catch (std::range_error) {
                            throw exceptions::allocation::DoubleOverflow(value); // TODO : Add new error management system
                        }
                        catch (...) {
                            throw exceptions::allocation::InvalidNumberLitteral(value); // TODO : Add new error management system
                        }
                    }
                    is_const = is_constant;
                    is_ptr = is_pointer;
                }
                Double(Double &obj) : DataType(obj.data_value, obj.is_const, obj.is_ptr) {
                    try {
                        val = new double(std::stod(obj.data_value));
                    }
                    catch (...) {
                        try {
                            val = new long double(std::stold(obj.data_value));
                        }
                        catch (std::range_error) {
                            throw exceptions::allocation::DoubleOverflow(obj.data_value); // TODO : Add new error management system
                        }
                        catch (...) {
                            throw exceptions::allocation::InvalidNumberLitteral(obj.data_value); // TODO : Add new error management system
                        }
                    }
                    is_const = obj.is_const;
                    is_ptr = obj.is_ptr;
                }
                std::variant<double*, long double*> GetValue() {
                    return val;
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
                            throw exceptions::allocation::AllocationFatalError(); // TODO : Add new error management system
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
                    int* temp;
                    try {
                        temp = new int(std::stoi(value));
                    } catch (...) {
                        if(value.length() == 1) {
                            temp = new int((int)value[0]);
                        }
                        else {
                            throw exceptions::allocation::ByteOverflow(value); // TODO : Add new error management system
                        }
                    }
                    if (*temp > 255 || *temp < 0 || std::to_string(*temp) != value) {
                        delete(temp);
                        throw exceptions::allocation::ByteOverflow(value); // TODO : Add new error management system
                    }
                    else
                        val = temp;
                    is_const = is_constant;
                    is_ptr = is_pointer;
                }
                Byte(Byte &obj) : DataType(obj.data_value, obj.is_const, obj.is_ptr) {
                    try {
                        val = new int(std::stoi(obj.data_value));
                    } catch (...) {
                        if(obj.data_value.length() == 1) {
                            val = new int((int)obj.data_value[0]);
                        }
                        else {
                            throw exceptions::allocation::ByteOverflow(obj.data_value); // TODO : Add new error management system
                        }
                    }
                    is_const = obj.is_const;
                    is_ptr = obj.is_ptr;
                }
                int* GetValue() {
                    return val;
                }
                ~Byte() {
                    try {
                        delete val;
                    } catch (...) {
                        throw exceptions::allocation::AllocationFatalError(); // TODO : Add new error management system
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
                        try {
                            *val = static_cast<char>(std::stoi(value));
                        } catch (...) {
                           throw exceptions::allocation::CharOverflow(value); // TODO : Add new error management system
                        }
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
                char* GetValue() {
                    return val;
                }
                ~Char() {
                    try {
                        delete val;
                    } catch (...) {
                        throw exceptions::allocation::AllocationFatalError(); // TODO : Add new error management system
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
                        throw exceptions::allocation::InvalidBooleanValue(value); // TODO : Add new error management system
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
                bool* GetValue() {
                    return val;
                }
                ~Bool() {
                    try {
                        delete val;
                    } catch (...) {
                        throw exceptions::allocation::AllocationFatalError(); // TODO : Add new error management system
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
                std::string* GetValue() {
                    return val;
                }
                ~Str() {
                    try {
                        delete val;
                    } catch (...) {
                        throw exceptions::allocation::AllocationFatalError(); // TODO : Add new error management system
                    }
                }
            };

            // ! NOT FINISHED
            class Undefined : public DataType {
                std::string value;
                std::variant<Int*, Double*, Byte*, Char*, Bool*, Str*> val;
                bool is_const;
                bool is_ptr;

                void EndConstructor(std::string value, bool is_cst, bool is_ptr) {
                    try {
                        val = new Char(value, is_cst, is_ptr);
                    } catch (exceptions::allocation::CharOverflow) {
                        val = new Str(value, is_cst, is_ptr);
                    }
                }

            public:
                Undefined(std::string value, bool is_constant, bool is_pointer) : DataType(value, is_constant, is_pointer) {
                    try {
                        val = new Bool(value, is_constant, is_ptr);
                        std::cout << "bool" << std::endl;
                    } catch (exceptions::allocation::InvalidBooleanValue) {
                        try {
                            val = new Byte(value, is_constant, is_ptr);
                            std::cout << "byte" << std::endl;
                        } catch (exceptions::allocation::ByteOverflow) {
                            try {
                                val = new Int(value, is_constant, is_ptr);
                                std::cout << "int" << std::endl;
                            } catch (...) { // TODO : Replace with Int errors parent
                                try{
                                    val = new Double(value, is_constant, is_pointer);
                                    std::cout << "double" << std::endl;
                                } catch(exceptions::allocation::DoubleOverflow) {
                                    try {
                                        val = new Char(value, is_constant, is_pointer);
                                        std::cout << "char" << std::endl;
                                    } catch (exceptions::allocation::CharOverflow) {
                                        std::cout << "str" << std::endl;
                                        val = new Str(value, is_constant, is_pointer);
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
                            } catch (...) { // TODO : Replace with Int errors parent
                                try{
                                    val = new Double(obj.data_value, obj.is_const, obj.is_ptr);
                                    std::cout << "double" << std::endl;
                                } catch(exceptions::allocation::DoubleOverflow) {
                                    try {
                                        val = new Char(obj.data_value, obj.is_const, obj.is_ptr);
                                        std::cout << "char" << std::endl;
                                    } catch (exceptions::allocation::CharOverflow) {
                                        std::cout << "str" << std::endl;
                                        val = new Str(obj.data_value, obj.is_const, obj.is_ptr);
                                    }
                                }
                            }
                        }
                    }
                    is_const = obj.is_const;
                    is_ptr = obj.is_ptr;
                }

                std::variant<Int*, Double*, Byte*, Char*, Bool*, Str*> GetValue() {
                    return val;
                }
                
                ~Undefined() {
                    try {
                        delete std::get<Int*>(val);
                    } catch (std::bad_variant_access) {
                        try {
                            delete std::get<Double*>(val);
                        } catch (std::bad_variant_access) {
                            try {
                                delete std::get<Byte*>(val);
                            } catch (std::bad_variant_access) {
                                try {
                                    delete std::get<Char*>(val);
                                } catch (std::bad_variant_access) {
                                    try {
                                        delete std::get<Bool*>(val);
                                    } catch (std::bad_variant_access) {
                                        try {
                                            delete std::get<Str*>(val);
                                        } catch (std::bad_variant_access) {
                                            throw exceptions::allocation::AllocationFatalError(); // TODO : Add new error management system
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            };

            // ! NOT FINISHED
            class GenericType {
            private:
                std::variant<Int*, Double*, Byte*, Char*, Bool*, Str*, Undefined*> data;

            public:
                GenericType(std::variant<Int*, Double*, Byte*, Char*, Bool*, Str*, Undefined*> specific_data) {
                    data = specific_data;
                    std::cout << "Generic" << std::endl;
                }

                std::string GetIntValue(Int type) {
                    std::string rt_value;
                    std::variant<int*, long int*, long long int*> dvalue = type.GetValue();
                    try {
                        rt_value = std::to_string(*std::get<int*>(dvalue));
                    } catch (std::bad_variant_access) {
                        try {
                            rt_value = std::to_string(*std::get<long int*>(dvalue));
                        } catch (std::bad_variant_access) {
                            try{
                                rt_value = std::to_string(*std::get<long long int*>(dvalue));
                            } catch(std::bad_variant_access) {
                                std::cout << "prob" << std::endl;
                            }
                        }
                    }
                    std::cout << rt_value << std::endl;
                    return rt_value;
                }

                std::string GetDoubleValue(Double type) {
                    std::string rt_value;
                    std::variant<double*, long double*> dvalue = type.GetValue();
                    try {
                        rt_value = std::to_string(*std::get<double*>(dvalue));
                    } catch (std::bad_variant_access) {
                        rt_value = std::to_string(*std::get<long double*>(dvalue));
                    }
                    return rt_value;
                }

                std::string GetByteValue(Byte type) {
                    return std::to_string(*type.GetValue());
                }

                std::string GetCharValue(Char type) {
                    return std::to_string(*type.GetValue());
                }

                std::string GetBoolValue(Bool type) {
                    std::cout << "bool" << std::endl;
                    std::string ret_value = *type.GetValue() ? "true" : "false";
                    return ret_value;
                }

                std::string GetStrValue(Str type) {
                    return *type.GetValue();
                }

                std::string GetUndefinedValue(Undefined type) {
                    std::string rt_value;
                    std::variant<Int*, Double*, Byte*, Char*, Bool*, Str*> vl = type.GetValue();
                    std::cout << "udf" << std::endl;
                    try {
                        try {
                            std::cout << "OK0" << std::endl;
                            Int temp = *std::get<Int*>(vl);
                            rt_value = GetIntValue(temp);
                        } catch (std::bad_variant_access) {
                            try {
                                std::cout << "OK1" << std::endl;
                                Double temp = *std::get<Double*>(vl);
                                rt_value = GetDoubleValue(temp);
                            } catch (std::bad_variant_access) {
                                try {
                                    std::cout << "OK2" << std::endl;
                                    Byte temp = *std::get<Byte*>(vl);
                                    rt_value = GetByteValue(temp);
                                } catch (std::bad_variant_access) {
                                    try {
                                        std::cout << "OK3" << std::endl;
                                        Char temp = *std::get<Char*>(vl);
                                        rt_value = GetCharValue(temp);
                                    } catch (std::bad_variant_access) {
                                        try {
                                            std::cout << "OK4" << std::endl;
                                            Bool temp = *std::get<Bool*>(vl);
                                            rt_value = GetBoolValue(temp);
                                        } catch (std::bad_variant_access) {
                                            try {
                                                std::cout << "OK5" << std::endl;
                                                Str temp = *std::get<Str*>(vl);
                                                rt_value = GetStrValue(temp);
                                            } catch (std::bad_variant_access) {
                                                std::cout << "OK6" << std::endl;
                                                throw exceptions::allocation::AllocationFatalError(); // TODO : Add new error management system
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    } catch (std::bad_variant_access) {
                        throw exceptions::allocation::AllocationFatalError(); // TODO : Add new error management system
                    }

                    return rt_value;
                }

                std::string GetGenericValue() {
                    std::cout << "get" << std::endl;
                    std::string return_value;
                    try {
                        Int type = *std::get<Int*>(data);
                        return_value = GetIntValue(type);
                    } catch(std::bad_variant_access) {
                        try {
                            Double type = *std::get<Double*>(data);
                            return_value = GetDoubleValue(type);
                        } catch (std::bad_variant_access) {
                            try {
                                Byte type = *std::get<Byte*>(data);
                                return_value = GetByteValue(type);
                            } catch (std::bad_variant_access) {
                                try {
                                    Char type = *std::get<Char*>(data);
                                    return_value = GetCharValue(type);
                                } catch (std::bad_variant_access) {
                                    try {
                                        Bool type = *std::get<Bool*>(data);
                                        return_value = GetBoolValue(type);
                                    } catch (std::bad_variant_access) {
                                        try {
                                            Str type = *std::get<Str*>(data);
                                            return_value = GetStrValue(type);
                                        } catch (std::bad_variant_access) {
                                            try {
                                                Undefined type = *std::get<Undefined*>(data);
                                                return_value = GetUndefinedValue(type);
                                            } catch (std::bad_variant_access) {
                                                throw exceptions::allocation::AllocationFatalError(); // TODO : Add new error management system
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }

                    return return_value;
                }
            };
        }

        class MemoryManager {
        private:
            std::map<std::string, std::variant<data_types::Int*, data_types::Double*, data_types::Byte*, data_types::Char*, data_types::Bool*, data_types::Str*, data_types::Undefined*>> memory;
            std::map<std::string, std::string> generic_values;
        public:
            MemoryManager() {
                memory = {};
                generic_values = {};
            }
            void Add(std::string name, std::variant<data_types::Int*, data_types::Double*, data_types::Byte*, data_types::Char*, data_types::Bool*, data_types::Str*, data_types::Undefined*> value) {
                memory[name] = value;
                data_types::GenericType type = data_types::GenericType(value);
                generic_values[name] = type.GetGenericValue();
            }
            // TODO : Add an Update method
            void Remove(std::string name) {
                memory.erase(name);
                generic_values.erase(name);
            }
            std::variant<data_types::Int*, data_types::Double*, data_types::Byte*, data_types::Char*, data_types::Bool*, data_types::Str*, data_types::Undefined*> Get(std::string name) {
                return memory[name];
            }
            std::string GetValue(std::string name) {
                return generic_values[name];
            }
            ~MemoryManager() {
                delete &memory;
            }
        };
    }
}

int main() {
    // Create a memory manager
    Y::memory::MemoryManager manager = Y::memory::MemoryManager();

    // Create 2 variables
    Y::memory::data_types::Undefined datavalue = Y::memory::data_types::Undefined("true", false, false);
    Y::memory::data_types::Int datavalue2 = Y::memory::data_types::Int("564663", false, false);
    Y::memory::data_types::Double datavalue3 = Y::memory::data_types::Double("564663.3456", false, false);

    // Add the variables to the memory manager
    manager.Add("myUdf", &datavalue);
    manager.Add("myInt", &datavalue2);
    manager.Add("myDbl", &datavalue3);

    // Get and print their values
    std::string datavalue_value = manager.GetValue("myInt");
    std::cout << "-" << datavalue_value << "-" << std::endl;

    std::string datavalue_value3 = manager.GetValue("myDbl");
    std::cout << "-" << datavalue_value3 << "-" << std::endl;

    std::string datavalue_value2 = manager.GetValue("myUdf");
    std::cout << "-" << datavalue_value2 << "-" << std::endl;

    return 0;
}