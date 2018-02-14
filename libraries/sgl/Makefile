# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pgritsen <pgritsen@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/10 17:05:19 by pgritsen          #+#    #+#              #
#    Updated: 2018/02/10 14:49:45 by pgritsen         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libsgl.a
DLLNAME		=	sgl.dll

CC			=	gcc

CFLAGS		=	-Wextra -Werror -Wall -O3 -g3

HDRS		=	sgl.h sgl_private.h

SRCS		=	sgl_draw_line.c sgl_plot.c sgl_new_window.c sgl_get_window.c	\
				sgl_init.c sgl_get_font.c sgl_add_font.c sgl_quit.c				\
				sgl_draw_str.c sgl_get_window_by_id.c sgl_resize_window.c		\
				s_sys_handler.c sgl_vsync.c sgl_get.c sgl_blit_line.c

OBJDIR		=	obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

INCLUDES	=	-I ../libft
INCLUDES	+=	-I../../frameworks/SDL2/include
INCLUDES	+=	-I../../frameworks/SDL2_ttf/include
INCLUDES	+=	-I../../frameworks/SDL2_image/include
INCLUDES	+=	-I../../frameworks/SDL2_mixer/include

LIBRARIES	=	../libft/ft.dll
LIBRARIES	+=	../../frameworks/SDL2/SDL2.dll
LIBRARIES	+=	../../frameworks/SDL2_image/libjpeg-9.dll ../../frameworks/SDL2_image/libpng16-16.dll	\
				../../frameworks/SDL2_image/libtiff-5.dll ../../frameworks/SDL2_image/libwebp-7.dll		\
				../../frameworks/SDL2_image/SDL2_image.dll ../../frameworks/SDL2_image/zlib1.dll
LIBRARIES	+=	../../frameworks/SDL2_ttf/libfreetype-6.dll ../../frameworks/SDL2_ttf/SDL2_ttf.dll		\
				../../frameworks/SDL2_ttf/zlib1.dll
LIBRARIES	+=	../../frameworks/SDL2_mixer/SDL2_mixer.dll ../../frameworks/SDL2_mixer/libvorbisfile-3.dll	\
				../../frameworks/SDL2_mixer/libvorbis-0.dll ../../frameworks/SDL2_mixer/libogg-0.dll	\
				../../frameworks/SDL2_mixer/libmpg123-0.dll ../../frameworks/SDL2_mixer/libmodplug-1.dll	\
				../../frameworks/SDL2_mixer/libFLAC-8.dll

all: $(NAME)

$(NAME): $(DLLNAME) $(OBJDIR) $(OBJ) $(OBJM) $(HDRS)
	@printf "\033[32m[Creating $(NAME)].......\033[0m"
	@$(CC) $(CFLAGS) -shared -o $(DLLNAME) $(OBJ) $(LIBRARIES)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJDIR):
	@printf "\033[32m[Creating folder $(OBJDIR)].......\033[0m"
	@mkdir $(OBJDIR)
	@printf "\033[32m[DONE]\033[0m\n"

$(OBJ): $(OBJDIR)/%.o : %.c
	@printf "\033[32m[Compiling $<].......\033[0m"
	@$(CC) $(CFLAGS) -c $< -o $@ $(INCLUDES)
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
