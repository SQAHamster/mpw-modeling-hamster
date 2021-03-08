module de.unistuttgart.hamstersimulator {
    requires transitive de.unistuttgart.hamster;
    requires mpw.framework.utils;

    requires javafx.base;
    requires javafx.fxml;
    requires javafx.controls;

    opens de.unistuttgart.hamstersimulator.ui;
    opens fxml;
    opens css;
    opens images;
}