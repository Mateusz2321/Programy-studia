package entities;

import entities.Daneplacowki;
import entities.Magazyn;
import entities.Zamowienie;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.7.7.v20200504-rNA", date="2022-02-01T16:18:46")
@StaticMetamodel(Apteka.class)
public class Apteka_ { 

    public static volatile CollectionAttribute<Apteka, Zamowienie> zamowienieCollection;
    public static volatile SingularAttribute<Apteka, Magazyn> idMagazynu;
    public static volatile SingularAttribute<Apteka, Integer> idApteki;
    public static volatile SingularAttribute<Apteka, Daneplacowki> danePlacowki;

}