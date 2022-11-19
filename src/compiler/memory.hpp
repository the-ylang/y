/*
 > Code by Icy
 > Y Programming Language
 > Memory Management
*/

#ifndef __MEMORY_HPP__
    #define __MEMORY_HPP__

    #include <iostream>
    #include <string>
    #include <map>
  
    namespace Y {
        namespace memory {
            /**
             * @brief Structure for data
             */
            typedef struct variable {
                /**
                 * @brief The data
                 */
                std::string value;
                /**
                 * @brief The type of the data
                 */
                std::string type;
				/**
				 * @brief If the data is a constant
				 */
				bool is_constant;
            } variable;

            /**
             * @brief Memory Manager
             */
            class MemoryManager {
            private:
                /**
                 * @brief Memory storage map
                 */
                std::map<std::string, variable*> memory;
                
                /**
                 * @brief Check if value is in memory
                 * 
                 * @param value The variable to check in memory
                 * @return true -> The value is in memory
                 * @return false -> The value is not in memory
                 */
                bool is_value_in_memory(variable* value);
    
                /**
                 * @brief Remove key by value
                 * 
                 * @param value The variable to remove
                 */
                void remove_key_by_value(variable* value);
    
            public:
                /**
                 * @brief Construct a new Memory Manager object
                 */
                MemoryManager();
                /**
                 * @brief Destroy the Memory Manager object
                 */
                ~MemoryManager();
                /**
                 * @brief Allocate a memory space with a given size and name
                 * 
                 * @param size The size of the memory space
                 * @param name The name used to access the memory space
                 * @return variable* -> The pointer to the memory space
                 */
                variable *allocate(size_t size, std::string name);
                /**
                 * @brief Allocate a memory space with a given value and name
                 * 
                 * @param data The value of the memory space
                 * @param name The name used to access the memory space
                 * @return variable* -> The pointer to the memory space
                 */
                variable *allocate(variable data, std::string name);
                /**
                 * @brief Update the value of a memory space
                 * 
                 * @param data The new value of the memory space
                 * @param name The name used to access the memory space
                 * @return variable* -> The pointer to the memory space
                 */
                variable *update_allocation(variable data, std::string name);
                /**
                 * @brief Deallocate a memory space with a given adress
                 * 
                 * @param ptr The pointer to the memory space
                 */
                void deallocate(variable *ptr);
                /**
                 * @brief Deallocate a memory space with a given name
                 * 
                 * @param name The name used to access the memory space
                 */
                void deallocate(std::string name);
                /**
                 * @brief Get the value of a memory space with its name
                 * 
                 * @param name The name used to access the memory space
                 * @return variable* -> The pointer to the memory space
                 */
                variable *get(std::string name);
            };
        }
    }

#endif