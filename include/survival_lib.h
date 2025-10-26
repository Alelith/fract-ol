/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   survival_lib.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 11:29:11 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/26 10:03:17 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/**
 * @mainpage Survival Library
 * 
 * This library provides a set of standard functions in C, including
 * check functions, conversion functions, memory functions, and string 
 * functions. It is designed to be a comprehensive utility library for 
 * C programming.
 * 
 * @section intro_sec Introduction
 * The Survival Library is a collection of functions that are 
 * commonly used in C programming.
 * 
 * @section usage_sec Usage
 * To use the Survival Library, include the header file `survival_lib.h` in 
 * your C source files. You can then call the functions provided by the 
 * library.
 * 
 * @section functions_sec Functions
 * The library provides the following categories of functions:
 * - [Check functions](group__check__functions.html): 
 * Functions to check character properties, string equality, etc.
 * - [Conversion functions](group__conversion__functions.html): 
 * Functions to convert between integers and strings,
 *  character case conversion, etc.
 * - [Memory functions](group__memory__functions.html): 
 * Functions for memory allocation, comparison and copying.
 * - [String functions](group__string__functions.html): 
 * Functions for string manipulation, 
 * including concatenation, splitting, and searching.
 * 
 * @section author_sec Authors
 * This library was developed by:
 * - Lilith Estévez Boeta
 */

/**
 * @file survival_lib.h
 * @author Lilith Estévez Boeta
 * @brief Header of the standard functions in C
 */

#ifndef SURVIVAL_LIB_H
# define SURVIVAL_LIB_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 256
# endif

# include <stddef.h>
# include <stdlib.h>
# include <fcntl.h>
# include <unistd.h>

/*=====================================================================
--------------------------- Check functions ---------------------------
=====================================================================*/

/**
 * @defgroup check_functions Check functions
 * @brief Functions to check character properties and string equality.
 */

int				is_alphabetic(int c);
int				is_alphanumeric(int c);
int				is_ascii(int c);
int				is_digit(int c);
int				is_from_set(char c, const char *set);
int				is_print(int c);
int				is_space(char c);
int				str_compare_all(const char *s1, const char *s2);
int				str_compare_n(const char *s1, const char *s2, size_t n);
int				str_contains(char *str, char *set);

/*=====================================================================
------------------------ Conversion functions -------------------------
=====================================================================*/

/**
 * @defgroup conversion_functions Conversion functions
 * @brief Functions for converting between different data types 
 * or representations.
 */

char			*int_to_str(int n);
char			*uint_to_str(unsigned int n);
char			*float_to_str(float n, int decimals);
char			*bnum_to_str(int n, int base, int is_upper);
int				str_to_int(const char *nptr);
unsigned int	str_to_uint(const char *nptr);
float			str_to_float(const char *nptr);
int				to_upper(int c);
int				to_lower(int c);

/*=====================================================================
-------------------------- Memory functions ---------------------------
=====================================================================*/

/**
 * @defgroup memory_functions Memory functions
 * @brief Functions for managing memory.
 */

void			*callocation(size_t nmemb, size_t size);
void			*reallocation(void *ptr, unsigned long new_size,
					unsigned long old_size);
int				mem_compare(const void *s1, const void *s2, size_t n);
void			*mem_copy(void *dest, const void *src, size_t n);
int				mem_len(void *ptr, size_t blk_size);
void			*mem_move(void *dest, const void *src, size_t n);
void			*mem_search(const void *s, int c, size_t n);
void			*mem_set(void *s, int c, size_t n);
void			set_zero(void *s, size_t n);

/*=====================================================================
-------------------------- String functions ---------------------------
=====================================================================*/

/**
 * @defgroup string_functions String functions
 * @brief Functions for manipulating strings.
 */

size_t			str_concat(char *dst, const char *src, size_t size);
size_t			str_copy(char *dst, const char *src, size_t size);
char			*str_duplicate(const char *s);
char			*str_join(char const *s1, char const *s2);
size_t			str_len(const char *str);
char			*str_search_char(const char *s, int c);
char			*str_search_rev_char(const char *s, int c);
char			*str_search_str(const char *big, const char *little,
					size_t len);
char			**str_split(char const *s, char c);
char			*str_substring(char const *s, unsigned int start, size_t len);
char			*str_trim(char const *s1, char const *set);

/*=====================================================================
--------------------------- Print formatted ---------------------------
=====================================================================*/

/**
 * @defgroup print_functions Print functions
 * @brief Function for printing in a specified format.
 */

int				print_format(const char *format, ...);

/*=====================================================================
---------------------------- Get next line ----------------------------
=====================================================================*/

/**
 * @defgroup get_next_line Get Next Line
 * @brief Function to read a line from a file descriptor.
 */

char			*get_next_line(int fd);

#endif
