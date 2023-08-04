CXXFLAGS = -g -std=c++11
FLAG_SFML = -lsfml-graphics -lsfml-window -lsfml-system
DIR_SRC = src
DIR_HD = hd
DIR_OBJ = obj
CONST = $(DIR_HD)/constantes.hpp
OBJ= $(DIR_OBJ)/main.o $(DIR_OBJ)/snake.o $(DIR_OBJ)/game_hdlr.o

Snake: $(OBJ)
	g++ $^ -o $@ $(CXXFLAGS) $(FLAG_SFML)
	rm -f $(DIR_HD)/*~
	rm -f $(DIR_SRC)/*~

$(DIR_OBJ)/main.o: $(DIR_SRC)/main.cpp $(CONST) $(DIR_HD)/snake.hpp
	g++ -o $@ -c $< $(CXXFLAGS)

$(DIR_OBJ)/game_hdlr.o: $(DIR_HD)/snake.hpp

$(DIR_OBJ)/%.o: $(DIR_SRC)/%.cpp $(DIR_HD)/%.hpp $(CONST)
	g++ -o $@ -c $< $(CXXFLAGS)

clean:
	rm -f $(DIR_OBJ)/*.o $(DIR_HD)/*~ $(DIR_SRC)/*~

CLEAN:
	rm -f $(DIR_OBJ)/*.o $(DIR_HD)/*~ $(DIR_SRC)/*~ Snake
