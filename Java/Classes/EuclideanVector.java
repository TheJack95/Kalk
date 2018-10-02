package Classes;

import java.awt.geom.Point2D;
import java.lang.*;

public class EuclideanVector extends BaseClass {
    private Point2D p1 = new Point2D.Double();
    private Point2D p2;
    private double length;
    private double angle;

    public EuclideanVector(double l, double a, Point2D p, String n)
    {
        super(n);

        if( Math.abs(a) == 90 || Math.abs(a) == 180)
        {
            p2 = new Point2D.Double(0,l);
        }
        else
            if (Math.abs(a) == 0 || Math.abs(a) == 360)
            {
                p2 = new Point2D.Double(l,0);
            }
            else
                p2 = new Point2D.Double(Math.cos(a * Math.PI / 180) * l, Math.sin(a * Math.PI / 180) * l);

        length = l;
        angle = a;
    }

    public EuclideanVector(double l, double a, String n)
    {
        super(n);
        p2 = new Point2D.Double( Math.cos(a*Math.PI/180)*l, Math.sin(a*Math.PI/180)*l );
        length = l;
        angle = a;
    }

    public EuclideanVector(String n, Point2D pa, Point2D pb)
    {
        super(n);
        p1 = pa;
        p2 = pb;
        length = Math.sqrt( Math.pow(p2.getX()-p1.getX(),2) + Math.pow(p2.getY()-p1.getY(),2) );
        angle = Math.atan ((p2.getY()-p1.getY()) / (p2.getX()-p1.getX()) ) * 180 / Math.PI;

    }

    public EuclideanVector(EuclideanVector v)
    {
        super(v.getName());
        p1=v.p1;
        p2=v.p2;
        length=v.length;
        angle=v.angle;
    }

    public EuclideanVector()
    {
        super("null");
        p1 = new Point2D.Double();
        p2 = new Point2D.Double();
        length = 0;
        angle = 0;
    }

    public double getA() { return angle; }

    public double getL() { return length; }

    public static double Angle(EuclideanVector v1, EuclideanVector v2) //angolo tra due vettori
    {
        return Math.acos( ( (v1.dotProduct(v2)) / (v1.length*v2.length) ) * Math.PI/180);
    }

    public EuclideanVector crossProduct(EuclideanVector v) //prodotto vettoriale
    {
        return  new EuclideanVector(v.length*length*Math.sin(Angle(this,v)),0,"Result");
    }

    public double dotProduct(EuclideanVector v) //prodotto scalare
    {
        return p2.getX()*v.p2.getX()+p2.getY()*v.p2.getY();
    }

    public EuclideanVector sum(EuclideanVector v)
    {
        Point2D p = new Point2D.Double(p1.getX()+p2.getX(),v.p1.getY()+v.p2.getY());
        return new EuclideanVector("result", p, new Point2D.Double());
    }

    public EuclideanVector minum(EuclideanVector v)
    {
        Point2D p = new Point2D.Double(p1.getX()-p2.getX(),v.p1.getY()-v.p2.getY());
        return new EuclideanVector("result", p, new Point2D.Double());
    }

    public EuclideanVector molt(double n)
    {
        return new EuclideanVector(length*=n,angle,getName());
    }

    public String print()
    {
        String aux="Vettore  " + super.print();
        aux += "\nPunto di applicazione : ("+ p1.getX() + ',' + p1.getY() + ")" + "\nPunto 2 : (" + p2.getX() + ',' + p2.getY() + ")";
        aux += "\nModulo = " + length;
        aux += "\nAngolo = " + angle;
        return aux;
    }
}
