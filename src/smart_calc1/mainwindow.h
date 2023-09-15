#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QVector>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE


#ifdef __cplusplus

extern "C" {
#endif

#include "calc.h"
#ifdef __cplusplus
}
#endif


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

private slots:
    void input_chars();
    void func();
    void on_pushButton_AC_clicked();
    void on_pushButton_eq_clicked();
    void on_pushButton_graph_clicked();
};

#endif // MAINWINDOW_H
