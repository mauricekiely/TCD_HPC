#ifndef INSTRUMENTS_H_VK2TICXL
#define INSTRUMENTS_H_VK2TICXL
#include <vector>
#include <iostream>

/**
 * @brief Abstract Base Class Trade
 * 	This class represents the concept of a trade i.e. something we buy, or a contract that we enter into
 */
class Trade
{
public:
	// Define copy and move constructors as default
	Trade(const Trade&) = default;
	Trade(Trade&&) = default; 
	// Delete assignment operators
	Trade& operator=(const Trade&) = delete;
	Trade& operator=(Trade&&) = delete;

	/**
	 * @brief Default construtor for Trade class
	 * 	This sets the value of cost equal to zero
	 */
	Trade() : cost {0}{
		std::cout << "Trade (base class) Constructor (Default)\n";
	}

	/**
	 * @brief Constructor for Trade class
	 *
	 * @param[in] cost This parameter is the price you paid to purchase, or enter the trade
	 */
	Trade (const double cost) : cost {cost} {
		std::cout << "Trade (base class) Constructor (overloaded)\n";
	}

	/**
	 * @brief Destructor for Trade
	 */
	virtual ~Trade (){
		std::cout << "Trade (base class) Destructor\n";
	}

	// Declare payoff as a pure virtual constant member function
	virtual double payoff(double ST) const = 0;

	// Grant access to private member of this class to any non-member functions that need it
	double get_cost() const {
		return cost;
	}

private:
	const double cost;	///< Holds the premium, or cost paid to enter the trade
};

/**
 * @brief Class to represent a forward trade.
 */
class Forward : public Trade {
public: 
	// Constructor for Forward Contract with price (fp). Initialize with cost 0 by calling base class.
	Forward(double fp): Trade(0), forward_price {fp} {
		std::cout << "Constructor for Forward with forward price "<< fp << std::endl;
	}
	// Delete default constructor
	Forward() = delete;

	// Destructor for Forward contract
	~Forward() {
		std::cout << "Destroying Forward with forward price "<< forward_price << std::endl;
	}

	/**
	* @brief Calculate payoff of forward price given a final price ST
	* @param[in] S_T Final value of the underlying
	**/
	double payoff(double ST) const override {
		return ST - forward_price;
	}
private: 
	const double forward_price;
};


/**
 * @brief Class to represent a Call Option
 */
class Call : public Trade {
public: 
	// Constructor for Call Option Contract with strike (k) and. Initialize with cost -> cost by calling base class.
	Call(double cost, double k): Trade(cost), strike {k} {
		std::cout << "Constructor for Call with strike "<< k << ". Premium: "<< cost << std::endl;
	}
	// Delete default constructor
	Call() = delete;

	// Destructor for option contract
	~Call() {
		std::cout << "Destroying Call with with strike "<< strike << std::endl;
	}

	/**
	* @brief Calculate payoff at expiry of call option given ST
	* @param[in] S_T Final value of the underlying
	**/
	double payoff(double ST) const override {
		return std::max(0.0, ST - strike);
	}
private: 
	const double strike;
};


/**
 * @brief Class to represent a Put Option
 */
class Put : public Trade {
public: 
	// Constructor for Put Option Contract with strike (k) and. Initialize with cost -> cost by calling base class.
	Put(double cost, double k):  Trade(cost), strike {k} {
		std::cout << "Constructor for Put with strike "<< k << ". Premium: "<< cost << std::endl;
	}
	// Delete default constructor
	Put() = delete;

	// Destructor for option contract
	~Put() {
		std::cout << "Destroying Put with with strike "<< strike << std::endl;
	}

	/**
	* @brief Calculate payoff at expiry of put option given ST
	* @param[in] S_T Final value of the underlying
	**/
	double payoff(double ST) const override {
		return std::max(0.0, strike - ST);
	}
private: 
	const double strike;
};


#endif /* end of include guard: INSTRUMENTS_H_VK2TICXL */
