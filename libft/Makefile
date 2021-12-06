# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dmorty <dmorty@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/04/20 21:30:46 by dmorty            #+#    #+#              #
#    Updated: 2021/11/26 21:07:55 by dmorty           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libft.a

LIST =		ft_atoi.c		ft_bzero.c 		ft_isalnum.c\
			ft_isalpha.c	ft_isascii.c	ft_isdigit.c\
			ft_isprint.c	ft_memccpy.c	ft_memchr.c\
			ft_memcmp.c		ft_memcpy.c		ft_memmove.c\
			ft_strlen.c		ft_memset.c		ft_strchr.c\
			ft_strlcat.c	ft_strlcpy.c	ft_strncmp.c\
			ft_strrchr.c	ft_tolower.c	ft_str_add_c.c\
			ft_toupper.c	ft_calloc.c		ft_strdup.c\
			ft_putchar_fd.c	ft_putstr_fd.c	ft_putendl_fd.c\
			ft_putnbr_fd.c	ft_strjoin.c	ft_substr.c\
			ft_strtrim.c	ft_itoa.c		ft_split.c\
			ft_strmapi.c	ft_lstlast.c	ft_lstadd_back.c\
			ft_strisnum.c	ft_putstr_color_fd.c	get_next_line.c \
			long_atoi.c		ft_lstnew.c		ft_lstadd_front.c\
			ft_lstsize.c\
			ft_lstadd_back.c\
			ft_lstlast.c\
			ft_lstdelone.c\
			ft_lstclear.c\
			ft_lstiter.c\
			ft_lstmap.c
			
			

OBJ = $(patsubst %.c,%.o,$(LIST))

FLAGS = -Wall -Werror -Wextra

all : $(NAME)

$(NAME): $(OBJ)
	ar rcs $(NAME) $?

%.o : %.c
	gcc $(FLAGS) -c $< -o $@ 

clean :
	@rm -f $(OBJ)

fclean : clean
	@rm -f $(NAME)
re : fclean all

.PHONY : all clean fclean re bonus
