SRC = src/*.cpp

OBJ	=	$(SRC:.cpp=.o)

INCLUDE = -I ./include

NAME = pbrain-gomoku-ai

all : $(NAME)

$(NAME) :
	g++ -o $(NAME) $(SRC) $(INCLUDE)

re : fclean all

fclean : clean
	rm -f $(NAME)

clean :
	rm -f $(OBJ)

.PHONY : all re fclean clean