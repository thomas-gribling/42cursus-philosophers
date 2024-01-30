/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/19 10:13:12 by tgriblin          #+#    #+#             */
/*   Updated: 2024/01/27 10:43:15 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

// tous commencer par penser
// si temps de vie < temps penser + temps manger = DEAD

void	*output_thread(void *vargp)
{
	t_stats	*st;

	st = (t_stats *)vargp;
	st->philos[st->i]->state = THINKING;
	printf("thread created! (%p)\n", vargp);
	return (NULL);
}

void	create_philos(t_stats *st)
{
	st->philos = malloc((st->n_philos + 1) * sizeof(t_philo *));
	st->i = -1;
	while (++st->i < st->n_philos)
	{
		st->philos[st->i] = malloc(sizeof(t_philo));
		st->philos[st->i]->curr_lifetime = st->t_die;
		pthread_create(&st->philos[st->i]->t, NULL, output_thread, st);
		pthread_mutex_init(&st->philos[st->i]->fork, NULL);
		pthread_join(st->philos[st->i]->t, NULL);
	}
	st->philos[st->i] = NULL;
}
