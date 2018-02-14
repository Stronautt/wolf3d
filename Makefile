# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/10 17:05:19 by pgritsen          #+#    #+#              #
#    Updated: 2018/02/14 17:26:06 by pgritsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	wolf3d

CC			=	gcc

CFLAGS		=	-Wextra -Wall -g3 -O3 -mwindows

CONFSRC		=	conf.rc

CONFOBJ		=	$(CONFSRC:.rc=.o)

HDRSDIR		=	./includes

HDRS		=	$(addprefix $(HDRSDIR)/, wolf.h)

SRCSDIR		=	./sources

SRCS		=	main.c sys_handler.c event.c movement.c fps.c draw.c map.c	\
				menu.c level_selector.c utils.c hud.c

OBJDIR		=	./obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

LIBFOLDER	=	./libraries

LIBSDEPS	=	$(addprefix $(LIBFOLDER)/, libft/libft.a sgl/libsgl.a)

INCLUDES	=	-I./includes
INCLUDES	+=	-I./frameworks/SDL2/include
INCLUDES	+=	-I./frameworks/SDL2_ttf/include
INCLUDES	+=	-I./frameworks/SDL2_image/include
INCLUDES	+=	-I./frameworks/SDL2_mixer/include
INCLUDES	+=	$(addprefix -I$(LIBFOLDER)/, libft sgl)

LIBRARIES	=	$(addprefix -L$(LIBFOLDER)/, libft sgl) -lft -lsgl
LIBRARIES	+=	$(addprefix -Lframeworks/, SDL2 SDL2_image SDL2_ttf) -lsdl2 -lsdl2main -lsdl2_image -lsdl2_ttf
LIBRARIES	+=	./ft.dll
LIBRARIES	+=	./sgl.dll
LIBRARIES	+=	./SDL2.dll
LIBRARIES	+=	./libjpeg-9.dll ./libpng16-16.dll ./libtiff-5.dll ./libwebp-7.dll		\
				./SDL2_image.dll ./zlib1.dll
LIBRARIES	+=	./libfreetype-6.dll ./SDL2_ttf.dll ./SDL2_mixer.dll ./libvorbisfile-3.dll
LIBRARIES	+=	./libvorbis-0.dll ./libogg-0.dll ./libmpg123-0.dll ./libmodplug-1.dll
LIBRARIES	+=	./libFLAC-8.dll

all: lib $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(HDRS) $(LIBSDEPS) $(CONFOBJ)
	@printf "\n\033[32m[Creating $(NAME)].......\033[0m"
	@$(CC) $(CFLAGS) -g -o $(NAME) $(OBJ) $(LIBRARIES) $(INCLUDES) $(CONFOBJ)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJDIR):
	@printf "\n\033[32m[Creating folder $(OBJDIR)].......\033[0m"
	@mkdir $(OBJDIR)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJ): $(OBJDIR)/%.o : $(SRCSDIR)/%.c
	@printf "\033[32m[Compiling $<].......\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
	@printf "\033[32m[DONE]\033[0m\n"

$(CONFOBJ):
	@windres.exe $(@:.o=.rc) $@

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
	@rm -rf $(CONFOBJ)
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
