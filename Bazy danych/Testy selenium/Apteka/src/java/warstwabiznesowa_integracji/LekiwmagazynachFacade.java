/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package warstwabiznesowa_integracji;

import entities.Lekiwmagazynach;
import javax.ejb.Stateless;
import javax.persistence.EntityManager;
import javax.persistence.PersistenceContext;

/**
 *
 * @author mateu
 */
@Stateless
public class LekiwmagazynachFacade extends AbstractFacade<Lekiwmagazynach> {

    @PersistenceContext(unitName = "ApptekaPU")
    private EntityManager em;

    @Override
    protected EntityManager getEntityManager() {
        return em;
    }

    public LekiwmagazynachFacade() {
        super(Lekiwmagazynach.class);
    }
    
}
