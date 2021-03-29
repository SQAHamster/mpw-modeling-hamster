package de.unistuttgart.hamster.examples;

import de.unistuttgart.hamster.main.SimpleHamsterGame;

public class Example01 extends SimpleHamsterGame {
    public static void main(final String[] args) {
        createInstance(Example01.class);
    }

    /**
     * How often Paule should repeat its behaviour.
     */
    private static final int SCENARIO_REPETITION_COUNT = 20;

    @Override
    protected void run() {
        displayInNewGameWindow();
        for (int i = 0; i < SCENARIO_REPETITION_COUNT; i++) {
            paule.putBreadcrumb();
            paule.move();
            paule.putBreadcrumb();
            paule.move();
            paule.pickGrain();
            paule.pickGrain();
            paule.putGrain();
            paule.putGrain();
            paule.turnLeft();
            paule.turnLeft();
            paule.move();
            paule.pickBreadcrumb();
            paule.move();
            paule.pickBreadcrumb();
            paule.turnLeft();
            paule.turnLeft();
        }
    }

}
