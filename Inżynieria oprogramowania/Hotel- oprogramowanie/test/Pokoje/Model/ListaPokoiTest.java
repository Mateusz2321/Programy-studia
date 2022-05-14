/*
 * Click nbfs://nbhost/SystemFileSystem/Templates/Licenses/license-default.txt to change this license
 * Click nbfs://nbhost/SystemFileSystem/Templates/UnitTests/JUnit4TestClass.java to edit this template
 */
package Pokoje.Model;


import Testy.Dane;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.Collection;
import java.util.IllegalFormatCodePointException;
import java.util.List;
import org.junit.AfterClass;
import org.junit.Assert;
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
import org.junit.runners.Parameterized.Parameter;

//@Categories.SuiteClasses({Group.class})
@FixMethodOrder(MethodSorters.NAME_ASCENDING)
@RunWith(Parameterized.class)
//@Category({FirstGroup.class})
public class ListaPokoiTest {
   private static ListaPokoi listaPokoi; 
   private Dane dane=new Dane();
    public ListaPokoiTest() {
         
    }
    static Integer x[]=new Integer[5];
    @BeforeClass
    public static void setUpClass() {
        listaPokoi=new ListaPokoi();
        assertNotNull("Lista pokoi nie jest pusta",listaPokoi.pobierzListePokoi());
         
        for(int i = 0; i < 5; i++)
        {
            x[i] = listaPokoi.dodajPustyPokoj(); 
        }
    }
    
    @AfterClass
    public static void tearDownClass() {
    }
    
    


   @Parameterized.Parameter
  public Integer operations;
   
   @Parameterized.Parameters
   public static Collection<Object[]>data(){
      Object[][] data1 = new Object[][]{{0},{1},{2},{3},{4}};
      return Arrays.asList(data1);       
   }
   
    @Test
    @Category(FirstGroup.class)
    public void testUsunPokoj() {
            List<Pokoj> arr=listaPokoi.pobierzListePokoi();
            int numberOfRoomsBefore=arr.size();
        
            listaPokoi.usunPokoj(dane.nowyNr[operations]);
             arr=listaPokoi.pobierzListePokoi();
            int numberOfRooms=arr.size();
       
            assertEquals("Sprawdzenie, czy lista pokoi jest o 1 mniejsza.",numberOfRoomsBefore-1,numberOfRooms);
            assertNull("Sprawdzenie,czy lista pokoi nie zawiera usuniętego elementu.",listaPokoi.znajdzPokoj(x[operations]));
 
    }
    
    
    @Rule
    public ExpectedException exception=ExpectedException.none();
    
    @Test
    @Category(FirstGroup.class)
    public void testModyfikujAtrybutyPokoju() {
    	Pokoj pBefore=listaPokoi.znajdzPokoj(x[operations]);
    	if(pBefore!=null){
            assertTrue(listaPokoi.modyfikujAtrybutyPokoju(dane.cena[operations],dane.liczbaMiejsc[operations],dane.wyposazenie[operations],
    			Arrays.asList(dane.dniRezerwacji[operations]),x[operations],dane.nowyNr[operations],
    			dane.dodanieNowego[operations]));
            Pokoj p;
            p=listaPokoi.znajdzPokoj(dane.nowyNr[operations]);
    	
            assertEquals("Cena takia sama.",dane.cena[operations],p.getCena());
            assertEquals("Liczba miejsc taka sama.",dane.liczbaMiejsc[operations],p.getLiczbaMiejsc());
            assertArrayEquals("Wyposażenie takie same.",dane.wyposazenie[operations],p.getWyposazenie());
            assertEquals("Dni rezerwacji takie same.",Arrays.asList(dane.dniRezerwacji[operations]),p.getDniRezerwacji());
            assertEquals("Nowy nr pokoju.",dane.nowyNr[operations],p.getNumerPokoju());
        }else{
            assertFalse(listaPokoi.modyfikujAtrybutyPokoju(dane.cena[operations],dane.liczbaMiejsc[operations],dane.wyposazenie[operations],
    			Arrays.asList(dane.dniRezerwacji[operations]),x[operations],dane.nowyNr[operations],
    			dane.dodanieNowego[operations]));
            
        }  
        exception.expect(IllegalFormatCodePointException.class);
        exception.expectMessage("Code point = 0x0");
        listaPokoi.modyfikujAtrybutyPokoju(dane.cena[operations],dane.liczbaMiejsc[operations],null,
    			Arrays.asList(dane.dniRezerwacji[operations]),x[operations],dane.nowyNr[operations],
    			dane.dodanieNowego[operations]);
        
    }
    
}
