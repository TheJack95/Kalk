#include "euclideanvector.h"
#include <typeinfo>
#include "exception.h"
#include <iostream>
#include <math.h>

EuclideanVector::EuclideanVector(double l, double a, QPointF p, QString n) : BaseClass (n),
  p1(p), p2(QPointF(l*cos(a*M_PI/180),l*sin(a*M_PI/180))), length(l), angle(a)
{
  if(std::abs(a)==90.0 || std::abs(a)==180.0)
    p2=QPointF(0,l);
  else if (std::abs(a)==0.0 || std::abs(a)==360.0)
    {
      p2=QPointF(l,0);
    }
}

//costruisce un vettore che ha come punto di applicazione l'origine
EuclideanVector::EuclideanVector(double l, double a, QString n) : BaseClass (n),
  p1(QPointF()), p2(QPointF(l*cos(a*M_PI/180),l*sin(a*M_PI/180))), length(l), angle(a)
{

  if(std::abs(a)==90.0 || std::abs(a)==180.0)
    p2=QPointF(0,l);
  else if (std::abs(a)==0.0 || std::abs(a)==360.0)
    {
      p2=QPointF(l,0);
    }
}

EuclideanVector::EuclideanVector(QString n, QPointF p2, QPointF p1) : BaseClass (n), p1(p1), p2(p2),
  length(sqrt(pow((p2.x()-p1.x()),2)+pow((p2.y()-p1.y()),2))), angle(atan((p2.y()-p1.y())/(p2.x()-p1.x()))*180/M_PI)
{}

EuclideanVector::EuclideanVector(double a, QString n) : BaseClass(n), p1(QPointF(0,0)), p2(QPointF(0,0)),
  length(a), angle(0) {}

EuclideanVector::EuclideanVector(const EuclideanVector& v) : BaseClass (v.getName()), p1(v.p1), p2(v.p2), length(v.length), angle(v.angle) {}

EuclideanVector::EuclideanVector() : BaseClass(" "), p1(), p2(), length(0), angle(0) {}

double EuclideanVector::dotProduct(const EuclideanVector& v) const
{
  return p2.x()*v.p2.x()+p2.y()*v.p2.y();
}

//angolo tra due vettori
double EuclideanVector::Angle(const EuclideanVector &v1, const EuclideanVector &v2)
{
  return acos( ( (v1.dotProduct(v2)) / (v1.length*v2.length) ) *M_PI/180);
}

EuclideanVector* EuclideanVector::operator+(const BaseClass &v) const
{
  if(typeid(*this) != typeid(v))
    throw InvalidOperation();

  QPointF p(p1.x()+p2.x(),static_cast<const EuclideanVector&>(v).p1.y()+static_cast<const EuclideanVector&>(v).p2.y());
  return new EuclideanVector("result",p);
}

EuclideanVector* EuclideanVector::operator-(const BaseClass &v) const
{
  if(typeid(*this) != typeid(v))
    throw InvalidOperation();

  QPointF p(p1.x()-p2.x(),static_cast<const EuclideanVector&>(v).p1.y()-static_cast<const EuclideanVector&>(v).p2.y());
  return new EuclideanVector("result",p);
}


EuclideanVector* EuclideanVector::operator*(const BaseClass &v) const //prodotto scalare
{
  if(typeid(*this) != typeid(v))
    throw InvalidOperation();

  return new EuclideanVector(this->dotProduct(static_cast<const EuclideanVector&>(v)),"DotProduct");
}

EuclideanVector* EuclideanVector::operator/(const BaseClass &v) //prodotto vettoriale
{
  if(typeid(*this) != typeid(v))
    throw InvalidOperation();

  delete this;
  *this = EuclideanVector(length * static_cast<const EuclideanVector&>(v).length *
                             sin(Angle(*this,static_cast<const EuclideanVector&>(v))*M_PI/180),0,"Result");
  return this;
}

QString EuclideanVector::print() const
{
  if(angle==0. && p1==QPointF(0,0) && p2==QPointF(0,0))
    return QString("Prodotto Scalare = "+QString::number(length));

  QString aux="Vettore  "+BaseClass::print();
  aux.append("\r\nPunto di applicazione : ("+QString::number(p1.x())+','+QString::number(p1.y())+")" +
             "   Punto 2 : ("+QString::number(p2.x())+','+QString::number(p2.y())+")");
  aux.append("\r\nModulo = "+QString::number(length));
  aux.append("\r\nAngolo = "+QString::number(angle));
  return aux;
}


