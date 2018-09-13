# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phrytsenko <phrytsenko@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/10 17:05:19 by pgritsen          #+#    #+#              #
#    Updated: 2018/08/09 11:51:23 by phrytsenko       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	wolf3d

CC			=	gcc

CFLAGS		+=	-Wextra -Wextra -Wall -O3 -g3 -fno-unwind-tables				\
				-fno-asynchronous-unwind-tables

BFLAGS		=	-s -ffunction-sections -fdata-sections	-fno-ident				\
				-fmerge-all-constants

HDRSDIR		=	./includes

HDRS		=	$(addprefix $(HDRSDIR)/, wolf.h)

SRCSDIR		=	./sources

SRCS		=	main.c sys_handler.c event.c movement.c fps.c draw.c draw_ext.c	\
				map.c menu.c level_selector.c hud.c utils.c fun.c

OBJDIR		=	./obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFOLDER	=	./libraries

LIBSDEPS	=	$(addprefix $(LIBFOLDER)/, libft/libft.a sgl/libsgl.a)

INCLUDES	=	-I./includes
INCLUDES	+=	$(addprefix -I$(LIBFOLDER)/, libft sgl)

LIBRARIES	=	$(addprefix -L$(LIBFOLDER)/, libft sgl) -lsgl -lft `sdl2-config --libs` -lm -pthread -lSDL2_ttf -lSDL2_image -lSDL2_mixer

RESDIR		=	resources

all: lib $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(HDRS) $(LIBSDEPS)
	@printf "\n\033[32m[Creating $(NAME)].......\033[0m"
	@$(CC) $(CFLAGS) $(BFLAGS) -o $(NAME) $(OBJ) $(LIBRARIES)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJDIR):
	@printf "\n\033[32m[Creating folder $(OBJDIR)].......\033[0m"
	@mkdir $(OBJDIR)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJ): $(OBJDIR)/%.o : $(SRCSDIR)/%.c $(HDRS)
	@printf "\033[32m[Compiling $<].......\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@printf "\033[32m[DONE]\033[0m\n"

$(LIBSDEPS): lib

lib:
	@printf "\033[33m[Creating libft.a].......[START]\033[0m\n"
	@make -j3 -C $(LIBFOLDER)/libft
	@printf "\033[33m[Creating libft.a].......[END]\033[0m\n\n"
	@printf "\033[33m[Creating libsgl.a].......[START]\033[0m\n"
	@make -j3 -C $(LIBFOLDER)/sgl
	@printf "\033[33m[Creating libsgl.a].......[END]\033[0m\n"

clean:
	@printf "\n\033[31m[Cleaning $(NAME) object files].......\033[0m"
	@rm -rf $(OBJDIR)
	@printf "\033[31m[DONE]\033[0m\n"

clean_%:
	@make -j3 -C $(LIBFOLDER)/$(subst clean_,,$@) clean

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[31m[Removing $(NAME)].......[DONE]\033[0m\n"

fclean_%:
	@make -j3 -C $(LIBFOLDER)/$(subst fclean_,,$@) fclean

rebuild_message:
	@printf "\033[33m[Rebuild $(NAME)].......[START]\033[0m\n"

re:	rebuild_message fclean all
	@printf "\033[33m[Rebuild $(NAME)].......[END]\033[0m\n"

re_%:
	@make -j3 -C $(LIBFOLDER)/$(subst re_,,$@) re

.NOTPARALLEL: all $(NAME) re
