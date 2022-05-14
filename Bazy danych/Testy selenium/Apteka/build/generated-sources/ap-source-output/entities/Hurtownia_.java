package entities;

import entities.Daneplacowki;
import entities.Magazyn;
import entities.Zamowienie;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.7.7.v20200504-rNA", date="2022-02-01T16:18:46")
@StaticMetamodel(Hurtownia.class)
public class Hurtownia_ { 

    public static volatile CollectionAttribute<Hurtownia, Zamowienie> zamowienieCollection;
    public static volatile SingularAttribute<Hurtownia, Integer> idHurtowni;
    public static volatile SingularAttribute<Hurtownia, Magazyn> idMagazynu;
    public static volatile SingularAttribute<Hurtownia, Daneplacowki> idDanePlacowki;

}