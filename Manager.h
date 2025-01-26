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
    Manager() : QObject(), sprzezeniezwrotne(), gen_wart() {}
    ~Manager() {}

public slots:

    void setGenerator(Sygnal typ, std::vector<double>& ParametryGen) {
        qDebug() << "ParametryGen:" << ParametryGen;

        gen_wart.setGen(typ, ParametryGen);
    }

    void setRegulatorPID(std::vector<double>& ParametryPID) {
        sprzezeniezwrotne.setPID(ParametryPID);
    }

    void setModelARX(std::vector<double>& A, std::vector<double>& B, int delay, double Z = 0.0) {
        sprzezeniezwrotne.setARX(A, B, delay, Z);
    }
    void ResetSim() {
        sprzezeniezwrotne.ResetSim();
        gen_wart.ResetCzas();
    }
    std::vector<double> Symuluj(double czas) {
        double wartZadana = gen_wart.GenerujSygnal(czas);
        return sprzezeniezwrotne.SimUAR(wartZadana);
    }

private:
    SprzezenieZwrotne sprzezeniezwrotne;
    GenWartZadana gen_wart;
};

