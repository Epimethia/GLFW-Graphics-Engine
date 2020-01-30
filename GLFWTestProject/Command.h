#pragma once

//TEMPORARY POINTER TO A GAME ACTOR
class GameActor;

//Command base class implementation. This is essentially a glorified
//functor.
class Command {
private:

public:
	virtual ~Command() {};
	virtual void execute(GameActor& _Actor) = 0;
};

