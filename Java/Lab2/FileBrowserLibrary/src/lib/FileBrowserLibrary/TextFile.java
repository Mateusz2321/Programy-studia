package lib.FileBrowserLibrary;

import java.io.File;
import java.io.FileNotFoundException;
import java.util.Scanner;

public class TextFile extends AFile{
    private String name;
    private String surname;
    private String age;
    private String hobby;


    public String getName() {
        return this.name;
    }
    public String getSurname() {
        return this.surname;
    }
    public String getAge() {
        return this.age;
    }
    public String getHobby() {
        return this.hobby;
    }
    private String readLine(Scanner sc){
        if(sc.hasNextLine()){
            return sc.nextLine();
        }
        return "";
    }
    @Override
    public void readFromFile(String path) {
        if(!checkIfFileExists(path)) return;
        file=new File(path);
        try {
            Scanner sc= new Scanner(file);
            name=readLine(sc);
            surname=readLine(sc);
            age=readLine(sc);
            hobby=readLine(sc);

        } catch (FileNotFoundException e) {
            e.printStackTrace();
        }
    }
}
