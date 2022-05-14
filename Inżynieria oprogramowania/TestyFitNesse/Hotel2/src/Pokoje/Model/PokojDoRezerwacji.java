package Pokoje.Model;

import java.util.List;

public class PokojDoRezerwacji {

	private Float cena;
	private List<Integer> dniRezerwacji;
	private Integer nrPokoju;
        private Boolean reserved;
        
        public PokojDoRezerwacji(Float cena, List<Integer> dniRezerwacji,Integer nrPokoju){
            this.cena=cena;
            this.dniRezerwacji=dniRezerwacji;
            this.nrPokoju=nrPokoju; 
            reserved=false;
        }
        public void reserve(){
            reserved=true;
        }
        public Boolean getReserve(){
            return reserved;
        }
        
	public List<Integer> getDniRezerwacji() {
		return this.dniRezerwacji;
	}

	public Integer getNrPokoju() {
		return this.nrPokoju;
	}
        public Float getCena(){
            return this.cena;
        }
        

}