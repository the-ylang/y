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
            // MemoryManager class
            class MemoryManager {
            private:
                // Memory storage map
                std::map<std::string, data_types::variables::variable*> memory;
                
                // Check if a variable is already in memory
                bool is_value_in_memory(data_types::variables::variable* value);
    
                // Remove a key by its value
                data_types::variables::variable remove_key_by_value(data_types::variables::variable* value);
    
            public:
                // MemoryManager constructor
                MemoryManager();
                // MemoryManager destructor
                ~MemoryManager();
                // Allocate a memory space with a given size and a given name
                data_types::variables::variable *allocate(size_t size, std::string name);
                // Allocata a variable with its data and name
                data_types::variables::variable *allocate(data_types::variables::variable data, std::string name);
                // Update a data already in memory
                data_types::variables::variable *update_allocation(data_types::variables::variable data, std::string name);
                // Deallocate a variable by its address
                data_types::variables::variable deallocate(data_types::variables::variable *ptr);
                // Deallocate a variable by its name
                data_types::variables::variable deallocate(std::string name);
                // Get a variable by its name
                data_types::variables::variable *get(std::string name);
            };
            namespace data_types {
                namespace variables {
                    // Variable settings type struct
                    typedef struct settings {
                        std::string type;
                        bool is_const;
                        bool is_ptr;
                    } settings;
    
                    // Variable type struct
                    typedef struct variable {
                        std::string value;
                        settings sttngs;
                    } variable;
                    
                    // DataType class
                    class DataType {
                    private:
                        // Memory manager  
                        MemoryManager data_memory_manager;
                        // Data name
                        std::string data_name;
                        // Data type
                        std::string data_type;
                        // Data value
                        std::string data_value;
                        // Is the data a constant
                        bool data_is_const;
                        // Is the data a pointer
                        bool data_is_ptr;
    
                        // Get all datas from a variable
                        variable get_data();
                        // Get variable value
                        std::string get_value();
                        settings get_settings();
    
                    public:
                        // DataType class constructor
                        DataType(MemoryManager memory_manager, std::string name, std::string type, std::string value, bool is_const, bool is_ptr);
    
                        // Register a new variable
                        variable name_data_register();
    
                        // Register a new memory space with a given size
                        void size_data_register();
    
                        // Get the type of the variable
                        std::string get_type(settings stgs);
                        // Gets if the variable is a contant
                        bool get_is_const(settings stgs);
                        // Gets if the variable is a pointer
                        bool get_is_ptr(settings stgs);
    
                        // Update the value of the variable
                        void update_data(std::string type, std::string value, bool is_const, bool is_ptr);
    
                        // Delete the variable
                        void delete_data();
                    };
                }
            }
        }
    }

#endif