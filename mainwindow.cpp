#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#include "Manager.h"


MainWindow::MainWindow(Manager* manager,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , manager(manager)
    , series(nullptr)
    , series2(nullptr)
    , series3(nullptr)
    ,timer(nullptr)
{


    ui->setupUi(this);
    ui->Aa->setRange(-9999.0,9999.0);
    ui->Ab->setRange(-9999.0,9999.0);
    ui->Ac->setRange(-9999.0,9999.0);
    ui->Ba->setRange(-9999.0,9999.0);
    ui->Bb->setRange(-9999.0,9999.0);
    ui->Bc->setRange(-9999.0,9999.0);

    ui->st_calk->setRange(0,9999.0);
    ui->st_rozn->setRange(0,9999.0);
    ui->wzmocn->setRange(-9999.0,9999.0);
    ui->wej_t->setRange(0,9999.0);
    ui->wej_Amp->setRange(0,9999.0);
    ui->wej_T->setRange(0,9999.0);
    ui->wej_p->setRange(0,9999.0);
    ui->opoznienie->setRange(0,9999.0);

    ui->opoznienie->setValue(1);
    ui->wej_t->setValue(1);
    ui->wej_Amp->setValue(1);
    ui->wej_T->setValue(1);
    ui->wej_p->setValue(1);


    on_widget1_customContextMenuRequested(QPoint(0, 0));
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::confSim(){

    double Ti = ui->st_calk->value();
    double Td= ui->st_rozn->value();
    double k= ui->wzmocn->value();

    std::vector<double> ParametryPID = {k,Ti,Td};
    manager->setRegulatorPID(ParametryPID);

    double Aa = ui->Aa->value();
    double Ab = ui->Ab->value();
    double Ac= ui->Ac->value();
    double Ba = ui->Ba->value();
    double Bb = ui->Bb->value();
    double Bc = ui->Bc->value();
    double delay = ui->opoznienie->value();

    std::vector<double> A = {Aa,Ab,Ac};
    std::vector<double> B = {Ba,Bb,Bc};

    manager->setModelARX(A,B,delay);

    bool is_sin = ui->sin->isChecked();
    bool is_prost = ui->prost->isChecked();
    bool is_krok_jedn = ui->krok_jedn->isChecked();

    Sygnal ksztalt = Sygnal::Nieustawiony;
    ksztalt = (is_sin == true) ? Sygnal::Sin:ksztalt;
    ksztalt = (is_prost == true) ? Sygnal::Prostokat:ksztalt;
    ksztalt = (is_krok_jedn == true) ? Sygnal::Skok:ksztalt;
    if (ksztalt==Sygnal::Nieustawiony) {
        QMessageBox::critical(this, "Zła wartość!", "Nie wybrano kształtu sygnału.");
        return;
    }

    double t = ui->wej_t->value();
    Amp = ui->wej_Amp->value();
    double T = ui->wej_T->value();
    double p = ui->wej_p->value();

    if(T<=0||Amp<=0)
    {
        QMessageBox::critical(this,"Zła wartość!","Okres ani amplituda nie mogą być równe 0!");
        return;
    }

    std::vector<double> ParametryGen = {t,Amp,T,p};
    manager->setGenerator(ksztalt, ParametryGen);
}


void MainWindow::updateChart() {
    manager->Symuluj(x);

    WY = manager->getWY();

    series->append(x, WY[1]);
    series2->append(x, WY[2]);
    series3->append(x,WY[0]);

    x++;

    /*
    if (series->count() > 100) {
        series->remove(0);
    }
    if (series2->count() > 100) {
        series2->remove(0);
    }
    if (series3->count() > 100) {
        series3->remove(0);
    }
    */

    chart->scroll(300, 0);

    qDebug()<<WY;
}

void MainWindow::on_Start_Button_clicked()
{

    if (!timer) {
        timer = new QTimer(this);
        connect(timer, &QTimer::timeout, this, &MainWindow::updateChart);
    }

    timer->start(500);
}



void MainWindow::on_Reset_Button_clicked()
{
    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }

    if (chart && series && series2 && series3) {
        chart->removeSeries(series);
        chart->removeSeries(series2);
        chart->removeSeries(series3);

        delete series;
        delete series2;
        delete series3;

        series = new QLineSeries();
        series->setColor("blue");
        chart->addSeries(series);
        series2 = new QLineSeries();
        series2->setColor("red");
        chart->addSeries(series2);
        series3 = new QLineSeries();
        series3->setColor("green");
        chart->addSeries(series3);

        chart->createDefaultAxes();
        chart->axes(Qt::Vertical).first()->setRange(-500, 500);
    }

    x = 0;

    qDebug()<<series<<series2<<series3;
}

void MainWindow::on_Stop_Button_clicked()
{
    if (timer) {
        timer->stop();
        delete timer;
        timer = nullptr;
    }
}

void MainWindow::on_widget1_customContextMenuRequested(const QPoint &pos)
{
    series = new QLineSeries();
    series->setColor("blue");

    series2 = new QLineSeries();
    series2->setColor("red");

    series3 = new QLineSeries();
    series3->setColor("green");

    chart = new QChart();
    chart->addSeries(series);
    chart->addSeries(series2);
    chart->addSeries(series3);
    chart->createDefaultAxes();
    chart->axes(Qt::Vertical).first()->setRange(-500, 500);
    chart->setTitle("Wykres <span style='color:blue;'> U(t) </span>, <span style='color:red;'>Y(t)</span> oraz <span style='color:green;'>wartość zadana</span>");

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);

    chartView->setParent(ui->widget1);
    chartView->setGeometry(ui->widget1->rect());
}


void MainWindow::on_Single_shot_button_clicked()
{

    QTimer::singleShot(100,this,&MainWindow::updateChart);
}


void MainWindow::on_Conf_Button_clicked()
{
    confSim();
}

