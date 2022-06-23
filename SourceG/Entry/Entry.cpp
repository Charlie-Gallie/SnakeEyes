#include <iostream>

#include "../SnakeEyes/SnakeEyes.h"

using namespace std;

int main() {
	/*	This is a pointer rather than a stack alloc'd object	*/
	/*	incase the size of the object exceeds the stack size.	*/
	/*	I'm not sure if it matters though.						*/
	SnakeEyes* snakeEyes = new SnakeEyes;
	snakeEyes->begin();
	delete snakeEyes;

	return 0;
}