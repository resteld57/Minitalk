#include <stdio.h>
#include <signal.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct	s_talk
{
  unsigned int	pid;
  unsigned int	tmp_pid;
  unsigned char	c;
  unsigned char tmp_c;
  int		pos;
}		t_talk;

t_talk	talk;

void	my_clientpid(int sig)
{
  if (talk.pos >= 0)
    {
      talk.tmp_pid = talk.tmp_pid << 1;
      sig == 12 ? talk.tmp_pid++ : 0;
      talk.pos--;
    }
  if (talk.pos < 0)
    {
      talk.pid = talk.tmp_pid;
      talk.tmp_pid = 0;
      talk.pos = 8;
      kill(talk.pid, SIGUSR1);
    }
}

void	my_signal(int sig)
{
  if (talk.pid != 0)
    {
      sig == 10 ? (talk.c = (talk.c << 1)) : (talk.c = (talk.c << 1) + 1);
      talk.pos--;
      if (talk.pos == 0)
	{
	  talk.pos = 8;
	  if (talk.c != 4)
	    write(1, &(talk.c), 1);
	  else
	    {
	      talk.pid = 0;
	      talk.pos = 15;
	    }
	  talk.c = 0;
	}
      talk.pid != 0 ? kill(talk.pid, SIGUSR1) : 0;
    }
  else
    my_clientpid(sig);
}

int	main()
{
  printf("%d\n", getpid());
  talk.pid = 0;
  talk.tmp_pid = 0;
  talk.pos = 15;
  talk.c = 0;
  signal(SIGUSR1, my_signal);
  signal(SIGUSR2, my_signal);
  while (1)
    pause();
}
