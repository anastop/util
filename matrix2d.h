/**
 * @file
 * Template functions for 2D matrices manipulation
 */ 
#ifndef MATRIX2D_H_
#define MATRIX2D_H_

#include <iostream>
#include <cstdlib>

/**
 * Allocate nrows x ncols matrix
 * @param nrows num of rows
 * @param ncols num of columns
 * @return pointer to matrix 
 */
template <typename T>
T** matrix2d_alloc(size_t nrows, size_t ncols)
{
    T **m = NULL;

    try {
        m = new T* [nrows];
    } catch (std::exception& e) {
        std::cerr << "Standard exception: " << e.what() << std::endl;
    }

    for ( size_t i = 0; i < nrows; i++ ) {
        try {
            m[i] = new T [ncols];
        } catch (std::exception& e) {
            std::cerr << "Standard exception: " << e.what() << std::endl;
        }
    }

    return m; 
}

/**
 * Initialize matrix with specified value
 * @param m pointer to matrix 
 * @param nrows num of rows
 * @param ncols num of columns
 * @param val value to initialize all emenents with
 */
template <typename T>
void matrix2d_init(T** m, size_t nrows, size_t ncols, T val)
{
    for ( size_t i = 0; i < nrows; i++ )
        for ( size_t j = 0; j < ncols; j++ )  
            m[i][j] = val;
}

/**
 * Initialize matrix with random double values
 * @param m pointer to matrix 
 * @param nrows num of rows
 * @param ncols num of columns
 */
void matrix2d_init_random_double(double **m, size_t nrows, size_t ncols)
{
    for ( size_t i = 0; i < nrows; i++ )
        for ( size_t j = 0; j < ncols; j++ )
            m[i][j] = (rand()%1000)/100.0f;
}
 


/**
 * Deallocate matrix
 * @param m pointer to matrix as returned by allocation function
 * @param nrows number of matrix rows
 */
template <typename T>
void matrix2d_destroy(T** m, size_t nrows)
{
    for ( size_t i = 0; i < nrows; i++ )
        delete [] m[i];

    delete [] m;
}

/**
 * Copy matrices
 * @param s source matrix
 * @param t destination matrix
 * @param nrows number of matrix rows
 * @param ncols number of matrix columns
 */
template <typename T>
void matrix2d_copy(T** s, T** t, size_t nrows, size_t ncols)
{
    for ( size_t i = 0; i < nrows; i++ )
        for ( size_t j = 0; j < ncols; j++ )
            t[i][j] = s[i][j];
}



/**
 * Print matrix 
 * @param m pointer to matrix 
 * @param nrows num of rows
 * @param ncols num of columns
 */
template <typename T>
void matrix2d_print(T** m, size_t nrows, size_t ncols)
{
    std::cout << "Matrix = [ " << std::endl;
    for ( size_t i = 0; i < nrows; i++ ) {
        std::cout << "\t"; 
        for ( size_t j = 0; j < ncols; j++ )  
            std::cout << m[i][j] << " ";
        std::cout << ";" << std::endl;
    }
    std::cout << "]" << std::endl;
}

#endif
