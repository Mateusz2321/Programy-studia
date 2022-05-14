/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package entities;

import java.io.Serializable;
import java.util.Collection;
import java.util.Date;
import javax.persistence.Basic;
import javax.persistence.CascadeType;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author mateu
 */
@Entity
@Table(name = "LEK")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Lek.findAll", query = "SELECT l FROM Lek l"),
    @NamedQuery(name = "Lek.findByIdLeku", query = "SELECT l FROM Lek l WHERE l.idLeku = :idLeku"),
    @NamedQuery(name = "Lek.findByNazwaLeku", query = "SELECT l FROM Lek l WHERE l.nazwaLeku = :nazwaLeku"),
    @NamedQuery(name = "Lek.findByDataProdukcji", query = "SELECT l FROM Lek l WHERE l.dataProdukcji = :dataProdukcji"),
    @NamedQuery(name = "Lek.findByDataWaznosci", query = "SELECT l FROM Lek l WHERE l.dataWaznosci = :dataWaznosci"),
    @NamedQuery(name = "Lek.findBySposobPodania", query = "SELECT l FROM Lek l WHERE l.sposobPodania = :sposobPodania"),
    @NamedQuery(name = "Lek.findByPostacLeku", query = "SELECT l FROM Lek l WHERE l.postacLeku = :postacLeku"),
    @NamedQuery(name = "Lek.findByWaga", query = "SELECT l FROM Lek l WHERE l.waga = :waga"),
    @NamedQuery(name = "Lek.findByCena", query = "SELECT l FROM Lek l WHERE l.cena = :cena"),
    @NamedQuery(name = "Lek.findByProducent", query = "SELECT l FROM Lek l WHERE l.producent = :producent"),
    @NamedQuery(name = "Lek.findByLiczbaSztukWOpakowaniu", query = "SELECT l FROM Lek l WHERE l.liczbaSztukWOpakowaniu = :liczbaSztukWOpakowaniu"),
    @NamedQuery(name = "Lek.findByZastosowanie", query = "SELECT l FROM Lek l WHERE l.zastosowanie = :zastosowanie")})
public class Lek implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "ID_LEKU")
    private Integer idLeku;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 255)
    @Column(name = "NAZWA_LEKU")
    private String nazwaLeku;
    @Basic(optional = false)
    @NotNull
    @Column(name = "DATA_PRODUKCJI")
    @Temporal(TemporalType.DATE)
    private Date dataProdukcji;
    @Basic(optional = false)
    @NotNull
    @Column(name = "DATA_WAZNOSCI")
    @Temporal(TemporalType.DATE)
    private Date dataWaznosci;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "SPOSOB_PODANIA")
    private String sposobPodania;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "POSTAC_LEKU")
    private String postacLeku;
    @Basic(optional = false)
    @NotNull
    @Column(name = "WAGA")
    private double waga;
    @Basic(optional = false)
    @NotNull
    @Column(name = "CENA")
    private double cena;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "PRODUCENT")
    private String producent;
    @Basic(optional = false)
    @NotNull
    @Column(name = "LICZBA_SZTUK_W_OPAKOWANIU")
    private int liczbaSztukWOpakowaniu;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 255)
    @Column(name = "ZASTOSOWANIE")
    private String zastosowanie;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "idLeku")
    private Collection<Zamowienie> zamowienieCollection;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "idLeku")
    private Collection<Lekiwmagazynach> lekiwmagazynachCollection;

    public Lek() {
    }

    public Lek(Integer idLeku) {
        this.idLeku = idLeku;
    }

    public Lek(Integer idLeku, String nazwaLeku, Date dataProdukcji, Date dataWaznosci, String sposobPodania, String postacLeku, double waga, double cena, String producent, int liczbaSztukWOpakowaniu, String zastosowanie) {
        this.idLeku = idLeku;
        this.nazwaLeku = nazwaLeku;
        this.dataProdukcji = dataProdukcji;
        this.dataWaznosci = dataWaznosci;
        this.sposobPodania = sposobPodania;
        this.postacLeku = postacLeku;
        this.waga = waga;
        this.cena = cena;
        this.producent = producent;
        this.liczbaSztukWOpakowaniu = liczbaSztukWOpakowaniu;
        this.zastosowanie = zastosowanie;
    }

    public Integer getIdLeku() {
        return idLeku;
    }

    public void setIdLeku(Integer idLeku) {
        this.idLeku = idLeku;
    }

    public String getNazwaLeku() {
        return nazwaLeku;
    }

    public void setNazwaLeku(String nazwaLeku) {
        this.nazwaLeku = nazwaLeku;
    }

    public Date getDataProdukcji() {
        return dataProdukcji;
    }

    public void setDataProdukcji(Date dataProdukcji) {
        this.dataProdukcji = dataProdukcji;
    }

    public Date getDataWaznosci() {
        return dataWaznosci;
    }

    public void setDataWaznosci(Date dataWaznosci) {
        this.dataWaznosci = dataWaznosci;
    }

    public String getSposobPodania() {
        return sposobPodania;
    }

    public void setSposobPodania(String sposobPodania) {
        this.sposobPodania = sposobPodania;
    }

    public String getPostacLeku() {
        return postacLeku;
    }

    public void setPostacLeku(String postacLeku) {
        this.postacLeku = postacLeku;
    }

    public double getWaga() {
        return waga;
    }

    public void setWaga(double waga) {
        this.waga = waga;
    }

    public double getCena() {
        return cena;
    }

    public void setCena(double cena) {
        this.cena = cena;
    }

    public String getProducent() {
        return producent;
    }

    public void setProducent(String producent) {
        this.producent = producent;
    }

    public int getLiczbaSztukWOpakowaniu() {
        return liczbaSztukWOpakowaniu;
    }

    public void setLiczbaSztukWOpakowaniu(int liczbaSztukWOpakowaniu) {
        this.liczbaSztukWOpakowaniu = liczbaSztukWOpakowaniu;
    }

    public String getZastosowanie() {
        return zastosowanie;
    }

    public void setZastosowanie(String zastosowanie) {
        this.zastosowanie = zastosowanie;
    }

    @XmlTransient
    public Collection<Zamowienie> getZamowienieCollection() {
        return zamowienieCollection;
    }

    public void setZamowienieCollection(Collection<Zamowienie> zamowienieCollection) {
        this.zamowienieCollection = zamowienieCollection;
    }

    @XmlTransient
    public Collection<Lekiwmagazynach> getLekiwmagazynachCollection() {
        return lekiwmagazynachCollection;
    }

    public void setLekiwmagazynachCollection(Collection<Lekiwmagazynach> lekiwmagazynachCollection) {
        this.lekiwmagazynachCollection = lekiwmagazynachCollection;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idLeku != null ? idLeku.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Lek)) {
            return false;
        }
        Lek other = (Lek) object;
        if ((this.idLeku == null && other.idLeku != null) || (this.idLeku != null && !this.idLeku.equals(other.idLeku))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "entities.Lek[ idLeku=" + idLeku + " ]";
    }
    
}
