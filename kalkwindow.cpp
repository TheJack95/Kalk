#include "kalkwindow.h"
#include "ui_kalkwindow.h"

#include <QDesktopWidget>
#include <QRect>
#include <QMessageBox>
#include <QStringList>

KalkWindow::KalkWindow(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::KalkWindow), kalk(new Kalk())
{
  ui->setupUi(this);

  connect(ui->somma,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
  connect(ui->sottrazione,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
  connect(ui->moltiplicazione,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
  connect(ui->divisione,SIGNAL(released()),this,SLOT(binary_operation_pressed()));
  connect(ui->delMem,SIGNAL(released()),this,SLOT(on_delMem_released()));


  ui->somma->setCheckable(true);
  ui->sottrazione->setCheckable(true);
  ui->moltiplicazione->setCheckable(true);
  ui->divisione->setCheckable(true);
  QRect desktopRect = QApplication::desktop()->availableGeometry(this);
  QPoint center = desktopRect.center();

  setGeometry(center.x()-width()/2, center.y()-height()/2,width(),height());
}

KalkWindow::~KalkWindow()
{
  delete ui;
  delete kalk;
}

void KalkWindow::on_salva_clicked()
{
  QStringList data = {ui->nomeInput->text(), ui->polyInput->text(),
                      ui->punto1->text(), ui->punto2->text(), ui->angolo->text(),ui->modulo->text() };

  try
  {
    BaseClass *aux=kalk->save(data,true);
    ui->output->append("Oggetto '"+ui->nomeInput->text()+"' salvato in memoria");
    ui->output->append(aux->print());
  }
  catch (Exception& e)
  {
    QMessageBox *m=new QMessageBox();
    m->setText(e.toQString());
    m->show();
  }

  ui->polyInput->clear();
  ui->nomeInput->clear();
  ui->punto1->clear();
  ui->punto2->clear();
  ui->angolo->clear();
  ui->modulo->clear();
}

void KalkWindow::on_uguale_released()
{
  QStringList data={ui->nomeInput->text(), ui->polyInput->text(),
                    ui->punto1->text(), ui->punto2->text(), ui->angolo->text(),ui->modulo->text() };

  BaseClass *tmp=0;
  try
  {
    kalk->setS(data);
    ui->output->append(kalk->getSecond()->print() +"   =");
    ui->output->append(" ");

    if(ui->somma->isChecked())
      {
        tmp=kalk->plus();
        ui->somma->setChecked(false);
      }

    else if(ui->sottrazione->isChecked())
      {
        tmp=kalk->minus();
        ui->sottrazione->setChecked(false);
      }

    else if(ui->moltiplicazione->isChecked())
      {
        tmp=kalk->per();
        ui->moltiplicazione->setChecked(false);
      }

    else if(ui->divisione->isChecked())
      {
        tmp=kalk->div();
        ui->divisione->setChecked(false);
        ui->output->append("Resto : " + kalk->getFirst()->print());
      }
    ui->output->append(tmp->print());
    ui->output->append(" ");
  }
  catch (Exception& e)
  {
    QMessageBox *m=new QMessageBox();
    m->setText(e.toQString());
    m->show();
  }

  ui->polyInput->clear();
  ui->nomeInput->clear();
  ui->punto1->clear();
  ui->punto2->clear();
  ui->angolo->clear();
  ui->modulo->clear();

  kalk->del();
  delete tmp;
}

void KalkWindow::on_clear_released()
{
  ui->output->clear();
}

void KalkWindow::binary_operation_pressed()
{
  QPushButton *button = dynamic_cast<QPushButton*>(sender());

  //lista in cui salvo tutti i dati inseriti
  QStringList data={ui->nomeInput->text(), ui->polyInput->text(),
                    ui->punto1->text(), ui->punto2->text(), ui->angolo->text(),ui->modulo->text() };

  try
  {
    kalk->setF(data);
    ui->output->append(kalk->getFirst()->print() + "   " + button->text());
  }
  catch (Exception& e)
  {
    QMessageBox *m=new QMessageBox();
    m->setText(e.toQString());
    m->show();
  }

  ui->polyInput->clear();
  ui->nomeInput->clear();
  ui->punto1->clear();
  ui->punto2->clear();
  ui->angolo->clear();
  ui->modulo->clear();

  button->setChecked(true);
}

void KalkWindow::on_esegui_released()
{
  BaseClass *tmp=0;
  tmp=kalk->operations(ui->operazioni->text());
  ui->output->append(tmp->print());

  ui->output->append(" ");
  ui->operazioni->clear();
  delete tmp;
}


void KalkWindow::on_delMem_released()
{
}



