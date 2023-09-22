#include "credit.h"
#include "ui_credit.h"
#include "calc.h"

credit::credit(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::credit)
{
    ui->setupUi(this);
}

credit::~credit()
{
    delete ui;
}


void credit::on_pushButton_res_clicked()
{
    // clear old results
    ui->label_1->setText("");
    ui->label_2->setText("");
    ui->label_3->setText("");


    double monthly_max = 0.0;
    double monthly_min = 0.0;
    double percents = 0.0;
    double all = 0.0;

    bool an = ui->radioButton_an->isChecked();
    bool dif = ui->radioButton_dif->isChecked();

    if (an) {
        credit_calc(ui->sum->value(), ui->months->value(), ui->rate->value(), &monthly_max, &monthly_min, &percents, &all, 1);
        ui->label_1->setText(QString::number(monthly_max, 'f', 2));
    }
    else if (dif) {
        credit_calc(ui->sum->value(), ui->months->value(), ui->rate->value(), &monthly_max, &monthly_min, &percents, &all, 2);
        ui->label_1->setText(QString::number(monthly_max, 'f', 2) + "..." + QString::number(monthly_min, 'f', 7));
    }

    ui->label_2->setText(QString::number(percents, 'f', 2));
    ui->label_3->setText(QString::number(all, 'f', 2));


}

