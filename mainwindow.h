#include <QMainWindow>
#include "Manager.h"
#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QTimer>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include <QHBoxLayout>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(Manager* manager, QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_Start_Button_clicked();
    void on_Reset_Button_clicked();
    void on_Stop_Button_clicked();
    void updateChart();
    void confSim();
    void on_widget1_customContextMenuRequested(const QPoint &pos);
    void on_Single_shot_button_clicked();
    void on_Conf_Button_clicked();

private:
    double Amp;
    Ui::MainWindow *ui;
    Manager* manager;

    QChart *chart;
    QLineSeries *series;
    QLineSeries *series2;
    QLineSeries *series3;
    QTimer *timer;
    int x = 0;

    std::vector<double> WY;
};
