/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package testyfitnessefixture;

import fit.ColumnFixture;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.IllegalFormatCodePointException;
import java.util.List;


public class TestDodawaniePokoju extends ColumnFixture{
    Float cena;
    Integer liczbaMiejsc;
    Boolean[] wyposazenie;
    Integer[] dniRezerwacji;
    Integer nowyNr;
    Boolean dodanieNowego;
    public boolean dodajPokoj() throws IllegalFormatCodePointException {
    int s1 = liczbaPokoi();
    List<Integer> l=new ArrayList<>(Arrays.asList(dniRezerwacji));
    try{
        SetUp.listaPokoi.modyfikujAtrybutyPokoju(cena, liczbaMiejsc, wyposazenie, l, 
                SetUp.listaPokoi.dodajPustyPokoj(), nowyNr, dodanieNowego);
        int s2 = liczbaPokoi();
        return s1!=s2;
    } catch(IllegalFormatCodePointException e) {
    }
    return false;
}
public int liczbaPokoi() {
    return SetUp.listaPokoi.pobierzListePokoi().size();
}
}