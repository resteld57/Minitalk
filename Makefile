##
## Makefile for makefile in 
## 
## Made by Dylan RESTELLI
## Login   <restel_d@epitech.net>
## 
## Started on  Mon Dec 21 15:28:49 2015 Dylan RESTELLI
## Last update Wed Feb 17 23:54:59 2016 restel_d
##

CC      =       gcc

RM      =       rm -f

NAME	=	server/server

NAME2	=	client/client

SRCS	=	server/serveur_2.c

SRCS2	=	client/test.c

OBJS	=	$(SRCS:.c=.o)

OBJS2	=	$(SRCS2:.c=.o)

all	:	$(NAME) $(NAME2)

$(NAME)	:	$(OBJS)
	$(CC) -o $(NAME) $(OBJS)

$(NAME2):	$(OBJS2)
	$(CC) -o $(NAME2) $(OBJS2)

clean   :
	$(RM) $(OBJS) $(OBJS2)

fclean	:	clean
	$(RM) $(NAME) $(NAME2)

re      :	fclean all
