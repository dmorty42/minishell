# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/10/18 23:22:12 by dmorty            #+#    #+#              #
#    Updated: 2021/12/28 03:29:42 by dmorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS	=	./srcs/main.c\
			./srcs/env_parser.c\
			./srcs/checking.c\
			./srcs/parser.c\
			./srcs/parser_util.c\
			./srcs/checking_str.c\
			./srcs/two_dim.c\
			./utils/ft_strcmp.c\
			./utils/ft_lstnew_i.c\
			./utils/ft_atoi_long.c\
			./functions/buildin.c\
			./functions/cd_f.c\
			./srcs/redir_util.c\
			./functions/env_f.c\
			./functions/exit_f.c\
			./srcs/work_with_files.c\
			./srcs/heredoc.c\
			./srcs/pipe.c\
			./srcs/cmd_executing.c\
			./srcs/cleaning.c\
			./srcs/redirecting.c

HEAD	=	./includes/minishell.h
LIBFT	=	./libft/libft.a
NAME	=	minishell
OBJS	=	$(SRCS:.c=.o)


.c.o:
			$(GCC) $(FLAG) $(C) $< $(O) $(<:.c=.o)

GCC		= 	gcc
FLAG	=	-Wall -Wextra -Werror  
LINE	=	-lreadline
RM		=	rm -f
C		=	-c
O		=	-o

$(NAME):	$(OBJS)
			$(MAKE) -C ./libft
			$(MAKE) bonus -C ./libft
			$(GCC) $(LINE) $(FLAG) $(O) $(NAME) $(OBJS) $(LIBFT)

$(OBJS):	$(HEAD)

all:		$(NAME)

clean:
			$(MAKE) clean -C ./libft
			$(RM) $(OBJS)

fclean:		clean
			$(MAKE) fclean -C ./libft
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re