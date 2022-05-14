/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/Classes/Class.java to edit this template
 */
package testyfitnessefixture;

import fit.ColumnFixture;
import java.util.IllegalFormatCodePointException;

/**
 *
 * @author Paweł
 */
public class TestUsuwaniePokoju extends ColumnFixture{
    Integer nrPokoju;
    public boolean usunPokoj() throws IllegalFormatCodePointException {
    int s1 = liczbaPokoi();
    try{
        SetUp.listaPokoi.usunPokoj(nrPokoju);
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