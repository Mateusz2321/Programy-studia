package entities;

import entities.Lek;
import entities.Magazyn;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.7.7.v20200504-rNA", date="2022-02-01T16:18:46")
@StaticMetamodel(Lekiwmagazynach.class)
public class Lekiwmagazynach_ { 

    public static volatile SingularAttribute<Lekiwmagazynach, Integer> ilosc;
    public static volatile SingularAttribute<Lekiwmagazynach, Integer> nrWiersza;
    public static volatile SingularAttribute<Lekiwmagazynach, Magazyn> idMagazynu;
    public static volatile SingularAttribute<Lekiwmagazynach, Lek> idLeku;

}