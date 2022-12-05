/*
 > Code by Icy
 > Y Programming Language
 > Memory Management
*/

#include "memory.hpp"

#include <iostream>
#include <map>
#include <string>

bool Y::memory::MemoryManager::is_value_in_memory(Y::memory::variable *value) {
  for (auto &i : memory) {
    if (i.second == value) {
      return true;
    }
  }
  return false;
}

void Y::memory::MemoryManager::remove_key_by_value(Y::memory::variable *value) {
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
Y::memory::variable *Y::memory::MemoryManager::allocate(size_t size,
                                                        std::string name) {
  if (memory.find(name) != memory.end()) {
    std::cout << "Memory already allocated" << std::endl;
    return nullptr;
  }
  Y::memory::variable *ptr = new Y::memory::variable[size];
  std::cout << "Allocated " << size << " bytes at " << ptr << std::endl;
  memory.insert(std::pair<std::string, Y::memory::variable *>(name, ptr));
  return ptr;
}
Y::memory::variable *
Y::memory::MemoryManager::allocate(Y::memory::variable data, std::string name) {
  if (memory.find(name) != memory.end()) {
    std::cout << "Memory already allocated" << std::endl;
    return nullptr;
  }
  Y::memory::variable *ptr = new Y::memory::variable;
  *ptr = data;
  std::cout << "Allocated (value) " << sizeof(data) << " bytes at " << ptr
            << std::endl;
  memory.insert(std::pair<std::string, Y::memory::variable *>(name, ptr));
  return ptr;
}
Y::memory::variable *
Y::memory::MemoryManager::update_allocation(Y::memory::variable data,
                                            std::string name) {
  if (memory.find(name) == memory.end()) {
    std::cout << "Memory not allocated yet" << std::endl;
    return nullptr;
  }
	*memory[name] = data;
  std::cout << "Updated allocation " << sizeof(data) << " bytes at " << memory[name]
            << std::endl;
  return memory[name];
}
void Y::memory::MemoryManager::deallocate(Y::memory::variable *ptr) {
  if (!is_value_in_memory(ptr)) {
    std::cout << "Memory not allocated" << std::endl;
    return;
  }
  std::cout << "Deallocated " << ptr << std::endl;
  remove_key_by_value(ptr);
  free(ptr);
}
void Y::memory::MemoryManager::deallocate(std::string name) {
  if (memory.find(name) == memory.end()) {
    std::cout << "Memory not allocated" << std::endl;
    return;
  }
  std::cout << "Deallocated " << memory[name] << std::endl;
  free(memory[name]);
  memory.erase(name);
}
Y::memory::variable *Y::memory::MemoryManager::get(std::string name) {
  if (memory.find(name) == memory.end()) {
    std::cout << "Memory not allocated" << std::endl;
    return nullptr;
  }
  return memory[name];
}