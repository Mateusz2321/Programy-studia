/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit4TestClass.java to edit this template
 */
package Pokoje.Model;

import Pokoje.Aplikacja;
import static Pokoje.Model.ListaPokoiTest.x;
import Testy.Dane;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
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
import org.junit.runners.Parameterized;
//Categories.SuiteClasses({Group.class})
//@Category({Group.class})
@FixMethodOrder(MethodSorters.NAME_ASCENDING)
@RunWith(Parameterized.class)
public class RezerwacjaTest {
    static private Dane dane=new Dane();
    static private ListaPokoi lista;
    static private Rezerwacja rezerwacja;
    public RezerwacjaTest() {
    }
    static Integer x[]=new Integer[5];
    @BeforeClass
    public static void setUpClass() {
        
        Aplikacja ap=new Aplikacja();
        lista=new ListaPokoi();
        ap.setListaPokoi(lista);
        rezerwacja=new Rezerwacja(lista);
        ap.setRezerwacja(rezerwacja);
             for(int i = 0; i < 5; i++)
        {
            x[i] = lista.dodajPustyPokoj(); 
            lista.modyfikujAtrybutyPokoju(dane.cena[i],dane.liczbaMiejsc[i],dane.wyposazenie[i],
    			Arrays.asList(dane.dniRezerwacji[i]),x[i],dane.nowyNr[i],
    			dane.dodanieNowego[i]);
        }
    }
    
    @AfterClass
    public static void tearDownClass() {
    }
    
    @Parameterized.Parameter
    public Integer opNumb;
   
    @Parameterized.Parameters
    public static Collection<Object[]>data(){
      Object[][] data1 = new Object[][]{{0},{1},{2},{3},{4}};
      return Arrays.asList(data1);       
   }    
    @Rule
    public ExpectedException exception=ExpectedException.none();
    
    @Test
    @Category(SecondGroup.class)
    public void aTestDodajPokoj() {
        rezerwacja.dodajPokoj(Arrays.asList(dane.dni[opNumb]),dane.nowyNr[opNumb]);
        int sizeAfter=rezerwacja.getListaPokoiDoRezerwacji().size();
        
        assertEquals("Sprawdzenie, czy rezerwacja zawiera 1 element więcej.",opNumb+1,sizeAfter);//op_numb.intValue(),sizeAfter);
        exception.expect(IllegalFormatCodePointException.class);
        exception.expectMessage("Code point = 0x0");
        rezerwacja.dodajPokoj(null,dane.nowyNr[opNumb]);
        
    }

 
    @Test
    @Category(SecondGroup.class)
    public void testAktualizujAtrybutyPokoi() {
       
       List<PokojDoRezerwacji> rezPokojList=rezerwacja.getListaPokoiDoRezerwacji();       
       Pokoj p=lista.znajdzPokoj(rezPokojList.get(opNumb).getNrPokoju());
       List<Integer> lista1=p.getDniRezerwacji();
       List<Integer> lista2=new ArrayList<>();       
       for(int i=0;i<lista1.size();i++){
           lista2.add(lista1.get(i));
       }
       int sizeBefore=lista2.size();
       rezerwacja.aktualizujAtrybutyPokoi();
       List<Integer> listaAfter=p.getDniRezerwacji();
       int sizeAfter=listaAfter.size();
       assertEquals("Sprawdzenie,czy pokoj zawiera niformacje o dniach nowej rezerwacji.",sizeBefore+3,sizeAfter);
        
        
        
    }

  
    
}
