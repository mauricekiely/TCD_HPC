/**
 * @file assignment2a.cc
 * @brief  Simple toy example to use inheritance in C++
 * 	You just need to write the two struct definitions below where is says "TODO"
 * @author R. Morrin
 * @version 2.0
 * @date 2024-02-24
 */

#include <iostream>
#include <iomanip>

// Use this, and std::numbers::pi if you have C++20
#include <numbers>

// Use this if you don't have C++20
/*
#include <cmath>
const double A = M_PI;
*/

/**
 * @brief Shape struct for assignment2a. This will be a base struct you 
 * 	can derive the Cube and Cylinder structs from. You don't need to change this struct.
 */
struct Shape
{
	Shape () 			= delete; 	// Delete default constructor 
	// Overloaded Constructor
	Shape (double v, double sa) : volume {v}, surface_area{sa} {
		std::cout << "Constructing Shape with volume = " << volume 
			<< " and surface area = " << surface_area << std::endl; 
	}; 	
	// Destructor
	~Shape () {
		std::cout << "Destroying Shape with volume = " << volume
			<< " and surface area = " << surface_area << std::endl; 
	}

	Shape(const Shape&) 		= default; 	// Copy constructor
	Shape(Shape&&) 			= default; 	// Move constructor. Will actually be the same as copy for this class

	// Delete assignment operations
	Shape& operator=(const Shape &) = delete;
	Shape& operator=(Shape &&) 	= delete;

	// Member variables. 
	const double volume; 		//!< Holds the volume of the Shape
	const double surface_area; 	//!< Holds surface area of the Shape
};

// TODO:
// (1) Write struct Cube which inherits from Shape. It will have a const member variable "side"
// (2) Write struct Cylinder which inherits from Shape. It will have const member variables "radius" and "height"

/**
 * @brief Cube struct. Is child struct of Shape. Has non-inherited member variable side and inherited member variables
 * volume and surface_area
 */
struct Cube : public Shape {
	// Constructor for cube with side length (side). Initialize with volume and surface area from calling base class.
    Cube (double side) : Shape(side * side * side, 6 * side * side), side(side) {
        std::cout << "Constructing Cube with side = " << side << std::endl;
    }
	// Cube Destructor
    ~Cube() {
        std::cout << "Destroying Cube with side = " << side << std::endl;
    }

	const double side;
};

/**
 * @brief Cylinder struct. Is child struct of Shape. Has non-inherited member variables height and radius and inherited member variables
 * volume and surface_area
 */
struct Cylinder : public Shape {
	// Constructor for Cylinder with radius -> radius and height -> height. Initialize with volume and surface area from calling base class.
    Cylinder (double radius, double height) : Shape(std::numbers::pi * radius * radius * height, 2 * std::numbers::pi * radius * (radius + height)), 
          radius(radius), height(height) {
        std::cout << "Constructing Cylinder with radius = " << radius << " and height = " << height << std::endl;
    }
	// Cylinder Destructor
    ~Cylinder() {
        std::cout << "Destroying Cylinder with radius = " << radius << " and height = " << height << std::endl;
    }

	const double radius;
    const double height;
};



/// END: You shouldn't need to edit below here.

int main()
{
	const int w1{26}, w2{10}; 	// For formatting output
	std::cout << std::fixed << std::setprecision(3);
	
	// Cube {side_length}
	const Cube cube {1.2};
	std::cout<<std::setw(w1) << std::left << "\nSide of cube:"       << std::setw(w2) << std::right << cube.side         << '\n' 
		<< std::setw(w1) << std::left << "Volume of cube:"       << std::setw(w2) << std::right << cube.volume       << '\n' 
		<< std::setw(w1) << std::left << "Surface area of cube:" << std::setw(w2) << std::right << cube.surface_area << "\n\n\n";

	// Cylinder {radius, height}
	const Cylinder cylinder {3.4, 5.0};
	std::cout<<std::setw(w1) << std::left << "\nHeight of cylinder:"     << std::setw(w2) << std::right << cylinder.height       << '\n' 
		<< std::setw(w1) << std::left << "Radius of cylinder:"       << std::setw(w2) << std::right << cylinder.radius       << '\n' 
		<< std::setw(w1) << std::left << "Volume of cylinder:"       << std::setw(w2) << std::right << cylinder.volume       << '\n' 
		<< std::setw(w1) << std::left << "Surface area of cylinder:" << std::setw(w2) << std::right << cylinder.surface_area << "\n\n\n";

	return 0;
}
