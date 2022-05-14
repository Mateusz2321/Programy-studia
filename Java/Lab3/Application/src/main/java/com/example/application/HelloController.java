package com.example.application;

import com.example.format.ChoiceFormatTextChanging;
import com.example.http.HttpConnection;
import com.example.preferences.LanguagePreferences;
import javafx.collections.FXCollections;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.*;

import java.net.URL;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.ResourceBundle;

public class HelloController implements Initializable {
    private String lang=new String("");
    private HttpConnection con=new HttpConnection();
    private HashMap<String,String> response=new HashMap<>();
    private LanguagePreferences preferences=new LanguagePreferences();
    private ChoiceFormatTextChanging cf= new ChoiceFormatTextChanging();
    @FXML
    private Label l1;
    @FXML
    private Label l2;
    @FXML
    private Label l3;
    @FXML
    private Label l4;
    @FXML
    private Label l5;
    @FXML
    private Label l6;
    @FXML
    private Label l7;
    @FXML
    private Label l8;
    @FXML
    private Label l9;
    @FXML
    private Label l10;
    @FXML
    private ComboBox cb1;
    @FXML
    private CheckBox check;
    @FXML
    private TextField tf;
    @FXML
    private TextField tf2;
    @FXML
    private TextField tf3;
    @FXML
    private TextField tf4;
    @FXML
    private Button tf1;
    @FXML
    private Button b1;
    @FXML
    private Button b2;
    @FXML
    private Button bt1;
    @FXML
    private Button bt2;
    @FXML
    private Button bt3;
    @FXML
    private Button bt4;
    private String getLanguage(){
        if(check.isSelected()) return new String("english");
        else return new String("polish");
    }

    @FXML
    private void onChange(){
        lang=getLanguage();
        setLanguage(lang);
    }

    @FXML
    private void getUserPreferences(){

        String prefLanguage = preferences.getPreferences(getLanguage());
        if(prefLanguage==null) return;
        if(prefLanguage.isEmpty()) return;
        lang=prefLanguage;
        setLanguage(prefLanguage);
    }
    @FXML
    private void getSystemPreferences(){
        String prefLanguage = preferences.getSystemPreferences(getLanguage());
        if(prefLanguage==null) return;
        if(prefLanguage.isEmpty()) return;
        lang=prefLanguage;
        setLanguage(prefLanguage);
    }
    private void setLanguage(String language){
        if(language.equals("polish")){
            check.setSelected(false);
            l1.setText("Ile dużych obszarów miejskich znajduje się na tym kontynencie?");
            tf1.setText("Odpowiedz");
            l3.setText("Wybierz kontynent i odpowiedz");
            l5.setText("Wybór kontynentu");
            l7.setText("Jak dużo państw znajduje się na tym kontynencie?");
            b2.setText("Odpowiedz");
            l8.setText("Wybierz kontynent i odpowiedz");
            l2.setText("Wybór nazwy miasta");
            l4.setText("Jak dużo miast na świecie ma taką nazwę?");
            b1.setText("Odpowiedz");
            l6.setText("Wpisz nazwę miasta i odpowiedz");
            l9.setText("Wybierz język");
            check.setText("Angielski");
            l10.setText("Wybrany język : polski");
            bt1.setText("Pobierz preferencje użytkownika");
            bt2.setText("Pobierz preferencje systemowe");
            bt3.setText("Ustaw preferencje użytkownika");
            bt4.setText("Ustaw preferencje systemowe");


        }else{
            check.setSelected(true);
            l1.setText("How many big urban areas is on this continent?");
            tf1.setText("Answer");
            l3.setText("Choose continent and answer");
            l5.setText("Continent choosing");
            l7.setText("How many countries contains this continent ?");
            b2.setText("Answer");
            l8.setText("Choose continent and answer");
            l2.setText("City name choosing");
            l4.setText("How much cities has this name on the world?");
            b1.setText("Answer");
            l6.setText("Write city name and answer");
            l9.setText("Choose language");
            check.setText("English");
            l10.setText("Chosen language: english");
            bt1.setText("Get user preferences");
            bt2.setText("Get system preferences");
            bt3.setText("Set user preferences");
            bt4.setText("Set system preferences");

        }
    }



    @FXML
    private void setUserPreferences(){
        Boolean tmp=check.isSelected();
        if(tmp)
            preferences.setPreferences("english");
        else
            preferences.setPreferences("polish");
    }
    @FXML
    private void setSystemPreferences(){
        Boolean tmp=check.isSelected();
        if(tmp)
        preferences.setSystemPreferences("english");
        else
            preferences.setSystemPreferences("polish");
    }

    @FXML
    private void getContinentData(){
        String name=new String("");
        Object o=cb1.getValue();
        if(o==null) return;
        name=o.toString();
        if(name.isEmpty()) return;
        String value=new String("");
        value=tf4.getText();
        if(value.isEmpty()) return;
        String shortcut=response.get(name);
        String response= con.getContinentData(shortcut);
        if(response==null || response.isEmpty()) return;
        if(Integer.parseInt(value)==Integer.parseInt(response)){
            if(lang.equals("polish")){
                l8.setText("Dobra odpowiedź! Ten kontynent zawiera "+cf.getPolishContinentCountriesFormat(response));
            }
            else{
                l8.setText("Good answer! This continent contains "+ cf.getEnglishContinentCountriesFormat(response));
            }
        }else{
            if(lang.equals("polish")){
                l8.setText("Zła odpowiedź! Ten kontynent zawiera "+cf.getPolishContinentCountriesFormat(response));
            }
            else{
                l8.setText("Bad answer! This continent contains "+ cf.getEnglishContinentCountriesFormat(response));
            }
        }
    }
    @FXML
    private void getCityData(){
        String name=new String("");
        name=tf2.getText();
        if(name.isEmpty()) return;
        String value=new String("");
        value=tf3.getText();
        if(value.isEmpty()) return;
        String response= con.getCityData(name);
        if(response.isEmpty()) return;
        if(Integer.parseInt(value)==Integer.parseInt(response)){
            if(lang.equals("polish")){
                l6.setText("Dobra odpowiedź! Na świecie występuje "+cf.getCitiesFormat(response)+" o takiej nazwie");
            }
            else{
                l6.setText("Good answer! On the world there "+ cf.getEnglishCitiesFormat(response));
            }
        }else{
            if(lang.equals("polish")){
                l6.setText("Zła odpowiedź! Na świecie występuje "+cf.getCitiesFormat(response)+" o takiej nazwie");
            }
            else{
                l6.setText("Bad answer! On the world there "+ cf.getEnglishCitiesFormat(response));
            }
        }
    }
    @FXML
    private void getUrbanAreasNumber(){
        String name=new String("");
        Object o=cb1.getValue();
        if(o==null) return;
        name=o.toString();
        if(name.isEmpty()) return;
        String value=new String("");
        value=tf.getText();
        if(value.isEmpty()) return;
        String shortcut=response.get(name);
        String response= con.getContinentUrbanAreasNumber(shortcut);
        if(response==null || response.isEmpty()) return;
        if(Integer.parseInt(value)==Integer.parseInt(response)){
            if(lang.equals("polish")){
                l3.setText("Dobra odpowiedź! Ten kontynent zawiera "+cf.getPolishContinentAreasFormat(response));
            }
            else{
                l3.setText("Good answer! This continent contains "+ cf.getEnglishContinentAreasFormat(response));
            }
        }else{
            if(lang.equals("polish")){
                l3.setText("Zła odpowiedź! Ten kontynent zawiera "+cf.getPolishContinentAreasFormat(response));
            }
            else{
                l3.setText("Bad answer! This continent contains "+ cf.getEnglishContinentAreasFormat(response));
            }
        }
    }

    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        response=con.getContinents();
        ArrayList<String> str=new ArrayList<>(response.keySet());
        cb1.setItems(FXCollections.observableList(str));
        lang=preferences.getPreferences("english");
        setLanguage(lang);
    }
}