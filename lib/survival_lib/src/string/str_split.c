/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   str_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: acesteve <acesteve@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/24 23:15:38 by acesteve          #+#    #+#             */
/*   Updated: 2025/10/26 10:02:33 by acesteve         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "survival_lib.h"

/**
 * @file str_split.c
 * @author Lilith Estévez Boeta
 * @brief This file contains the implementation of the str_split function.
 */

/**
 * @brief Helper function to calculate the length of a word until the delimiter.
 * 
 * @param s The string to analyze.
 * @param c The delimiter character.
 * 
 * @return The length of the word.
 */
static int	word_len(char const *s, char c)
{
	int	len;

	len = 0;
	while (s && s[len] && s[len] != c)
		len++;
	return (len);
}

/**
 * @brief Helper function to free all strings in an array.
 * 
 * @param res The array of strings to free.
 * @param len The number of strings to free.
 */
static void	free_split_array(char **res, int len)
{
	while (len > 0)
		free(res[--len]);
	free(res);
}

/**
 * @brief Helper function to allocate and add a word to the result array.
 * 
 * @param res The result array (will be reallocated).
 * @param s The source string.
 * @param i The index in the source string.
 * @param c The delimiter character.
 * @param len Pointer to the current number of elements.
 * 
 * @return The reallocated array, or NULL on error.
 */
static char	**add_word(char **res, char const *s, char c, int *len)
{
	char	**tmp;
	char	*word_end;

	tmp = reallocation(res, sizeof(char *) * (*len + 2),
			sizeof(char *) * (*len + 1));
	if (!tmp)
		return (NULL);
	res = tmp;
	word_end = str_search_char(s, c);
	if (word_end)
		res[*len] = str_substring(s, 0, word_end - s);
	else
		res[*len] = str_substring(s, 0, str_len(s));
	if (!res[*len])
		return (NULL);
	(*len)++;
	return (res);
}

/**
 * @brief Helper function to process the main splitting loop.
 * 
 * @param s The source string.
 * @param c The delimiter character.
 * @param res Pointer to the result array pointer.
 * @param len Pointer to the current number of elements.
 * 
 * @return 0 on success, -1 on error.
 */
static int	split_loop(char const *s, char c, char ***res, int *len)
{
	int		i;

	i = 0;
	while (s[i])
	{
		while (s[i] && s[i] == c)
			i++;
		if (!s[i])
			break ;
		*res = add_word(*res, &s[i], c, len);
		if (!*res)
			return (-1);
		i += word_len(&s[i], c);
	}
	return (0);
}

/**
 * @brief Splits a string into an array of strings based on a delimiter.
 * @ingroup string_functions
 * 
 * @param s The string to split.
 * @param c The delimiter character.
 * 
 * @return An array of strings (NULL-terminated) where the string was split.
 * @retval NULL if the allocation failed.
 * @warning Needs to be freed after use, including each string in the array.
 */
char	**str_split(char const *s, char c)
{
	int		len;
	char	**tmp;
	char	**res;

	if (!s)
		return (NULL);
	len = 0;
	res = NULL;
	if (split_loop(s, c, &res, &len) == -1)
	{
		free_split_array(res, len);
		return (NULL);
	}
	tmp = reallocation(res, sizeof(char *) * (len + 1),
			sizeof(char *) * len);
	if (!tmp)
	{
		free_split_array(res, len);
		return (NULL);
	}
	res = tmp;
	res[len] = NULL;
	return (res);
}
