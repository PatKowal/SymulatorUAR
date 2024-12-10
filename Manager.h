#pragma once
#include "Biblioteki.h"
#include "SprzezenieZwrotne.h"

class Manager
{
public:
	Manager(std::vector<double>& A, std::vector<double>& B, int delay, double Z, std::vector<double>& ParametryPID)
		: A(A), B(B), delay(delay), ParametryPID(ParametryPID) {};
	~Manager() {};

	void setGen(Sygnal typ, std::vector<double>& ParametryGen) {
		gen_w.setGen(typ, ParametryGen);
	};
	void setPID(std::vector<double>& ParametryPID) {
		loop.setPID(ParametryPID);
		loop.ResetPID();
	};
	void setARX(std::vector<double>& A, std::vector<double>& B, int delay, double Z) {
		loop.setARX(A, B, delay, Z);
	};
	std::vector<double> getWY() {
		std::vector<double>WY;
		WY[0] = gen_w.getWartZadana();
		WY[1] = loop.getU_ost();
		WY[2] = loop.getY_ost();
		return WY;
	};

private:
	SprzezenieZwrotne loop;
	GenWartZadana gen_w;
	std::vector<double>A, B, ParametryPID;
	int delay;
};