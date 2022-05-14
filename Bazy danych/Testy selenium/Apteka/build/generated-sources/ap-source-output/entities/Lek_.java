package entities;

import entities.Lekiwmagazynach;
import entities.Zamowienie;
import java.util.Date;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.7.7.v20200504-rNA", date="2022-02-01T16:18:46")
@StaticMetamodel(Lek.class)
public class Lek_ { 

    public static volatile SingularAttribute<Lek, String> postacLeku;
    public static volatile CollectionAttribute<Lek, Lekiwmagazynach> lekiwmagazynachCollection;
    public static volatile SingularAttribute<Lek, Date> dataWaznosci;
    public static volatile SingularAttribute<Lek, String> producent;
    public static volatile SingularAttribute<Lek, String> nazwaLeku;
    public static volatile SingularAttribute<Lek, Integer> idLeku;
    public static volatile SingularAttribute<Lek, String> sposobPodania;
    public static volatile CollectionAttribute<Lek, Zamowienie> zamowienieCollection;
    public static volatile SingularAttribute<Lek, Double> waga;
    public static volatile SingularAttribute<Lek, Integer> liczbaSztukWOpakowaniu;
    public static volatile SingularAttribute<Lek, String> zastosowanie;
    public static volatile SingularAttribute<Lek, Double> cena;
    public static volatile SingularAttribute<Lek, Date> dataProdukcji;

}