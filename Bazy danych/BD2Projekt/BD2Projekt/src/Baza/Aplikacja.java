package Baza;
import java.awt.Color;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;

public class Aplikacja {

	
	public static void main(String[] args) {
		JFrame f= new JFrame("Wybór roli"); 
		f.setBounds(300, 300, 400, 200);
		f.setLocationRelativeTo(null);
		f.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		f.getContentPane().setLayout(null);
		f.setBackground(Color.CYAN);
		
		JLabel label=new JLabel("Wybierz rolê dla siebie");
		label.setBounds(110,30,140,20);
		f.add(label);
		JButton button= new JButton("Aptekarz");
		button.setBounds(24,60,149,80);
		button.addActionListener ( new ActionListener()  
        {  
            public void actionPerformed( ActionEvent e )  
            {  
            	new Aptekarz();
                f.setVisible(false);  
				f.dispose();
            }  
        });  
		f.add(button);
		
		JButton button2= new JButton("Pracownik Hurtowni");
		button2.setBounds(207,60,149,80);
		f.add(button2);
		button2.addActionListener(new ActionListener(){
			public void actionPerformed( ActionEvent e )  
            {  
				new PracownikHurtowni();
                f.setVisible(false); 
                f.dispose();
            } 
		});	
		
		f.setVisible(true); 
	}

	
}
