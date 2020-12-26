GAME = _game$(shell python3-config --extension-suffix)

PYBIND_INCLUDE := `python3 -m pybind11 --includes`

GAME: game.h game.cpp cell.h util.h point.h
	g++ -O3 -Wall -shared --std=c++17 -fPIC $(PYBIND_INCLUDE) game.cpp -o $(GAME)

clean:
	rm -rf $(GAME)
