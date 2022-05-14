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
import javax.validation.constraints.Size;
import javax.xml.bind.annotation.XmlRootElement;
import javax.xml.bind.annotation.XmlTransient;

/**
 *
 * @author mateu
 */
@Entity
@Table(name = "MAGAZYN")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Magazyn.findAll", query = "SELECT m FROM Magazyn m"),
    @NamedQuery(name = "Magazyn.findByIdMagazynu", query = "SELECT m FROM Magazyn m WHERE m.idMagazynu = :idMagazynu"),
    @NamedQuery(name = "Magazyn.findByGodzinyOtwarcia", query = "SELECT m FROM Magazyn m WHERE m.godzinyOtwarcia = :godzinyOtwarcia")})
public class Magazyn implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "ID_MAGAZYNU")
    private Integer idMagazynu;
    @Size(max = 50)
    @Column(name = "GODZINY_OTWARCIA")
    private String godzinyOtwarcia;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "idMagazynu")
    private Collection<Hurtownia> hurtowniaCollection;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "idMagazynu")
    private Collection<Lekiwmagazynach> lekiwmagazynachCollection;
    @OneToMany(cascade = CascadeType.ALL, mappedBy = "idMagazynu")
    private Collection<Apteka> aptekaCollection;

    public Magazyn() {
    }

    public Magazyn(Integer idMagazynu) {
        this.idMagazynu = idMagazynu;
    }

    public Integer getIdMagazynu() {
        return idMagazynu;
    }

    public void setIdMagazynu(Integer idMagazynu) {
        this.idMagazynu = idMagazynu;
    }

    public String getGodzinyOtwarcia() {
        return godzinyOtwarcia;
    }

    public void setGodzinyOtwarcia(String godzinyOtwarcia) {
        this.godzinyOtwarcia = godzinyOtwarcia;
    }

    @XmlTransient
    public Collection<Hurtownia> getHurtowniaCollection() {
        return hurtowniaCollection;
    }

    public void setHurtowniaCollection(Collection<Hurtownia> hurtowniaCollection) {
        this.hurtowniaCollection = hurtowniaCollection;
    }

    @XmlTransient
    public Collection<Lekiwmagazynach> getLekiwmagazynachCollection() {
        return lekiwmagazynachCollection;
    }

    public void setLekiwmagazynachCollection(Collection<Lekiwmagazynach> lekiwmagazynachCollection) {
        this.lekiwmagazynachCollection = lekiwmagazynachCollection;
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
        hash += (idMagazynu != null ? idMagazynu.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Magazyn)) {
            return false;
        }
        Magazyn other = (Magazyn) object;
        if ((this.idMagazynu == null && other.idMagazynu != null) || (this.idMagazynu != null && !this.idMagazynu.equals(other.idMagazynu))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "entities.Magazyn[ idMagazynu=" + idMagazynu + " ]";
    }
    
}
