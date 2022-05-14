package lib.FileBrowserLibrary;

import java.io.File;
import java.nio.file.Files;
import java.nio.file.Paths;

public abstract class AFile implements FileOperations{
    protected File file;
    @Override
    public Boolean checkIfFileExists(String path) {
        if(Files.exists(Paths.get(path))) return true;
        else return false;
    }
}
