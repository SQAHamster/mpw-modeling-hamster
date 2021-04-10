package de.unistuttgart.hamster.view;

import de.unistuttgart.iste.sqa.mpw.framework.exceptions.CommandConstraintException;
import de.unistuttgart.iste.sqa.mpw.framework.datatypes.Direction;
import org.junit.jupiter.api.Test;

import java.io.IOException;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

/**
 * Tests on the view-model layer, which are using the {@link HamsterViewModelStringifier} to create
 * string based representations.
 */
public class HamsterViewModelTest extends HamsterViewTestBase {

    @Test
    public void testInit() throws IOException {
        withTerritory("example01.ter");
        assertTerritory(
                "|####|####|####|####|####|\n" +
                "|####|>   |    | 2* |####|\n" +
                "|####|####|####|####|####|\n");
        assertEquals(true, paule.mouthEmpty());
        assertEquals(true, paule.frontIsClear());
        assertEquals(false, paule.grainAvailable());
        assertEquals(Direction.EAST, paule.getDirection());
        assertEquals(1, paule.getLocation().getRow());
        assertEquals(1, paule.getLocation().getColumn());
    }

    @Test
    public void testMove() throws IOException {
        withTerritory("example01.ter");
        paule.move();
        assertTerritory(
                "|####|####|####|####|####|\n" +
                "|####|    |>   | 2* |####|\n" +
                "|####|####|####|####|####|\n");
        assertEquals(true, paule.mouthEmpty());
        assertEquals(true, paule.frontIsClear());
        assertEquals(false, paule.grainAvailable());
        assertEquals(Direction.EAST, paule.getDirection());
        assertEquals(1, paule.getLocation().getRow());
        assertEquals(2, paule.getLocation().getColumn());
    }

    @Test
    public void testPickGrain() throws IOException {
        withTerritory("example01.ter");
        paule.move();
        paule.move();
        paule.pickGrain();
        assertTerritory(
                "|####|####|####|####|####|\n" +
                "|####|    |    | 1*>|####|\n" +
                "|####|####|####|####|####|\n");
        assertEquals(false, paule.mouthEmpty());
        assertEquals(false, paule.frontIsClear());
        assertEquals(true, paule.grainAvailable());
        assertEquals(Direction.EAST, paule.getDirection());
        assertEquals(1, paule.getLocation().getRow());
        assertEquals(3, paule.getLocation().getColumn());
    }

    @Test
    public void testPickGrainAndPutGrain() throws IOException {
        withTerritory("example01.ter");
        paule.move();
        paule.move();
        paule.pickGrain();
        paule.putGrain();
        assertTerritory(
                "|####|####|####|####|####|\n" +
                "|####|    |    | 2*>|####|\n" +
                "|####|####|####|####|####|\n");
        assertEquals(true, paule.mouthEmpty());
        assertEquals(false, paule.frontIsClear());
        assertEquals(true, paule.grainAvailable());
        assertEquals(Direction.EAST, paule.getDirection());
        assertEquals(1, paule.getLocation().getRow());
        assertEquals(3, paule.getLocation().getColumn());
    }

    @Test
    public void testMoveAndRotateAndMove() throws IOException {
        withTerritory("example01.ter");
        paule.move();
        paule.turnLeft();
        paule.turnLeft();
        paule.move();
        assertTerritory(
                "|####|####|####|####|####|\n" +
                "|####|<   |    | 2* |####|\n" +
                "|####|####|####|####|####|\n");
        assertEquals(true, paule.mouthEmpty());
        assertEquals(false, paule.frontIsClear());
        assertEquals(false, paule.grainAvailable());
        assertEquals(Direction.WEST, paule.getDirection());
        assertEquals(1, paule.getLocation().getRow());
        assertEquals(1, paule.getLocation().getColumn());
    }

    @Test
    public void testInitializeFurtherTerritory() throws IOException {
        withTerritory("example01.ter");
        initializeOtherTerritory("example03.ter");
        assertTerritory(
                "|####|####|####|\n" +
                "|####|>   |####|\n" +
                "|####|    |####|\n" +
                "|####| 2* |####|\n" +
                "|####|####|####|\n");
        initializeOtherTerritory("example01.ter");
        assertTerritory(
                "|####|####|####|####|####|\n" +
                "|####|>   |    | 2* |####|\n" +
                "|####|####|####|####|####|\n");
    }

    @Test
    public void testMoveAgainstWall() throws IOException {
        withTerritory("example01.ter");
        paule.move();
        paule.turnLeft();

        assertThrows(CommandConstraintException.class, () -> {
            paule.move();
        });
    }

    @Test
    public void testLog() throws IOException {
        withTerritory("example01.ter");
        paule.move();
        paule.move();
        paule.pickGrain();
        paule.putGrain();
        paule.turnLeft();
        paule.write("Hello");
        assertLog(
                "Move\n" +
                "Move\n" +
                "Pick Grain\n" +
                "Put Grain\n" +
                "Turn Left\n" +
                "Hello\n");
    }


    /*
     * [button] means: button is enabled
     * /button/ means: button is disabled
     */
    @Test
    public void testButtonsForModes() throws IOException {
        withTerritory("example01.ter");
        assertButtons("/play/ [pause] /undo/ /redo/");
        paule.move();
        paule.turnLeft();
        assertButtons("/play/ [pause] /undo/ /redo/");
        clickPause();
        assertButtons("[play] /pause/ [undo] /redo/");
        clickUndo();
        assertButtons("[play] /pause/ [undo] [redo]");
        clickUndo();
        assertButtons("[play] /pause/ /undo/ [redo]");
        clickRedo();
        assertButtons("[play] /pause/ [undo] [redo]");
        clickPlay();
        assertButtons("/play/ [pause] /undo/ /redo/");
        clickPause();
        assertButtons("[play] /pause/ [undo] /redo/");
        assertTerritory(
                "|####|####|####|####|####|\n" +
                "|####|    |^   | 2* |####|\n" +
                "|####|####|####|####|####|\n");
    }

}