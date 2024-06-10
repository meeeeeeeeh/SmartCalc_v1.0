#ifndef CREDIT_H
#define CREDIT_H

#include <QWidget>

namespace Ui {
class credit;
}

#ifdef __cplusplus

extern "C" {
#endif

#include "calc.h"
#ifdef __cplusplus
}
#endif

class credit : public QWidget {
  Q_OBJECT

 public:
  explicit credit(QWidget *parent = nullptr);
  ~credit();

 private slots:
  void on_pushButton_res_clicked();

 private:
  Ui::credit *ui;
};

#endif  // CREDIT_H
