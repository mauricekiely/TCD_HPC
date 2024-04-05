/**
 * @file matrix.h
 * @brief Templated Matrix class for Assignment 3 of 5614 C++ programming
 * @author R. Morrin
 * @version 2.0
 * @date 2024-03-09
 */

#ifndef MATRIX_H_FIYNRKOJ
#define MATRIX_H_FIYNRKOJ

#include <iostream>
#include <iomanip>
#include <fstream>
#include "hpc_concepts.h"
#include "logging.h"

namespace HPC
{
	
	/**
	 * @brief Class to hold a Matrix. 5614 Assignment 3
	 *  	Modified from https://isocpp.org/wiki/faq/operator-overloading#matrix-subscript-op
	 *  	Store the matrix data as a single C-style array
	 *  	Students need to write function definitions for all the included member functions (except the deleted constructor)
	 *
	 * @tparam T Number type template parameter
	 */
	template <Number T>
		class Matrix {
			public:
				Matrix() = delete; 								// Delete default constructor. Really only a comment.
				Matrix(std::size_t const rows, std::size_t const cols); 			// Overloaded Constructor
				Matrix(std::string const file); 						// Overloaded Constructor. Read data from file.
				T& operator() (std::size_t const row_num, std::size_t const col_num);        	// non-const version which can be used to modify objects
				T  operator() (std::size_t const row_num, std::size_t const col_num) const;  	// Const version to be called on const objects

				~Matrix();                              // Destructor
				Matrix(Matrix const& m);               	// Copy constructor
				Matrix& operator=(Matrix const& m);   	// Assignment operator
				Matrix(Matrix && in); 			// Move Constructor
				Matrix& operator=(Matrix&& in); 	// Move Assignment operator

				// Note: Need the template brackets here in declaration.
				template<typename U>
				friend std::ostream& operator<<(std::ostream& os, const Matrix<U>& matrix);

				std::size_t get_num_rows() const{ return rows;};
				std::size_t get_num_cols() const{ return cols;};

			private:
				std::size_t rows, cols;
				T* data;
		};


	/**
	 * @brief Basic overloaded constructor for Matrix<T> class
	 * 		Note that this will set the values in data to zero.
	 * 		Don't need to check for negative values as size_t will be unsigned.
	 *
	 * @tparam T 	Number type that the matrix contains
	 * @param[in] num_rows Number of rows in created matrix
	 * @param[in] num_cols Number of columns in created matrix.
	 */
	template <Number T>
		Matrix<T>::Matrix(std::size_t const num_rows, std::size_t const num_cols)
		: rows {num_rows}
		, cols {num_cols}
		, data {new T [rows * cols]{}}
	{
		std::cout << "Constructing " << rows << " x " << cols << " Matrix\n";
	}

	/**
	 * @brief Overloaded constructor for Matrix<T> class
	 * 		Takes file as argument with first line indicating dimensions
	 * 		and remaining files indicating elements
	 *
	 * @tparam T	Number type that the matrix contains
	 * @param[in] file File that matrix is being read from
	 */
	template <Number T>
		Matrix<T>::Matrix(std::string const file) {
			std::ifstream infile {file};
			if (!infile.is_open()) {
				// Error handling for no file found
				throw std::string("No file to read: " );
			}
			// Read Rows and cols from first line
			infile >> rows >> cols;
			if (infile.fail()){
				throw std::out_of_range("Rows and Cols not defined correctly: " );
			}
			// Allocate memory for matrix elements 
			data = new T[rows * cols];
			for (std::size_t i = 0; i < rows; i++) {
				for (std::size_t j = 0; j < cols; j++){
					if (!(infile >> data[i * cols + j])) {
						delete[] data;
						throw std::out_of_range("Rows and Cols cant be populated correctly: " );
					}
				}
			}
			std::cout << "Constructing matrix of size" << rows << " x " << cols << "from file" << "\n";
		}

	/**
	 * @brief Destructor for Matrix<T> class
	 */
	template <Number T>
		Matrix<T>::~Matrix() {
			delete[] data;
			std::cout << "Matrix destroyed\t"  << std::endl;
		}

	/**
	 * @brief Copy Constructor for matrix<T> class
	 * 
	 * @tparam T	Number type that the matrix contains
	 * @param[in] m Matrix being copied
	 */
	template <Number T>
		Matrix<T>::Matrix(const Matrix<T>& m)
			: rows(m.rows), cols(m.cols), data(new T[rows * cols]) {
			std::copy(m.data, m.data + rows * cols, data);
		}

	/**
	 * @brief Copy Assignment Operator for matrix<T> class
	 * 
	 * @tparam T	Number type that the matrix contains
	 * @param[in] m Matrix being copied
	 */
	template <Number T>
		Matrix<T>& Matrix<T>::operator=(const Matrix<T>& m) {
			if (this != &m) {
				T* newData = new T[m.rows * m.cols];
				std::copy(m.data, m.data + m.rows * m.cols, newData);
				delete[] data; 
				data = newData;
				rows = m.rows;
				cols = m.cols;
			}
			return *this;
		}
	
	/**
	 * @brief Move Constructor for matrix<T> class
	 * 
	 * @tparam T	Number type that the matrix contains
	 * @param[in] in Matrix being moved.
	 */
	template <Number T>
		Matrix<T>::Matrix(Matrix<T> && in)
			: rows(in.rows), cols(in.cols), data(in.data) {
			in.rows = 0;
			in.cols = 0;
			in.data = nullptr;
		}

	/**
	 * @brief Move Assignment Operator for matrix<T> class
	 * 
	 * @tparam T  Number type that the matrix contains
	 * @param[in] in Matrix being moved.
	 */
	template <Number T>
		Matrix<T>& Matrix<T>::operator=(Matrix<T>&& in) {
			if (this != &in) { 
				delete[] data; 
				data = in.data;
				rows = in.rows;
				cols = in.cols;

				in.data = nullptr;
				in.rows = 0;
				in.cols = 0;
			}
			return *this;
		}

	
	/**
	 * @brief Operator overloader to access i elements
	 * 
	 * @tparam T  Number type that the matrix contains
	 * @param[in] row_num  Row index
	 * @param[in] col_num  Col index
	 */
	template <Number T>
		T& Matrix<T>::operator()(std::size_t const row_num, std::size_t const col_num) {
			if (row_num >= rows || col_num >= cols) {
				throw std::out_of_range("Elements out of range: ");
			}
			return data[row_num * cols + col_num];
		}

	
	/**
	 * @brief Operator overloader to access i elements in const object
	 * 
	 * @tparam T  Number type that the matrix contains
	 * @param[in] row_num  Row index
	 * @param[in] col_num  Col index
	 */
	template <Number T>
		T Matrix<T>::operator()(std::size_t const row_num, std::size_t const col_num) const {
			if (row_num >= rows || col_num >= cols) {
				throw std::out_of_range("Elements out of range: ");
			}
			return data[row_num * cols + col_num];
		}


	/**
	 * @brief Operator overloader to print matrix 
	 * 
	 * @tparam T  Number type that the matrix contains
	 * @param[in] os output stream to hold output
	 * @param[in] matrix Matrix to be printed
	 */
	template <typename T>
		std::ostream& operator<<(std::ostream& os, const HPC::Matrix<T>& matrix) {
			std::size_t rows = matrix.get_num_rows();
			std::size_t cols = matrix.get_num_cols();
			for (std::size_t i = 0; i < rows; i++) {
				os << "| ";
				for (std::size_t j = 0; j < cols; j++) {
					os << matrix(i, j);
					if (j < cols - 1) os << "\t";
				}
				os << " |\n";  
			}
			return os;
		}
		

	/**
	 * @brief Operator overloader to print matrix 
	 * 
	 * @tparam T1  Number type that the first matrix contains
	 * @tparam T2  Number type that the second matrix contains
	 * @param[in] m1 first matrix to be added
	 * @param[in] m2 second Matrix to be added
	 * 
	 *  @param[out] result Summed matrix
	 */
	template <Number T1, Number T2>
		auto operator+(const Matrix<T1>& M1, const Matrix<T2>& M2) {
			if (M1.get_num_rows() != M2.get_num_rows() || M1.get_num_cols() != M2.get_num_cols()) {
				throw std::out_of_range("Matrices are different size: ");
			}
			Matrix<decltype(T1() + T2())> result(M1.get_num_rows(), M1.get_num_cols());
			for (std::size_t i = 0; i < M1.get_num_rows(); ++i) {
				for (std::size_t j = 0; j < M1.get_num_cols(); ++j) {
					result(i, j) = M1(i, j) + M2(i, j);
				}
				
			}
			return result;
		}

	/**
	 * @brief Operator overloader to print matrix 
	 * 
	 * @tparam T1  Number type that the first matrix contains
	 * @tparam T2  Number type that the second matrix contains
	 * @param[in] m1 first matrix to be multiplied
	 * @param[in] m2 second Matrix to be multiplied
	 * 
	 *  @param[out] result Summed matrix
	 */
	template <Number T1, Number T2>
		auto operator*(const Matrix<T1>& M1, const Matrix<T2>& M2) {
			// Matrix-vector multiplication
			if (M2.get_num_cols() == 1) {
				if (M1.get_num_cols() != M2.get_num_rows()) {
					throw std::out_of_range("Wrong dimensions for multiplication");
				}
				Matrix<decltype(T1{} * T2{})> result(M1.get_num_rows(), 1);
				for (std::size_t i = 0; i < M1.get_num_rows(); ++i) {
					for (std::size_t k = 0; k < M1.get_num_cols(); ++k) {
						result(i, 0) += M1(i, k) * M2(k, 0);
					}
				}
				return result;
			} else {
				// Matrix-matrix multiplication
				Matrix<decltype(T1{} * T2{})> result(M1.get_num_rows(), M2.get_num_cols());
				for (std::size_t i = 0; i < result.get_num_rows(); ++i) {
					for (std::size_t j = 0; j < result.get_num_cols(); ++j) {
						for (std::size_t k = 0; k < M1.get_num_cols(); ++k) {
							result(i, j) += M1(i, k) * M2(k, j);
						}
					}
				}
				return result;
			}
		}


	/**
	 * @brief Converts input matrix to identity matrix
	 * 
	 * @param in Matrix to be converted
	 */
	void identity(auto& in) {
        for (std::size_t i = 0; i < in.get_num_rows(); ++i) {
            for (std::size_t j = 0; j < in.get_num_cols(); ++j) {
				if (i == j) {
					in(i, j) = 1.0;
				} else {
					in(i, j) = 0.0;
 				}
            }
        }
    }
} /*  HPC */ 

#endif /* end of include guard: MATRIX_H_FIYNRKOJ */