#ifndef KALKWINDOW_H
#define KALKWINDOW_H

#include "kalk.h"
#include <QMainWindow>
#include "kalkmemory.h"


namespace Ui {
  class KalkWindow;
}

class KalkWindow : public QMainWindow
{
  Q_OBJECT

public:
  explicit KalkWindow(QWidget *parent = nullptr);
  ~KalkWindow();

private slots:
  void binary_operation_pressed();
  void on_salva_clicked();
  void on_uguale_released();
  void on_clear_released();
  void on_esegui_released();
  void on_delMem_released();

private:
  Ui::KalkWindow *ui;
  Kalk *kalk;
};

#endif // KALKWINDOW_H
