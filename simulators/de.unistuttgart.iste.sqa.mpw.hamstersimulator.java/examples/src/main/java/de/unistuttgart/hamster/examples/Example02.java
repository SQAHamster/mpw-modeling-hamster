package de.unistuttgart.hamster.examples;

import de.unistuttgart.hamster.main.SimpleHamsterGame;
import de.unistuttgart.hamster.facade.Hamster;

public class Example02 extends SimpleHamsterGame {
    public static void main(final String[] args) {
        createInstance(Example02.class);
    }

    Hamster paula;

    /**
     * Another hamster program. The idea is to create Paula close to Paula with
     * grain in her mouth. She drops it and Paule picks it up.
     */
    @Override
    protected void run() {
        displayInNewGameWindow();

        paula = new Hamster(game.getTerritory(), paule.getLocation(), paule.getDirection(), 1);
        paula.move();
        paula.putGrain();
        paula.move();

        paule.move();
        paule.pickGrain();
        paule.turnLeft();
        paule.turnLeft();
        paule.move();
        paule.putGrain();
    }
}
