/*
 > Code by Icy
 > Y Programming Language
 > Memory Management
*/

#include <iostream>
#include <string>
#include <vector>
#include <map>

namespace Y {
    namespace memory {
        class MemoryManager {
        private:
            std::map<std::string, Y::memory::variables::variable*> memory;

            bool is_value_in_memory(datatypes::variables::variable* value) {
                for (auto& i : memory) {
                    if (i.second == value) {
                        return true;
                    }
                }
                return false;
            }

            datatypes::variables::variable remove_key_by_value(datatypes::variables::variable* value) {
                for (auto it = memory.begin(); it != memory.end(); ++it) {
                    if (it->second == value) {
                        memory.erase(it);
                        return;
                    }
                }
            }

        public:
            MemoryManager() {
                std::cout << "Memory Manager Initialized" << std::endl;
            }
            ~MemoryManager() {
                std::cout << "Memory Manager Destroyed" << std::endl;
            }
            datatypes::variables::variable *allocate(size_t size, std::string name) {
                if(memory.find(name) != memory.end()) {
                    std::cout << "Memory already allocated" << std::endl;
                    return nullptr;
                }
                datatypes::variables::variable *ptr = malloc(size);
                std::cout << "Allocated " << size << " bytes at " << ptr << std::endl;
                memory.insert(std::pair<std::string, datatypes::variables::variable*>(name, ptr));
                return ptr;
            }
            datatypes::variables::variable *allocate(datatypes::variables::variable data, std::string name) {
                if(memory.find(name) != memory.end()) {
                    std::cout << "Memory already allocated" << std::endl;
                    return nullptr;
                }
                datatypes::variables::variable *ptr = malloc(sizeof(data));
                *ptr = data;
                std::cout << "Allocated (value) " << size << " bytes at " << ptr << std::endl;
                memory.insert(std::pair<std::string, datatypes::variables::variable*>(name, ptr));
                return ptr;
            }
            datatypes::variables::variable *update_allocation(datatypes::variables::variable data, std::string name) {
                if(memory.find(name) == memory.end()) {
                    std::cout << "Memory not allocated yet" << std::endl;
                    return nullptr;
                }
                datatypes::variables::variable *ptr = malloc(sizeof(data));
                *ptr = data;
                std::cout << "Updated allocation " << size << " bytes at " << ptr << std::endl;
                memory[name] = ptr;
                return ptr;
            }
            datatypes::variables::variable deallocate(datatypes::variables::variable *ptr) {
                if(!is_value_in_memory(ptr)) {
                    std::cout << "Memory not allocated" << std::endl;
                    return;
                }
                std::cout << "Deallocated " << ptr << std::endl;
                remove_key_by_value(ptr);
                free(ptr);
            }
            datatypes::variables::variable deallocate(std::string name) {
                if(memory.find(name) == memory.end()) {
                    std::cout << "Memory not allocated" << std::endl;
                    return;
                }
                std::cout << "Deallocated " << memory[name] << std::endl;
                free(memory[name]);
                memory.erase(name);
            }
            datatypes::variables::variable *get(std::string name) {
                if(memory.find(name) == memory.end()) {
                    std::cout << "Memory not allocated" << std::endl;
                    return nullptr;
                }
                return memory[name];
            }
        };
        namespace datatypes {
            namespace variables {

                typedef struct settings {
                    std::string type;
                    bool is_const;
                    bool is_ptr;
                } settings;

                typedef struct variable {
                    std::string value;
                    settings sttngs;
                } variable;
                
                class DataType {
                private:
                    Y::memory::MemoryManager data_memory_manager;
                    std::string data_name;
                    std::string data_type;
                    std::string data_value;
                    bool data_is_const;
                    bool data_is_ptr;

                    variable get_data() {
                        return *data_memory_manager.get(data_name);
                    }
                    std::string get_value() {
                        return get_data().value;
                    }
                    settings get_settings() {
                        return get_data().sttngs;
                    }

                public:
                    DataType(Y::memory::MemoryManager memory_manager, std::string name, std::string type, std::string value, bool is_const, bool is_ptr) {
                        data_memory_manager = memory_manager;
                        data_name = name;
                        data_type = type;
                        data_value = value;
                        data_is_const = is_const;
                        data_is_ptr = is_ptr;
                    }

                    // Register a new variable
                    variable name_data_register() {
                        settings stgs = {data_type, data_is_const, data_is_ptr};
                        variable var = {data_value, stgs};
                        data_memory_manager.allocate(var, data_name);
                        return var;
                    }

                    // Register a new memory space with a given size
                    void size_data_register() {
                        settings stgs = {data_type, data_is_const, data_is_ptr};
                        variable var = {data_value, stgs};
                        data_memory_manager.allocate(sizeof(var), data_name);
                    }

                    // Get the type of the variable
                    std::string get_type(settings stgs) {
                        return get_settings.type;
                    }
                    // Gets if the variable is a contant
                    bool get_is_const(settings stgs) {
                        return get_settings.is_const;
                    }
                    // Gets if the variable is a pointer
                    bool get_is_ptr(settings stgs) {
                        return get_settings.is_ptr;
                    }

                    // Update the value of the variable
                    void update_data(std::string type, std::string value, bool is_const, bool is_ptr) {
                        settings stgs = {type, is_const, is_ptr};
                        variable var = {value, stgs};
                        *data_memory_manager.update_allocation(var, data_name);
                    }

                    // Delete the variable
                    void delete_data() {
                        data_memory_manager.deallocate(data_name);
                    }
                };
            }
        }
    }
}

int main() {
    Y::memory::MemoryManager memory_manager;
    Y::datatypes::variables::DataType data = Y::datatypes::variables::DataType(memory_manager, "test", "int", "0", false, false);
    data.name_data_register();
    data.update_data("int", "1", false, false);
    data.delete_data();
}

// Path: ._Y\2022.10.25\src\main.cpp
