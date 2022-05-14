package Pokoje.Model;

import java.util.ArrayList;
import java.util.List;

public class Pokoj {

	private Float cena;
	private Integer liczbaMiejsc;
	private List<Integer> dniRezerwacji;
	private Integer nrPokoju;
	private Boolean wyposazenie[];
        
        public Boolean czyZarezerwowany(List<Integer> listaDniDoRezerwacji){
            for(Integer i : dniRezerwacji){
                for(Integer j : listaDniDoRezerwacji){
                    if(i==j) return true;
                }        
            }
            return false;            
        }
        public void dodajDniRezerwacji(List<Integer> lista){
            
            List<Integer> l=new ArrayList<>();
            for(int i=0;i<dniRezerwacji.size();i++){
                l.add(dniRezerwacji.get(i));
            }
             for(int i=0;i<lista.size();i++){
                l.add(lista.get(i));
            }            
            dniRezerwacji=l;
        }
        
	public Float getCena() {
		return this.cena;
	}

	public Integer getLiczbaMiejsc() {
            return this.liczbaMiejsc;
            
	}

	public void setLiczbaMiejsc(Integer liczbaMiejsc) {
		this.liczbaMiejsc = liczbaMiejsc;
	}

	public Boolean[] getWyposazenie() {
		   
            return wyposazenie;
	}

	public Pokoj(Float cena, int liczbaMiejsc, Boolean[] wyposazenie,Integer nrPokoju) {
            this.cena=cena;
            this.liczbaMiejsc=liczbaMiejsc;
            this.wyposazenie=wyposazenie;
            this.nrPokoju=nrPokoju;
            dniRezerwacji=new ArrayList<>();
	}

	public void setCena(Float cena) {
		this.cena = cena;
	}

	public List<Integer> getDniRezerwacji() {
		return this.dniRezerwacji;
	}

	public void setDniRezerwacji(List<Integer> dniRezerwacji) {
            if(dniRezerwacji.isEmpty()) return;
            if(dniRezerwacji.get(0)>=0)
		this.dniRezerwacji=dniRezerwacji;
	}

	public void setWyposazenie(Boolean[] wyposazenie) {
            if(wyposazenie[5]){
                this.wyposazenie=wyposazenie;          
                      
            }
            
	}

	public void setNumerPokoju(Integer nr) {
		this.nrPokoju=nr;
	}

	public Integer getNumerPokoju() {
		return nrPokoju;
	}
           
	public void to_string() {
        System.out.println("Dane pokoju");
        System.out.println("Numer pokoju: "+nrPokoju );   
        System.out.println("Cena: "+cena );           
        System.out.println("Liczba miejsc: "+liczbaMiejsc);   
        System.out.print("Wyposażenie: ");
                for(int i=0;i<5;i++)
                System.out.print(wyposazenie[i].toString()+",");
                System.out.print("\n");
                System.out.print("Dni rezerwacji: ");
                for(Integer d : dniRezerwacji)
                System.out.print(d.toString()+",");
                System.out.print("\n");       
	}
}