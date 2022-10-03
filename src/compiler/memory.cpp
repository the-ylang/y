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
            public:
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
                    val = new double(std::stoi(obj.data_value));
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
                std::variant<Int*, Double*, Byte*, Char*, Bool*, Str*> val;
                bool is_const;
                bool is_ptr;

            public:
                Undefined(std::string value, bool is_constant, bool is_pointer) : DataType(value, is_constant, is_pointer) {
                    try {
                        val = &Bool(value, is_constant, is_pointer);
                    } catch (exceptions::allocation::InvalidBooleanValue) {
                        try {
                            val = &Byte(value, is_constant, is_pointer);
                        } catch (exceptions::allocation::ByteOverflow) {
                            try {
                                val = &Int(value, is_constant, is_pointer);
                            } catch (exceptions::allocation::IntegerOverflow) {
                                try {
                                    val = &Double(value, is_constant, is_pointer);
                                } catch (exceptions::allocation::DoubleOverflow) {
                                    try {
                                        val = &Char(value, is_constant, is_pointer);
                                    } catch (exceptions::allocation::CharOverflow) {
                                        val = &Str(value, is_constant, is_pointer);
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
                Int* GetInt() {
                    return std::get<Int*>(val);
                }
                Double* GetDouble() {
                    return std::get<Double*>(val);
                }
                Byte* GetByte() {
                    return std::get<Byte*>(val);
                }
                Char* GetChar() {
                    return std::get<Char*>(val);
                }
                Bool* GetBool() {
                    return std::get<Bool*>(val);
                }
                Str* GetStr() {
                    return std::get<Str*>(val);
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
                }

                std::string GetValue() {
                    std::string return_value;
                    try {
                        Int type = *std::get<Int*>(data);
                        std::variant<int*, long int*, long long int*> dvalue = type.GetValue();
                        try {
                            return_value = std::to_string(*std::get<int*>(dvalue));
                        } catch (std::bad_variant_access) {
                            try {
                                return_value = std::to_string(*std::get<long int*>(dvalue));
                            } catch (std::bad_variant_access) {
                                return_value = std::to_string(*std::get<long long int*>(dvalue));
                            }
                        }
                    } catch(std::bad_variant_access) {
                        try {
                            Double type = *std::get<Double*>(data);
                            std::variant <double*, long double*> dvalue = type.GetValue();
                            try {
                                return_value = std::to_string(*std::get<double*>(dvalue));
                            } catch (std::bad_variant_access) {
                                return_value = std::to_string(*std::get<long double*>(dvalue));
                            }
                        } catch (std::bad_variant_access) {
                            try {
                                Byte type = *std::get<Byte>(data);
                                return_value = std::to_string(*type.GetValue());
                            } catch (std::bad_variant_access) {
                                try {
                                    Char type = *std::get<Char*>(data);
                                    return_value = *type.GetValue();
                                } catch (std::bad_variant_access) {
                                    try {
                                        Bool type = *std::get<Bool*>(data);
                                        return_value = *type.GetValue();
                                    } catch (std::bad_variant_access) {
                                        try {
                                            Str type = *std::get<Str*>(data);
                                            return_value = *type.GetValue();
                                        } catch (std::bad_variant_access) {
                                            // TODO : Make undefined type part
                                            try {
                                                Undefined type = *std::get<Undefined*>(data);
                                                try {
                                                    std::variant<int*, long int*, long long int*> v = type.GetInt()->GetValue();
                                                    try {
                                                        return_value = std::to_string(*std::get<int*>(v));
                                                    } catch (std::bad_variant_access) {
                                                        try {
                                                            return_value = std::to_string(*std::get<long int*>(v));
                                                        } catch (std::bad_variant_access) {
                                                            return_value = std::to_string(*std::get<long long int*>(v));
                                                        }
                                                    }
                                                } catch (std::bad_variant_access) {
                                                    try {
                                                        std::variant<double*, long double*> v = type.GetDouble()->GetValue();
                                                        try {
                                                            return_value = std::to_string(*std::get<double*>(v));
                                                        } catch (std::bad_variant_access) {
                                                            return_value = std::to_string(*std::get<long double*>(v));
                                                        }
                                                    } catch (std::bad_variant_access) {
                                                        try {
                                                            return_value = std::to_string(*type.GetByte()->GetValue());
                                                        } catch (std::bad_variant_access) {
                                                            try {
                                                                return_value = *type.GetChar()->GetValue();
                                                            } catch (std::bad_variant_access) {
                                                                try {
                                                                    return_value = *type.GetBool()->GetValue();
                                                                } catch (std::bad_variant_access) {
                                                                    try {
                                                                        return_value = *type.GetStr()->GetValue();
                                                                    } catch (std::bad_variant_access) {
                                                                        throw exceptions::allocation::AllocationFatalError(); // TODO : Add new error management system
                                                                    }
                                                                }
                                                            }
                                                        }
                                                    }
                                                }
                                            }
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            };
        }

        class MemoryManager {
        private:
            std::map<std::string, std::variant<data_types::Int*, data_types::Double*, data_types::Byte*, data_types::Char*, data_types::Bool*, data_types::Str*, data_types::Undefined*>> memory;
        public:
            MemoryManager() {
                memory = {};
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
            ~MemoryManager() {
                delete &memory;
            }
        };
    }
}

int main() {
    Y::memory::MemoryManager manager = Y::memory::MemoryManager();
    Y::memory::data_types::Byte datavalue = Y::memory::data_types::Byte("255", false, false);
    Y::memory::data_types::Int datavalue2 = Y::memory::data_types::Int("564663", false, false);

    manager.Add("myByte", &datavalue);
    manager.Add("myInt", &datavalue2);

    std::variant<Y::memory::data_types::Int*, Y::memory::data_types::Double*, Y::memory::data_types::Byte*, Y::memory::data_types::Char*, Y::memory::data_types::Bool*, Y::memory::data_types::Str*, Y::memory::data_types::Undefined*> temp = manager.Get("myByte");
    std::variant<Y::memory::data_types::Int*, Y::memory::data_types::Double*, Y::memory::data_types::Byte*, Y::memory::data_types::Char*, Y::memory::data_types::Bool*, Y::memory::data_types::Str*, Y::memory::data_types::Undefined*> temp2 = manager.Get("myInt");

    return 0;
}