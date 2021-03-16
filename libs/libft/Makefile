# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: weambros <weambros@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/11/07 23:16:07 by weambros          #+#    #+#              #
#    Updated: 2021/03/15 13:31:34 by weambros         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a
OBJS_PATH		=	objs/
HEADER			=	libft.h
SRCS		=	ft_atoi.c			ft_isalnum.c 			ft_isalpha.c		\
				ft_isascii.c		ft_isdigit.c			ft_isprint.c		\
				ft_strchr.c			ft_strlcat.c			ft_strlcpy.c		\
				ft_strlen.c			ft_strncmp.c			ft_strnstr.c		\
				ft_strdup.c			ft_tolower.c			ft_toupper.c		\
				ft_memset.c			ft_memcmp.c				ft_memchr.c			\
				ft_bzero.c			ft_substr.c				ft_strjoin.c		\
				ft_strtrim.c		ft_split.c				ft_itoa.c			\
				ft_strmapi.c		ft_putchar_fd.c			ft_putnbr_fd.c		\
				ft_putstr_fd.c		ft_putendl_fd.c			ft_calloc.c			\
				ft_lstnew.c			ft_lstadd_front.c		ft_lstsize.c		\
				ft_lstlast.c		ft_lstadd_back.c		ft_lstdelone.c		\
				ft_lstclear.c		ft_lstiter.c			ft_lstmap.c			\
				ft_isspace.c		get_next_line.c
OBJS_LIST		=	$(patsubst %.c, %.o, $(SRCS))
OBJS			=	$(addprefix $(OBJS_PATH),$(OBJS_LIST))
CC				=	gcc
CFLAGS			=	-Wall -Wextra -Werror -c -I
RM				=	rm -rf
MAKE_LIBFT		=	make -C /libs/libft
.PHONY:	all clean fclean

all: $(NAME) 

$(NAME): $(OBJS_PATH) $(OBJS) 
	@ar rcs $(NAME) $(OBJS)

$(OBJS_PATH):
	@mkdir -p $(OBJS_PATH)

$(OBJS_PATH)%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) $(HEADER) $< -o $@

clean:
	@$(RM) $(OBJS_PATH)
	@$(RM) $(OBJS_PATH_BONUS)

fclean: clean
	@$(RM) $(NAME)

re: fclean all