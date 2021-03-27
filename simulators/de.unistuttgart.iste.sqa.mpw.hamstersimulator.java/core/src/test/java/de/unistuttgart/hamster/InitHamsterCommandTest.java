package de.unistuttgart.hamster;

import de.unistuttgart.iste.sqa.mpw.framework.exceptions.CommandConstraintException;
import de.unistuttgart.hamster.facade.HamsterGame;
import de.unistuttgart.iste.sqa.mpw.framework.datatypes.Direction;
import de.unistuttgart.iste.sqa.mpw.framework.datatypes.Location;
import de.unistuttgart.hamster.util.GameStringifier;
import org.junit.jupiter.api.Test;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertThrows;

public class InitHamsterCommandTest {
	
	@Test
	public void testInitHamsterOn1x1_and4Grains() {
		HamsterGame game = GameStringifier.createFromStringStarted("   ;" +
															       "   ;");

		var sut = game.getTerritory().getDefaultHamster();
		sut.init(game.getTerritory(), locationOf(1, 1), Direction.SOUTH, 4);

		String actual = GameStringifier.toString(game);
		assertEquals("   ;" +
				     " v ;", actual);
		assertEquals(4, sut.getInternalHamster().getGrains().size());
	}


	@Test
	public void testInitHamster_invalidGrainCount() {
		HamsterGame game = GameStringifier.createFromStringStarted(" ;");

		var sut = game.getTerritory().getDefaultHamster();
		assertThrows(CommandConstraintException.class, () -> {
			sut.init(game.getTerritory(), locationOf(0, 0), Direction.SOUTH, -1);
		});
	}

	@Test
	public void testUndoInitHamster() {
		HamsterGame game = GameStringifier.createFromStringStarted("  ;");

		var sut = game.getTerritory().getDefaultHamster();
		sut.init(game.getTerritory(), locationOf(0, 0), Direction.SOUTH, 2);
		game.getGameCommandStack().undo();

		assertEquals(null, sut.getInternalHamster().getDirection());
		assertEquals(0, sut.getInternalHamster().getGrains().size());
	}

	private Location locationOf(int column, int row) {
		var location = new Location();
		location.setColumn(column);
		location.setRow(row);
		return location;
	}


}
