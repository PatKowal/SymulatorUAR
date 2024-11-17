#pragma once
#include "Biblioteki.h"

class Kolejki
{
public:
	Kolejki() {
		Queue_EI = std::deque<double>(2, 0.0); // Rownoznaczny zapis: Queue_EI = { 0.0,0.0 };
	};
	~Kolejki() {};

protected:
	std::deque<double> Queue_EI, Queue_U, Queue_Y;
};