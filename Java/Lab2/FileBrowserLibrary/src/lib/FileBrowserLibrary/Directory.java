package lib.FileBrowserLibrary;

import java.util.ArrayList;
import java.util.List;

public class Directory {
    private String path;
    private TextFile textFile;
    private ImageFile imageFile;
    public Directory(String path){
        this.path=path;
    }
    public void readAllFiles(){
        String path1=path+"\\record.txt";
        textFile=new TextFile();
        textFile.readFromFile(path1);

       imageFile=new ImageFile();
        path1=path+"\\image.png";
        imageFile.readFromFile(path1);

    }
    public TextFile getTextFile(){
        return textFile;
    }
    public ImageFile getImageFile(){
        return imageFile;
    }



}
