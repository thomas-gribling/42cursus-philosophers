/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tgriblin <tgriblin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/18 15:15:48 by tgriblin          #+#    #+#             */
/*   Updated: 2024/01/27 10:38:35 by tgriblin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define SLEEPING 0
# define THINKING 1
# define EATING 2

typedef struct s_philo
{
	int				state;
	int				curr_lifetime;
	pthread_t		t;
	pthread_mutex_t	fork;
}				t_philo;

typedef struct s_stats
{
	long		n_philos;
	long		n_eat;
	long		t_die;
	long		t_eat;
	long		t_sleep;
	int			i;
	t_philo		**philos;	
}				t_stats;

void	create_philos(t_stats *st);
long	ft_atol(char *s);

#endif