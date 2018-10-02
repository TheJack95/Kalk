#include "kalk.h"
#include "exception.h"
#include <typeinfo>

Kalk::Kalk() : memoria(new KalkMemory()), first(nullptr), second(nullptr) {}

Kalk::~Kalk()
{
  delete memoria;
  if(first)
    delete first;
  if(second)
    delete second;
}
void Kalk::del()
{
  delete first;
  delete second;
  first=second=0;
}
BaseClass* Kalk::save(QStringList d, bool ok=true)
{
  BaseClass *aux=0;
  if(!d[1].isEmpty())
    aux=new Polynom(d[1],d[0]);
  else if((!d[4].isEmpty() && !d[5].isEmpty()) && (d[2].isEmpty() && d[3].isEmpty()))
    aux=new EuclideanVector(d[5].toDouble(),d[4].toDouble(),d[0]);
  else if ((d[4].isEmpty() && d[5].isEmpty()) && (!d[2].isEmpty() && !d[3].isEmpty()))
    {
      QStringList pa=d[2].split(',',QString::SkipEmptyParts);
      QStringList pb=d[3].split(',',QString::SkipEmptyParts);
      aux=new EuclideanVector(d[0],QPointF(pb[0].toDouble(),pb[1].toDouble()),QPointF(pa[0].toDouble(),pa[1].toDouble()));
    }
  else if (!d[4].isEmpty() && !d[5].isEmpty() && !d[2].isEmpty() && d[3].isEmpty())
    {
      QStringList pa=d[2].split(',',QString::SkipEmptyParts);
      aux=new EuclideanVector(d[5].toDouble(),d[4].toDouble(),QPointF(pa[0].toDouble(),pa[1].toDouble()),d[0]);
    }
  else
    throw DataErr();

  if(ok)
    memoria->insert(aux);

  return aux;
}

void Kalk::setF(QStringList b)
{
  first = save(b,false);
}

void Kalk::setS(QStringList b)
{
  second = save(b,false);
}

BaseClass* Kalk::getFirst() const { return first; }

BaseClass* Kalk::getSecond() const { return second; }

BaseClass* Kalk::getMemory(QString name) const { return memoria->search(name); }

BaseClass* Kalk::plus() const
{
  if(typeid(*first)!=typeid(*second))
    throw InvalidOperation();

   return *first + *second;

}

BaseClass* Kalk::minus() const
{
  if(typeid(first)!=typeid(second))
    throw InvalidOperation();

  return *first - *second;
}

BaseClass* Kalk::per() const
{
  if(typeid(*first)!=typeid(*second))
    throw InvalidOperation();

  return *first * *second;
}

BaseClass* Kalk::div() const
{
  if(typeid(*first)!=typeid(*second))
    throw InvalidOperation();

  return *first / *second;
}

BaseClass* Kalk::operations(QString o) const
{
  BaseClass *r=0;
  int i=0;
  while(i < o.size()-1)
        {
          switch (o.at(i+1).toLatin1())
            {
            case '+':
              {
                r = *(memoria->search(o.at(i+2))) + *(memoria->search(o.at(i)));
                break;
              }
            case '-':
              {
                r = *(memoria->search(o.at(i+2))) - *(memoria->search(o.at(i)));
                break;
              }
            case '/':
              {
                r = *(memoria->search(o.at(i+2))) / *(memoria->search(o.at(i)));
                break;
              }
            case '*':
              {
                r = *(memoria->search(o.at(i+2))) * *(memoria->search(o.at(i)));
                break;
              }
            default:
              break;
            }
          i+=2;
     }
  return r;
}
