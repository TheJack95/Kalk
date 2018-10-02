#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>
#include <QTextStream>
#include <QFile>
#include <QString>
#include <QLabel>
#include <QTextBrowser>
#include <QDesktopWidget>
#include <QRect>

#include "kalkwindow.h"

MainWindow::MainWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::MainWindow)
{
  ui->setupUi(this);

  QRect desktopRect = QApplication::desktop()->availableGeometry(this);
  QPoint center = desktopRect.center();
  setGeometry(center.x()-width()/2, center.y()-height()/2,width(),height());
}

MainWindow::~MainWindow()
{
  delete ui;
}

void MainWindow::on_avvia_clicked()
{
  QMainWindow *mp=new KalkWindow();
  mp->show();
  this->close();
}

void MainWindow::on_guida_released()
{
  QFile file("../KALK/guida");
  QLabel *x=new QLabel();
  x->setWindowTitle("Guida");
  x->setMargin(10);

  QString line;
  if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
      QTextStream stream(&file);
      while (!stream.atEnd())
        {

          line.append(stream.readLine()+"\n");
        }
      x->setText(line);
    }

  file.close();
  x->show();
}
