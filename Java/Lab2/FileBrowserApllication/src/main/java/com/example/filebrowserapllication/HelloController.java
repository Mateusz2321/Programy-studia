package com.example.filebrowserapllication;

import com.example.communicationWithLibrary.AuxiliaryClass;
import javafx.collections.FXCollections;
import javafx.collections.ObservableList;
import javafx.fxml.FXML;
import javafx.scene.control.Label;
import javafx.scene.control.ListView;
import javafx.scene.control.TextField;
import javafx.scene.image.Image;
import javafx.scene.image.ImageView;

import javafx.scene.image.PixelWriter;
import javafx.scene.image.WritableImage;
import lib.FileBrowserLibrary.Directory;
import lib.FileBrowserLibrary.Library;

import java.awt.image.BufferedImage;
import java.util.ArrayList;
import java.util.HashMap;

public class HelloController {
    private String path="";
    private AuxiliaryClass cl=new AuxiliaryClass();
    private Boolean status;
    @FXML
    private Label welcomeText;
    @FXML
    private TextField tf1;
    @FXML
    private TextField tf2;
    @FXML
    private TextField tf3;
    @FXML
    private TextField tf4;
    @FXML
    private ImageView img1;
    @FXML
    private ListView list1;
    @FXML
    protected void onHelloButtonClick() {
       if(path.isEmpty()){
           welcomeText.setText("First choose folder!");
           return;
       }
       cl.getDirectory(path+"\\"+list1.getSelectionModel().getSelectedItem());

       tf1.setText(cl.getName());
       tf2.setText(cl.getSurname());
       tf3.setText(cl.getAge());
       tf4.setText(cl.getHobby());
       status=cl.getStatus();
       if(status==true){
           welcomeText.setText("Dane pobrane z WeakHashMap");

       }else{
           welcomeText.setText("Dane wczytane z dysku.");
       }
       BufferedImage bf=cl.getImage();
       // Image im= SwingFXUtils.toFXImage(bf, null);
       //img1.setImage();
        WritableImage wr = null;
        if (bf != null) {
            wr = new WritableImage(bf.getWidth(), bf.getHeight());
            PixelWriter pw = wr.getPixelWriter();
            for (int x = 0; x < bf.getWidth(); x++) {
                for (int y = 0; y < bf.getHeight(); y++) {
                    pw.setArgb(x, y, bf.getRGB(x, y));
                }
            }
        }
        img1.setImage(wr);


    }
    @FXML
    protected void onChooseFolderButtonClick() {

        path=cl.getFolder();
        if(path.isEmpty()){
            welcomeText.setText("Error in choosing folder!");
        }else{
            welcomeText.setText("Folder chosen!");
            ArrayList<String> al=cl.getFoldersNames(path);
            ObservableList<String> ol= FXCollections.observableArrayList();;
            for(String str:al){
                ol.add(str);
            }
            list1.setItems(ol);
        }
    }

}