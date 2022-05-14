package Baza;

import java.sql.DriverManager;

import java.sql.ResultSet;
import java.sql.SQLException;

public class PracownikHurtowni extends WspolneFunkcje{
	private String dbURL = "jdbc:oracle:thin:@//localhost:1521/XEPDB2";
	private String username = "";
	private String password = "";
	private Prac pracownikInterface;
	
public void setUsername(String username) {
	this.username=username;
}
public void setPassword(String password) {
	this.password=password;
}
public Boolean connect(){

	try {
		connection= DriverManager.getConnection(dbURL, username, password);
		return true;
	} catch (SQLException e) {
		e.printStackTrace();
		return false;
	}
}

public PracownikHurtowni() {
		pracownikInterface=new Prac(this);
		Prac.main(pracownikInterface);
		
	}
void edytujStanMagazynu(String id_leku,String ilosc, String id_magazynu){
	try {
		s = connection.prepareCall("{call ADMINISTRATOR_BAZA.AKTUALIZUJ_STAN_MAGAZYNU_HURTOWNI(?,?,?) }");
		s.setInt(1, Integer.parseInt(id_magazynu));
		s.setInt(2, Integer.parseInt(id_leku));
		s.setInt(3,Integer.parseInt(ilosc));
		
		 s.execute();
		
	} catch (SQLException e) {
		e.printStackTrace();
		
	}
	
}
void zrealizujZamowienie(String id_zamowienia){
	try {
		s = connection.prepareCall("{call ADMINISTRATOR_BAZA.ZREALIZUJ_ZAMOWIENIE(?) }");
		s.setInt(1, Integer.parseInt(id_zamowienia));
		
		 s.execute();
		
	} catch (SQLException e) {
		e.printStackTrace();
		
	}
}

ResultSet pokazListeZmian(String id_hurtowni){
	ResultSet rs;
	try {
		s = connection.prepareCall("{ ? = call ADMINISTRATOR_BAZA.POKAZ_LISTE_ZMIAN(?) }");
		s.setInt(2,Integer.parseInt(id_hurtowni) );
		s.registerOutParameter(1,java.sql.Types.REF_CURSOR);
		 s.execute();
		 rs=(ResultSet)s.getObject(1);

		return rs;
	} catch (SQLException e) {
		e.printStackTrace();
		return null;
	}	

}
ResultSet pokazListeZamowien(String idHurtowni){ 
	ResultSet rs;
	try {
		s = connection.prepareCall("{ ? = call ADMINISTRATOR_BAZA.WYSWIETL_ZAMOWIENIA_HURTOWNI(?) }");
		s.setInt(2,Integer.parseInt(idHurtowni) );
		s.registerOutParameter(1,java.sql.Types.REF_CURSOR);
		 s.execute();
		 rs=(ResultSet)s.getObject(1);

		return rs;
	} catch (SQLException e) {
		e.printStackTrace();
		return null;
	}	

}

public ResultSet wyswietlDaneHurtowni(String id){
	ResultSet rs;
	try {
		s = connection.prepareCall("{ ? = call ADMINISTRATOR_BAZA.WYSWIETL_HURTOWNIE(?) }");
		s.setInt(2,Integer.parseInt(id) );
		s.registerOutParameter(1,java.sql.Types.REF_CURSOR);
		 s.execute();
		 rs=(ResultSet)s.getObject(1);

		return rs;
	} catch (SQLException e) {
		e.printStackTrace();
		return null;
	}	
}

ResultSet wyswietlStanMagazynu(String id){
	ResultSet rs;
	try {
		s = connection.prepareCall("{ ? = call ADMINISTRATOR_BAZA.WYSWIETL_STAN_MAGAZYNU_HURTOWNI(?) }");
		s.setInt(2,Integer.parseInt(id) );
		s.registerOutParameter(1,java.sql.Types.REF_CURSOR);
		 s.execute();
		 rs=(ResultSet)s.getObject(1);

		return rs;
	} catch (SQLException e) {
		e.printStackTrace();
		return null;
	}	
}

public void onClose() {

	if(connection!=null) {
				
		try {
			connection.close();
		} catch (SQLException e) {
			
			e.printStackTrace();
		}
	}	
}

}
