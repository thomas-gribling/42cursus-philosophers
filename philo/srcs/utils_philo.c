/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_philo.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 10:54:39 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/20 08:44:58 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/philo.h"

void	put_message(char *msg, t_philo *phi)
{
	pthread_mutex_lock(&phi->all->write_mutex);
	if (!(phi->all->dead && ft_strcmp(msg, MSG_DIE)))
	{
		ft_putstr("|");
		ft_putnbr(get_time() - phi->all->start, 6);
		ft_putstr(" ");
		ft_putnbr(phi->i + 1, 4);
		ft_putstr(msg);
	}
	pthread_mutex_unlock(&phi->all->write_mutex);
}

void	put_msg_quick(char *msg, unsigned int time, int i)
{
	ft_putstr("|");
	ft_putnbr(time, 6);
	ft_putstr(" ");
	ft_putnbr(i + 1, 4);
	ft_putstr(msg);
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

void	free_philos(t_philo **phi)
{
	int	i;

	i = -1;
	while (phi[++i])
		free(phi[i]);
	free(phi);
}
