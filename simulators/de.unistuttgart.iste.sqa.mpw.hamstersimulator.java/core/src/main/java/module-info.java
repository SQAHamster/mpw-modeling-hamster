module de.unistuttgart.hamster {
    requires transitive mpw.framework.core;
    requires mpw.framework.utils;
    requires javafx.base;

    exports de.unistuttgart.hamster;
    exports de.unistuttgart.hamster.hamster;
    exports de.unistuttgart.hamster.viewmodel.impl;
}