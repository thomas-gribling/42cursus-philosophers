/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:37:42 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/19 09:02:04 by tgriblin         ###   ########.fr       */
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

int	is_num(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		if (s[i] < '0' || s[i] > '9')
			return (0);
	return (1);
}

int	ft_strlen(char *s)
{
	int	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *s)
{
	int	i;

	i = -1;
	while (s[++i])
		ft_putchar(s[i]);
}

size_t	unsigned_len(unsigned int n)
{
	size_t	len;
	
	len = 1;
	while (n > 9)
	{
		n /= 10;
		len++;
	}
	return (len);
}

void	ft_putnbr(unsigned int n, size_t len)
{
	size_t	n_len;

	n_len = unsigned_len(n);
	while (len > n_len)
	{
		ft_putchar(' ');
		len--;
	}
	if (n > 9)
		ft_putnbr(n / 10, 0);
	ft_putchar(n % 10 + '0');
}
