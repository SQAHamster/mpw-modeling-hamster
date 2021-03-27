package de.unistuttgart.hamster;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertFalse;
import static org.junit.jupiter.api.Assertions.assertTrue;
import static org.junit.jupiter.api.Assertions.assertThrows;

import de.unistuttgart.iste.sqa.mpw.framework.exceptions.CommandConstraintException;
import de.unistuttgart.hamster.hamster.*;
import de.unistuttgart.hamster.facade.*;
import de.unistuttgart.iste.sqa.mpw.framework.datatypes.Direction;
import de.unistuttgart.iste.sqa.mpw.framework.datatypes.Location;
import de.unistuttgart.iste.sqa.mpw.framework.mpw.LogEntry;
import de.unistuttgart.iste.sqa.mpw.framework.mpw.Tile;
import de.unistuttgart.hamster.util.GameStringifier;
import org.junit.jupiter.api.Test;

import java.util.Collection;
import java.util.stream.Collectors;

/**
 * Tests for game commands on the facade layer, which are using the {@link GameStringifier} to create
 * simple string based representations.
 */
public class HamsterCommandsTest {
	private HamsterGame game;
	private Hamster sut;

	//<editor-fold desc="Feature: move">
	@Test
	public void givenHamsterEast_whenMove_thenMovedToRight() {
		withTerritory(
				  "  #;"
				+ "> #;"
				+ "  #;");

		move();

		assertTerritory(
				  "  #;"
				+ " >#;"
				+ "  #;");
	}

	@Test
	public void givenHamsterNorth_whenMove_thenMovedToNorth() {
		withTerritory(
				  "  #;"
				+ "^ #;"
				+ "  #;");

		move();

		assertTerritory(
				  "^ #;"
				+ "  #;"
				+ "  #;");
	}

	@Test
	public void givenHamsterSouth_whenMove_thenMovedToSouth() {
		withTerritory(
				  "  #;"
				+ "v #;"
				+ "  #;");

		move();

		assertTerritory(
				  "  #;"
				+ "  #;"
				+ "v #;");
	}

	@Test
	public void givenHamsterWest_whenMove_thenMovedToWest() {
		withTerritory(
				  "  #;"
				+ " <#;"
				+ "  #;");

		move();

		assertTerritory(
				  "  #;"
				+ "< #;"
				+ "  #;");
	}
	//</editor-fold>

	//<editor-fold desc="Feature: pick/put grains">

	@Test
	public void givenHamsterWithGrainAvailable_whenPickGrain_thenPickedGrain() {
		withTerritory(">;");
		andGrainOn(0, 0);

		pickGrain();

		assertGrainsInMouth(1);
		assertGrainsOnTerritory("0;");
	}

	@Test
	public void givenHamsterWithGrainInMouth_whenPutGrain_thenPutGrainOnTile() {
		withTerritory(">;");
		andGrainsInMouth(1);

		putGrain();

		assertGrainsInMouth(0);
		assertGrainsOnTerritory("1;");
	}

	@Test
	public void givenHamsterWithNoGrainAvailable_whenPickGrain_ThenExceptionIsThrown() {
		withTerritory(">;");

		assertThrows(CommandConstraintException.class, () -> {
			pickGrain();
		});
	}

	@Test
	public void givenHamsterWithEmptyMouth_whenPutGrain_ThenExceptionIsThrown() {
		withTerritory(">;");

		assertThrows(CommandConstraintException.class, () -> {
			putGrain();
		});
	}

	//</editor-fold>

	//<editor-fold desc="Feature: turnLeft">
	@Test
	public void givenHamsterEast_whenTurnLeft_thenDirectionIsNorth() {
		withTerritory(">;");
		turnLeft();
		assertTerritory("^;");
	}
	@Test
	public void givenHamsterNorth_whenTurnLeft_thenDirectionIsWest() {
		withTerritory("^;");
		turnLeft();
		assertTerritory("<;");
	}
	@Test
	public void givenHamsterWest_whenTurnLeft_thenDirectionIsSouth() {
		withTerritory("<;");
		turnLeft();
		assertTerritory("v;");
	}
	@Test
	public void givenHamsterSouth_whenTurnLeft_thenDirectionIsEast() {
		withTerritory("v;");
		turnLeft();
		assertTerritory(">;");
	}
	//</editor-fold>

	//<editor-fold desc="Feature: frontIsClear">
	@Test
	public void givenHamsterInAnyDirection_andFrontCellIsEmpty_whenCheckFrontIsClear_thenIsTrue() {
		withTerritory(" <;");
		assertFrontIsClear();

		withTerritory("> ;");
		assertFrontIsClear();

		withTerritory(" ;^;");
		assertFrontIsClear();

		withTerritory("v; ;");
		assertFrontIsClear();
	}

	@Test
	public void givenHamsterInAnyDirection_andFrontCellIsWall_whenCheckFrontIsNotClear_thenIsTrue() {
		withTerritory("#<;");
		assertFrontIsNotClear();

		withTerritory(">#;");
		assertFrontIsNotClear();

		withTerritory("#;^;");
		assertFrontIsNotClear();

		withTerritory("v;#;");
		assertFrontIsNotClear();
	}

	@Test
	public void givenHamsterInAnyDirection_andFrontCellIsGrain_whenCheckFrontIsClear_thenIsTrue() {
		withTerritory("*<;");
		assertFrontIsClear();

		withTerritory(">*;");
		assertFrontIsClear();

		withTerritory("*;^;");
		assertFrontIsClear();

		withTerritory("v;*;");
		assertFrontIsClear();
	}

	@Test
	public void givenHamsterInAnyDirection_andFrontCellIsEndOfMap_whenCheckFrontIsNotClear_thenIsTrue() {
		withTerritory("<;");
		assertFrontIsNotClear();

		withTerritory(">;");
		assertFrontIsNotClear();

		withTerritory("^;");
		assertFrontIsNotClear();

		withTerritory("v;");
		assertFrontIsNotClear();
	}
	
	@Test
	public void givenHamsterBeforeWall_whenMove_ThenExceptionIsThrown() {
		withTerritory("#<;");

		assertThrows(CommandConstraintException.class, () -> {
			move();			
		});
	}

	@Test // test of invariant "isInitialized"
	public void givenHamsterWithCurrentTileIsNull_whenMove_ThenExceptionIsThrown() {
		withTerritory(" <;");
		removeFromStage();

		assertThrows(CommandConstraintException.class, () -> {
			move();
		});
	}

	//</editor-fold>

	//<editor-fold desc="Feature: gameLog">
	@Test
	public void givenHamster_whenExecuteAndCommand_thenGameLogIsAdded() {
		withTerritory(" *;");

		initNewHamster(locationOf(0, 0), Direction.EAST);
		move();
		pickGrain();
		putGrain();
		turnLeft();
		write("Custom Message");

		assertGameLog(
				"Init Hamster",
				"Move",
				"Pick Grain",
				"Put Grain",
				"Turn Left",
				"Custom Message");
	}

	//</editor-fold>


	//<editor-fold desc="helpers">

	private void withTerritory(String map) {
		game = GameStringifier.createFromStringStarted(map);
		sut = game.getTerritory().getDefaultHamster();
	}

	private void initNewHamster(Location location, Direction direction) {
		sut = new Hamster(game.getTerritory(), location, direction, 0);
	}

	private void removeFromStage() {
		// use internal class to be able to set an "invalid state" where the stage is not set
		var internalHamster = (ConcreteHamster) sut.getInternalHamster();
		internalHamster.setStage(null);
	}

	private static Location locationOf(int x, int y) {
		return new Location(x, y);
	}

	private void andGrainOn(int columnIndex, int rowIndex) {
		var tile = getTileAt(columnIndex, rowIndex);
		tile.addToContents(new Grain());
	}

	private void andGrainsInMouth(int count) {
		var internalHamster = (ConcreteHamster) this.sut.getInternalHamster();
		var stage = internalHamster.getStage();
		for (int i = 0; i < count; i++) {
			var grain = new Grain();
			stage.addToTileContents(grain);
			internalHamster.addToGrains(grain);
		}
	}

	private void turnLeft() {
		 sut.turnLeft();
	}

	private void move() {
		 sut.move();
	}

	private void pickGrain() {
		sut.pickGrain();
	}

	private void putGrain() {
		 sut.putGrain();
	}

	private void write(String message) {
		 sut.write(message);
	}

	private void assertTerritory(String expected) {
		String actual = GameStringifier.toString(game);
		assertEquals(expected, actual);
	}

	private void assertFrontIsClear() {
		assertTrue(sut.frontIsClear());
	}

	private void assertFrontIsNotClear() {
		assertFalse(sut.frontIsClear());
	}

	private void assertGrainsInMouth(int expected) {
		var internalHamster = sut.getInternalHamster();
		var actual = internalHamster.getGrains().size();
		assertEquals(expected, actual);
	}

	private void assertGrainsOnTerritory(String expected) {
		String actual = GameStringifier.grainsOnTerritoryToString(game);
		assertEquals(expected, actual);
	}

	private void assertGameLog(String...expectedStrings) {
		String actual = String.join("|", getLogMessages());
		String expected = String.join("|", expectedStrings);
		assertEquals(expected, actual);
	}

	private Collection<String> getLogMessages() {
		return game.getGameLog().getLogEntries().stream()
				.map(LogEntry::getMessage)
				.collect(Collectors.toList());
	}

	private Tile getTileAt(int columnIndex, int rowIndex) {
		var internalTerritory = game.getTerritory().getInternalTerritory();
		return internalTerritory.getTileAt(Location.from(columnIndex, rowIndex));
	}

	//</editor-fold>
}
