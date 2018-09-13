# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: phrytsenko <phrytsenko@student.42.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/10 17:05:19 by pgritsen          #+#    #+#              #
#    Updated: 2018/08/09 11:52:00 by phrytsenko       ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libsgl.a

CC			=	gcc

CFLAGS		=	-Wextra -Werror -Wall -O3 -g3

HDRS		=	sgl.h sgl_private.h

SRCS		=	sgl_draw_line.c sgl_plot.c sgl_new_window.c sgl_get_window.c	\
				sgl_init.c sgl_get_font.c sgl_add_font.c sgl_quit.c				\
				sgl_draw_str.c sgl_get_window_by_id.c sgl_resize_window.c		\
				s_sys_handler.c sgl_vsync.c sgl_get.c sgl_blit_line.c			\
				sgl_rewite.c sgl_fix_point.c sgl_apply_mask.c sgl_plot_m.c		\
				sgl_imgload.c sgl_str_size.c

OBJDIR		=	./obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

INCLUDES	=	-I ../libft

ifeq ($(OS), Linux)
	INCLUDES	+= `sdl2-config --cflags --libs` -lSDL2 -lSDL2_image -lSDL2_mixer -lSDL2_ttf -lm
else
	INCLUDES	+=	-I../../frameworks/SDL2.framework/Headers
	INCLUDES	+=	-I../../frameworks/SDL2_ttf.framework/Headers
	INCLUDES	+=	-I../../frameworks/SDL2_image.framework/Headers
	INCLUDES	+=	-I../../frameworks/SDL2_mixer.framework/Headers
	INCLUDES	+=	-F../../frameworks
endif

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(OBJM) $(HDRS)
	@printf "\033[32m[Creating $(NAME)].......\033[0m"
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJDIR):
	@printf "\033[32m[Creating folder $(OBJDIR)].......\033[0m"
	@mkdir $(OBJDIR)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJ): $(OBJDIR)/%.o : %.c $(HDRS)
	@printf "\033[32m[Compiling $<].......\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES) `sdl2-config --cflags`
	@printf "\033[32m[DONE]\033[0m\n"

clean:
	@printf "\033[31m[Cleaning $(NAME) object files].......\033[0m"
	@rm -rf $(OBJDIR)
	@printf "\033[31m[DONE]\033[0m\n"

fclean: clean
	@rm -rf $(NAME)
	@printf "\033[31m[Removing $(NAME)].......[DONE]\033[0m\n"

rebuild_message:
	@printf "\033[33m[Rebuild $(NAME)].......[START]\033[0m\n"

re:	rebuild_message fclean all
	@printf "\033[33m[Rebuild $(NAME)].......[END]\033[0m\n"

.NOTPARALLEL: all $(NAME) re
