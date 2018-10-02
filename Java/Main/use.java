package Main;

import Classes.*;

public class use {

    public static void main(String[] args)
    {
	try
	    {
		Polynom p = new Polynom("4x+5x^2+66","P1");
		Polynom p2 = new Polynom("2x^2","P2");
		System.out.println(p.print());
		System.out.println(p2.print());
		System.out.println((p.sum(p2)).print()); //somma
		System.out.println(p.minum(p2).print()); //sottrazione
		System.out.println(p.mult(p2).print()); //moltiplicazione

		System.out.println();

		EuclideanVector v1 = new EuclideanVector(5,0,"v1");
		EuclideanVector v2 = new EuclideanVector(7,45,"v2");
		System.out.println(v1.print());
		System.out.println(v2.print());
		System.out.println((v1.sum(v2)).print()); //somma
		System.out.println(v1.minum(v2).print()); //sottrazione
		System.out.println(v1.crossProduct(v2).print()); //prodotto vettoriale
		System.out.println("Prodotto scalare = "+v1.dotProduct(v2)); //prodotto scalare
	    }
	catch(Exception e)
	    {
		System.out.println(e.toString);
	    }

    }
}
