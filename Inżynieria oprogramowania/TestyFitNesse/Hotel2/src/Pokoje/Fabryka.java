package Pokoje;

import Pokoje.Model.Pokoj;

public class Fabryka {

	public Fabryka() {
		
	}
        public Pokoj stworzPokoj(Float cena, int liczbaMiejsc, Boolean[] wyposazenie,Integer nrPokoju){
            return new Pokoj(cena,liczbaMiejsc,wyposazenie,nrPokoju);
            
        }

}