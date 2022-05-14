package app.fileChangeDetectionApplication;

import lib.FileChangeDetectionLibrary.FileChangeDetectionLibrary;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class FileChangeDetectionApplication {
    private JButton chooseFolderButton;

    private JPanel panel1;
    private JTextArea textArea1;
    private JButton checkUpdateButton;
    private JButton button1;
    private FileChangeDetectionLibrary lib=new FileChangeDetectionLibrary();
    private String pathToFile=new String("");


    public FileChangeDetectionApplication() {
        textArea1.setEditable(false);

        chooseFolderButton.setBounds(50,30,450,30);
        checkUpdateButton.setBounds(50,70,450,30);
        button1.setBounds(520,70,100,30);
        chooseFolderButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                pathToFile=lib.chooseFolder();
                if(pathToFile.length()>0){
                    textArea1.append("----------\n");
                    textArea1.append("Wybrany folder: "+pathToFile+"\n");
                }else{
                    textArea1.append("----------\n");
                    textArea1.append("Wybór folderu zakończył się niepowodzeniem.\n");
                }

            }
        });
        checkUpdateButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                if(pathToFile.length()>0){
                    textArea1.append("----------\n");
                    textArea1.append(lib.checkForUpdates(pathToFile));
                }else textArea1.append("----------\nNie wybrano folderu! Wybierz najpierw folder!\n");
            }
        });
        textArea1.setBounds(10,110,610,390);
        button1.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                textArea1.setText("");
            }
        });
    }

    public static void main(String[] args) {
        JFrame frame=new JFrame("Lab1-FileChangeDetectionApplication");
        Dimension d=new Dimension();
        d.setSize(650,550);
        frame.setPreferredSize(d);
        frame.setContentPane(new FileChangeDetectionApplication().panel1);
        frame.getContentPane().setLayout(null);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();
        frame.setVisible(true);
    }
}
