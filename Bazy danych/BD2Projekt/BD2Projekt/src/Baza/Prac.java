package Baza;

import java.awt.Color;
import java.awt.Dialog;
import java.awt.EventQueue;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.sql.ResultSet;
import java.sql.SQLException;

import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JDialog;
import javax.swing.JTextField;
import javax.swing.ScrollPaneConstants;
import javax.swing.border.LineBorder;
import javax.swing.JLabel;
import javax.swing.JScrollPane;
import javax.swing.JTextArea;

public class Prac{

	private JFrame frame;
	private JTextField textField;
	private PracownikHurtowni prac;
	private JTextField hurtowniaTextField;
	private JTextField textField_1;
	public Prac(PracownikHurtowni h) {
		prac=h;
	}

	public static void main(Prac temp) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					Prac window = temp;
					temp.initialize();
					window.frame.setVisible(true);
					JDialog dialog=new JDialog(window.frame, "Logowanie",Dialog.ModalityType.DOCUMENT_MODAL);
					dialog.setAlwaysOnTop(true);
					dialog.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
				
					dialog.setBounds(window.frame.getX()+10, window.frame.getY()+10,420, 200);
					
					dialog.getContentPane().setLayout(null);
					JLabel ll1=new JLabel("Login: ");
					JLabel ll2=new JLabel("Has³o: ");
					JTextField ttf1=new JTextField();
					JTextField ttf2=new JTextField();
					ll1.setBounds(30,20,140,30);
					ll2.setBounds(30,60,140,30);
					ttf1.setBounds(190,20,200,30);
					ttf2.setBounds(190,60,200,30);
					dialog.getContentPane().add(ll1);
					dialog.getContentPane().add(ll2);
					dialog.getContentPane().add(ttf1);
					dialog.getContentPane().add(ttf2);
					JButton b=new JButton("Zaloguj");
					b.setBounds(240,120,100,30);
					b.addActionListener(new ActionListener() {			
						public void actionPerformed(ActionEvent e) {
							window.prac.setUsername(ttf1.getText());
							window.prac.setPassword(ttf2.getText());
							if(window.prac.connect())
							dialog.dispose();						
						}
					});
					dialog.getContentPane().add(b);
					dialog.setVisible(true);
					
					
					
				} catch (Exception e) {
					e.printStackTrace();
				}
			}
		});		
		
	}
	/**
	 * Initialize the contents of the frame.
	 */
	private void initialize() {
		

		frame = new JFrame("Pracownik hurtowni");
		frame.setBounds(100, 100, 846, 481);
		frame.setLocationRelativeTo(null);
		
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		
		frame.addWindowListener(new WindowListener() {
			
			@Override
			public void windowOpened(WindowEvent e) {
			}
			@Override
			public void windowClosing(WindowEvent e) {
				prac.onClose();				
			}
			@Override
			public void windowClosed(WindowEvent e) {
			}
			@Override
			public void windowIconified(WindowEvent e) {
			}
			@Override
			public void windowDeiconified(WindowEvent e) {
			}
			@Override
			public void windowActivated(WindowEvent e) {	
			}
			@Override
			public void windowDeactivated(WindowEvent e) {
			}
		
		}		
				
				);
		
		JButton btnButton = new JButton("Zrealizuj zam\u00F3wienie");
		btnButton.setBounds(64, 109, 180, 29);
		frame.getContentPane().add(btnButton);
		
		JButton btnButton_1 = new JButton("Poka\u017C list\u0119 zam\u00F3wie\u0144");
		btnButton_1.setBounds(254, 110, 185, 26);
		frame.getContentPane().add(btnButton_1);
		
		JButton btnButton_2 = new JButton("Aktualizuj stan");
		btnButton_2.setBounds(167, 141, 197, 29);
		frame.getContentPane().add(btnButton_2);
		
		JButton btnButton_3 = new JButton("Poka\u017C ostatnie zmiany");
		btnButton_3.setBounds(10, 66, 166, 29);
		frame.getContentPane().add(btnButton_3);
		
		JButton btnButton_4 = new JButton("Wy\u015Bwietl dane plac\u00F3wki");
		btnButton_4.setBounds(197, 11, 212, 23);
		frame.getContentPane().add(btnButton_4);
		
		textField = new JTextField();
		textField.setBounds(101, 12, 86, 20);
		frame.getContentPane().add(textField);
		textField.setColumns(10);
		
		JLabel lblNewLabel = new JLabel("Nr placowki");
		lblNewLabel.setBounds(10, 15, 86, 14);
		frame.getContentPane().add(lblNewLabel);
		
		JTextArea textArea = new JTextArea();
		textArea.setBounds(10, 129, 620, 212);
		textArea.setEditable(false);
		textArea.setBorder(new LineBorder(Color.BLACK));
		JScrollPane scrollPane=new JScrollPane();
		
		scrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		scrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
		scrollPane.setBounds(10, 181, 810, 250);
		scrollPane.getViewport().setBackground(Color.WHITE);
		scrollPane.setViewportView(textArea);
		frame.getContentPane().add(scrollPane);
		
		JLabel lblNewLabel_1 = new JLabel("Wyniki");
		lblNewLabel_1.setBounds(10, 156, 46, 14);
		frame.getContentPane().add(lblNewLabel_1);
		
		JButton wyswietlMagazyn = new JButton("Wy\u015Bwietl stan magazynu");
		wyswietlMagazyn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String s=hurtowniaTextField.getText();
				if(!s.isEmpty()) {
					Integer x=Integer.parseInt(s) ;
					if(x>=0) {
						ResultSet rs= prac.wyswietlStanMagazynu(s);
						
							try {
								textArea.append("================\nStan magazynu hurtowni nr:"+s+"\n");
								while(rs.next())
					textArea.append("--------------\nNr wiersza: "+rs.getInt(1)+"\nId leku: "+rs.getInt(2) + "\nIlosc: " + rs.getInt(3) + "\nId magazynu: " + rs.getInt(4)+"\n");
					}
							 catch (SQLException e1) {
								
								e1.printStackTrace();
							}
						
						
						
						
					}else textArea.append("Nie podano prawid³owego numeru hurtowni!\n");
					
					
				}else textArea.append("Nie podano numeru hurtowni!\n");	
				
				
				
				
				
			}
		});
		wyswietlMagazyn.setBounds(186, 67, 223, 26);
		frame.getContentPane().add(wyswietlMagazyn);
		
		JLabel lblNewLabel_2 = new JLabel("Nr hurtowni");
		lblNewLabel_2.setBounds(10, 41, 86, 14);
		frame.getContentPane().add(lblNewLabel_2);
		
		hurtowniaTextField = new JTextField();
		hurtowniaTextField.setBounds(101, 38, 86, 20);
		frame.getContentPane().add(hurtowniaTextField);
		hurtowniaTextField.setColumns(10);
		
		JButton btnNewButton = new JButton("Wy\u015Bwietl dane hurtowni");
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String s=hurtowniaTextField.getText();
				if(!s.isEmpty()) {
					Integer x=Integer.parseInt(s) ;
					if(x>=0) {
						ResultSet rs=prac.wyswietlDaneHurtowni(s);
						if(rs!=null) {
							try {
								textArea.append("======================\n"+"Dane hurtowni:\n");
								while(rs.next())
									textArea.append("Id hurtowni "+rs.getInt(1)+"\nId placówki: "+rs.getInt(2) + "\nId magazynu: " + rs.getInt(3)+"\n");
							} catch (SQLException e1) {
								
								e1.printStackTrace();
							}
							
						}		
						
						
					}else textArea.append("Nie podano prawid³owego numeru hurtowni!\n");
					
					
				}else textArea.append("Nie podano numeru hurtowni!\n");
				
			}
		});
		btnNewButton.setBounds(197, 37, 212, 23);
		frame.getContentPane().add(btnNewButton);
		
		JButton btnNewButton_1 = new JButton("Wy\u015Bwietl dost\u0119pne plac\u00F3wki");
		btnNewButton_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ResultSet rs=prac.wyswietlDostepnePlacowki();
				if(rs!=null) {
					textArea.append("================\nDane wszystkich placówek:\n");					
						try {
							while(rs.next()) {
							textArea.append("Id placowki: "+rs.getInt(1)+", Nazwa: "+rs.getString(2)+"\n");
							}
						} catch (SQLException e1) {

							e1.printStackTrace();
						}					
					
				}else textArea.append("Brak dostêpnych placówek!\n");
				
				
				
			}
		});
		btnNewButton_1.setBounds(516, 11, 250, 44);
		frame.getContentPane().add(btnNewButton_1);
		
		JButton btnNewButton_2 = new JButton("Wy\u015Bwietl dost\u0119pne leki");
		btnNewButton_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ResultSet rs=prac.wyswietlDostepneLeki();
				if(rs!=null) {
					textArea.append("================\nDane wszystkich leków:\n");					
						try {
							while(rs.next()) {
							textArea.append("Id leku: "+rs.getInt(1)+", Nazwa: "+rs.getString(2)+"\n");
							}
						} catch (SQLException e1) {

							e1.printStackTrace();
						}					
					
				}else textArea.append("Brak dostêpnych leków!\n");					
				
			}
		});
		btnNewButton_2.setBounds(516, 55, 251, 44);
		frame.getContentPane().add(btnNewButton_2);
		
		textField_1 = new JTextField();
		textField_1.setBounds(561, 138, 86, 20);
		frame.getContentPane().add(textField_1);
		textField_1.setColumns(10);
		
		JLabel lblNewLabel_3 = new JLabel("Dane leku: ");
		lblNewLabel_3.setBounds(476, 141, 76, 14);
		frame.getContentPane().add(lblNewLabel_3);
		
		JButton btnNewButton_3 = new JButton("Wy\u015Bwietl");
		btnNewButton_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ResultSet rs=prac.wyswietlDaneLeku(textField_1.getText());
				if(rs!=null) {
					textArea.append("==============\nDane leku:\n");
					try {
						while(rs.next()) {
							textArea.append("Id leku: "+rs.getInt(1)+"\nNazwa leku: "+rs.getString(2)+"\nData produkcji: "+rs.getDate(3)+"\nData wa¿noœci: "+rs.getDate(4)+"\nSposób podania: "+rs.getString(5)+
									"\nPostaæ leku: "+rs.getString(6)+"\nWaga: "+rs.getFloat(7)+"\nCena: "+rs.getFloat(8)
							+"\nProducent: "+rs.getString(9)+"\nLiczba sztuk w opakowaniu: "+rs.getInt(10)+"\nZastosowanie: "+rs.getString(11)+"\n");
														
						}
					} catch (SQLException e1) {
						
						e1.printStackTrace();
					}				
					
				}				
				
			}
		});
		btnNewButton_3.setBounds(657, 138, 144, 19);
		frame.getContentPane().add(btnNewButton_3);

		

		btnButton.addActionListener(new ActionListener(){
			public void actionPerformed( ActionEvent e )  
            {  
				JDialog dialog=new JDialog(frame, "Akceptacja zamówienia",Dialog.ModalityType.DOCUMENT_MODAL);
				dialog.setAlwaysOnTop(true);
				dialog.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
			
				dialog.setBounds(frame.getX()+10, frame.getY()+10, frame.getWidth()-20, frame.getHeight()-20);
				
				dialog.getContentPane().setLayout(null);
				JButton button=new JButton("Akceptuj");
				button.setBounds(273,300,100,30);
				dialog.getContentPane().add(button);
				
				JTextField tf1=new JTextField();
				JLabel l1=new JLabel("Id zamówienia: ");
				l1.setBounds(30,20,200,30);
				tf1.setBounds(250,20,200,30);
				dialog.getContentPane().add(l1);
				dialog.getContentPane().add(tf1);
				button.addActionListener(new ActionListener() {			
					public void actionPerformed(ActionEvent e) {
						String s=tf1.getText();
						if(!s.isEmpty()) {
							Integer x=Integer.parseInt(s) ;
							if(x>=0) {
								prac.zrealizujZamowienie(s);
								dialog.dispose();
							}else textArea.append("Nie podano prawid³owego numeru zamówienia!\n");
							
							
						}else textArea.append("Nie podano numeru zamówienia!\n");	
					}
				});				
				
				dialog.setVisible(true);					
				
			}
		});
		btnButton_1.addActionListener(new ActionListener(){
		public void actionPerformed( ActionEvent e )  
        {  
			String str=hurtowniaTextField.getText();
			if(str.length()>0) {
				ResultSet rs=prac.pokazListeZamowien(str);
				if(rs!=null) {
					textArea.append("===============\nZamówienia hurtowni:\n");
					try{
						while(rs.next()){
							textArea.append("----------------------\nID zamówienia: "+rs.getInt(1) + "\nLiczba sztuk: " +rs.getInt(2)+"\nSposób odbioru zamówienia: "+rs.getString(3) + "\nTermin realizacji: "
									+ rs.getDate(4) + "\nID apteki: " + rs.getInt(5) + "\nID leku: " + rs.getInt(6) + "\nStatus: " + rs.getString(7)+"\n");
						}
					}
					catch(SQLException e1){
						textArea.append("SQL Exception occured while printing query output in pokazListeZamowien");
					}			
					
				}
			}
						
		}
		});
		btnButton_2.addActionListener(new ActionListener(){
			public void actionPerformed( ActionEvent e )  
            {  
				JDialog dialog=new JDialog(frame, "Edycja stanu magazynu",Dialog.ModalityType.DOCUMENT_MODAL);
				dialog.setAlwaysOnTop(true);
				dialog.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
			
				dialog.setBounds(frame.getX()+10, frame.getY()+10, frame.getWidth()-20, frame.getHeight()-20);
				dialog.getContentPane().setLayout(null);
				JButton button=new JButton("Edytuj");
				button.setBounds(273,300,100,30);
				dialog.getContentPane().add(button);
				
				JTextField tf1=new JTextField();
				JTextField tf2=new JTextField();
				JTextField tf3=new JTextField();
				JLabel l1=new JLabel("Id leku: ");
				JLabel l2=new JLabel("Ilosc: ");
				JLabel l3=new JLabel("Id magazynu: ");				
				l1.setBounds(30,20,200,30);
				l2.setBounds(30,60,200,30);
				l3.setBounds(30,100,200,30);
				tf1.setBounds(250,20,200,30);
				tf2.setBounds(250,60,200,30);
				tf3.setBounds(250,100,200,30);
				dialog.getContentPane().add(l1);
				dialog.getContentPane().add(l2);
				dialog.getContentPane().add(l3);
				dialog.getContentPane().add(tf1);
				dialog.getContentPane().add(tf2);
				dialog.getContentPane().add(tf3);
				button.addActionListener(new ActionListener() {			
					public void actionPerformed(ActionEvent e) {
						prac.edytujStanMagazynu(tf1.getText(),tf2.getText(),tf3.getText());
						dialog.dispose();
					}
				});
				dialog.setVisible(true);
			}
		});
		btnButton_3.addActionListener(new ActionListener(){
			public void actionPerformed( ActionEvent e )  
            {  
				String s=hurtowniaTextField.getText();
				if(!s.isEmpty()) {
					Integer x=Integer.parseInt(s) ;
					if(x>=0) {
						ResultSet r=prac.pokazListeZmian(s);
						if(r!=null) {
							try{
								textArea.append("================\nDane zamówieñ, które zosta³y zmodyfikowane przez jedn¹ z aptek:\n");
								while(r.next()){
									textArea.append("--------------\nId zamówienia: "+r.getInt(1) + "\nLiczba sztuk: " + r.getInt(2) + "\nSposób odbioru zamówienia: " + r.getString(3)+ "\nTermin realizacji: " 
									+ r.getDate(4) + "\nId apteki: " + r.getInt(5) + "\nId hurtowni: " + r.getInt(6) + "\nId leku: " + r.getInt(7) + "\nStatus: " + r.getString(8) + "\n");
								}
							}
							catch(SQLException e1){
								textArea.append("SQL Exception occured while printing query output in pokazListeZmian");
							}			
				
						}			
					}else textArea.append("Nie podano prawid³owego numeru placówki!\n");
					
					
				}else textArea.append("Nie podano numeru placówki!\n");	
				
			}
		});
		btnButton_4.addActionListener(new ActionListener(){
			public void actionPerformed( ActionEvent e )  
            {  
				String s=textField.getText();
				if(!s.isEmpty()) {
					Integer x=Integer.parseInt(s) ;
					if(x>=0) {
						ResultSet rs=prac.wyswietlDanePlacowki(s);
						if(rs!=null) {
							try {
								while(rs.next())
								textArea.append("======================\n"+"Dane placówki nr "+rs.getInt(1)+":\nNazwa: "+rs.getString(2) + "\nKraj: " + rs.getString(3) + "\nMiasto: " + rs.getString(4)+ "\nUlica: " 
										+ rs.getString(5) + "\nNr: " + rs.getInt(6) + "\nKod pocztowy: " + rs.getString(7) + "\nNr kontaktowy: " + rs.getInt(8) + "\nEmail: " + rs.getString(9)+"\n");
							} catch (SQLException e1) {
								System.out.print("SQL Exception occured while printing query output in pokazDanePlacowki");
								e1.printStackTrace();
							}
							
						}		
												
					}else textArea.append("Nie podano prawid³owego numeru placówki!\n");
										
				}else textArea.append("Nie podano numeru placówki!\n");				
			
			}
		});
	}
}
