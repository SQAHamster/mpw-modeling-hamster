package de.unistuttgart.hamster.view;

import de.unistuttgart.hamster.facade.TerritoryLoader;
import de.unistuttgart.hamster.facade.Hamster;
import de.unistuttgart.hamster.facade.HamsterGame;
import de.unistuttgart.hamster.viewmodel.impl.HamsterGameViewPresenter;
import de.unistuttgart.iste.sqa.mpw.framework.viewmodel.GameViewInput;
import de.unistuttgart.iste.sqa.mpw.framework.viewmodel.GameViewModel;
import de.unistuttgart.iste.sqa.mpw.framework.viewmodel.ViewModelCell;
import de.unistuttgart.iste.sqa.mpw.framework.viewmodel.ViewModelRow;
import org.junit.jupiter.api.BeforeAll;

import java.io.IOException;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

import static org.junit.jupiter.api.Assertions.assertEquals;

public class HamsterViewTestBase {

    private int maxCharsPerCell = 4;
    private static Map<String, String> characterMap = new HashMap<>();
    private HamsterGame game;
    protected Hamster paule;
    protected GameViewInput viewInput;
    protected GameViewModel viewModel;

    @BeforeAll
    public static void setup() {
        initCharMapping();
    }

    protected void withTerritory(final String fileName) throws IOException {
        final String path = getResourcePath(fileName);
        game = new HamsterGame();
        TerritoryLoader.initializeFor(game).loadFromResourceFile(path);

        game.startGame();
        game.getPerformance().setDelayEnabled(false);

        var territory = game.getTerritory();
        paule = territory.getDefaultHamster();

        var presenter = new HamsterGameViewPresenter(game);
        presenter.bind();
        viewInput = presenter;
        viewModel = presenter.getViewModel();

        game.setUserInputInterface(new UserInputInterfaceFake());
    }

    protected void initializeOtherTerritory(final String fileName) throws IOException {
        game.hardReset();
        TerritoryLoader.initializeFor(game).loadFromResourceFile(getResourcePath(fileName));
    }

    private String getResourcePath(String fileName) {
        return "de.unistuttgart.hamster.territories/" + fileName;
    }

    protected void clickPlay() {
        viewInput.playClicked();
    }

    protected void clickPause() {
        viewInput.pauseClicked();
    }

    protected void clickUndo() {
        viewInput.undoClicked();
    }

    protected void clickRedo() {
        viewInput.redoClicked();
    }

    protected void assertTerritory(String expected) {
        var actual = new HamsterViewModelStringifier(characterMap, maxCharsPerCell)
                .territoryToExpectationString(viewModel);
        assertEquals(expected, actual);
        assertLocationsAreSet();
        assertSizeIsConsistent();
    }

    protected void assertButtons(String expected) {
        var actual = HamsterViewModelStringifier.buttonBarToExpectationString(viewModel);
        assertEquals(expected, actual);
        assertLocationsAreSet();
        assertSizeIsConsistent();
    }

    private void assertLocationsAreSet() {
        List<ViewModelRow> rows = viewModel.getRows();
        for (int rowIndex = 0; rowIndex < rows.size(); rowIndex++) {
            ViewModelRow row = rows.get(rowIndex);
            List<ViewModelCell> cells = row.getCells();
            for (int columnIndex = 0; columnIndex < cells.size(); columnIndex++) {
                ViewModelCell cell = cells.get(columnIndex);
                assertEquals(columnIndex, cell.getLocation().getColumn());
                assertEquals(rowIndex, cell.getLocation().getRow());
            }

        }

    }

    private void assertSizeIsConsistent() {
        List<ViewModelRow> rows = viewModel.getRows();
        assertEquals(rows.size(), viewModel.getSize().getRowCount());
        for (ViewModelRow row : rows) {
            assertEquals(row.getCells().size(), viewModel.getSize().getColumnCount());
        }
    }

    protected void assertLog(String expected) {
        String actual = HamsterViewModelStringifier.logToString(viewModel);
        assertEquals(expected, actual);
    }

    private static void initCharMapping() {
        characterMap.put("1Corn", " 1*");
        characterMap.put("2Corn", " 2*");
        characterMap.put("3Corn", " 3*");
        characterMap.put("4Corn", " 4*");
        characterMap.put("5Corn", " 5*");
        characterMap.put("6Corn", " 6*");
        characterMap.put("7Corn", " 7*");
        characterMap.put("8Corn", " 8*");
        characterMap.put("9Corn", " 9*");
        characterMap.put("10Corn", "10*");
        characterMap.put("11Corn", "11*");
        characterMap.put("12Corn", "12*");
        characterMap.put("12PlusCorn", "12+");
        characterMap.put("Hamster", ">");
        characterMap.put("Hamster[90]", "v");
        characterMap.put("Hamster[180]", "<");
        characterMap.put("Hamster[270]", "^");
        characterMap.put("Wall", "####");
    }

}
