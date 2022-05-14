package lib.FileBrowserLibrary;

import javax.imageio.ImageIO;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;

public class ImageFile extends AFile{
    private BufferedImage image;
    public ImageFile(){
        image=null;
    }

    public BufferedImage getImage() {
        return image;
    }

    @Override
    public void readFromFile(String path) {
        if(!checkIfFileExists(path)) return;
        file=new File(path);
        try {
            image= ImageIO.read(file);
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
