/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   states.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/05 08:52:55 by tgriblin          #+#    #+#             */
/*   Updated: 2024/02/05 09:49:01 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void	start_eating(t_stats *st, int n)
{
	int	left;
	int	right;

	left = n - 1;
	if (n == 0)
		left = st->n_philos - 1;
	right = n + 1;
	if (n == st->n_philos - 1)
		right = 0;
	pthread_mutex_lock(&st->philos[left]->fork);
	put_msg(st, MSG_TOOK_FORK, n + 1);
	pthread_mutex_lock(&st->philos[right]->fork);
	put_msg(st, MSG_TOOK_FORK, n + 1);
	st->philos[n]->state = EATING;
	put_msg(st, MSG_EATING, n + 1);
}

void	start_sleeping(t_stats *st, int n)
{
	int	left;
	int	right;

	left = n - 1;
	if (n == 0)
		left = st->n_philos - 1;
	right = n + 1;
	if (n == st->n_philos - 1)
		right = 0;
	pthread_mutex_unlock(&st->philos[left]->fork);
	pthread_mutex_unlock(&st->philos[right]->fork);
	st->philos[n]->state = SLEEPING;
	put_msg(st, MSG_SLEEP, n + 1);
}

void	start_thinking(t_stats *st, int n)
{
	st->philos[n]->state = THINKING;
	put_msg(st, MSG_THINK, n + 1);
}
