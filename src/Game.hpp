//
// Created by tiyst on 23/11/2019.
//

#ifndef SNAKERINO_GAME_HPP
#define SNAKERINO_GAME_HPP


class Game {

public:
	Game(ResourceLoader &rl);
	~Game();

	void run();


private:
	GameBoard* board;
	ResourceLoader &rl;


};


#endif //SNAKERINO_GAME_HPP
