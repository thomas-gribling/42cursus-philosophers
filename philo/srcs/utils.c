/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:37:42 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/23 08:37:31 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

long	ft_atol(char *s)
{
	long	i;
	long	sign;
	long	sign_count;
	long	out;

	i = 0;
	sign = 1;
	sign_count = 0;
	out = 0;
	while (s[i] == ' ' || (s[i] >= 9 && s[i] <= 13))
		i++;
	while (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-')
			sign = -sign;
		i++;
		sign_count++;
	}
	while (s[i] >= '0' && s[i] <= '9' && sign_count < 2)
	{
		out = 10 * out + s[i] - '0';
		i++;
	}
	return (sign * out);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

int	ft_min(int a, int b)
{
	if (a < b)
		return (a);
	return (b);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

int	ft_puterror(char *s, int format)
{
	int	i;

	i = -1;
	if (format)
		write(2, "Error: ", 7);
	while (s[++i])
		write(2, &s[i], 1);
	if (format)
		write(2, "\n", 1);
	return (1);
}
