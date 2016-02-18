#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_struct
{
  int		i;
  int		x;
  int		pid;
  char		*str;
  unsigned char	c;
}		t_talk;

t_talk	talk;

void	my_new_str(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    i++;
  talk.str = malloc(sizeof (char) * (i + 1));
  i = 0;
  while (str[i])
    talk.str[i] = str[i++];
  talk.str[i] = 4;
}

int	my_getnbr(char *str)
{
  int	i;
  int	res;

  i = 0;
  res = 0;
  while(str[i] != 0)
    res = res * 10 + (str[i++] - '0');
  return (res);
}

void	decompos_int(unsigned int c, int pid)
{
  unsigned int b;
  int i;

  i = 15;
  while (i >= 0)
    {
      b = (c >> i) & 1;
      if (b == 0)
	kill(pid, SIGUSR1);
      else
	kill(pid, SIGUSR2);
      usleep(1000);
      i--;
    }
}

void	my_sig()
{
  talk.c = (talk.str[talk.x] >> talk.i) & 1;
  talk.i--;
  if (talk.c == 0)
    kill(talk.pid, SIGUSR1);
  else
    kill(talk.pid, SIGUSR2);
  if (talk.i < 0)
    {
      talk.i = 7;
      talk.x++;
    }
}

int	main(int ac, char **av)
{
  int	pid;

  if (ac > 2)
    {
      signal(SIGUSR1, my_sig);
      signal(SIGUSR2, my_sig);
      talk.pid = my_getnbr(av[1]);
      my_new_str(av[2]);
      talk.x = 0;
      talk.i = 7;
      decompos_int(getpid(), talk.pid);
      while(talk.str[talk.x])
	pause();
      free(talk.str);
    }
  return (0);
}
