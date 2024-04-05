/**
 * @file logging.h
 * @brief Header file for logging functions.
 * 		See https://en.cppreference.com/w/cpp/utility/source_location
 * @author R. Morrin
 * @version 2.0
 * @date 2024-03-09
 */
#ifndef LOGGING_H_QYJGNTWO
#define LOGGING_H_QYJGNTWO
#include <source_location>
#include <string>

std::string sourceline(const std::source_location location = std::source_location::current());

#endif /* end of include guard: LOGGING_H_QYJGNTWO */
