# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    make_template.py                                   :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#              #
#    Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########         #
#                                                                              #
# **************************************************************************** #

MAKEFILE_PART1 = """\
# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tsudo <tsudo@student.42tokyo.jp>           +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/07/01 00:00:00 by tsudo             #+#    #+#              #
#    Updated: 2022/07/01 00:00:00 by tsudo            ###   ##########         #
#                                                                              #
# **************************************************************************** #

NAME	:= philo
CC		:= gcc
CFLAGS	:= -Wall -Wextra -Werror -MMD -MP -O0
LDFLAGS	:= -lpthread
RM		:= rm -f
LIBFT	:=
UNAME	:= $(shell uname)

ifeq ($(DEBUG), 1)
CFLAGS	+= -g3 -fsanitize=thread
endif

# **************************************************************************** #
"""

MAKEFILE_PART2 = """
INCS	:= \\
	includes \\
	$(dir $(LIBFT))/includes \\

LIBS	:= \\
	$(LIBFT) \\

# **************************************************************************** #

OBJDIR	= objs/
OBJS	= $(patsubst %.c,$(OBJDIR)%.o, $(notdir $(SRCS)))
DEPS	= $(OBJS:.o=.d)
CFLAGS	+= $(addprefix -I,$(INCS))
LDFLAGS	+= $(addprefix -L,$(dir $(LIBS)))
vpath %.c $(sort $(dir $(SRCS)))

GR	= \\033[32;1m
RE	= \\033[31;1m
YE	= \\033[33;1m
CY	= \\033[36;1m
RC	= \\033[0m

# **************************************************************************** #

all: $(NAME)

$(NAME): $(LIBS) $(OBJDIR) $(OBJS)
	@printf "\\n$(GR)=== Compiled [$(CC) $(CFLAGS)] ==="
	@printf "\\n--- $(notdir $(SRCS))$(RC)\\n"
	@$(CC) $(CFLAGS) $(OBJS) $(LIBS) $(LDFLAGS) -o $@
	@printf "$(YE)&&& Linked [$(CC) $(LDFLAGS)] &&&\\n--- $(NAME)$(RC)\\n"

-include $(DEPS)

$(OBJDIR):
	@mkdir -p $(OBJDIR)

$(OBJDIR)%.o: %.c
	@$(CC) $(CFLAGS) -c -o $@ $<
	@printf "$(GR)+$(RC)"

ifdef $(LIBFT)
$(LIBFT):
	@printf "\\n$(CY)~~~ Preparing $@ ~~~\\n$(RC)"
	@make -C $(dir $(LIBFT))
endif

mostlyclean:
	@printf "$(RE)--- Removing $(OBJDIR)$(RC)\\n"
	@$(RM) -r $(OBJDIR)

clean: mostlyclean
ifdef $(LIBFT)
	@printf "$(RE)--- Removing $(LIBFT)$(RC)\\n"
	@make -C $(dir $(LIBFT)) fclean
endif

fclean: clean
	@printf "$(RE)--- Removing $(NAME)$(RC)\\n"
	@$(RM) $(NAME)

re: fclean all

bonus: all

.PHONY: all mostlyclean clean fclean re bonus

# **************************************************************************** #
"""
