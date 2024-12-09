#pragma once
#define M_PI 3.14159265358979323846 // pi
#include "Biblioteki.h"
enum class Sygnal { Krok, Prostokat, Sin };

class GenWartZadana
{
public:
	GenWartZadana(Sygnal typ, double t = 5.0, double A = 1.0, double T = 0.2, double p = 0.2)
		: typ(typ), t(t), A(A), T(T), p(p), i(0.0) 
	{
		WalidacjaParametrow();
	}
	~GenWartZadana() {};

	double GenerujSygnal(double czas) {
		i += czas;
		switch (typ) {
		case Sygnal::Krok:
			if (i <= t) {
				return A;
			}
			else {
				return 0.0;
			}
		case Sygnal::Prostokat:
			if (fmod(i, T) < p * T) {
				return A;
			}
			else {
				return 0.0;
			}
		case Sygnal::Sin:
			return (A * sin(2 * M_PI * fmod(i, T) / T));
		default:
			return 0.0;
		}
	}
	void setGen(Sygnal typ, double t, double A, double T, double p) {
		this->typ = typ;
		this->t = t;
		this->A = A;
		this->T = T;
		this->p = p;
		WalidacjaParametrow();
		i = 0.0;
	}

private:
	Sygnal typ;
	double t;	// chwila aktywacji
	double A;	// wart stala
	double T;	// okres 
	double p;	// wypelnienie
	double i;	// czas??

	void WalidacjaParametrow() {
		if (T <= 0) {
			throw std::invalid_argument("Okres musi byæ wiêkszy od 0!");
		}
		if (A <= 0) {
			throw std::invalid_argument("Amplituda musi byæ wiêksza od 0!");
		}
	}
};