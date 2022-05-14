module com.example.application {
    requires javafx.controls;
    requires javafx.fxml;
    requires javafx.web;
    requires org.controlsfx.controls;
    requires com.dlsc.formsfx;
    requires validatorfx;
    requires org.kordamp.ikonli.javafx;
    requires org.kordamp.bootstrapfx.core;
    requires eu.hansolo.tilesfx;
    requires ShortcutsLibrary;


    opens pl.edu.pwr.simpleLibraryUse to javafx.fxml;
    exports pl.edu.pwr.simpleLibraryUse;
}