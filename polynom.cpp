#include "polynom.h"
#include <cstdlib>
#include <typeinfo>
#include "exception.h"
#include <regex>
using std::regex;

#include <iostream>

QPair<double,int> Polynom::converti(QString a) //conversione da QString a qMakePair
{
  int i=0;
  if(a.size()==1 && a[0]=='x') //monomio = x
    return qMakePair(1,1);
  else
    {
      if(a[i]=='x') //monomio = x^b
        {
          a.remove('x');
          a.remove('^');
          return qMakePair(1,a.toInt());
        }
      else
        {
          QString aux;
          while(a[i]!='x' && i<a.size()) //aux è il coefficiente
            {
              aux.append(a[i]);
              ++i;
            }

          if((aux[0]=='-' || aux[0]=='+') && aux.size()==1) // monomio = -x^b
            aux.append('1');

          a.remove(0,i); //rimuovo i primi 'i' elementi cioè il coefficiente

          if(a.size()==0) //monomio = a
            return qMakePair(aux.toDouble(),0);

          a.remove('x');
          a.remove('^');

          if(a.size()==0) //monommio = ax
            return (qMakePair(aux.toDouble(),1));

          return qMakePair(aux.toDouble(), a.toInt()); //monomio = ax^b
        }
    }
}

void Polynom::sort()  //ordina in modo decrescente
{
  for (int j=1; j<list.size(); ++j)
    {

      QPair<double,int> key = list[j];
      int i=j-1;
      while(i>=0 && list[i].second<=key.second)
        {
          list[i+1]=list[i];
          i--;
        }

      list[i+1]=key;
    }
}


Polynom::Polynom(QString poly, QString name) : BaseClass (name)
{
  regex valid("((\\+|-)?[[:digit:]]*(x|(x[^][[:digit:]]+))?)+");
  if(!regex_match(poly.toStdString(),valid))
    {
      this->BaseClass::~BaseClass();
      throw InvalidPolynom();
    }

  int i=0;
  while(i<poly.size())
    {
      QString aux;
      if(poly[i]=='+' || poly[i]=='-')
        {
          aux.append(poly[i]);
          ++i;
        }

      while(i<poly.size() && poly[i]!='+' &&  poly[i]!='-')
        {
          aux.append(poly[i]);
          ++i;
        }

      QPair<double,int> p = converti(aux);
      list.push_back(p);
    }
  sort();
}

Polynom::Polynom(const Polynom& p) : BaseClass (p.getName()), list(p.list) {}

Polynom::Polynom(QVector<QPair<double, int> > p, QString name) : BaseClass (name), list(p) {}

Polynom::Polynom() : BaseClass(" "), list() { list .push_back(qMakePair(0,0)); }

Polynom* Polynom::operator+(const BaseClass& p) const
{
  Polynom a = static_cast<const Polynom&>(p);

  if(typeid(*this) != typeid(p))
    throw InvalidOperation();

  QVector<QPair<double,int>> aux;
  int j=0, k=0;
  while(j < list.size() && k < a.list.size())
    {
      if(list[j].second == a.list[k].second)
        {
          if(list[j].first + a.list[k].first != 0. )
            aux.push_back(qMakePair(list[j].first + a.list[k].first , list[j].second));
          k++;
          j++;
        }
      else
        {
          if(list[j].second > a.list[k].second)
            {
              aux.push_back(QPair<double,int>(list[j]));
              j++;
            }
          else
            if(list[j].second < a.list[k].second)
              {
                aux.push_back(QPair<double,int>(a.list[k]));
                k++;
              }
        }
    }

  //nel caso in cui il numero dei monomi dei due polinomi non sia lo stesso devo aggiungere quelli "mancanti" al risultato
  while(j < list.size())
    {
      aux.push_back(qMakePair(list[j].first,list[j].second));
      j++;
    }

  while(k < a.list.size())
    {
      aux.push_back(qMakePair(a.list[k].first,a.list[k].second));
      k++;
    }

  if(aux.empty())
    aux.push_back(qMakePair(0,0));

  return new Polynom(aux,"Result");
}

Polynom* Polynom::operator-(const BaseClass& p) const
{
  Polynom a = static_cast<const Polynom&>(p);

  if(typeid(*this) != typeid(p))
    throw InvalidOperation();

  return new Polynom(*(*(a * Polynom("-1","")) + *this ));

}

Polynom Polynom::molt(const QPair<double,int>& term) const
{
  QVector<QPair<double,int>> aux;
  for(int i=0; i<list.size(); ++i)
    {
      double coef=list[i].first * term.first;
      int exp=list[i].second + term.second;
      aux.push_back(qMakePair(coef, exp));
    }
  return Polynom(aux,"");
}

Polynom* Polynom::operator*(const BaseClass& p) const
{
  if(typeid(*this) != typeid(p))
    throw InvalidOperation();

  Polynom *aux=new Polynom();

  for(int j=0; j<list.size(); ++j)
    {
      Polynom tmp = static_cast<const Polynom&>(p).molt(this->list[j]);
      aux = *aux + tmp;
    }
  aux->setName("Result");
  return aux;
}

Polynom* Polynom::operator/(const BaseClass& p)
{
  Polynom a = static_cast<const Polynom&>(p);

  if(typeid(*this) != typeid(p))
    throw InvalidOperation();

  if(list[0].second < a.list[0].second)
    {
      Polynom *tmp= new Polynom();
      tmp->list.push_back(qMakePair(0,0));
      tmp->setName("Result");
      return tmp;
    }

  int i=0;
  while(i<list.size())
    {
       if(i+1<list.size() && list[i].second-list[i+1].second != 1)
         list.insert(i+1,qMakePair(0,list[i].second-1));
        i++;
    }

  QVector<QPair<double,int>> q;
  while(a.list[0].second<=this->list[0].second)
    {
      q.append(qMakePair(list[0].first/a.list[0].first,list[0].second-a.list[0].second));
       *this = *(*this - a.molt(q.last()));

    }

  if(list.empty())
    list.push_back(qMakePair(0,0));

  this->setName("Resto");


  return new Polynom(q,"Result");
}

Polynom* Polynom::operator=(const BaseClass& p)
{
  if(this != &static_cast<const Polynom&>(p))
    {
      delete this;
      list = static_cast<const Polynom&>(p).list;
    }
  return this;
}

QString Polynom::print() const
{
  QString aux;
  for(int i=0; i<list.size(); ++i)
    {
      if(list[i].first >= 0.0 && i != 0) //aggiunge + se coefficiente positivo
        aux.append("+");
      if(list[i].second == 0) // esponente = 0 non aggungo la x
        aux.append(QString::number(list[i].first));
      else //monomio del tipo ax^b
        {
          if(list[i].first == -1 )
            aux.append('-');
          else
            if(list[i].first != 1.0) //se coefficiente==1 non lo considero
              aux.append(QString::number(list[i].first));

          aux.append("x");
          if(list[i].second != 1) // aggiungo l'esponente se != da 1
            aux.append("^"+QString::number((list[i].second)));
        }
    }
  return aux;
}

