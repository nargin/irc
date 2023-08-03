# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: robin <robin@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/03 03:42:17 by romaurel          #+#    #+#              #
#    Updated: 2023/08/03 22:14:27 by robin            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	:=	ircserv

SOURCES	:=	./src
INCLUDES:=	./includes
OBJECTS	:=	./obj

SRCS	:=	main \
			Client \
			Server \
			utils \
			Channel \
			Commands \

OBJS	:=	$(foreach src,$(SRCS),$(OBJECTS)/$(src).o)

FLAGS	:=	-Wall -Wextra -Werror -std=c++98 -I includes

BLACK	:=	\033[30m
WHITE	:=	\033[37m
RED		:=	\033[31m
GRE		:=	\033[32m
GRA		:=	\033[37m
BLU		:=	\033[34m
PUR		:=	\033[35m
CYA		:=	\033[36m
YELLOW	:=	\033[33m
EOC		:=	\033[0m

${OBJECTS}/%.o: ${SOURCES}/%.cpp
	@echo "$(YELLOW)uwu: $(PUR)Compiling $^ 🤡$(EOC)"
	@mkdir -p $(dir $@)
	@g++ $(FLAGS) $^ -c -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@echo "$(WHITE)owo: $(GRE)Compiling $(NAME) 🥺 $(EOC)"
	@g++ $(FLAGS) $(OBJS) $(LINK) -o $(NAME)

run :
	@./$(NAME) 6667 hihi

lrun :
	@valgrind -q -s ./$(NAME) 6667 hihi

nc :
	@nc -v localhost 6667

clean:
	@echo "$(RED)Removing objects 💣$(EOC)"
	@rm -rf ${OBJECTS}

fclean: clean
	@echo "$(RED)zzz Removing binary 💤$(EOC)"
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re run bonus