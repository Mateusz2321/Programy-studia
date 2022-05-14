package Baza;

import java.sql.CallableStatement;
import java.sql.Connection;
import java.sql.ResultSet;
import java.sql.SQLException;

public class WspolneFunkcje {
	protected CallableStatement s;
	protected Connection connection=null;
	
	public ResultSet wyswietlDanePlacowki(String id){		
		ResultSet rs;
		try {
			s = connection.prepareCall("{ ? = call ADMINISTRATOR_BAZA.WYSWIETL_DANE_PLACOWKI(?) }");
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
	
	public ResultSet wyswietlDostepnePlacowki() {
		ResultSet rs;
		try {
			s = connection.prepareCall("{ ? = call ADMINISTRATOR_BAZA.WYSWIETL_DOSTEPNE_PLACOWKI() }");
			s.registerOutParameter(1,java.sql.Types.REF_CURSOR);
			 s.execute();
			 rs=(ResultSet)s.getObject(1);

			return rs;
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
			
	}
	public ResultSet wyswietlDostepneLeki() {
		ResultSet rs;
		try {
			s = connection.prepareCall("{ ? = call ADMINISTRATOR_BAZA.WYSWIETL_DOSTEPNE_LEKI() }");
			s.registerOutParameter(1,java.sql.Types.REF_CURSOR);
			 s.execute();
			 rs=(ResultSet)s.getObject(1);

			return rs;
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}
			
	}
	public ResultSet wyswietlDaneLeku(String id_leku) {
		ResultSet rs;
		try {
			s = connection.prepareCall("{ ? = call ADMINISTRATOR_BAZA.WYSWIETL_LEK(?) }");
			s.setInt(2,Integer.parseInt(id_leku) );
			s.registerOutParameter(1,java.sql.Types.REF_CURSOR);
			 s.execute();
			 rs=(ResultSet)s.getObject(1);

			return rs;
		} catch (SQLException e) {
			e.printStackTrace();
			return null;
		}	
	}
	
}
