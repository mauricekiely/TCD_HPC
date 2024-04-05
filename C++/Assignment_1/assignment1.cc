/**
 * @file assignment1.cc
 * @brief Skeleton of code for 5614 Assignment 1. 
 * 
 * 5614 Assignment 1. This file contains the bones of the class
 * definition plus the main function. The main function that you
 * finish with should be the same as provided.
 * Please add the rest of the code as instructed in the document. 
 * Don't forget to use comments.
 * 	
 * @author R. Morrin
 * @version 5.0
 * @date 2024-02-02
 */
#include <iostream> 			// Needed for I/O
#include <cmath> 			// Needed for maths functions
#include <iomanip> 			// Output formatting


const double MYPI {4 * std::atan(1.0)};
//Use the below instead if not using g++ and you get errors with line above
//constexpr double MYPI = M_PI;

/**
 * @class Gaussian
 * @brief A class to represent a normal distribution
 *
 * This class stores the parameters for an object which 
 * represents a Gaussian distribution.
 */
class Gaussian
{
    public:
    Gaussian () : mu(0.0), sigma(1.0) {
        std::cout << "Constructing default with mean 0.0, stdev 1.0" << std::endl;
    }; 				// Default Constructor    	// WRITE DEFINITION INLINE
    Gaussian (double mean, double stdev) : mu{mean}, sigma{stdev} {
        std::cout << "Constructing with mean " << mu << " and stdev "<< sigma << std::endl;
    }; 	// Overloaded constructor 	// WRITE DEFINITION INLINE
    double get_mu() const{
        return mu;
    }; 		 	// Return value of mu		// WRITE DEFINITION INLINE
    double get_sigma() const {
        return sigma;
    }; 		// Return value of sigma	// WRITE DEFINITION INLINE
    double normalized(double x) const {
        return ((x - mu)/sigma);
    }; 	// return normalized z value 	// WRITE DEFINITION INLINE

	// Write remaining member function definitions outside of class body
	Gaussian(const Gaussian& rhs); 					// Copy constructor
	Gaussian & operator=(const Gaussian &rhs); 			// Copy assignment operator
	double pdf(double x) const; 					// return pdf at x
	double cdf(double x, double left=-8, double step=1e-3) const; 	// return cdf at x using numerical approx
	double cdf_erfc(double x) const; 				// return cdf at x using std::erfc
	void print_parameters() const; 					// Print distribution parameters

	// You don't need to modify from here to the end of the class definition.
	double cdf_poly(double x) const; 				// Code provided below for Hart approximation
	~Gaussian() { 							// Destructor
	    std::cout << "Destroying object with mu = " << mu << " stdev = " << sigma << '\n';
	}

    private:
	double mu; 							///< Holds mean of Gaussian
	double sigma; 							///< Holds standard deviation of Gaussian
};

/**
 * @brief Copy constructor for Gaussian.
 *
 * Initializes a new Gaussian class by copying the values form another instance.
 *
 * @param rhs The Gaussian object from which values are copied.
 */
Gaussian::Gaussian(const Gaussian& rhs) {
    mu = rhs.mu;
    sigma = rhs.sigma;
    std::cout << "Copy constructor called successfully\n";
}

/**
 * @brief Copy assignment operator for Gaussian.
 *
 * Assigns the values of one Gaussian object from another Gaussian object.
 *
 * @param rhs The Gaussian object to assign from.
 * @return Gaussian& A reference to current object.
 */
Gaussian& Gaussian::operator=(const Gaussian &rhs) {
    if (this != &rhs) {
        mu = rhs.mu;
        sigma = rhs.sigma;
        std::cout << "Assignment operator called successfully\n";
    }
    return *this;
}

// Non member function declarations.
// These are just another way to get same functionality.
// Will discuss later in lectures.
void print_parameters(const Gaussian & dist);
double pdf(const Gaussian & dist, double x);
double cdf(const Gaussian & dist, double x, double start=-10, double step=1e-3);
double cdf_poly(const Gaussian & dist, const double x);
double cdf_erfc(const Gaussian & dist, const double x);


//
/**
 * @brief Prints the parameters Gaussian.
 *
 * Prints the values of the Gaussian object.
 */
void Gaussian::print_parameters() const {
    std::cout << "Normal distribution with mean " << mu << " and standard deviation " << sigma << std::endl;
}

/**
 * @brief Calculates the PDF for a given x.
 *
 * @param x The point at which to evaluate the PDF.
 * @return PDF value for x.
 */
double Gaussian::pdf(double x) const {
    return (1 / (sigma * std::sqrt(2 * MYPI))) * std::exp(-0.5 * normalized(x) * normalized(x));
}

/**
 * @brief Calculates the CDF using erfc.
 *
 * @param x The point at which to evaluate the CDF.
 * @return CDF value for x.
 */
double Gaussian::cdf_erfc(double x) const {
    double z = normalized(x);
    return 0.5 * std::erfc(-z/std::sqrt(2));
}

/**
 * @brief Calculates the CDF using numerical integration (Trapeziod).
 *
 * Computes the CDF at a specific point x by summing the average PDFs from consecutive areas of width step from a
 * starting point to x.
 *
 * @param x The point at which to evaluate the CDF.
 * @param left The number of stdevs left of the mean from which to start the summation.
 * @param step The step size for each iteration.
 * @return CDF value for x.
 */
double Gaussian::cdf(double x, double left, double step) const {
    double area = 0.0;
    // Take starting value of x
    double curr_x = mu + left * sigma;
    
    while (curr_x < x) {
        // Take the next x value whos pdf is needed and calculate pdfs
        double next_x = curr_x + step;
        double f_curr_x = pdf(curr_x);
        double f_next_x = pdf(next_x);
        // Add current area to total
        area += ((f_curr_x + f_next_x) / 2.0) * (step);;
        curr_x = next_x;
    }

    return area;
}

//



/**
 * @brief Function to return a polynomial approximation to the cumulative distribution function for the normal distribution
 *
 * This member function uses the Hart approximation for the error function to compute a polynomial approximation
 * to the CDF of the standard normal distribution.
 *
 * @param x
 *
 * @return $\Phi(x)$ 
 */
double Gaussian::cdf_poly(const double x) const{
    const double norm {normalized(x)};
    constexpr double boundary {7.07106781186547};

    constexpr double N0 {220.206867912376};
    constexpr double N1 {221.213596169931};
    constexpr double N2 {112.079291497871};
    constexpr double N3 {33.912866078383};
    constexpr double N4 {6.37396220353165};
    constexpr double N5 {0.700383064443688};
    constexpr double N6 {3.52624965998911e-02};

    constexpr double M0 {440.413735824752};
    constexpr double M1 {793.826512519948};
    constexpr double M2 {637.333633378831};
    constexpr double M3 {296.564248779674};
    constexpr double M4 {86.7807322029461};
    constexpr double M5 {16.064177579207};
    constexpr double M6 {1.75566716318264};
    constexpr double M7 {8.83883476483184e-02};

    const double z {std::fabs(norm)};
    double c {0.0};

    if(z<=37.0)
    {
	const double e {std::exp(-z*z/2.0)};
	if(z<boundary)
	{
	    const double n {(((((N6*z + N5)*z + N4)*z + N3)*z + N2)*z + N1)*z + N0};
	    const double d {((((((M7*z + M6)*z + M5)*z + M4)*z + M3)*z + M2)*z + M1)*z + M0};
	    c = e*n/d;
	}
	else
	{
	    const double f {z + 1.0/(z + 2.0/(z + 3.0/(z + 4.0/(z + 13.0/20.0))))};
	    c = e/(std::sqrt(2*MYPI)*f);
	}
    }
    return norm<=0.0 ? c : 1-c;
}


/**
 * @brief Prints the parameters Gaussian.
 *
 * Prints the values of the Gaussian object.
 * @param dist  The Gaussian object that holds the distribution parameters.
 */
void print_parameters(const Gaussian & dist){
    std::cout << "Normal distribution with mean " << dist.get_mu() << " and standard deviation " << dist.get_sigma() << std::endl;
}

/**
 * @brief Calculates the PDF for a given x.
 *
 * @param dist  The Gaussian object that holds the distribution parameters.
 * @param x The point at which to evaluate the PDF.
 * @return PDF value for x.
 */
double pdf(const Gaussian & dist, double x) {
    return  (1 / (dist.get_sigma() * std::sqrt(2 * MYPI))) * std::exp(-0.5 * ((x - dist.get_mu())/dist.get_sigma()) * ((x - dist.get_mu())/dist.get_sigma()));
}

/**
 * @brief Calculates the CDF using erfc.
 *
 * @param dist  The Gaussian object that holds the distribution parameters.
 * @param x The point at which to evaluate the CDF.
 * @return CDF value for x.
 */
double cdf_erfc(const Gaussian & dist, const double x){
    double z = (x - dist.get_mu()) / (dist.get_sigma());
    return 0.5 * std::erfc(-z / std::sqrt(2));
}

/**
 * @brief Calculates the CDF using numerical integration (Trapeziod).
 *
 * Computes the CDF at a specific point x by summing the average PDFs from consecutive areas of width step from a
 * starting point to x.
 *
 * @param dist  The Gaussian object that holds the distribution parameters.
 * @param x The point at which to evaluate the CDF.
 * @param left The number of stdevs left of the mean from which to start the summation.
 * @param step The step size for each iteration.
 * @return CDF value for x.
 */
double cdf(const Gaussian & dist, double x, double start, double step) {
    double area = 0.0;
    // Take the next x value whos pdf is needed and calculate pdfs
    double curr_x = dist.get_mu() + (start * dist.get_sigma());
    while (curr_x < x) {
        double next_x = curr_x + step;
        double f_curr_x = pdf(dist, curr_x);
        double f_next_x = pdf(dist, next_x);
        // Add current area to total
        area += ((f_curr_x + f_next_x) / 2.0) * step;
        curr_x = next_x;
    }
    return area;
}

/**
 * @brief Function to return a polynomial approximation to the cumulative distribution function for the normal distribution
 *
 * This member function uses the Hart approximation for the error function to compute a polynomial approximation
 * to the CDF of the standard normal distribution.
 *
 * @param dist  The Gaussian object that holds the distribution parameters.
 * @param x
 * @return $\Phi(x)$
 */
double cdf_poly(const Gaussian &dist, double x) {
    // Manually normalize x
    double norm = (x - dist.get_mu()) / dist.get_sigma();

    constexpr double boundary {7.07106781186547};

    constexpr double N0 {220.206867912376};
    constexpr double N1 {221.213596169931};
    constexpr double N2 {112.079291497871};
    constexpr double N3 {33.912866078383};
    constexpr double N4 {6.37396220353165};
    constexpr double N5 {0.700383064443688};
    constexpr double N6 {3.52624965998911e-02};

    constexpr double M0 {440.413735824752};
    constexpr double M1 {793.826512519948};
    constexpr double M2 {637.333633378831};
    constexpr double M3 {296.564248779674};
    constexpr double M4 {86.7807322029461};
    constexpr double M5 {16.064177579207};
    constexpr double M6 {1.75566716318264};
    constexpr double M7 {8.83883476483184e-02};

    const double z {std::fabs(norm)};
    double c {0.0};

    if(z <= 37.0) {
        const double e {std::exp(-z*z/2.0)};
        if(z < boundary) {
            const double n {(((((N6*z + N5)*z + N4)*z + N3)*z + N2)*z + N1)*z + N0};
            const double d {((((((M7*z + M6)*z + M5)*z + M4)*z + M3)*z + M2)*z + M1)*z + M0};
            c = e*n/d;
        } else {
            const double f {z + 1.0/(z + 2.0/(z + 3.0/(z + 4.0/(z + 13.0/20.0))))};
            c = e/(std::sqrt(2*MYPI)*f);
        }
    }
    return norm <= 0.0 ? c : 1-c;
}
//



// Main function for 5614 Assigment 1
// Note that a lot of the code below is simply formatting output.
// If it is confusing, email me and I will provide the same without the formatting
// You shouldn't need to add anything here. Your final code should run with this as-is.

int main()
{
    Gaussian A;  			// Create object of class Gaussian via default constructor
    Gaussian B {1, 2}; 			// Create object of class Gaussian via overloaded constructor

    // Create a list. Is ok to use auto here 
    auto list = {-3.0, -2.0, -1.0, -0.5, 0.0, 0.5, 1.0, 2.0, 3.0};

    // Calculate and print cumulative density function values for A for a number of input values.
    // Most of these lines are for formatting output. We will cover this later.
    std::cout << std::fixed << '\n';
    A.print_parameters();
    std::cout << std::setw(60) << std::setfill('-') << '\n' << std::setfill(' ');
    std::cout <<  "  x           Phi(x)             Method \n";
    // Print the various values
    for (auto  i : list) {
	std::cout << std::setw(4) <<  std::setprecision(1) <<  i << "\t" << std::setprecision(14) <<  A.cdf(i)       << "  \tNum. Int.\n"
	    << std::setw(4) <<  std::setprecision(1) <<  i << "\t" << std::setprecision(14) <<  A.cdf_erfc(i)  << "  \tUsing std::erfc.\n"
	    << std::setw(4) <<  std::setprecision(1) <<  i << "\t" << std::setprecision(14) <<  A.cdf_poly(i)  << "  \tHart approx.\n";
    }
    std::cout << std::setw(60) << std::setfill('-') << '\n' << std::setfill(' ');
    std::cout << "\n\n";


    // Calculate and print cumulative density function values for B for a number of input values.
    B.print_parameters();
    std::cout << std::setw(60) << std::setfill('-') << '\n' << std::setfill(' ');
    for (auto  i : list) {
	std::cout << std::setw(4) <<  std::setprecision(1) <<  i << "\t"<< std::setprecision(14) <<  B.cdf(i, -10.0, 1e-6) << "  \tNum. Int.\n"
	    << std::setw(4) <<  std::setprecision(1) <<  i << "\t" << std::setprecision(14) <<  B.cdf_erfc(i)  << "  \tUsing std::erfc.\n"
	    << std::setw(4) <<  std::setprecision(1) <<  i << "\t"<< std::setprecision(14) <<  B.cdf_poly(i)         << "  \tHart approx.\n";
    }
    std::cout << std::setw(60) << std::setfill('-') << '\n' << std::setfill(' ');
    std::cout << "\n";

	
    //
    // The non-member functions are used below here.
    //

    std::cout << "\nUsing free functions\n" << std::endl;
    Gaussian D {2,5}; 			// Create another object of class Gaussian
    print_parameters(D); 		// Print the parameters of D using non-member function
    Gaussian C {D}; 			// Should call copy constructor
    print_parameters(C); 		// Print the parameters of C using non-member function
    std::cout << "\n\n";

    A = B; 				// Should call copy assignment operator you wrote

    // Print parameters of A, followed by an example CDF calculation using the free functions.
    print_parameters(A);
    std::cout << std::setprecision(12) << "PDF of A at x=1 is " << pdf(A, 3.0) << '\n';
    std::cout << std::setprecision(12) << "Num. Int.:\tCDF of A at x=3 is " << cdf(A, 3.0) << '\n';
    std::cout << std::setprecision(12) << "std::erfc:\tCDF of A at x=3 is " << cdf_erfc(A, 3.0) << '\n';
    std::cout << std::setprecision(12) << "Hart Approx:\tCDF of A at x=3 is " << cdf_poly(A, 3.0) << '\n';

    std::cout << "\n\n" << std::setprecision(1);
    return 0;
}
