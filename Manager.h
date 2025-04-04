#pragma once
#include <QObject>
#include <vector>
#include <cassert>
#include "SprzezenieZwrotne.h"
#include "GenWartZadana.h"
#include <QFile>
#include <QString>
#include <QMessageBox>
#include <QWidget>

class Manager : public QObject
{
    Q_OBJECT

public:
    Manager() : QObject(), sprzezeniezwrotne(), gen_wart() {}
    ~Manager() {}

public slots:

    void setGenerator(Sygnal typ, std::vector<double>& ParametryGen) { gen_wart.setGen(typ, ParametryGen); }
    void setRegulatorPID(std::vector<double>& ParametryPID) { sprzezeniezwrotne.setPID(ParametryPID); }
    void setTrybPID(const bool Tryb) { sprzezeniezwrotne.setTrybPID(Tryb); }
    void setModelARX(std::vector<double>& A, std::vector<double>& B, int delay, double Z = 0.0) { sprzezeniezwrotne.setARX(A, B, delay, Z); }
    void ResetSim() { sprzezeniezwrotne.ResetSim(); }
    void ResetPID() { sprzezeniezwrotne.ResetPID(); }

    std::vector<double> Symuluj(double czas) {
        double wartZadana = gen_wart.GenerujSygnal(czas);
        return sprzezeniezwrotne.SimUAR(wartZadana);
    }

    void zapisz(const std::vector<double>& ParametryPID,
                const std::vector<double>& A,
                const std::vector<double>& B,
                const int delay, const double zaklucenia,
                const std::vector<double>& ParametryGen) {
        QString nazwaPliku = "Dane.txt";
        QFile plik(nazwaPliku);

        if (!plik.open(QIODevice::WriteOnly | QIODevice::Text)) {
            qDebug() << "Nie udało się otworzyć pliku!";
            return;
        }

        QTextStream out(&plik);

        // Zapis PID:
        zapiszWiersz(out, ParametryPID);
        out << "\n";

        // Zapis ARX:
        zapiszWiersz(out, A);
        out << "|";
        zapiszWiersz(out, B);
        out << "|" << delay << "|" << zaklucenia << "\n";

        // Zapis Generatora:
        zapiszWiersz(out, ParametryGen);

        plik.close();
    }

    void odczyt(std::vector<double>& ParametryPID,
                  std::vector<double>& A,
                  std::vector<double>& B,
                  int& delay,
                  double& zaklucenia,
                  std::vector<double>& ParametryGen) {
        QString nazwaPliku = "Dane.txt";
        QFile plik(nazwaPliku);

        if (!plik.exists()) {
            QMessageBox::critical(nullptr,"Błąd!","Plik nie istnieje!");
            return;
        }

        plik.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&plik);

        // Odczyt PID:
        odczytajWiersz(in, ParametryPID);

        // Odczyt ARX (A | B | delay | zaklucenia):
        QString line;
        in.readLineInto(&line);
        QStringList parts = line.split("|");

        odczytajWiersz(parts[0], A);
        odczytajWiersz(parts[1], B);

        delay = parts[2].toInt();
        zaklucenia = parts[3].toDouble();

        // Odczyt Generatora:
        odczytajWiersz(in, ParametryGen);

        plik.close();
    }

private:
    SprzezenieZwrotne sprzezeniezwrotne;
    GenWartZadana gen_wart;

    void zapiszWiersz(QTextStream& out, const std::vector<double>& vec) {
        for (size_t i = 0; i < vec.size(); ++i) {
            out << vec[i];
            if (i < vec.size() - 1) {
                out << ",";
            }
        }
    }
    void odczytajWiersz(QTextStream& in, std::vector<double>& vec) {
        QString line;
        in.readLineInto(&line);
        odczytajWiersz(line, vec);
    }

    void odczytajWiersz(const QString& line, std::vector<double>& vec) {
        vec.clear();
        QStringList numbers = line.split(",");
        for (const QString& num : numbers) {
            vec.push_back(num.toDouble());
        }
    }
};
