/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package testyfitnessefixture;

import fit.ColumnFixture;
import java.util.Arrays;
import java.util.IllegalFormatCodePointException;

/**
 *
 * @author Paweł
 */
public class TestDodawaniePokojuDoRezerwacji extends ColumnFixture{
    Integer[] dniRezerwacji;
    Integer nrPokoju;
    public boolean dodajPokojDoRezerwacji() throws IllegalFormatCodePointException {
    int s1 = liczbaPokoi();
    try{
        SetUp.rezerwacja.dodajPokoj(Arrays.asList(dniRezerwacji), nrPokoju);
        int s2 = liczbaPokoi();
        return s1!=s2;
    } catch(IllegalFormatCodePointException e) {
    }
    return false;
}
public int liczbaPokoi() {
    return SetUp.rezerwacja.getListaPokoiDoRezerwacji().size();
}
}