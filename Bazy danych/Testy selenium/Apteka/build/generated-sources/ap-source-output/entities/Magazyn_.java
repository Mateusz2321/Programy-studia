package entities;

import entities.Apteka;
import entities.Hurtownia;
import entities.Lekiwmagazynach;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.7.7.v20200504-rNA", date="2022-02-01T16:18:46")
@StaticMetamodel(Magazyn.class)
public class Magazyn_ { 

    public static volatile CollectionAttribute<Magazyn, Lekiwmagazynach> lekiwmagazynachCollection;
    public static volatile SingularAttribute<Magazyn, String> godzinyOtwarcia;
    public static volatile CollectionAttribute<Magazyn, Apteka> aptekaCollection;
    public static volatile SingularAttribute<Magazyn, Integer> idMagazynu;
    public static volatile CollectionAttribute<Magazyn, Hurtownia> hurtowniaCollection;

}