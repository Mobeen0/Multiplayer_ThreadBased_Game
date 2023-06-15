*MUST HAVE SFML LIBRARY*:
TO EXECUTE:
g++ -O execName game.cpp -lsfml-graphics -lsfml-window -lsfml-system -lpthread


I Only used SFML library to generate game board,characters and display string on the board.
Rest I created some user defined data types in Utility.h 
The threads are used in handling each player movement and item collections.

Movements: 
	Player 1: Arrow keys
	PLayer 2: W,A,S,D
	Player 3: J,I,K,L
