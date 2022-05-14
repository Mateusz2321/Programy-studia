/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package entities;

import java.io.Serializable;
import java.util.Collection;
import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author mateu
 */
@Entity
@Table(name = "APTEKA")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Apteka.findAll", query = "SELECT a FROM Apteka a"),
    @NamedQuery(name = "Apteka.findByIdApteki", query = "SELECT a FROM Apteka a WHERE a.idApteki = :idApteki")})
public class Apteka implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "ID_APTEKI")
    private Integer idApteki;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "idApteki")
    private Collection<Zamowienie> zamowienieCollection;
    @JoinColumn(name = "DANE_PLACOWKI", referencedColumnName = "ID_DANE_PLACOWKI")
    @ManyToOne(optional = false)
    private Daneplacowki danePlacowki;
    @JoinColumn(name = "ID_MAGAZYNU", referencedColumnName = "ID_MAGAZYNU")
    @ManyToOne(optional = false)
    private Magazyn idMagazynu;

    public Apteka() {
    }

    public Apteka(Integer idApteki) {
        this.idApteki = idApteki;
    }

    public Integer getIdApteki() {
        return idApteki;
    }

    public void setIdApteki(Integer idApteki) {
        this.idApteki = idApteki;
    }

    @XmlTransient
    public Collection<Zamowienie> getZamowienieCollection() {
        return zamowienieCollection;
    }

    public void setZamowienieCollection(Collection<Zamowienie> zamowienieCollection) {
        this.zamowienieCollection = zamowienieCollection;
    }

    public Daneplacowki getDanePlacowki() {
        return danePlacowki;
    }

    public void setDanePlacowki(Daneplacowki danePlacowki) {
        this.danePlacowki = danePlacowki;
    }

    public Magazyn getIdMagazynu() {
        return idMagazynu;
    }

    public void setIdMagazynu(Magazyn idMagazynu) {
        this.idMagazynu = idMagazynu;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idApteki != null ? idApteki.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Apteka)) {
            return false;
        }
        Apteka other = (Apteka) object;
        if ((this.idApteki == null && other.idApteki != null) || (this.idApteki != null && !this.idApteki.equals(other.idApteki))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "entities.Apteka[ idApteki=" + idApteki + " ]";
    }
    
}
