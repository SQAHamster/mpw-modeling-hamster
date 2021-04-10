package de.unistuttgart.hamster.examples;

import de.unistuttgart.hamster.facade.Hamster;
import de.unistuttgart.hamster.main.SimpleHamsterGame;

public class Example03 extends SimpleHamsterGame {
    public static void main(final String[] args) {
        createInstance(Example03.class);
    }

    Hamster paula;

    /**
     * Another hamster program. The idea is to create Paula close to Paula with
     * grain in her mouth. She drops it and Paule picks it up.
     */
    @Override
    protected void run() {
        displayInNewGameWindow();
        loadTerritoryFromResourceFile("de.unistuttgart.hamster.territories/example03.ter");
        startGame();

        turnRight();
        paule.move();
    }

    void turnRight() {
        paule.turnLeft();
        paule.turnLeft();
        paule.turnLeft();
    }
}
