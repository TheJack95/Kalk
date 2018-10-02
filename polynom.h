#ifndef POLYNOM_H
#define POLYNOM_H

#include "QVector"
#include "QPair"
#include "baseclass.h"

using std::vector;

class Polynom : public BaseClass {
private:
  QVector< QPair<double,int> > list;
  void sort();
  static QPair<double,int> converti(QString);
public:
  Polynom(QString poly,QString name);
  Polynom(const Polynom&);
  Polynom(QVector< QPair<double,int> > p,QString name);
  Polynom();
  ~Polynom() =default;
  Polynom* operator+(const BaseClass&) const;
  Polynom* operator-(const BaseClass&) const;
  Polynom* operator*(const BaseClass&) const;
  Polynom molt(const QPair<double,int>& term) const;
  Polynom* operator/(const BaseClass&);
  Polynom* operator=(const BaseClass& p);
  QString print() const;
};

#endif // POLYNOM_H
