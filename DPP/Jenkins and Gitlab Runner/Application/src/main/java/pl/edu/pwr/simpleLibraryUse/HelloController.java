package pl.edu.pwr.simpleLibraryUse;
import pl.edu.pwr.sampleLibrary.Shortcuts;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.control.Label;
import javafx.scene.control.TextArea;

import java.net.URL;
import java.util.ResourceBundle;

public class HelloController implements Initializable {
    private Shortcuts s=new Shortcuts();
    private String text;
    @FXML
    private TextArea tArea;

    @FXML
    private void getTextFromFile(){
        text=s.getText();
        tArea.setText(text);
    }
    @FXML
    private void changeToShortcuts1(){
        text=tArea.getText();
        String word=new String("");
        String textAfter=new String("");
        Integer len=text.length();
        Integer i=0;
        Boolean big;
        String textTmp=new String("");
        String textTmp2;
        Boolean found;
        while(i<len){
            word="";
            found=false;
            while(text.charAt(i)>='a'&&text.charAt(i)<='z'|| text.charAt(i)>='A'&&text.charAt(i)<='Z'){
                word=word+text.charAt(i);
                i++;
                found=true;
            }
            if(found==true){
                if(word.charAt(0)>='A'&&word.charAt(0)<='Z') {
                    big = true;
                }
                else big=false;
                textTmp=s.changeWordToShortcut(word,1);
                if(big==true){
                    textTmp2=textTmp.substring(1,textTmp.length());
                    textTmp=textTmp.substring(0,1).toUpperCase()+textTmp2;
                }
                textAfter=textAfter+textTmp;
                i--;
            }else textAfter=textAfter+text.charAt(i);

            i++;
        }
        tArea.setText(textAfter);
    }
    @FXML
    private void changeToShortcuts2(){
        text=tArea.getText();
        String word=new String("");
        String textAfter=new String("");
        Integer len=text.length();
        Integer i=0;
        Boolean big;
        String textTmp=new String("");
        String textTmp2;
        Boolean found;
        while(i<len){
            word="";
            found=false;
            while(text.charAt(i)>='a'&&text.charAt(i)<='z'|| text.charAt(i)>='A'&&text.charAt(i)<='Z'){
                word=word+text.charAt(i);
                i++;
                found=true;
            }
            if(found==true){
                if(word.charAt(0)>='A'&&word.charAt(0)<='Z') {
                    big = true;
                }
                else big=false;
                textTmp=s.changeWordToShortcut(word,2);
                if(big==true){
                    textTmp2=textTmp.substring(1,textTmp.length());
                    textTmp=textTmp.substring(0,1).toUpperCase()+textTmp2;
                }
                textAfter=textAfter+textTmp;
                i--;
            }else textAfter=textAfter+text.charAt(i);

            i++;
        }
        tArea.setText(textAfter);
    }
    @FXML
    private void changeToWords(){
        String word=new String("");
        String textAfter=new String("");
        Integer len=text.length();
        int i=0;
        String textTmp=new String("");
        Boolean found;
        Boolean big;
        String textTmp2;
        while(i<len){
            word="";
            found=false;
            while(text.charAt(i)>='a'&&text.charAt(i)<='z'|| text.charAt(i)>='A'&&text.charAt(i)<='Z'|| text.charAt(i)=='.'){
                word=word+text.charAt(i);
                i++;
                found=true;
            }
            if(found==true){
                if(word.charAt(0)>='A'&&word.charAt(0)<='Z') {
                    big = true;
                }
                else big=false;
                textTmp=s.changeShortcutToWord(word);
                if(big==true){
                    textTmp2=textTmp.substring(1,textTmp.length());
                    textTmp=textTmp.substring(0,1).toUpperCase()+textTmp2;
                }
                textAfter=textAfter+textTmp;
                i--;
            }else textAfter=textAfter+text.charAt(i);
            i++;
        }
        tArea.setText(textAfter);
    }
    @Override
    public void initialize(URL url, ResourceBundle resourceBundle) {
        getTextFromFile();

    }
}