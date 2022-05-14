package entities;

import entities.Apteka;
import entities.Hurtownia;
import javax.annotation.Generated;
import javax.persistence.metamodel.CollectionAttribute;
import javax.persistence.metamodel.SingularAttribute;
import javax.persistence.metamodel.StaticMetamodel;

@Generated(value="EclipseLink-2.7.7.v20200504-rNA", date="2022-02-01T16:18:46")
@StaticMetamodel(Daneplacowki.class)
public class Daneplacowki_ { 

    public static volatile SingularAttribute<Daneplacowki, String> kraj;
    public static volatile SingularAttribute<Daneplacowki, String> ulica;
    public static volatile SingularAttribute<Daneplacowki, Integer> nr;
    public static volatile SingularAttribute<Daneplacowki, String> nrKontaktowy;
    public static volatile CollectionAttribute<Daneplacowki, Apteka> aptekaCollection;
    public static volatile SingularAttribute<Daneplacowki, String> kodPocztowy;
    public static volatile SingularAttribute<Daneplacowki, Integer> idDanePlacowki;
    public static volatile CollectionAttribute<Daneplacowki, Hurtownia> hurtowniaCollection;
    public static volatile SingularAttribute<Daneplacowki, String> miasto;
    public static volatile SingularAttribute<Daneplacowki, String> nazwa;
    public static volatile SingularAttribute<Daneplacowki, String> email;

}