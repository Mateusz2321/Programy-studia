/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package entities;

import java.io.Serializable;
import java.util.Date;
import javax.persistence.Basic;
import javax.persistence.Column;
import javax.persistence.Entity;
import javax.persistence.GeneratedValue;
import javax.persistence.GenerationType;
import javax.persistence.Id;
import javax.persistence.JoinColumn;
import javax.persistence.ManyToOne;
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.Table;
import javax.persistence.Temporal;
import javax.persistence.TemporalType;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author mateu
 */
@Entity
@Table(name = "ZAMOWIENIE")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Zamowienie.findAll", query = "SELECT z FROM Zamowienie z"),
    @NamedQuery(name = "Zamowienie.findByIdZamowienia", query = "SELECT z FROM Zamowienie z WHERE z.idZamowienia = :idZamowienia"),
    @NamedQuery(name = "Zamowienie.findByLiczbaSztuk", query = "SELECT z FROM Zamowienie z WHERE z.liczbaSztuk = :liczbaSztuk"),
    @NamedQuery(name = "Zamowienie.findBySposobOdbioruZamowienia", query = "SELECT z FROM Zamowienie z WHERE z.sposobOdbioruZamowienia = :sposobOdbioruZamowienia"),
    @NamedQuery(name = "Zamowienie.findByTerminRealizacji", query = "SELECT z FROM Zamowienie z WHERE z.terminRealizacji = :terminRealizacji"),
    @NamedQuery(name = "Zamowienie.findByStatus", query = "SELECT z FROM Zamowienie z WHERE z.status = :status")})
public class Zamowienie implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "ID_ZAMOWIENIA")
    private Integer idZamowienia;
    @Basic(optional = false)
    @NotNull
    @Column(name = "LICZBA_SZTUK")
    private int liczbaSztuk;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 30)
    @Column(name = "SPOSOB_ODBIORU_ZAMOWIENIA")
    private String sposobOdbioruZamowienia;
    @Basic(optional = false)
    @NotNull
    @Column(name = "TERMIN_REALIZACJI")
    @Temporal(TemporalType.DATE)
    private Date terminRealizacji;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 30)
    @Column(name = "STATUS")
    private String status;
    @JoinColumn(name = "ID_APTEKI", referencedColumnName = "ID_APTEKI")
    @ManyToOne(optional = false)
    private Apteka idApteki;
    @JoinColumn(name = "ID_HURTOWNI", referencedColumnName = "ID_HURTOWNI")
    @ManyToOne(optional = false)
    private Hurtownia idHurtowni;
    @JoinColumn(name = "ID_LEKU", referencedColumnName = "ID_LEKU")
    @ManyToOne(optional = false)
    private Lek idLeku;

    public Zamowienie() {
    }

    public Zamowienie(Integer idZamowienia) {
        this.idZamowienia = idZamowienia;
    }

    public Zamowienie(Integer idZamowienia, int liczbaSztuk, String sposobOdbioruZamowienia, Date terminRealizacji, String status) {
        this.idZamowienia = idZamowienia;
        this.liczbaSztuk = liczbaSztuk;
        this.sposobOdbioruZamowienia = sposobOdbioruZamowienia;
        this.terminRealizacji = terminRealizacji;
        this.status = status;
    }

    public Integer getIdZamowienia() {
        return idZamowienia;
    }

    public void setIdZamowienia(Integer idZamowienia) {
        this.idZamowienia = idZamowienia;
    }

    public int getLiczbaSztuk() {
        return liczbaSztuk;
    }

    public void setLiczbaSztuk(int liczbaSztuk) {
        this.liczbaSztuk = liczbaSztuk;
    }

    public String getSposobOdbioruZamowienia() {
        return sposobOdbioruZamowienia;
    }

    public void setSposobOdbioruZamowienia(String sposobOdbioruZamowienia) {
        this.sposobOdbioruZamowienia = sposobOdbioruZamowienia;
    }

    public Date getTerminRealizacji() {
        return terminRealizacji;
    }

    public void setTerminRealizacji(Date terminRealizacji) {
        this.terminRealizacji = terminRealizacji;
    }

    public String getStatus() {
        return status;
    }

    public void setStatus(String status) {
        this.status = status;
    }

    public Apteka getIdApteki() {
        return idApteki;
    }

    public void setIdApteki(Apteka idApteki) {
        this.idApteki = idApteki;
    }

    public Hurtownia getIdHurtowni() {
        return idHurtowni;
    }

    public void setIdHurtowni(Hurtownia idHurtowni) {
        this.idHurtowni = idHurtowni;
    }

    public Lek getIdLeku() {
        return idLeku;
    }

    public void setIdLeku(Lek idLeku) {
        this.idLeku = idLeku;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idZamowienia != null ? idZamowienia.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Zamowienie)) {
            return false;
        }
        Zamowienie other = (Zamowienie) object;
        if ((this.idZamowienia == null && other.idZamowienia != null) || (this.idZamowienia != null && !this.idZamowienia.equals(other.idZamowienia))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "entities.Zamowienie[ idZamowienia=" + idZamowienia + " ]";
    }
    
}
