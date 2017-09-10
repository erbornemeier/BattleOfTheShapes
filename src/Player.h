/*
 *  CSCI 441 Computer Graphics, Fall 2017
 *
 *  Project: SQ1
 *  File: Player.h
 *
 *  Author: Easton Bornemeier
 *
 *  Description:
 *		This is the player class that handles drawing, shooting, and moving functionality
 *		for the player
 */


class Player{

public:

	Player(float x, float y);

	void shoot();
	void move();
	void drawPlayer();

private:
	float _posX;
	float _posY;
	Movement moving;

	static enum Movement {backwards = 1, stopped = 0, forwards = 1};
};