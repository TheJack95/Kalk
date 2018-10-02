#ifndef EUCLIDEANVECTOR_H
#define EUCLIDEANVECTOR_H

#include <QPointF>
#include "baseclass.h"

class EuclideanVector : public BaseClass {
private:
  QPointF p1;
  QPointF p2;
  double length;
  double angle;
public:
  EuclideanVector(double l, double a, QPointF p, QString n);
  EuclideanVector(double l, double a, QString n);
  EuclideanVector(QString n, QPointF p2, QPointF p1=QPointF(0,0));
  EuclideanVector(double,QString);
  EuclideanVector(const EuclideanVector&);
  EuclideanVector();
  ~EuclideanVector() =default;

  QString print() const;
  double getA() const { return angle; }
  double getL() const { return length; }
  static double Angle(const EuclideanVector&,const EuclideanVector&); //angolo tra due vettori
  EuclideanVector* operator/(const BaseClass&); //prodotto vettoriale
  double dotProduct(const EuclideanVector&) const;
  EuclideanVector* operator*(const BaseClass&) const; //prodotto scalare
  EuclideanVector* operator+(const BaseClass&) const;
  EuclideanVector* operator-(const BaseClass&) const;
  EuclideanVector* operator=(const BaseClass&);
};

#endif // EUCLIDEANVECTOR_H
