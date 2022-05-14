package com.example.http;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStreamReader;
import java.net.HttpURLConnection;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.HashMap;


public class HttpConnection {
    public String getCityData(String cityName){ //Funkcja zwraca liczbę miast o podanej nazwie jako String
        String temp= getData("https://api.teleport.org/api/cities/?search="+cityName);
        String result= new String("");
        Integer length= temp.length();
        Integer i=length-2;
        if(length>5){
            while(temp.charAt(i)>='0'&& temp.charAt(i)<='9')i--;
            i++;
            while(temp.charAt(i)>='0'&& temp.charAt(i)<='9'){
                result=result+temp.charAt(i);
                i++;
            }
        }
        return result;  //Dla miasta Częstochowa zwraca 1
    }
    public String getContinentData(String continentShortcut) {  //Funkcja zwraca liczbę państw na danym kontynencie jako String
        String temp= getData("https://api.teleport.org/api/continents/geonames%3A"+continentShortcut+"/countries/");
        String result=new String("");
        Integer length= temp.length();
        Integer i=length-2;
        if(length>5){
            while(temp.charAt(i)>='0'&& temp.charAt(i)<='9')i--;
            i++;
            while(temp.charAt(i)>='0'&& temp.charAt(i)<='9'){
                result=result+temp.charAt(i);
                i++;
            }
        }
        return result;
    }
    public String getContinentUrbanAreasNumber(String continentShortcut){   //Funkcja zwraca liczbę okręgów przemysłowych na danym kontynencie jako String
        String temp= getData("https://api.teleport.org/api/continents/geonames%3A"+continentShortcut+"/urban_areas/");
        String result=new String("");
        Integer length= temp.length();
        Integer i=length-2;
        if(length>5){
            while(temp.charAt(i)>='0'&& temp.charAt(i)<='9')i--;
            i++;
            while(temp.charAt(i)>='0'&& temp.charAt(i)<='9'){
                result=result+temp.charAt(i);
                i++;
            }
        }
        return result;
    }
    public HashMap<String,String> getContinents(){  //Funkcja zwraca nazwy wszystkich kontynentów i ich skróty jako HashMap
        HashMap<String,String >map=new HashMap<>();
        String temp= getData("https://api.teleport.org/api/continents/");
        Integer length=temp.length();
        Integer i=0;
        String key=new String("");
        String value=new String("");
        while(i<length-12){
            if(temp.charAt(i)=='g'&&temp.charAt(i+1)=='e'&&temp.charAt(i+2)=='o'&&temp.charAt(i+3)=='n'&&temp.charAt(i+4)=='a'&&temp.charAt(i+5)=='m'&&temp.charAt(i+6)=='e'&&temp.charAt(i+7)=='s'){
                i=i+9;
                key=key+temp.charAt(i)+temp.charAt(i+1);
                i=i+13;
                while((temp.charAt(i)>='a'&& temp.charAt(i)<='z')||(temp.charAt(i)>='A'&& temp.charAt(i)<='Z')||temp.charAt(i)==32){
                    value=value+temp.charAt(i);
                    i++;
                }
                map.put(value,key);
                key=value="";
            }
            i++;
        }
        return map;
    }
    private String getData(String path){    //Funkcja łaczy się z serwisem internetowym
        HttpURLConnection con=null;
        try{
            URL url =new URL(path);
            con=(HttpURLConnection)url.openConnection();
            con.setRequestMethod("GET");
            BufferedReader br=new BufferedReader(new InputStreamReader(con.getInputStream()));
            StringBuilder sb=new StringBuilder();
            String line;
            while((line=br.readLine())!=null) {
                sb.append(line);
            }
            br.close();
            return sb.toString();

        } catch (MalformedURLException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }
        return null;
    }
}
