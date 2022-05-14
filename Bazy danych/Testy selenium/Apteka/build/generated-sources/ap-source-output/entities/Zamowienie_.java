package entities;

import entities.Apteka;
import entities.Hurtownia;
import entities.Lek;
import java.util.Date;
import javax.annotation.Generated;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.7.7.v20200504-rNA", date="2022-02-01T16:18:46")
@StaticMetamodel(Zamowienie.class)
public class Zamowienie_ { 

    public static volatile SingularAttribute<Zamowienie, Date> terminRealizacji;
    public static volatile SingularAttribute<Zamowienie, Integer> liczbaSztuk;
    public static volatile SingularAttribute<Zamowienie, Integer> idZamowienia;
    public static volatile SingularAttribute<Zamowienie, Hurtownia> idHurtowni;
    public static volatile SingularAttribute<Zamowienie, Lek> idLeku;
    public static volatile SingularAttribute<Zamowienie, String> sposobOdbioruZamowienia;
    public static volatile SingularAttribute<Zamowienie, String> status;
    public static volatile SingularAttribute<Zamowienie, Apteka> idApteki;

}