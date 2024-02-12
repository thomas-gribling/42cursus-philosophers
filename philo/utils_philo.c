/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:54:39 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/12 10:55:08 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	put_message(char *msg, t_philo *phi)
{
	if (phi->all->dead && ft_strcmp(msg, MSG_DIE))
		return ;
	pthread_mutex_lock(&phi->all->write_mutex);
	printf(msg, get_time() - phi->all->start, phi->i);
	pthread_mutex_unlock(&phi->all->write_mutex);
}

void	put_msg_quick(char *msg, unsigned int time, int i)
{
	printf(msg, time, i);
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
