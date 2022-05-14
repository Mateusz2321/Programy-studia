/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package testyfitnessefixture;

import fit.Fixture;
import Pokoje.Model.ListaPokoi;
import Pokoje.Model.Rezerwacja;

/**
 *
 * @author mateu
 */
public class SetUp extends Fixture{
    static ListaPokoi listaPokoi;
    static Rezerwacja rezerwacja;
public SetUp() {
    listaPokoi = new ListaPokoi();
    rezerwacja = new Rezerwacja(listaPokoi);
}
}
