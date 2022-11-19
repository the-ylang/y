#include <iostream>

#include "compiler.hpp"

#include "memory.hpp"

Y::TYPL::Runtime::Runtime() {
  Y::memory::MemoryManager mem = Y::memory::MemoryManager();
  Y::memory::variable var = {"10", "int", false};
  Y::memory::variable var2 = {"50", "int", false};
  mem.allocate(var, "test");
  std::cout << mem.get("test")->value << std::endl;
  mem.update_allocation(var2, "test");
  std::cout << mem.get("test")->value << std::endl;
}

Y::TYPL::Runtime::~Runtime() {}