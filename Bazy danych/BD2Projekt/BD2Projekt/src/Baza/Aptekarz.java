package Baza;

import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;

public class Aptekarz extends WspolneFunkcje{
	
	private String dbURL = "jdbc:oracle:thin:@//localhost:1521/XEPDB2";
	private String username = "";
	private String password = "";	
	private Ap aptekarzInterface;	
	public void setUsername(String username) {
		this.username=username;
	}
	public void setPassword(String password) {
		this.password=password;
	}
	public Boolean connect() { 		
		try {
			connection= DriverManager.getConnection(dbURL, username, password);
			return true;
		} catch (SQLException e) {
			e.printStackTrace();
			return false;
		}
	}
	public Aptekarz() {
		aptekarzInterface=new Ap(this);
		Ap.main(aptekarzInterface);				
	}

public void zlozZamowienie(String liczba_sztuk, String sposob_odbioru_zamowienia,String termin_realizacji, String id_apteki, String id_hurtowni,String id_leku){
	try {
		s = connection.prepareCall("{call ADMINISTRATOR_BAZA.DODAJ_ZAMOWIENIE(?,?,?,?,?,?) }");
		s.setInt(1, Integer.parseInt(liczba_sztuk));
		s.setString(2, sposob_odbioru_zamowienia);
		s.setDate(3,java.sql.Date.valueOf(termin_realizacji));
		s.setInt(4,Integer.parseInt(id_apteki) );
		s.setInt(5,Integer.parseInt(id_hurtowni) );
		s.setInt(6,Integer.parseInt(id_leku) );
		
		 s.execute();
		
	} catch (SQLException e) {
		e.printStackTrace();
		
	}
	
}
public void aktualizujLeki(String id_leku,String ilosc, String id_magazynu){
	try {
		s = connection.prepareCall("{call ADMINISTRATOR_BAZA.AKTUALIZUJ_STAN_MAGAZYNU_APTEKI(?,?,?) }");
		s.setInt(1, Integer.parseInt(id_magazynu));
		s.setInt(2, Integer.parseInt(id_leku));
		s.setInt(3,Integer.parseInt(ilosc));
		
		 s.execute();
		
	} catch (SQLException e) {
		e.printStackTrace();
		
	}
	
}
public void edytujZamowienie(String id_zamowienia,String liczba_sztuk, String sposob_odbioru_zamowienia,String termin_realizacji,String id_leku){
	try {
		s = connection.prepareCall("{call ADMINISTRATOR_BAZA.EDYTUJ_ZAMOWIENIE(?,?,?,?,?) }");
		s.setInt(1, Integer.parseInt(id_zamowienia));
		s.setInt(2, Integer.parseInt(liczba_sztuk));
		s.setString(3, sposob_odbioru_zamowienia);
		s.setDate(4,java.sql.Date.valueOf(termin_realizacji));
		s.setInt(5,Integer.parseInt(id_leku) );		
		s.execute();
		
	} catch (SQLException e) {
		e.printStackTrace();
		
	}

}	

public ResultSet wyswietlDaneApteki(String id){
	ResultSet rs;
	try {
		s = connection.prepareCall("{ ? = call ADMINISTRATOR_BAZA.WYSWIETL_APTEKE(?) }");
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


ResultSet pokazStanMagazynu(String id){
	ResultSet rs;
	try {
		s = connection.prepareCall("{ ? = call ADMINISTRATOR_BAZA.WYSWIETL_STAN_MAGAZYNU_APTEKI(?) }");
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

ResultSet wyswietlZamowienia(String id){
	ResultSet rs;
	try {
		s = connection.prepareCall("{ ? = call ADMINISTRATOR_BAZA.WYSWIETL_ZAMOWIENIA_APTEKI(?) }");
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
			if(s!=null) {
				try {
					s.close();
				} catch (SQLException e) {
					e.printStackTrace();
				}				
				
			}
			try {
				connection.close();
			} catch (SQLException e) {
				e.printStackTrace();
			}
		}	
}	
}

	
