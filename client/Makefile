NAME=	client

SRC=	Packet.cpp	\
		Client.cpp	\
		dataBuilder.cpp	\
		main.cpp

OBJ=	$(SRC:.cpp=.o)

FLAGS=	-lpthread

all:	$(NAME)

$(NAME):	$(OBJ)
	g++ $(OBJ) -o $(NAME) $(FLAGS)

clean:
	rm -f $(OBJ)

fclean:	clean
	rm -f $(NAME)

re:	fclean all
