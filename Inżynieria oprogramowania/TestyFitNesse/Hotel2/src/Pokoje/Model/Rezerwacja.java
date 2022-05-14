package Pokoje.Model;

import java.util.ArrayList;
import java.util.IllegalFormatCodePointException;
import java.util.Iterator;
import java.util.List;

public class Rezerwacja {

	private List<PokojDoRezerwacji> listaPokoiDoRezerwacji;
	private ListaPokoi listaPokoi;
        
        public List<PokojDoRezerwacji> getListaPokoiDoRezerwacji(){
            return listaPokoiDoRezerwacji;
        }
        
        
        
        public void showList(){
            for(PokojDoRezerwacji p : listaPokoiDoRezerwacji){
                System.out.println("Dane pokoju: ");
                System.out.println("Numer pokoju: "+p.getNrPokoju());
                System.out.println("Cena: "+p.getCena());                
                List<Integer> x=p.getDniRezerwacji();
                System.out.println("Dni rezerwacji: ");
                for(Integer i : x){
                     System.out.print(i+", ");
                }
                System.out.println("");
            }
           
        }

	public void dodajPokoj(List<Integer> dniRezerwacji, Integer nrPokoju) {
            if(dniRezerwacji==null){
                throw new IllegalFormatCodePointException(0);
            }
            
            Pokoj pokoj = listaPokoi.znajdzPokoj(nrPokoju);
            List<Integer> dniRezerwacjiPokoju = pokoj.getDniRezerwacji();
            Boolean different = true;
            for(int i = 0; i < dniRezerwacji.size(); i++)
            {
                for(int j = 0; j < dniRezerwacjiPokoju.size(); j++)
                {
                    if(dniRezerwacji.get(i) == dniRezerwacjiPokoju.get(j))
                        different = false;
                }
            }
            if(different)
            {
                float cena = pokoj.getCena();
                PokojDoRezerwacji pokojDoRezerwacji = new PokojDoRezerwacji(cena, dniRezerwacji, nrPokoju);
                listaPokoiDoRezerwacji.add(pokojDoRezerwacji);
            }
	}

	public Rezerwacja(ListaPokoi listaPokoi) {
		this.listaPokoi=listaPokoi;
                listaPokoiDoRezerwacji = new ArrayList<PokojDoRezerwacji>();
	}

	public Float obliczWartoscRachunku() {
            Float cena_wszystkich=0.0f;
            for(PokojDoRezerwacji pok : listaPokoiDoRezerwacji){
                cena_wszystkich+=pok.getCena();
                
            }
            return cena_wszystkich;
	}

	public void aktualizujAtrybutyPokoi() {
          if(listaPokoiDoRezerwacji!=null){
              Iterator<PokojDoRezerwacji> iterator=listaPokoiDoRezerwacji.iterator();
            while(iterator.hasNext()){
                PokojDoRezerwacji pokoj=iterator.next();
                pokoj.reserve();
                List<Integer> dniRezerwacji=pokoj.getDniRezerwacji();
                Integer pNumber= pokoj.getNrPokoju();
                Pokoj p=listaPokoi.znajdzPokoj(pNumber);
                p.dodajDniRezerwacji(dniRezerwacji);
                
                
            } 
          }
                             
	}

}