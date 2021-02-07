package de.unistuttgart.hamstersimulator.examples;

class Example01 extends SimpleHamsterGame {

    /**
     * How often Paule should repeat its behaviour.
     */
    private static final int SCENARIO_REPETITION_COUNT = 20;

    @Override
    protected void run() {
        displayInNewGameWindow();
        for (int i = 0; i < SCENARIO_REPETITION_COUNT; i++) {
            paule.write("Hallo!");
            paule.move();
            paule.move();
            paule.pickGrain();
            paule.pickGrain();
            paule.putGrain();
            paule.putGrain();
            paule.turnLeft();
            paule.turnLeft();
            paule.move();
            paule.move();
            paule.turnLeft();
            paule.turnLeft();
        }
    }

}
