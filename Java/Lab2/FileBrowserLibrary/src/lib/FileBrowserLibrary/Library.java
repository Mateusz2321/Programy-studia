package lib.FileBrowserLibrary;

import java.util.HashMap;
import java.util.Map;
import java.util.WeakHashMap;

public class Library {
    private WeakHashMap<String,Directory> hashMap=new WeakHashMap<>();
    private Boolean status;
    public Directory getDirectory(String path){
        Directory d=null;
        if(hashMap.containsKey(path)){
            d=hashMap.get(path);
            status=true;
            return d;
        }
        d=new Directory(path);
        d.readAllFiles();
        hashMap.put(path,d);
        status=false;
        return d;
    }
    public Boolean getStatus(){
        return this.status;
    }





}
