/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 09:37:42 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/09 09:45:06 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_message(char *msg, t_philo *phi)
{
	if (phi->all->dead)
		return ;
	pthread_mutex_lock(&phi->all->write_mutex);
	printf(msg, get_time() - phi->all->start, phi->i);
	pthread_mutex_unlock(&phi->all->write_mutex);
}

unsigned int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(long ms)
{
	unsigned int	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(ms / 10);
}

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
