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
import javax.persistence.NamedQueries;
import javax.persistence.NamedQuery;
import javax.persistence.OneToMany;
import javax.persistence.Table;
import javax.validation.constraints.NotNull;
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author mateu
 */
@Entity
@Table(name = "DANEPLACOWKI")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Daneplacowki.findAll", query = "SELECT d FROM Daneplacowki d"),
    @NamedQuery(name = "Daneplacowki.findByIdDanePlacowki", query = "SELECT d FROM Daneplacowki d WHERE d.idDanePlacowki = :idDanePlacowki"),
    @NamedQuery(name = "Daneplacowki.findByNazwa", query = "SELECT d FROM Daneplacowki d WHERE d.nazwa = :nazwa"),
    @NamedQuery(name = "Daneplacowki.findByKraj", query = "SELECT d FROM Daneplacowki d WHERE d.kraj = :kraj"),
    @NamedQuery(name = "Daneplacowki.findByMiasto", query = "SELECT d FROM Daneplacowki d WHERE d.miasto = :miasto"),
    @NamedQuery(name = "Daneplacowki.findByUlica", query = "SELECT d FROM Daneplacowki d WHERE d.ulica = :ulica"),
    @NamedQuery(name = "Daneplacowki.findByNr", query = "SELECT d FROM Daneplacowki d WHERE d.nr = :nr"),
    @NamedQuery(name = "Daneplacowki.findByKodPocztowy", query = "SELECT d FROM Daneplacowki d WHERE d.kodPocztowy = :kodPocztowy"),
    @NamedQuery(name = "Daneplacowki.findByNrKontaktowy", query = "SELECT d FROM Daneplacowki d WHERE d.nrKontaktowy = :nrKontaktowy"),
    @NamedQuery(name = "Daneplacowki.findByEmail", query = "SELECT d FROM Daneplacowki d WHERE d.email = :email")})
public class Daneplacowki implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "ID_DANE_PLACOWKI")
    private Integer idDanePlacowki;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 200)
    @Column(name = "NAZWA")
    private String nazwa;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "KRAJ")
    private String kraj;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "MIASTO")
    private String miasto;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "ULICA")
    private String ulica;
    @Basic(optional = false)
    @NotNull
    @Column(name = "NR")
    private int nr;
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 10)
    @Column(name = "KOD_POCZTOWY")
    private String kodPocztowy;
    @Size(max = 15)
    @Column(name = "NR_KONTAKTOWY")
    private String nrKontaktowy;
    // @Pattern(regexp="[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?", message="Invalid email")//if the field contains email address consider using this annotation to enforce field validation
    @Basic(optional = false)
    @NotNull
    @Size(min = 1, max = 50)
    @Column(name = "EMAIL")
    private String email;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "idDanePlacowki")
    private Collection<Hurtownia> hurtowniaCollection;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "danePlacowki")
    private Collection<Apteka> aptekaCollection;

    public Daneplacowki() {
    }

    public Daneplacowki(Integer idDanePlacowki) {
        this.idDanePlacowki = idDanePlacowki;
    }

    public Daneplacowki(Integer idDanePlacowki, String nazwa, String kraj, String miasto, String ulica, int nr, String kodPocztowy, String email) {
        this.idDanePlacowki = idDanePlacowki;
        this.nazwa = nazwa;
        this.kraj = kraj;
        this.miasto = miasto;
        this.ulica = ulica;
        this.nr = nr;
        this.kodPocztowy = kodPocztowy;
        this.email = email;
    }

    public Integer getIdDanePlacowki() {
        return idDanePlacowki;
    }

    public void setIdDanePlacowki(Integer idDanePlacowki) {
        this.idDanePlacowki = idDanePlacowki;
    }

    public String getNazwa() {
        return nazwa;
    }

    public void setNazwa(String nazwa) {
        this.nazwa = nazwa;
    }

    public String getKraj() {
        return kraj;
    }

    public void setKraj(String kraj) {
        this.kraj = kraj;
    }

    public String getMiasto() {
        return miasto;
    }

    public void setMiasto(String miasto) {
        this.miasto = miasto;
    }

    public String getUlica() {
        return ulica;
    }

    public void setUlica(String ulica) {
        this.ulica = ulica;
    }

    public int getNr() {
        return nr;
    }

    public void setNr(int nr) {
        this.nr = nr;
    }

    public String getKodPocztowy() {
        return kodPocztowy;
    }

    public void setKodPocztowy(String kodPocztowy) {
        this.kodPocztowy = kodPocztowy;
    }

    public String getNrKontaktowy() {
        return nrKontaktowy;
    }

    public void setNrKontaktowy(String nrKontaktowy) {
        this.nrKontaktowy = nrKontaktowy;
    }

    public String getEmail() {
        return email;
    }

    public void setEmail(String email) {
        this.email = email;
    }

    @XmlTransient
    public Collection<Hurtownia> getHurtowniaCollection() {
        return hurtowniaCollection;
    }

    public void setHurtowniaCollection(Collection<Hurtownia> hurtowniaCollection) {
        this.hurtowniaCollection = hurtowniaCollection;
    }

    @XmlTransient
    public Collection<Apteka> getAptekaCollection() {
        return aptekaCollection;
    }

    public void setAptekaCollection(Collection<Apteka> aptekaCollection) {
        this.aptekaCollection = aptekaCollection;
    }

    @Override
    public int hashCode() {
        int hash = 0;
        hash += (idDanePlacowki != null ? idDanePlacowki.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Daneplacowki)) {
            return false;
        }
        Daneplacowki other = (Daneplacowki) object;
        if ((this.idDanePlacowki == null && other.idDanePlacowki != null) || (this.idDanePlacowki != null && !this.idDanePlacowki.equals(other.idDanePlacowki))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "entities.Daneplacowki[ idDanePlacowki=" + idDanePlacowki + " ]";
    }
    
}
