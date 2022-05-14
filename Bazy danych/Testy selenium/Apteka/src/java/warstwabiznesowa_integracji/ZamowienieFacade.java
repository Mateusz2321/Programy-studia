/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package warstwabiznesowa_integracji;

import entities.Zamowienie;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

/**
 *
 * @author mateu
 */
@Stateless
public class ZamowienieFacade extends AbstractFacade<Zamowienie> {

    @PersistenceContext(unitName = "ApptekaPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public ZamowienieFacade() {
        super(Zamowienie.class);
    }
    
}
