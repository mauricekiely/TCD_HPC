#include "logging.h"

/**
 * @brief Locate the error in a program
 * 
 * @param location location of the error
 * @return std::string with error location
 */
std::string sourceline(const std::source_location location) {
    std::string log = "Error in " + std::string(location.file_name()) + " on line " + std::to_string(location.line()) + 
            " on column " + std::to_string(location.column()) + " in function " + std::string(location.function_name());
    return log;
}