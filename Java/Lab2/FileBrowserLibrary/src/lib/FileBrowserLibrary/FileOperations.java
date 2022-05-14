package lib.FileBrowserLibrary;

import java.io.File;

public interface FileOperations {
    public Boolean checkIfFileExists(String path);
    public void readFromFile(String path);
}
