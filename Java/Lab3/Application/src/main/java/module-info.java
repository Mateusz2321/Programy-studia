module Application {
    requires Https;
    requires javafx.graphics;
    requires javafx.fxml;
    requires javafx.controls;
    requires java.prefs;
    exports com.example.application to javafx.graphics, javafx.fxml;
    exports com.example.preferences;
    opens com.example.application to  javafx.fxml;
}