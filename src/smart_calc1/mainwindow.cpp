#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "calc.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->pushButton_0, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_1, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_3, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_4, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_5, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_6, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_7, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_8, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_9, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_mod, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_sum, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_dot, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_sub, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_open_br, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_close_br, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_div, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_mult, SIGNAL(clicked()), this, SLOT(input_chars()));
    connect(ui->pushButton_cos, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_acos, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_sin, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_asin, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_tan, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_atan, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_ln, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_log, SIGNAL(clicked()), this, SLOT(func()));
    connect(ui->pushButton_sqrt, SIGNAL(clicked()), this, SLOT(func()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::input_chars()
{
    QPushButton *button = (QPushButton *)sender();
    QString new_label;

    if (ui->result->text() == "0" || ui->result->text() == "Error")
    {
        new_label = button->text();
    }
    else
    {
        new_label = ui->result->text() + button->text();
    }
    ui->result->setText(new_label);
}

void MainWindow::func()
{
    QPushButton *button = (QPushButton *)sender();
    QString new_label;

    if (ui->result->text() == "0")
    {
        new_label = button->text() + "(";
    }
    else
    {
        new_label = ui->result->text() + button->text() + "(";
    }
    ui->result->setText(new_label);
}



void MainWindow::on_pushButton_AC_clicked()
{
    ui->result->setText("0");
}


void MainWindow::on_pushButton_eq_clicked()
{
    double res = 0;
    double x = 0;
    QString new_label;
    QString text = ui->result->text().toLower().toStdString().c_str();
    if (!calc(text.toLower().toStdString().data(), &res, x) )
    {
        new_label = QString::number(res, 'f', 7);
        ui->result->setText(new_label);
    }
    else
    {
        ui->result->setText("Error");
    }

}




void MainWindow::on_pushButton_graph_clicked()
{
    int error = 0;
    double x_min = ui->x_min->value();
    double x_max = ui->x_max->value();
    double step = 0.01; //Шаг, с которым будем пробегать по оси Ox
    QVector<double> x, y; //Массивы координат точек

    //Вычисляем наши данные
    int i=0;
    //Пробегаем по всем точкам
    for (double X = x_min; X <= x_max; X += step) {
      double res = 0;
      QString text = ui->result->text().toLower().toStdString().c_str();
      error = calc(text.toLower().toStdString().data(), &res, X);
      y[i] = res;
      i++;


    }
    if (!error) {


        ui->widget->clearGraphs();//Если нужно, но очищаем все графики

        //Добавляем один график в widget
        ui->widget->addGraph();

        //Говорим, что отрисовать нужно график по нашим двум массивам x и y
        ui->widget->graph(0)->setData(x, y);

        //Подписываем оси Ox и Oy
        ui->widget->xAxis->setLabel("x");
        ui->widget->yAxis->setLabel("y");

        //Установим область, которая будет показываться на графике
        ui->widget->xAxis->setRange(x_min, x_max);//Для оси Ox

        //Для показа границ по оси Oy сложнее, так как надо по правильному
        //вычислить минимальное и максимальное значение в векторах
//        double minY = y[0], maxY = y[0];
//        for (int i = 1; i < N; i++) {
//          if (y[i] < minY) minY = y[i];
//          if (y[i] > maxY) maxY = y[i];
//        }
        ui->widget->yAxis->setRange(-10, 10);//Для оси Oy

        //И перерисуем график на нашем widget
        ui->widget->replot();

    }
    else {
        ui->result->setText("Error");
    }
}

