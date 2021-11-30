CC=cc
sol:
	$(CC) -o solitaire -DUNICODE -Wall -lncursesw -ltinfo src/main.cpp src/card.cpp src/pile.cpp src/deskpile.cpp src/discardpile.cpp src/suitpile.cpp src/tablepile.cpp src/controller.cpp src/renderer.cpp src/game.cpp
debug:
	$(CC) -g -o solitaire -DUNICODE -Wall -lncursesw -ltinfo src/main.cpp src/card.cpp src/pile.cpp src/deskpile.cpp src/discardpile.cpp src/suitpile.cpp src/tablepile.cpp src/controller.cpp src/renderer.cpp src/game.cpp
ascii:
	$(CC) -o solitaire -Wall -lncursesw -ltinfo src/main.cpp src/card.cpp src/pile.cpp src/deskpile.cpp src/discardpile.cpp src/suitpile.cpp src/tablepile.cpp src/controller.cpp src/renderer.cpp src/game.cpp

