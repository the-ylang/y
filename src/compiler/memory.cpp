/*
 > Code by Icy
 > Y Programming Language
 > Memory Management
*/

#include "memory.hpp"

#include <iostream>
#include <string>
#include <map>


bool Y::memory::MemoryManager::is_value_in_memory(Y::memory::variable* value) {
    for (auto& i : memory) {
        if (i.second == value) {
            return true;
        }
    }
    return false;
}

void Y::memory::MemoryManager::remove_key_by_value(Y::memory::variable* value) {
    for (auto it = memory.begin(); it != memory.end(); ++it) {
        if (it->second == value) {
            memory.erase(it);
            return;
        }
    }
}

Y::memory::MemoryManager::MemoryManager() {
    std::cout << "Memory Manager Initialized" << std::endl;
}
Y::memory::MemoryManager::~MemoryManager() {
    std::cout << "Memory Manager Destroyed" << std::endl;
}
Y::memory::variable *Y::memory::MemoryManager::allocate(size_t size, std::string name) {
    if(memory.find(name) != memory.end()) {
        std::cout << "Memory already allocated" << std::endl;
        return nullptr;
    }
    Y::memory::variable *ptr = new Y::memory::variable[size];
    std::cout << "Allocated " << size << " bytes at " << ptr << std::endl;
    memory.insert(std::pair<std::string, Y::memory::variable*>(name, ptr));
    return ptr;
}
Y::memory::variable *Y::memory::MemoryManager::allocate(Y::memory::variable data, std::string name) {
    if(memory.find(name) != memory.end()) {
        std::cout << "Memory already allocated" << std::endl;
        return nullptr;
    }
    Y::memory::variable *ptr = new Y::memory::variable;
    *ptr = data;
    std::cout << "Allocated (value) " << sizeof(data) << " bytes at " << ptr << std::endl;
    memory.insert(std::pair<std::string, Y::memory::variable*>(name, ptr));
    return ptr;
}
Y::memory::variable *Y::memory::MemoryManager::update_allocation(Y::memory::variable data, std::string name) {
    if(memory.find(name) == memory.end()) {
        std::cout << "Memory not allocated yet" << std::endl;
        return nullptr;
    }
    Y::memory::variable *ptr = new Y::memory::variable;
    *ptr = data;
    std::cout << "Updated allocation " << sizeof(data) << " bytes at " << ptr << std::endl;
    memory[name] = ptr;
    return ptr;
}
void Y::memory::MemoryManager::deallocate(Y::memory::variable *ptr) {
    if(!is_value_in_memory(ptr)) {
        std::cout << "Memory not allocated" << std::endl;
        return;
    }
    std::cout << "Deallocated " << ptr << std::endl;
    remove_key_by_value(ptr);
    free(ptr);
}
void Y::memory::MemoryManager::deallocate(std::string name) {
    if(memory.find(name) == memory.end()) {
        std::cout << "Memory not allocated" << std::endl;
        return;
    }
    std::cout << "Deallocated " << memory[name] << std::endl;
    free(memory[name]);
    memory.erase(name);
}
Y::memory::variable *Y::memory::MemoryManager::get(std::string name) {
    if(memory.find(name) == memory.end()) {
        std::cout << "Memory not allocated" << std::endl;
        return nullptr;
    }
    return memory[name];
}

typedef struct settings {
    std::string type;
    bool is_const;
    bool is_ptr;
} settings;

typedef struct variable {
    std::string value;
    settings sttngs;
} variable;

Y::memory::variable Y::memory::data_types::variables::DataType::get_data() {
    return *data_memory_manager.get(data_name);
}
std::string Y::memory::data_types::variables::DataType::get_value() {
    return get_data().value;
}
Y::memory::settings Y::memory::data_types::variables::DataType::get_settings() {
    return get_data().sttngs;
}

Y::memory::data_types::variables::DataType::DataType(Y::memory::MemoryManager memory_manager, std::string name, std::string type, std::string value, bool is_const, bool is_ptr) {
    data_memory_manager = memory_manager;
    data_name = name;
    data_type = type;
    data_value = value;
    data_is_const = is_const;
    data_is_ptr = is_ptr;
}

Y::memory::variable Y::memory::data_types::variables::DataType::name_data_register() {
    settings stgs = {data_type, data_is_const, data_is_ptr};
    variable var = {data_value, stgs};
    data_memory_manager.allocate(var, data_name);
    return var;
}

void Y::memory::data_types::variables::DataType::size_data_register() {
    settings stgs = {data_type, data_is_const, data_is_ptr};
    variable var = {data_value, stgs};
    data_memory_manager.allocate(sizeof(var), data_name);
}

std::string Y::memory::data_types::variables::DataType::get_type(settings stgs) {
    return stgs.type;
}
bool Y::memory::data_types::variables::DataType::get_is_const(settings stgs) {
    return stgs.is_const;
}
bool Y::memory::data_types::variables::DataType::get_is_ptr(settings stgs) {
    return stgs.is_ptr;
}

void Y::memory::data_types::variables::DataType::update_data(std::string type, std::string value, bool is_const, bool is_ptr) {
    settings stgs = {type, is_const, is_ptr};
    variable var = {value, stgs};
    *data_memory_manager.update_allocation(var, data_name);
}

void Y::memory::data_types::variables::DataType::delete_data() {
    data_memory_manager.deallocate(data_name);
}