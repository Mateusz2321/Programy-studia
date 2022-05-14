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
public class TestZnajdowaniePokoju extends ColumnFixture{
    Integer nrPokoju;
    public boolean znajdzPokoj() throws IllegalFormatCodePointException {
    int s1 = nrPokoju;
    try{
        SetUp.listaPokoi.znajdzPokoj(nrPokoju);
        int s2 = SetUp.listaPokoi.znajdzPokoj(nrPokoju).getNumerPokoju();
        return s1==s2;
    } catch(IllegalFormatCodePointException e) {
    }
    return false;
}
}