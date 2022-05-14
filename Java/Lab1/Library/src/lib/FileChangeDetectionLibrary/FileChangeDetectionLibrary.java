package lib.FileChangeDetectionLibrary;

import javax.swing.*;
import java.io.*;
import java.math.BigInteger;
import java.nio.file.DirectoryStream;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.Paths;
import java.security.MessageDigest;
import java.security.NoSuchAlgorithmException;
import java.util.*;
import java.util.stream.Collectors;
import java.util.stream.IntStream;

public class FileChangeDetectionLibrary {
    private String tempPath1,tempPath2;
    private Boolean good=true;
    private List<String> list= new ArrayList<>();
    private List<String> md5List= new ArrayList<>();
    private List<String> readedList=new ArrayList<>();
    private List<String> readedMd5List=new ArrayList<>();
    private void copy(List<String> ls){
        list.clear();
        for(String s:ls){
            list.add(s);
        }
    }
    public String checkForUpdates(String path){
        good=true;
        list.clear();
        md5List.clear();
        readedList.clear();
        readedMd5List.clear();
        String res="";
        tempPath1=path;
        tempPath1=tempPath1+"\\Log";
        if(Files.exists(Paths.get(tempPath1))){     //Był folder
            tempPath1=tempPath1+"\\log.txt";
            if(Files.exists(Paths.get(tempPath1))){     //Był plik
                try {
                    copy(getFiles(path));
                } catch (IOException e) {
                    good=false;
                }
                if(good==true) {
                    for(String s1: list){

                        byte[] b=getMd5(s1);
                        String output = String.format("%032X", new BigInteger(1, b));
                        md5List.add(output);

                    }
                    readFromFile(tempPath1);
                    Map<String,String> m=IntStream.range(0,list.size()).boxed().collect(Collectors.toMap(
                         list::get,md5List::get));
                    Map<String,String> m1= IntStream.range(0,readedList.size()).boxed().collect(Collectors.toMap(
                            readedList::get,readedMd5List::get));
                    res="Wykryte zmiany:\n";
                    /*
                    System.out.println("Now");      //Testy
                    for(String s:m.keySet()){
                        System.out.println(s);
                        System.out.println(m.get(s));
                    }
                    System.out.println("Before");
                    for(String s:m1.keySet()){
                        System.out.println(s);
                        System.out.println(m1.get(s));
                    }
                    */
                    for(String key : m1.keySet()){
                        if(m.containsKey(key)){
                            if(!m.get(key).equals(m1.get(key))){

                               res=res+key+"-modyfikacja pliku\n";
                            }
                            m.remove(key);
                        }else{
                            res=res+key+"-usuniecie pliku\n";

                        }
                    }
                    for(String key : m.keySet()){
                        res=res+key+"-utworzenie pliku\n";

                    }
                    saveToFile(path);

                }
            }else{          //Nie było pliku

                    try {
                        copy(getFiles(path));
                    } catch (IOException e) {

                        good=false;
                    }
                    if(good==true){
                        for(String s1: list){

                            byte[] b=getMd5(s1);
                            String output = String.format("%032X", new BigInteger(1, b));
                            md5List.add(output);
                        }
                    }
                saveToFile(path);
                res="Dane plików zostały zapisane w lokalizacji \\Log\\log.txt\nPlik został stworzony pierwszy raz.\n";
            }
        }else{              //Nie było folderu
            try {
                Files.createDirectory(Paths.get(tempPath1));        //Stworzenie folderu
            }
            catch(Exception e1){
                good=false;
            }
            if(good==true){
                try {
                    copy(getFiles(path));
                } catch (IOException e) {
                    good=false;
                }
                if(good==true){
                    for(String s1: list){

                        byte[] b=getMd5(s1);
                        String output = String.format("%032X", new BigInteger(1, b));
                        md5List.add(output);

                    }
                saveToFile(path);
                    res="Dane plików zostały zapisane w lokalizacji \\Log\\log.txt\nPlik został stworzony pierwszy raz.\n";
                }

            }
        }
    return res;
    }

    private void readFromFile(String path){
        File file=new File(path);
        Scanner in= null;
        try {
            in = new Scanner(file);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
        Boolean isName=true;
        while(in.hasNextLine()){
            if(isName==true){
                readedList.add(in.nextLine().toString());

                isName=false;
            }else{
                readedMd5List.add(in.nextLine());
                isName=true;
            }
        }
    }

    private void saveToFile(String path){

        String path2=path+"\\Log\\log.txt";
        try {
            PrintWriter save= new PrintWriter(path2);
            for(int i=0;i<list.size();i++){
                save.println(list.get(i));
                save.println(md5List.get(i));
            }
            save.close();
        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
    private byte[] getMd5(String ph){
        MessageDigest md = null;
        try {
            md = MessageDigest.getInstance("MD5");
        } catch (NoSuchAlgorithmException e) {

            e.printStackTrace();
        }
        try {
            md.update(Files.readAllBytes(Paths.get(ph)));
        } catch (IOException e) {

            e.printStackTrace();
        }
        byte[] digest = md.digest();
        return digest;
    }

    private List<String> getFiles(String p) throws IOException {
        List<String> l=new LinkedList<>();

        try(DirectoryStream<Path> stream= Files.newDirectoryStream(Paths.get(p))){
            for(Path p1:stream){
                if(!Files.isDirectory(p1)){
                    l.add(p+"\\"+p1.getFileName().toString());
                }
            }
        }
        return l;
    }

    public String chooseFolder(){
        String s=new String();
        JFileChooser c=new JFileChooser();
        c.setFileSelectionMode(JFileChooser.DIRECTORIES_ONLY);
        while(true){
        if(c.showOpenDialog(null)==JFileChooser.APPROVE_OPTION){
            File f=c.getSelectedFile();
            if(f.exists()){
                s=f.getAbsolutePath();
                break;
            }
            else {
                int reply = JOptionPane.showConfirmDialog(null, "Nie wybrano istniejącego folderu! Czy chcesz ponownie wybrać folder?", "Błąd", JOptionPane.YES_NO_OPTION);
                if (reply == JOptionPane.NO_OPTION) {
                    s="";
                    return s;
                }
            }
        }else break;
        }
        return s;
    }
}
