#pragma once
#include <QObject>
#include <vector>
#include <cassert>
#include "SprzezenieZwrotne.h"
#include "GenWartZadana.h"
#include <QDebug>



class Manager : public QObject
{
    Q_OBJECT

public:
    Manager() : QObject(), loop(), gen_w() {}
    ~Manager() {}

public slots:

    void setGenerator(Sygnal typ, std::vector<double>& ParametryGen) {
        qDebug() << "ParametryGen:" << ParametryGen;

        gen_w.setGen(typ, ParametryGen);
    }

    void setRegulatorPID(std::vector<double>& ParametryPID) {
        loop.setPID(ParametryPID);
    }

    void setModelARX(std::vector<double>& A, std::vector<double>& B, int delay, double Z = 0.0) {
        loop.setARX(A, B, delay, Z);
    }
    void ResetSim() {
        loop.ResetSim();
        gen_w.ResetCzas();
    }
    std::vector<double> getWY(){
        return { gen_w.getWartZadana(),loop.getU_ost(),loop.getY_ost() };
    }
    void Symuluj(double czas) {
        double wartZadana = gen_w.GenerujSygnal(czas);
        loop.SimUAR(wartZadana);
    }

private:
    SprzezenieZwrotne loop;
    GenWartZadana gen_w;
};

