/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package entities;

import java.io.Serializable;
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
import javax.validation.constraints.NotNull;
import javax.xml.bind.annotation.XmlRootElement;

/**
 *
 * @author mateu
 */
@Entity
@Table(name = "LEKIWMAGAZYNACH")
@XmlRootElement
@NamedQueries({
    @NamedQuery(name = "Lekiwmagazynach.findAll", query = "SELECT l FROM Lekiwmagazynach l"),
    @NamedQuery(name = "Lekiwmagazynach.findByNrWiersza", query = "SELECT l FROM Lekiwmagazynach l WHERE l.nrWiersza = :nrWiersza"),
    @NamedQuery(name = "Lekiwmagazynach.findByIlosc", query = "SELECT l FROM Lekiwmagazynach l WHERE l.ilosc = :ilosc")})
public class Lekiwmagazynach implements Serializable {

    private static final long serialVersionUID = 1L;
    @Id
    @GeneratedValue(strategy = GenerationType.IDENTITY)
    @Basic(optional = false)
    @Column(name = "NR_WIERSZA")
    private Integer nrWiersza;
    @Basic(optional = false)
    @NotNull
    @Column(name = "ILOSC")
    private int ilosc;
    @JoinColumn(name = "ID_LEKU", referencedColumnName = "ID_LEKU")
    @ManyToOne(optional = false)
    private Lek idLeku;
    @JoinColumn(name = "ID_MAGAZYNU", referencedColumnName = "ID_MAGAZYNU")
    @ManyToOne(optional = false)
    private Magazyn idMagazynu;

    public Lekiwmagazynach() {
    }

    public Lekiwmagazynach(Integer nrWiersza) {
        this.nrWiersza = nrWiersza;
    }

    public Lekiwmagazynach(Integer nrWiersza, int ilosc) {
        this.nrWiersza = nrWiersza;
        this.ilosc = ilosc;
    }

    public Integer getNrWiersza() {
        return nrWiersza;
    }

    public void setNrWiersza(Integer nrWiersza) {
        this.nrWiersza = nrWiersza;
    }

    public int getIlosc() {
        return ilosc;
    }

    public void setIlosc(int ilosc) {
        this.ilosc = ilosc;
    }

    public Lek getIdLeku() {
        return idLeku;
    }

    public void setIdLeku(Lek idLeku) {
        this.idLeku = idLeku;
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
        hash += (nrWiersza != null ? nrWiersza.hashCode() : 0);
        return hash;
    }

    @Override
    public boolean equals(Object object) {
        // TODO: Warning - this method won't work in the case the id fields are not set
        if (!(object instanceof Lekiwmagazynach)) {
            return false;
        }
        Lekiwmagazynach other = (Lekiwmagazynach) object;
        if ((this.nrWiersza == null && other.nrWiersza != null) || (this.nrWiersza != null && !this.nrWiersza.equals(other.nrWiersza))) {
            return false;
        }
        return true;
    }

    @Override
    public String toString() {
        return "entities.Lekiwmagazynach[ nrWiersza=" + nrWiersza + " ]";
    }
    
}
