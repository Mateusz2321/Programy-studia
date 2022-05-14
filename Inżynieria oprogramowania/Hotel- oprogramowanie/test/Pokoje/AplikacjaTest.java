/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit4TestClass.java to edit this template
 */
package Pokoje;

import Pokoje.Model.FirstGroup;
import Pokoje.Model.Group;
import Pokoje.Model.ListaPokoi;
import Pokoje.Model.PokojDoRezerwacji;
import Pokoje.Model.Rezerwacja;
import Pokoje.Model.SecondGroup;
import Testy.Dane;
import java.util.Arrays;
import java.util.IllegalFormatCodePointException;
import java.util.List;
import org.junit.AfterClass;
import org.junit.BeforeClass;
import org.junit.Test;
import static org.junit.Assert.*;
import org.junit.FixMethodOrder;
import org.junit.Rule;
import org.junit.experimental.categories.Categories;
import org.junit.experimental.categories.Category;
import org.junit.rules.ExpectedException;
import org.junit.runner.RunWith;
import org.junit.runners.MethodSorters;
//@Categories.SuiteClasses({Group.class})
//@RunWith(Categories.class)
//@Category({SecondGroup.class})
@FixMethodOrder(MethodSorters.NAME_ASCENDING)
public class AplikacjaTest {
    private static Dane dane=new Dane();
    private static Aplikacja ap;
    private static ListaPokoi lista;
    private static Rezerwacja rezerwacja;
    public AplikacjaTest() {
    }
    
    @BeforeClass
    public static void setUpClass() {
        ap=new Aplikacja();
        lista=ap.getListaPokoi();
        rezerwacja=ap.getRezerwacja();
        int x;
        for(int i=0;i<5;i++){
            x=lista.dodajPustyPokoj();
            lista.modyfikujAtrybutyPokoju(dane.cena[i],dane.liczbaMiejsc[i],dane.wyposazenie[i],
    			Arrays.asList(dane.dniRezerwacji[i]),x,dane.nowyNr[i],
    			true);
            rezerwacja.dodajPokoj(Arrays.asList(dane.dni[i]), dane.nowyNr[i]);
            
        }
    }
    
    @AfterClass
    public static void tearDownClass() {
    }

    @Test
    public void testModyfikujPokoj() {
     
    }
    
    @Rule
    public ExpectedException exception=ExpectedException.none();
    @Test
    @Category(FirstGroup.class)
    public void testDokonajRezerwacji() {        
        ap.dokonajRezerwacji();
        Rezerwacja r=ap.getRezerwacja();
        List<PokojDoRezerwacji> lr=r.getListaPokoiDoRezerwacji();
        Boolean reserved=true;
        for(int i=0;i<lr.size();i++){
            if(lr.get(i).getReserve()==false){
                reserved=false;
                break;
            }
        }
        assertTrue("Status pokoju powinien być ustawiony na zarezerwowany.",reserved);
        Aplikacja a=new Aplikacja();
        a.setRezerwacja(null);
        exception.expect(IllegalFormatCodePointException.class);
        exception.expectMessage("Code point = 0x0");
        a.dokonajRezerwacji();
    }

    @Test
    public void testObliczWartoscRachunku() {
       
        
    }

    @Test
    public void testPotwierdzRezerwacje() {
        
        
    }

    @Test
    public void testUsunPokoj() {
        
        
    }

    @Test
    public void testWskazPokojDoRezerwacji() {
       
        
    }

    @Test
    public void testZaplacZaRezerwacje() {
        
        
    }
    
}
