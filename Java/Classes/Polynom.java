package Classes;

import java.util.regex.Pattern;
import java.awt.geom.Point2D;
import java.util.Vector;

public class Polynom extends BaseClass
{
    private Vector<Point2D> list;
    
    private void sort()
    {
	
        for (int j = 1; j < list.size(); ++j)
	    {
		Point2D key = list.get(j);
		int i = j - 1;
		while (i >= 0 && list.get(i).getY() <= key.getY())
		    {
			list.set(i + 1, list.get(i));
			i--;
		    }
		list.set(i + 1, key);
	    }
    }
    
    private static Point2D converti(String a)
    {
        int i = 0;
	StringBuilder ax = new StringBuilder(a);
        if (ax.length() == 1 && ax.charAt(0) == 'x') //monomio = x
            return new Point2D.Double(1, 1);
        else
	    {
		if (ax.charAt(0) == 'x') //monomio = x^b
		    {
			a = a.replace("x", "");
			a = a.replace("^", "");
			return new Point2D.Double(1, Double.valueOf(a));
		    }
		else
		    {
			StringBuilder aux = new StringBuilder(); //aux è il coefficiente
			while (i < ax.length() && ax.charAt(i) != 'x')
			    {
				aux.append(ax.charAt(i));
				i++;
			    }

			if ((aux.charAt(0) == '-' || aux.charAt(0) == '+') && aux.length() == 1) // monomio = -x^b o +x^b
			    aux.append('1');
			
			ax.delete(0,i);
			
			if (ax.length() == 0) //monomio = a
			    return new Point2D.Double(Double.valueOf(aux.toString()), 0);
			
			a = ax.toString();
			a = a.replace("x", "");
			a = a.replace("^", "");
			if (a.length() == 0) //monommio = ax
			    return new Point2D.Double(Double.valueOf(aux.toString()), 1);
			
			return new Point2D.Double(Double.valueOf(aux.toString()), Integer.valueOf(a)); //monomio = ax^b
		    }
	    }
    }
    
    bool Polynom::polyVerify(String input)
    {
	regex number("((\\+|-)?[[:digit:]]*(x|(x[^][[:digit:]]+))?)+");
	return regex_match(input.toStdString(),number);    
    }
    
    public Polynom(String poly, String name)
    {
        super(name);
        list = new Vector<>();
        int i = 0;
        StringBuilder p = new StringBuilder(poly);
        while (i < p.length())
	    {
		StringBuilder aux = new StringBuilder();
		
		if (p.charAt(i) == '+' || p.charAt(i) == '-')
		    {
			aux.append(p.charAt(i));
			i++;
		    }
		
		while (i < p.length() && p.charAt(i) != '+' && p.charAt(i) != '-')
		    {
			aux.append(p.charAt(i));
			i++;
		    }
		
		Point2D point = converti(aux.toString());
		list.addElement(point);
	    }
        sort();
    }
    
    public Polynom(Polynom p)
    {
        super(p.getName());
        list = p.list;
    }
    
    public Polynom(Vector<Point2D> p, String name)
    {
        super(name);
        list = p;
    }

    public Polynom()
    {
        super("null");
        list = new Vector<>();
    }

    public Polynom sum(Polynom p)
    {
        if (list.isEmpty())
            return p;
	
        Vector<Point2D> aux = new Vector<>();
        int j = 0, k = 0;
	
        while (j < list.size() && k < p.list.size())
        {
            if (list.get(j).getY() == p.list.get(k).getY())
		{
		    if (list.get(j).getX() + p.list.get(k).getX() != 0.)
			aux.addElement(new Point2D.Double(list.get(j).getX() + p.list.get(k).getX(), list.get(j).getY()));
		    k++;
		    j++;
		}
            else
		{
		    if (list.get(j).getY() > p.list.get(k).getY())
			{
			    aux.addElement(list.get(j));
			    j++;
			}
		    else if (list.get(j).getY() < p.list.get(k).getY())
			{
			    aux.addElement(p.list.get(k));
			    k++;
			}
		}
        }

        while (j < list.size())
	    {
		aux.addElement(new Point2D.Double(list.get(j).getX(), list.get(j).getY()));
		j++;
	    }
	
        while (k < p.list.size())
	    {
		aux.addElement(new Point2D.Double(p.list.get(k).getX(), p.list.get(k).getY()));
		k++;
	    }
	
        Polynom a = new Polynom(aux, "Result");
	
        if (a.list.isEmpty())
            a.list.addElement(new Point2D.Double(0, 0));
	
        return a;
    }
    
    public Polynom minum(Polynom p)
    {
        if (list.isEmpty())
            return p;
	
        return  this.sum( p.mult(new Polynom("-1","")) ); // a - b = a + (-1)*b
    }
    
    public Polynom prod(Point2D term)
    {
        Vector<Point2D> aux=new Vector<>();
        for(int i=0; i<list.size(); i++)
	    {
		double coef = list.get(i).getX() * term.getX();
		double exp = list.get(i).getY() + term.getY();
		aux.addElement(new Point2D.Double(coef, exp));
	    }
        return new Polynom(aux,"");
    }
    
    public Polynom mult(Polynom p)
    {
        Polynom aux=new Polynom();
	
        for(int j=0; j<list.size(); j++)
	    {
		Polynom tmp = p.prod(this.list.get(j));
		aux=aux.sum(tmp);
	    }
        aux.setName("Result");
        return aux;
    }
    
    public Polynom div(Polynom p)
    {
	int i=0;
	while(i<list.size())
	    {
		if(i+1<list.size() && list.get(i).getY()-list.get(i+1).getY() != 1)
		    list.insert(i+1,new Point2D.Double(0,list.get(i).getY()-1));
		i++;
	    }
	
	Polynom q;
	while(p.list[0].second<=this->list[0].second)
	    {
		q.list.append(qMakePair(list[0].first/p.list[0].first,list[0].second-p.list[0].second));
		*this=*this-(p*q.list.last());
	    }
	q.setName("Result");
	this->setName("Resto");
	return q;
    }
    
    public String print()
    {
        StringBuilder aux=new StringBuilder();
        aux.append(super.print()+"= ");
        for(int i=0; i<list.size(); ++i)
	    {
		if(list.get(i).getX() > 0.0 && i != 0) //aggiunge + se coefficiente positivo
		    aux.append("+");
		if(list.get(i).getY() == 0) // esponente = 0 non aggungo la x
		    aux.append(String.valueOf(list.get(i).getX()));
		else //monomio del tipo ax^b
		    {
			if(list.get(i).getX() == -1. )
			    aux.append('-');
			else if(list.get(i).getX() != 1.0) //se coefficiente==1 non lo considero
			    aux.append(String.valueOf(list.get(i).getX()));
			
			aux.append("x");
			if(list.get(i).getY() != 1) // aggiungo l'esponente se != da 1
			    aux.append("^"+String.valueOf((int)list.get(i).getY()));
		    }
	    }
        return aux.toString();
    }
}
