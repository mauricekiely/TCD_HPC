/**
 * @file try_catch.cc
 * @brief  Short program to implement try-catch blocks to process some exceptions.
 * @author R. Morrin
 * @version 1.0
 * @date 2024-03-09
 */
#include <iostream>
#include <random>

/**
 * @brief Toy function that will throw various types of exceptions
 *
 * @param[in] in . A random number pulld from [0,1)
 */
void throw_fun(const double in){
	if(in <0.25){
		std::cout << "Throwing std::string" << std::endl;
		throw std::string("std::string");
	}
	if(in < 0.5){
		std::cout << "Throwing C-style string" << std::endl;
		throw "C-style";
	}
	if(in <0.75){
		std::cout << "Allocating memory" << std::endl;
		std::size_t s {100'000'000'000};
		[[maybe_unused]] double *t {new double[s]}; // The "[[maybe_unused]]" attribute just prevents compiler warnings for not using this.
	}
	std::cout << "Throwing int" << std::endl;
	throw -1;
}


int main()
{
	// You don't need to change this part. The
	// below code will just generate uniform
	// random variates on [0,1). The generator
	// used is the ranlux generator and it is
	// seeded via the random device.
	std::random_device rd;
	std::ranlux48 gen{rd()};
	std::uniform_real_distribution<> dist{0.0, 1.0};;
	double random_number = dist(gen);

	/// TODO
	/// Just wrap the below function call in a try block and 
	/// write the catch blocks below it to catch the various exceptions
	///
	try {
		throw_fun(random_number);		
	} catch (const std::string& e) {
        std::cerr << "Caught std::string: " << e << std::endl;
    }
    catch (const char* e) {
        std::cerr << "Caught C-style string: " << e << std::endl;
    }
	catch (int e) {
        std::cerr << "Caught int: " << e << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Caught std::exception: " << e.what() << std::endl;
    }
	catch (const std::bad_alloc& e) {
        std::cerr << "Caught std::bad_alloc: " << e.what() << std::endl;
    }
    catch (...) {
        std::cerr << "Caught an unknown exception" << std::endl;
    }

    return 0;
}

