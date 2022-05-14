package Pokoje.Model;

import Pokoje.Fabryka;
import java.util.ArrayList;
import java.util.IllegalFormatCodePointException;
import java.util.List;

public class ListaPokoi {

	private List<Pokoj> listaPokoi;
	private Integer nrPokoju=0;

	public void uzyjFiltrowWyszukiwania(Float cena, Integer liczbaMiejsc, Boolean wyposazenie[], List<Integer> dniRezerwacji,Boolean zarezerwowane) {
            for(int i = 0; i < listaPokoi.size(); i++)
        {
            
            Pokoj pokoj = listaPokoi.get(i);
            Float cenaI = pokoj.getCena();
            
            if(cenaI >= 0.0 && Float.compare(cenaI, cena)  == 0)
            {
                
                Integer liczbaMiejscI = pokoj.getLiczbaMiejsc();
                if(liczbaMiejscI >= 0 && liczbaMiejscI == liczbaMiejsc)
                {
                    Boolean [] wyposazenieI = pokoj.getWyposazenie();
                    if(wyposazenie[5] )
                    {
                        Boolean wyposazenieRowne = true;
                        for(int j = 0; j < 5; j++)
                        {
                            if(wyposazenieI[j] != wyposazenie[j])
                            {
                                wyposazenieRowne = false;
                                break; 
                            }
                               
                        }
                        if(wyposazenieRowne)
                        {
                            
                            if(zarezerwowane){
                                List<Integer> dniRezerwacjiI = pokoj.getDniRezerwacji();
                            if(dniRezerwacjiI.get(0) >= 0 && dniRezerwacjiI.equals(dniRezerwacji))
                            {
                                pokoj.to_string();
                            }
                                
                                
                                
                            }else {
                                 if(dniRezerwacji.get(0) >= 0 && (!pokoj.czyZarezerwowany(dniRezerwacji)))
                            {
                               
                                pokoj.to_string();
                            }
                            }
                           
                        }
                    }
                }
            }
        }
	}

	public void usunPokoj(Integer nrPokoju) {
            Pokoj pokoj = znajdzPokoj(nrPokoju);
            if(pokoj != null)
            {
                listaPokoi.remove(pokoj);
            }
	}

	public ListaPokoi() {
		listaPokoi=new ArrayList<Pokoj>();
                
	}

	public List<Pokoj> pobierzListePokoi() {
		return listaPokoi;
	}

	public Boolean modyfikujAtrybutyPokoju(Float cena, Integer liczbaMiejsc, Boolean[] wyposazenie, List<Integer> dniRezerwacji, Integer nrPokoju, Integer nowyNr, Boolean dodanieNowego) {
	if(wyposazenie==null){
            throw new IllegalFormatCodePointException(0);
        }            
        Pokoj pokoj = znajdzPokoj(nowyNr);
        Boolean change=false;
        if((pokoj == null &&dodanieNowego==false)||dodanieNowego==true)
        {
            pokoj = znajdzPokoj(nrPokoju);
            if(pokoj != null)
            {
                
                if(cena >= 0)
                {
                    pokoj.setCena(cena);
                }
                if(liczbaMiejsc > 0)
                {
                    pokoj.setLiczbaMiejsc(liczbaMiejsc);
                }
                if(wyposazenie[5] != false)
                {
                    pokoj.setWyposazenie(wyposazenie);
                }
                if(dniRezerwacji.get(0)>=0)
                {
                    pokoj.setDniRezerwacji(dniRezerwacji);
                    change=true;
                }
                if(nowyNr >= 0)
                {
                    pokoj.setNumerPokoju(nowyNr);
                }
            }
        }
            
            return change;
	}

	public Integer dodajPustyPokoj() {
                nrPokoju++;
                Boolean b[]={false,false,false,false,false,true};
                Fabryka fabryka=new Fabryka();
                Pokoj p=fabryka.stworzPokoj(100.0f,2,b,nrPokoju);
		listaPokoi.add(p);
                return p.getNumerPokoju();
	}

	public Pokoj znajdzPokoj(Integer nrPokoju) {
            for(Pokoj p : listaPokoi){
                if(p.getNumerPokoju()==nrPokoju){
                    return p;                          
                }                
            }
            return null;
            
	}

	public void to_string() {
            System.out.println("Lista pokoi:");
            for(Pokoj p : listaPokoi){
                System.out.println("------");
                System.out.println("Numer pokoju: "+p.getNumerPokoju());
                System.out.println("Cena pokoju: "+p.getCena());
                System.out.println("Liczba miejsc pokoju: "+p.getLiczbaMiejsc());
                System.out.print("Wyposazenie: ");
                Boolean w[]=p.getWyposazenie();
                for(int i=0;i<5;i++)
                System.out.print(w[i]+",");
                System.out.print("\n");               
                List<Integer> dniRezerwacji=p.getDniRezerwacji();
                if(dniRezerwacji!=null){
                   System.out.print("Dni rezerwacji: ");
                for(Integer d : dniRezerwacji)
                System.out.print(d.toString()+",");
                System.out.print("\n"); 
                }                                
            }       
            
	}

}