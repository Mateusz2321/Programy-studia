package Baza;

import java.awt.EventQueue;

import javax.swing.JFrame;
import javax.swing.JButton;
import javax.swing.JDialog;

import java.awt.Color;
import java.awt.Dialog;
import java.awt.event.ActionListener;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.awt.event.ActionEvent;
import javax.swing.JTextField;

import javax.swing.ScrollPaneConstants;
import javax.swing.border.LineBorder;
import javax.swing.JTextArea;
import javax.swing.JLabel;
import javax.swing.JScrollPane;

public class Ap {

	private JFrame frame;
	private JTextField textField;
	private Aptekarz apt;
	private JTextField aptekaTextField;
	private JTextField textField_1;
	public Ap(Aptekarz a) {
		apt=a;
	}

	public static void main(Ap temp) {
		EventQueue.invokeLater(new Runnable() {
			public void run() {
				try {
					 Ap window = temp;
					 window.initialize();
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
							window.apt.setUsername(ttf1.getText());
							window.apt.setPassword(ttf2.getText());
							if(window.apt.connect()) {
								
								dialog.dispose();
							}
													
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

	private void initialize() {			
		
		frame = new JFrame("Aptekarz");
		frame.setBounds(100, 100, 738, 469);
		frame.setLocationRelativeTo(null);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.getContentPane().setLayout(null);
		frame.addWindowListener(new WindowListener() {
		
			@Override
			public void windowOpened(WindowEvent e) {
			}
			@Override
			public void windowClosing(WindowEvent e) {
				apt.onClose();				
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
		
		JButton btnNewButton = new JButton("Edytuj zam\u00F3wienie");
		btnNewButton.setBounds(293, 76, 149, 50);
		frame.getContentPane().add(btnNewButton);
		btnNewButton.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JDialog dialog=new JDialog(frame, "Edycja zamówienia",Dialog.ModalityType.DOCUMENT_MODAL);
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
				JTextField tf4=new JTextField();
				JTextField tf5=new JTextField();
				
				JLabel l1=new JLabel("Id zamówienia: ");
				JLabel l2=new JLabel("Liczba sztuk: ");
				JLabel l3=new JLabel("Sposób odbioru zamówienia: ");
				JLabel l4=new JLabel("Termin realizacji: ");
				JLabel l5=new JLabel("ID leku: ");
				
				l1.setBounds(30,20,200,30);
				l2.setBounds(30,60,200,30);
				l3.setBounds(30,100,200,30);
				l4.setBounds(30,140,200,30);
				l5.setBounds(30,180,200,30);
				tf1.setBounds(250,20,200,30);
				tf2.setBounds(250,60,200,30);
				tf3.setBounds(250,100,200,30);
				tf4.setBounds(250,140,200,30);
				tf5.setBounds(250,180,200,30);			
				dialog.getContentPane().add(l1);
				dialog.getContentPane().add(l2);
				dialog.getContentPane().add(l3);
				dialog.getContentPane().add(l4);
				dialog.getContentPane().add(l5);
				dialog.getContentPane().add(tf1);
				dialog.getContentPane().add(tf2);
				dialog.getContentPane().add(tf3);
				dialog.getContentPane().add(tf4);
				dialog.getContentPane().add(tf5);			
				button.addActionListener(new ActionListener() {			
					public void actionPerformed(ActionEvent e) {
						apt.edytujZamowienie(tf1.getText(),tf2.getText(),tf3.getText(),tf4.getText(),tf5.getText());
						dialog.dispose();						
					}
				});
				dialog.setVisible(true);
				
			}
		});	
		
		JButton btnNewButton_1 = new JButton("Zam\u00F3w leki");
		btnNewButton_1.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JDialog dialog=new JDialog(frame, "Zamawianie leków",Dialog.ModalityType.DOCUMENT_MODAL);
				dialog.setAlwaysOnTop(true);
				dialog.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
			
				dialog.setBounds(frame.getX()+10, frame.getY()+10, frame.getWidth()-20, frame.getHeight()-20);
				
				dialog.getContentPane().setLayout(null);
				JButton button=new JButton("Zamów");
				button.setBounds(273,300,100,30);
				dialog.getContentPane().add(button);
				
				JTextField tf1=new JTextField();
				JTextField tf2=new JTextField();
				JTextField tf3=new JTextField();
				JTextField tf4=new JTextField();
				JTextField tf5=new JTextField();
				JTextField tf6=new JTextField();
				JLabel l1=new JLabel("Liczba sztuk: ");
				JLabel l2=new JLabel("Sposób odbioru zamówienia: ");
				JLabel l3=new JLabel("Termin realizacji: ");
				JLabel l4=new JLabel("ID Apteki: ");
				JLabel l5=new JLabel("ID Hurtowni: ");
				JLabel l6=new JLabel("ID Leku: ");
				l1.setBounds(30,20,200,30);
				l2.setBounds(30,60,200,30);
				l3.setBounds(30,100,200,30);
				l4.setBounds(30,140,200,30);
				l5.setBounds(30,180,200,30);
				l6.setBounds(30,220,200,30);
				tf1.setBounds(250,20,200,30);
				tf2.setBounds(250,60,200,30);
				tf3.setBounds(250,100,200,30);
				tf4.setBounds(250,140,200,30);
				tf5.setBounds(250,180,200,30);
				tf6.setBounds(250,220,200,30);
				dialog.getContentPane().add(l1);
				dialog.getContentPane().add(l2);
				dialog.getContentPane().add(l3);
				dialog.getContentPane().add(l4);
				dialog.getContentPane().add(l5);
				dialog.getContentPane().add(l6);
				dialog.getContentPane().add(tf1);
				dialog.getContentPane().add(tf2);
				dialog.getContentPane().add(tf3);
				dialog.getContentPane().add(tf4);
				dialog.getContentPane().add(tf5);
				dialog.getContentPane().add(tf6);
				button.addActionListener(new ActionListener() {			
					public void actionPerformed(ActionEvent e) {
						apt.zlozZamowienie(tf1.getText(),tf2.getText(),tf3.getText(),tf4.getText(),tf5.getText(),tf6.getText());
						dialog.dispose();
						
					}
				});
				dialog.setVisible(true);
				
			}
		});
		btnNewButton_1.setBounds(10, 76, 149, 50);
		frame.getContentPane().add(btnNewButton_1);
		
		JButton btnNewButton_2 = new JButton("Aktualizuj stan");
		btnNewButton_2.setBounds(156, 76, 140, 50);
		frame.getContentPane().add(btnNewButton_2);
		btnNewButton_2.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				JDialog dialog=new JDialog(frame, "Aktualizacja stanu leków",Dialog.ModalityType.DOCUMENT_MODAL);
				dialog.setAlwaysOnTop(true);
				dialog.setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
			
				dialog.setBounds(frame.getX()+10, frame.getY()+10, frame.getWidth()-20, frame.getHeight()-20);
				dialog.getContentPane().setLayout(null);
				JButton button=new JButton("Aktualizuj");
				button.setBounds(273,300,100,30);
				dialog.getContentPane().add(button);
				JTextField tf1=new JTextField();
				JTextField tf2=new JTextField();
				JTextField tf3=new JTextField();
				JLabel l1=new JLabel("Id leku: ");
				JLabel l2=new JLabel("Iloœæ: ");
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
						apt.aktualizujLeki(tf1.getText(),tf2.getText(),tf3.getText());
						dialog.dispose();
						
					}
				});
				dialog.setVisible(true);
			}
		});
		textField = new JTextField();
		textField.setBounds(116, 11, 86, 20);
		frame.getContentPane().add(textField);
		textField.setColumns(10);
		JTextArea textArea = new JTextArea();
		textArea.setBounds(10, 105, 435, 187);
		textArea.setEditable(false);
		textArea.setBorder(new LineBorder(Color.BLACK));
		
		JButton btnNewButton_3 = new JButton("Wy\u015Bwietl dane plac\u00F3wki");
		btnNewButton_3.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String s=textField.getText();
				if(!s.isEmpty()) {
					Integer x=Integer.parseInt(s) ;
					if(x>=0) {
						ResultSet rs=apt.wyswietlDanePlacowki(s);
						if(rs!=null) {
							try {
								while(rs.next())
									textArea.append("======================\n"+"Dane placówki nr "+rs.getInt(1)+":\nNazwa: "+rs.getString(2) + "\nKraj: " + rs.getString(3) + "\nMiasto: " + rs.getString(4)+ "\nUlica: " 
											+ rs.getString(5) + "\nNr: " + rs.getInt(6) + "\nKod pocztowy: " + rs.getString(7) + "\nNr kontaktowy: " + rs.getInt(8) + "\nEmail: " + rs.getString(9)+"\n");
							} catch (SQLException e1) {
								
								e1.printStackTrace();
							}
							
						}								
						
					}else textArea.append("Nie podano prawid³owego numeru placówki!\n");					
					
				}else textArea.append("Nie podano numeru placówki!\n");				
				
			}
		});
		btnNewButton_3.setBounds(223, 11, 190, 21);
		frame.getContentPane().add(btnNewButton_3);		
		
		JScrollPane scrollPane=new JScrollPane();
		
		scrollPane.setVerticalScrollBarPolicy(ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS);
		scrollPane.setHorizontalScrollBarPolicy(ScrollPaneConstants.HORIZONTAL_SCROLLBAR_ALWAYS);
		scrollPane.setBounds(10, 168, 702, 262);
		scrollPane.getViewport().setBackground(Color.WHITE);
		scrollPane.setViewportView(textArea);
		frame.getContentPane().add(scrollPane);
		JLabel lblNewLabel = new JLabel("Nr plac\u00F3wki");
		lblNewLabel.setBounds(20, 11, 92, 20);
		frame.getContentPane().add(lblNewLabel);
		
		JLabel lblNewLabel_1 = new JLabel("Wyniki");
		lblNewLabel_1.setBounds(20, 143, 46, 14);
		frame.getContentPane().add(lblNewLabel_1);
		
		JButton pokazMagazyn = new JButton("Poka\u017C stan magazynu");
		pokazMagazyn.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String s=aptekaTextField.getText();
				if(!s.isEmpty()) {
					Integer x=Integer.parseInt(s) ;
					if(x>=0) {
				ResultSet rs=apt.pokazStanMagazynu(s);
				try {
					if(rs!=null) {
						
					textArea.append("======================\n"+"Stan magazynu apteki nr "+s+":\n");
					while(rs.next()) {
						textArea.append("ID_leku: "+rs.getInt(1) + "  Ilosc: " + rs.getInt(2) + "  ID_magazynu: " + rs.getInt(3)+"\n");
					}
					
					}
				} catch (SQLException e1) {
					
					e1.printStackTrace();
				}
				}else textArea.append("Nie podano prawid³owego numeru apteki!\n");					
					
				}else textArea.append("Nie podano numeru apteki!\n");
			}
		});
		pokazMagazyn.setBounds(76, 137, 211, 20);
		frame.getContentPane().add(pokazMagazyn);
		
		JButton pokazZamowienia = new JButton("Wyswietl zam\u00F3wienia apteki");
		pokazZamowienia.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String s=aptekaTextField.getText();
				if(!s.isEmpty()) {
					Integer x=Integer.parseInt(s) ;
					if(x>=0) {
				ResultSet rs=apt.wyswietlZamowienia(s);
				try {
					textArea.append("======================\nZamowienia apteki nr "+s+":\n"); 
					while(rs.next())
					textArea.append("----------------------\nID zamówienia: "+rs.getInt(1) + "\nLiczba sztuk: " +rs.getInt(2)+"\nSposób odbioru zamówienia: "+rs.getString(3) + "\nTermin realizacji: "
					+ rs.getDate(4) + "\nID hurtowni: " + rs.getInt(5) + "\nID leku: " + rs.getInt(6) + "\nStatus: " + rs.getString(7)+"\n");
				} catch (SQLException e1) {
					
					e1.printStackTrace();
				}
				}else textArea.append("Nie podano prawid³owego numeru apteki!\n");					
					
				}else textArea.append("Nie podano numeru apteki!\n");
				
			}
		});
		pokazZamowienia.setBounds(286, 137, 211, 20);
		frame.getContentPane().add(pokazZamowienia);
		
		JLabel lblNewLabel_2 = new JLabel("Nr apteki");
		lblNewLabel_2.setBounds(20, 48, 86, 14);
		frame.getContentPane().add(lblNewLabel_2);
		
		aptekaTextField = new JTextField();
		aptekaTextField.setBounds(116, 45, 86, 20);
		frame.getContentPane().add(aptekaTextField);
		aptekaTextField.setColumns(10);
		
		JButton btnNewButton_4 = new JButton("Wy\u015Bwietl lek");
		btnNewButton_4.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ResultSet rs=apt.wyswietlDaneLeku(textField_1.getText());
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
		btnNewButton_4.setBounds(545, 134, 153, 23);
		frame.getContentPane().add(btnNewButton_4);
		
		JLabel lblNewLabel_3 = new JLabel("Id leku");
		lblNewLabel_3.setBounds(545, 112, 69, 14);
		frame.getContentPane().add(lblNewLabel_3);
		
		textField_1 = new JTextField();
		textField_1.setBounds(629, 106, 69, 20);
		frame.getContentPane().add(textField_1);
		textField_1.setColumns(10);
		
		JButton btnNewButton_5 = new JButton("Wyswietl dane apteki");
		btnNewButton_5.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				String s=aptekaTextField.getText();
				if(!s.isEmpty()) {
					Integer x=Integer.parseInt(s) ;
					if(x>=0) {
						ResultSet rs=apt.wyswietlDaneApteki(s);
						if(rs!=null) {
							try {
								textArea.append("======================\n"+"Dane apteki:\n");
								while(rs.next())
									textArea.append("Id apteki "+rs.getInt(1)+"\nId placówki: "+rs.getInt(2) + "\nId magazynu: " + rs.getInt(3)+"\n");
							} catch (SQLException e1) {
								
								e1.printStackTrace();
							}
							
						}								
						
					}else textArea.append("Nie podano prawid³owego numeru apteki!\n");					
					
				}else textArea.append("Nie podano numeru apteki!\n");				
				
			}
		});
		btnNewButton_5.setBounds(223, 42, 190, 23);
		frame.getContentPane().add(btnNewButton_5);
		
		JButton btnNewButton_6 = new JButton("Wy\u015Bwietl wszystkie plac\u00F3wki");
		btnNewButton_6.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ResultSet rs=apt.wyswietlDostepnePlacowki();
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
		btnNewButton_6.setBounds(471, 11, 227, 51);
		frame.getContentPane().add(btnNewButton_6);
		
		JButton btnNewButton_7 = new JButton("Wy\u015Bwietl wszystkie leki");
		btnNewButton_7.addActionListener(new ActionListener() {
			public void actionPerformed(ActionEvent e) {
				ResultSet rs=apt.wyswietlDostepneLeki();
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
		btnNewButton_7.setBounds(471, 59, 227, 42);
		frame.getContentPane().add(btnNewButton_7);
	}
}
