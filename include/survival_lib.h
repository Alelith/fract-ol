/**
 * @file survival_lib.h
 * @brief Main header file for the Survival Library
 *
 * @author Lilith Estévez Boeta
 * @date November 3, 2025
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

char			*int_to_str(int n);
char			*uint_to_str(unsigned int n);
char			*float_to_str(float n, int decimals);
char			*bnum_to_str(int n, int base, int is_upper);
int				str_to_int(const char *nptr);
unsigned int	str_to_uint(const char *nptr);
float			str_to_float(const char *nptr);
int				to_upper(int c);
int				to_lower(int c);

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

int				print_format(const char *format, ...);

char			*get_next_line(int fd);

#endif
