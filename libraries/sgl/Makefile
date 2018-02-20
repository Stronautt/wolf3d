# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: stronautt <phrytsenko@student.42.fr>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/12/10 17:05:19 by pgritsen          #+#    #+#              #
#    Updated: 2026/11/02 13:44:50 by stronautt        ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	libsgl.a

CC			=	gcc

CFLAGS		=	-Wextra -Werror -Wall -O3 -g3									\
				-ffunction-sections -fdata-sections

HDRS		=	sgl.h sgl_private.h

SRCS		=	sgl_draw_line.c sgl_plot.c sgl_new_window.c sgl_get_window.c	\
				sgl_init.c sgl_get_font.c sgl_add_font.c sgl_quit.c				\
				sgl_draw_str.c sgl_get_window_by_id.c sgl_resize_window.c		\
				s_sys_handler.c sgl_vsync.c sgl_get.c sgl_blit_line.c			\
				sgl_rewite.c sgl_fix_point.c sgl_apply_mask.c sgl_plot_m.c		\
				sgl_imgload.c sgl_str_size.c sgl_play.c sgl_update_window.c		\
				sgl_text.c sgl_ui.c sgl_ui_rect.c sgl_ui_event.c

OBJDIR		=	./obj

OBJ			=	$(addprefix $(OBJDIR)/, $(SRCS:.c=.o))

INCLUDES	=	-I ../libft

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(HDRS)
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
	@$(CC) -std=gnu17 $(CFLAGS) -MMD -MP -c $< -o $@ $(INCLUDES) `pkg-config --cflags sdl3 sdl3-ttf sdl3-image sdl3-mixer`
	@printf "\033[32m[DONE]\033[0m\n"

-include $(OBJ:.o=.d)

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
