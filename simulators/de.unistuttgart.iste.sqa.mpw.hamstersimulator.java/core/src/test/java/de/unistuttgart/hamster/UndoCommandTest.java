package de.unistuttgart.hamster;

import de.unistuttgart.hamster.facade.HamsterGame;
import de.unistuttgart.hamster.util.GameStringifier;
import org.junit.jupiter.api.Disabled;
import org.junit.jupiter.api.Test;

import java.util.stream.Collectors;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class UndoCommandTest {
	
	@Test
	public void testUndo() {
		HamsterGame game = GameStringifier.createFromString(" >*;" +
															"   ;");
		game.hardReset();
		game.startGame();

		var hamster = game.getTerritory().getDefaultHamster();
		hamster.move();
		hamster.pickGrain();

		hamster.turnLeft();
		hamster.turnLeft();
		hamster.turnLeft();

		hamster.move();

		var commandStack = game.getGameCommandStack();
		commandStack.undo();
		String actual = GameStringifier.toString(game);
		assertEquals("  v;" +
				     "   ;", actual);

		commandStack.undoAll();

		actual = GameStringifier.toString(game);
		assertEquals(" >*;" +
				     "   ;", actual);
	}

	@Test
	public void testUndoOfLogs() {
		HamsterGame game = GameStringifier.createFromString(" >*;" +
															"   ;");
		var commandStack = game.getGameCommandStack();

		game.hardReset();
		game.startGame();

		var hamster = game.getTerritory().getDefaultHamster();
		hamster.move();
		hamster.write("text");
		hamster.pickGrain();
		assertEquals("Move|text|Pick Grain", logToString(game));

		commandStack.undo();
		assertEquals("Move|text", logToString(game));

		commandStack.undo();
		assertEquals("Move", logToString(game));
		assertEquals("  >;" +
				     "   ;", GameStringifier.toString(game));

		commandStack.redo();
		assertEquals("Move|text", logToString(game));

		commandStack.redo();
		assertEquals("Move|text|Pick Grain", logToString(game));
	}

	private String logToString(HamsterGame game) {
		return game.getGameLog().getLogEntries().stream()
				.map(logEntry -> logEntry.getMessage())
				.collect(Collectors.joining("|"));
	}

}
