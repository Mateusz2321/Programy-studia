package Pokoje;

import Pokoje.Model.*;
import java.util.ArrayList;
import java.util.IllegalFormatCodePointException;
import java.util.List;
import java.util.Scanner;


public class Aplikacja {

	private ListaPokoi listaPokoi;
	private Rezerwacja rezerwacja;
        
	public Aplikacja(){
            listaPokoi= new ListaPokoi();
            rezerwacja= new Rezerwacja(listaPokoi);    
            
            
        }
        public ListaPokoi getListaPokoi(){
            return this.listaPokoi;
        }
        public void setListaPokoi(ListaPokoi listaPokoi){
            this.listaPokoi=listaPokoi;
        }
        public void setRezerwacja(Rezerwacja r){
            this.rezerwacja=r;
        }
        public Rezerwacja getRezerwacja(){
            return this.rezerwacja;
        }
	public static void main(String[] args) {
		
            System.out.println("Skompilowano");
            Aplikacja aplikacja=new Aplikacja();
           Scanner sc=new Scanner(System.in);   
            Integer con=1;
            while(con!=0){
                     
            System.out.println("Menu: ");
            System.out.println("1 - dodanie pokoju");
            System.out.println("2 - modyfikacja pokoju");
            System.out.println("3 - wybranie pokoju do rezerwacji");
            System.out.println("4 - dokonanie rezerwacji"); 
            System.out.println("5 - wyświetlenie listy pokoi"); 
            System.out.println("6 - wyświetlenie listy rezerwacji"); 
            System.out.println("0 - opuszczenie programu.");     
            System.out.print("Wybor: ");   
            con=sc.nextInt();
            switch(con)
                    {
                case 1:
                    System.out.println("=================");
                    System.out.println("Dodawanie pokoju");
                    aplikacja.dodajPokoj();
                    break;
                case 2: 
                    System.out.println("=================");
                    System.out.println("Modyfikacja pokoju");
                    aplikacja.modyfikujPokoj();
                    break;
                case 3:
                    System.out.println("=================");
                    System.out.println("Wskazanie pokoju do rezerwacji");
                    aplikacja.wskazPokojDoRezerwacji();
                    break;
                case 4:
                    System.out.println("=================");
                    System.out.println("Dokonanie rezerwacji");
                    aplikacja.dokonajRezerwacji();
                    break; 
                case 5:
                    aplikacja.showList();
                    break;
                case 6:
                    aplikacja.showReservationList();
                    break;
            }         

        }
                 
	}
        public void showList(){
            listaPokoi.to_string();
        }
        public void showReservationList() {
		rezerwacja.showList();
	}

	public void wyslijPowiadomienieKlientowi() {
		System.out.println("Powiadomienie o zmianie dni rezerwacji zostało wysłane klientowi.");
	}

	public void dodajPokoj() {
            Integer nrPokoju = listaPokoi.dodajPustyPokoj();
            Scanner in = new Scanner(System.in);
            System.out.print("Podaj cene pokoju: ");
            Float cena = in.nextFloat();
            System.out.print("Podaj liczbe miejsc w pokoju: ");
            Integer liczbaMiejsc = in.nextInt();
            Boolean wyposazenie[] = new Boolean[6];
            System.out.println("Wyposażenie (true - istnieje, false - nie istnieje):");
            for(int i = 0; i < 5; i++) {
                System.out.print("Wyposazenie["+ i+"]= ");
                wyposazenie[i] = in.nextBoolean();
            }
            wyposazenie[5] = true;
            List<Integer> dniRezerwacji = new ArrayList<Integer>();
            System.out.print("Podaj, na ile dni chcesz dodac rezerwacje pokoju: ");
            Integer ileDni = in.nextInt();
            for(int i = 0; i < ileDni; i++) {
                System.out.print("Numer dnia rezerwacji pokoju: ");
                dniRezerwacji.add(in.nextInt());
            }
            listaPokoi.modyfikujAtrybutyPokoju(cena, liczbaMiejsc, wyposazenie, 
            dniRezerwacji,nrPokoju,nrPokoju,true);
           
	}

	public void modyfikujPokoj() {
            Scanner in = new Scanner(System.in);
            System.out.println("Wyszukiwanie pokoju do modyfikacji");
            System.out.print("Podaj cene pokoju: ");
            float cena = in.nextFloat();
            System.out.print("Podaj liczbe miejsc w pokoju: ");
            int liczbaMiejsc = in.nextInt();
            System.out.println("Podaj wyposazenie pokoju: ");
            Boolean wyposazenie[] = new Boolean[6];
            for(int i = 0; i < 5; i++) {
                System.out.print("Wyposazenie["+i+"]= ");
                wyposazenie[i] = in.nextBoolean();
            }
            wyposazenie[5] = true;
            List<Integer> dniRezerwacji = new ArrayList<Integer>();
            System.out.print("Na ile dni pokoj jest zarezerwowany: ");
            int ileDni = in.nextInt();
            for(int i = 0; i < ileDni; i++) {
                System.out.print("Numer dnia rezerwacji pokoju: ");
                dniRezerwacji.add(in.nextInt());
            }
            listaPokoi.uzyjFiltrowWyszukiwania(cena, liczbaMiejsc, wyposazenie, dniRezerwacji,true);
            System.out.print("Podaj numer pokoju: ");
            Integer nrPokoju = in.nextInt();
            System.out.print("Chcesz usunac, czy zmodyfikowac pokoj(false-usuniecie,true-modyfikacja): ");
            Boolean choice = in.nextBoolean();            
            if(choice == false)
            {
                listaPokoi.usunPokoj(nrPokoju);
            }
            else
            {   
                System.out.print("Podaj nowa cene pokoju: ");
                float cenaNew = in.nextFloat();
                System.out.print("Podaj nowa liczbe miejsc w pokoju: ");
                Integer liczbaMiejscNew = in.nextInt();
                Boolean wyposazenieNew[] = new Boolean[6];
                for(int i = 0; i < 5; i++) {
                        System.out.print("Podaj wyposazenie pokoju["+i+"] (true-istnieje,false-brak): ");
                        wyposazenieNew[i] = in.nextBoolean();
                }
                wyposazenieNew[5] = true;
                List<Integer> dniRezerwacjiNew = new ArrayList<Integer>();
                System.out.print("Podaj, na ile dni ma byc zarezerwowany pokoj: ");
                int ileDniNew = in.nextInt();
                for(int i = 0; i < ileDniNew; i++) {
                    System.out.print("dzien rezerwacji["+i+"]: ");
                    
                        dniRezerwacjiNew.add(in.nextInt());
                }
            System.out.print("Podaj nowy nr pokoju: ");
            Integer nrPokojuNew = in.nextInt();
            Boolean zmianaDni=listaPokoi.modyfikujAtrybutyPokoju(cenaNew, liczbaMiejscNew, wyposazenieNew, dniRezerwacjiNew,
            nrPokoju, nrPokojuNew, false);
            if(zmianaDni) wyslijPowiadomienieKlientowi();
        }
           
	}

	public void dokonajRezerwacji() {
            if(rezerwacja==null){
                throw new IllegalFormatCodePointException(0);
            }
            obliczWartoscRachunku();
            Boolean zaplacono = zaplacZaRezerwacje();
            if(zaplacono)
            {
                rezerwacja.aktualizujAtrybutyPokoi();
            }
	}

	public void obliczWartoscRachunku() {
	System.out.println("Obliczona wartość rachunku wynosi: "+rezerwacja.obliczWartoscRachunku()+".");
        
	}

	public Boolean potwierdzRezerwacje() {
            System.out.println("Rezerwacja została potwierdzona.");
           return true; 
	}

	public void usunPokoj() {
            System.out.print("Podaj numer pokoju do usuniecia: ");
            Scanner scanner =new Scanner(System.in);
            Integer number = scanner.nextInt();
            listaPokoi.usunPokoj(number);               
                
	}

	public void wskazPokojDoRezerwacji() {
	Scanner in = new Scanner(System.in);
        List<Integer> dniRezerwacji = new ArrayList<Integer>();
        System.out.print("Podaj, na ile dni chcesz zarezerwować pokój: ");
            int ileDni = in.nextInt();
            for(int i = 0; i < ileDni; i++) {
                System.out.print("Podaj dzien nr["+i+"]: ");
                    dniRezerwacji.add(in.nextInt());
            }
            System.out.print("Czy chcesz użyć filtrów wyszukiwania(true-tak,false-nie): ");
        Boolean filters = in.nextBoolean();
        if(filters)
        {
            System.out.print("Podaj cene pokoju: ");
            Float cena = in.nextFloat();
            System.out.print("Podaj liczbe miejsc w pokoju: ");
                Integer liczbaMiejsc = in.nextInt();
                Boolean wyposazenie[] = new Boolean[6];
                for(int i = 0; i < 5; i++) {
                    System.out.print("czy pokoj zawiera wyposazenie nr["+i+"](true-tak,false-nie): ");
                        wyposazenie[i] = in.nextBoolean();
                }
                wyposazenie[5] = true;                      
            System.out.print("Dostepne pokoje: ");
               listaPokoi.uzyjFiltrowWyszukiwania(cena, liczbaMiejsc, wyposazenie, dniRezerwacji,false);
        }else listaPokoi.to_string();
      
        System.out.print("Podaj numer pokoju, ktory chcesz zarezerwowac: ");
        int nrPokoju = in.nextInt();
        rezerwacja.dodajPokoj(dniRezerwacji, nrPokoju);
        
	}

	public Boolean zaplacZaRezerwacje() {
       
            System.out.println("Tutaj byłby wybór systemu: ");        
            System.out.println("Oplacenie rezerwacji przebiegło pomyślnie.");
            return true;
        
	}

}