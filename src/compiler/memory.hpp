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
             * @brief Structure for data settings
             */
            typedef struct settings {
                std::string type;
                bool is_const;
                bool is_ptr;
            } settings;

            /**
             * @brief Structure for data
             */
            typedef struct variable {
                std::string value;
                settings sttngs;
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
            namespace data_types {
                namespace variables {
                    /**
                     * @brief Structure for data types
                     */
                    class DataType {
                    private:
                        /**
                         * @brief A memory manager from DataType
                         */
                        MemoryManager data_memory_manager;
                        /**
                         * @brief The name of the data
                         */
                        std::string data_name;
                        /**
                         * @brief The type of the data
                         */
                        std::string data_type;
                        /**
                         * @brief The value of the data
                         */
                        std::string data_value;
                        /**
                         * @brief Is the data a constant
                         */
                        bool data_is_const;
                        /**
                         * @brief Is the data a pointer
                         */
                        bool data_is_ptr;
    
                        /**
                         * @brief Get the data
                         * 
                         * @return variable -> The data
                         */
                        variable get_data();
                        /**
                         * @brief Get the value of the data
                         * 
                         * @return std::string -> The value of the data
                         */
                        std::string get_value();
                        /**
                         * @brief Get the settings of the data
                         * 
                         * @return settings -> The settings of the data
                         */
                        settings get_settings();
    
                    public:
                        /**
                         * @brief Construct a new Data Type object
                         * 
                         * @param name The name of the data
                         * @param type The type of the data
                         * @param value The value of the data
                         * @param is_const Is the data a constant
                         * @param is_ptr Is the data a pointer
                         */
                        DataType(MemoryManager memory_manager, std::string name, std::string type, std::string value, bool is_const, bool is_ptr);
    
                        /**
                         * @brief Register a new memory space with a given value
                         * 
                         * @return variable -> The initialized data
                         */
                        variable name_data_register();
    
                        /**
                         * @brief Register a new memory space with a given size 
                         */
                        void size_data_register();
    
                        /**
                         * @brief Get the type of the variable
                         * 
                         * @return std::string -> The type of the variable
                         */
                        std::string get_type(settings stgs);
                        /**
                         * @brief Get if the variable is a constant
                         * 
                         * @return true -> The variable is a constant
                         * @return false -> The variable is not a constant
                         */
                        bool get_is_const(settings stgs);
                        /**
                         * @brief Get if the variable is a pointer
                         * 
                         * @return true -> The variable is a pointer
                         * @return false -> The variable is not a pointer
                         */
                        bool get_is_ptr(settings stgs);
    
                        /**
                         * @brief Updates the value / settings of the variable
                         * 
                         * @param type The new data type
                         * @param value The new data value
                         * @param is_const The new data is_const
                         * @param is_ptr The new data is_ptr
                         */
                        void update_data(std::string type, std::string value, bool is_const, bool is_ptr);
    
                        /**
                         * @brief Deletes the variable
                         */
                        void delete_data();
                    };
                }
            }
        }
    }

#endif