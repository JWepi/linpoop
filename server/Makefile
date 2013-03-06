
NAME=	exec

SRC=	code/main.cpp \
	code/color.cpp \
	code/inits.cpp \
	code/utils.cpp \
	code/core.cpp \
	code/server.cpp \
	code/listener.cpp \
	code/actions.cpp \
	code/user.cpp \
	code/clientrcv.cpp \
        code/Packet.cpp \
	code/dataBuilder.cpp \
        code/usersManager.cpp

OBJ=	$(SRC:.cpp=.o)

CPPFLAGS=	-I./headfile

LFLAGS=	-lpthread

all:	$(NAME)

$(NAME):	$(OBJ)
		g++ -o exec/$(NAME) $(OBJ) $(LFLAGS)
		mv $(OBJ) Obj/
		@printf "\tProject 1 has been built !!\n"

clean:	
		rm -f Obj/*.o
		rm -f code/*.o
		@printf "\t.o files have been removed !!\n"

fclean:		clean
		rm -f exec/*
		@printf "\texecutable files have been removed !!\n"

lclean:
		rm -f logfile/*
		@printf "\tlogfiles have been removed !!\n"

dclean:
		rm -f data/users/*
		@printf "\tdata files have been removed !!\n"

sclean:		dclean lclean fclean

re:		fclean all

scrash:		sclean all
