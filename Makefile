# definfitely overkill, especially for this small program

EXEC			= sudoku_solver

# Makefile for C programs 
SRC				= src
BIN				= bin

SRCS			= $(wildcard $(SRC)/*.c)
TARGET			= $(EXEC)

OBJ				=  $(patsubst $(SRC)/%.c,$(BIN)/%.o,$(SRCS)) 

CXX 			= gcc
CFLAGS 			= -Wall
RM 				= rm
RMFLAGS			= -rf

all:			$(TARGET)

# create objects
$(BIN)/%.o: $(SRC)/%.c
				$(CXX) $(CFLAGS) -o $@ -c $<


$(TARGET):		$(OBJ)
				$(CXX) $(CFLAGS) -o $@ $^
				@echo [INFO]: build successful: '$(TARGET)'

clean:
				$(RM) $(RMFLAGS) ./$(BIN)/*.o ./$(EXEC)/*
				@echo [INFO]: clean successful.