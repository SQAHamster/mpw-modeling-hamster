package de.unistuttgart.hamster.examples;

import de.unistuttgart.hamster.main.SimpleHamsterGame;

public class Example03 extends SimpleHamsterGame {
    public static void main(final String[] args) {
        createInstance(Example03.class);
    }

    /**
     * Another hamster program, which tests the loading of another territory.
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
