module com.example.filebrowserapllication {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.web;
    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires validatorfx;
    requires org.kordamp.ikonli.javafx;
    requires org.kordamp.bootstrapfx.core;
    requires eu.hansolo.tilesfx;
    requires FileBrowserLibrary;
    requires java.desktop;
    opens com.example.filebrowserapllication to javafx.fxml;
    exports com.example.filebrowserapllication;
    exports com.example.communicationWithLibrary;
}