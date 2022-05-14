package pl.edu.pwr.sampleLibrary;

import java.io.*;
import java.util.HashMap;

public class Shortcuts {
    private String text;
    private File file;
    private HashMap<String, String> shortcuts= new HashMap<>();
    public Shortcuts(){
        readFromFile();
        readShortcutsDataFromFile();
    }
    public String getText(){
        return text;
    }
    public void readShortcutsDataFromFile(){
        shortcuts.clear();
        file=new File("C:\\MUrbanczyk_Maven\\Data.csv");
        BufferedReader br= null;
        try {
            br = new BufferedReader(new FileReader(file));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        String temp;
        String temp2;
        String temp3;
        int i;
        int len;
        try {
            while(true){
                if (((temp=br.readLine())!=null)){
                    i=0;
                    len=temp.length();
                    while(temp.charAt(i)!=';') i++;
                    temp2=temp.substring(0,i);
                    temp3=temp.substring(i+1, len);
                    shortcuts.put(temp2,temp3);
                }
                else break;
            }
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
    public void readFromFile() {
        text="";
        file=new File("C:\\MUrbanczyk_Maven\\Text.txt");
        BufferedReader br= null;
        try {
            br = new BufferedReader(new FileReader(file));
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        String temp=new String("");
        try {
            while(true){
                if (((temp=br.readLine())!=null))
                    text=text+temp+"\n";
                else break;
            }
            br.close();
        } catch (IOException e) {
            e.printStackTrace();
        }
    }

    public String changeShortcutToWord(String shortcut){
        String t=shortcut.toLowerCase();
        for(String k:shortcuts.keySet()){
            if(k.equals(t)){
                return shortcuts.get(k);
            }
        }
        return shortcut;
    }
    public String changeWordToShortcut(String word,int mode){
        if(mode==1){
            String t=word.toLowerCase();
            for(String k:shortcuts.keySet()){
                if(shortcuts.get(k).equals(t)){
                    return k;
                }
            }
            return word;
        }else{
            String tmp;
            String t=word.toLowerCase();
            Boolean equals;
            String k_temp;
            for(String k:shortcuts.keySet()){
                k_temp=k;
                tmp=shortcuts.get(k);
                if(tmp.length()>word.length())continue;
                equals=true;
                for(int i=0;i<tmp.length();i++){
                    if(tmp.charAt(i)!=word.charAt(i)) {
                        equals=false;
                        break;
                    }
                }
                if(equals==true) {
                    if(word.length()>tmp.length()) {
                        if(k_temp.charAt(k_temp.length()-1)=='.')k_temp= k_temp.substring(0,k_temp.length()-1);
                        k_temp=k_temp+"-";
                        for(int i=tmp.length();i<word.length();i++){
                            k_temp=k_temp+word.charAt(i);
                        }
                    }
                    return k_temp;
                }
            }
            return word;
        }
    }

}