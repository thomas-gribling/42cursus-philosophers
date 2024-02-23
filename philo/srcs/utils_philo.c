/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:54:39 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/23 09:18:20 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	put_message(char *msg, t_philo *phi)
{
	pthread_mutex_lock(&phi->kill_mutex);
	if (phi->all->dead)
	{
		pthread_mutex_unlock(&phi->kill_mutex);
		return ;
	}
	pthread_mutex_lock(&phi->all->write_mutex);
	if (!phi->all->dead)
		printf(msg, get_time() - phi->start, phi->i + 1);
	pthread_mutex_unlock(&phi->all->write_mutex);
	pthread_mutex_unlock(&phi->kill_mutex);
}

void	put_msg_quick(char *msg, unsigned int time, int i)
{
	printf(msg, time, i + 1);
}

unsigned int	get_time(void)
{
	struct timeval	tv;

	if (gettimeofday(&tv, NULL))
		return (0);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

void	ft_usleep(unsigned int ms)
{
	unsigned int	start;

	start = get_time();
	while (get_time() - start < ms)
		usleep(ms / 10);
}

void	free_philos(t_philo **phi)
{
	int	i;

	i = -1;
	while (phi[++i])
		free(phi[i]);
	free(phi);
}
