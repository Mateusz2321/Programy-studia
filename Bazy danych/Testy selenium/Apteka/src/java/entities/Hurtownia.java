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
@Table(name = "HURTOWNIA")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Hurtownia.findAll", query = "SELECT h FROM Hurtownia h"),
    @NamedQuery(name = "Hurtownia.findByIdHurtowni", query = "SELECT h FROM Hurtownia h WHERE h.idHurtowni = :idHurtowni")})
public class Hurtownia implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "ID_HURTOWNI")
    private Integer idHurtowni;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "idHurtowni")
    private Collection<Zamowienie> zamowienieCollection;
    @JoinColumn(name = "ID_DANE_PLACOWKI", referencedColumnName = "ID_DANE_PLACOWKI")
    @ManyToOne(optional = false)
    private Daneplacowki idDanePlacowki;
    @JoinColumn(name = "ID_MAGAZYNU", referencedColumnName = "ID_MAGAZYNU")
    @ManyToOne(optional = false)
    private Magazyn idMagazynu;

    public Hurtownia() {
    }

    public Hurtownia(Integer idHurtowni) {
        this.idHurtowni = idHurtowni;
    }

    public Integer getIdHurtowni() {
        return idHurtowni;
    }

    public void setIdHurtowni(Integer idHurtowni) {
        this.idHurtowni = idHurtowni;
    }

    @XmlTransient
    public Collection<Zamowienie> getZamowienieCollection() {
        return zamowienieCollection;
    }

    public void setZamowienieCollection(Collection<Zamowienie> zamowienieCollection) {
        this.zamowienieCollection = zamowienieCollection;
    }

    public Daneplacowki getIdDanePlacowki() {
        return idDanePlacowki;
    }

    public void setIdDanePlacowki(Daneplacowki idDanePlacowki) {
        this.idDanePlacowki = idDanePlacowki;
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
        hash += (idHurtowni != null ? idHurtowni.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Hurtownia)) {
            return false;
        }
        Hurtownia other = (Hurtownia) object;
        if ((this.idHurtowni == null && other.idHurtowni != null) || (this.idHurtowni != null && !this.idHurtowni.equals(other.idHurtowni))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "entities.Hurtownia[ idHurtowni=" + idHurtowni + " ]";
    }
    
}
