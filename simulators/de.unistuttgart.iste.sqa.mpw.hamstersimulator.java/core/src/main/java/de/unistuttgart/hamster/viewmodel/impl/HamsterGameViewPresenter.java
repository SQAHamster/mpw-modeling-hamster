package de.unistuttgart.hamster.viewmodel.impl;

import de.unistuttgart.hamster.facade.*;
import de.unistuttgart.hamster.hamster.*;
import de.unistuttgart.iste.sqa.mpw.framework.datatypes.Direction;
import de.unistuttgart.iste.sqa.mpw.framework.mpw.LogEntry;
import de.unistuttgart.iste.sqa.mpw.framework.datatypes.Size;
import de.unistuttgart.iste.sqa.mpw.framework.mpw.Tile;
import de.unistuttgart.iste.sqa.mpw.framework.datatypes.Color;
import de.unistuttgart.iste.sqa.mpw.framework.viewmodel.ViewModelCell;
import de.unistuttgart.iste.sqa.mpw.framework.viewmodel.ViewModelCellLayer;
import de.unistuttgart.iste.sqa.mpw.framework.viewmodel.impl.GameViewPresenterBase;
import javafx.beans.property.ReadOnlyListProperty;
import javafx.beans.property.ReadOnlyObjectProperty;
import javafx.beans.value.ChangeListener;

import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Optional;
import java.util.stream.Collectors;

public class HamsterGameViewPresenter extends GameViewPresenterBase {
	private final Territory territory;

	private final Map<ReadOnlyHamster, Color> hamsterToColorMap = new HashMap<>();
	private final Map<ReadOnlyHamster, ChangeListener<Direction>> hamsterDirectionChangeListeners = new HashMap<>();

	public HamsterGameViewPresenter(final HamsterGame game) {
		super(game);
		this.territory = game.getTerritory();
	}

	@Override
	protected ReadOnlyObjectProperty<Size> getStageSizeFromConcreteStage() {
		return territory.getInternalTerritory().stageSizeProperty();
	}

	@Override
	protected ReadOnlyListProperty<Tile> getTilesPropertyFromConcreteStage() {
		return territory.getInternalTerritory().tilesProperty();
	}

	@Override
	protected Color getColorForLogEntry(final LogEntry entry) {
		if (hamsterToColorMap.containsKey(entry.getActor())) {
			return hamsterToColorMap.get(entry.getActor());
		}
		return super.getColorForLogEntry(entry);
	}

	@Override
	protected void onSetTileNodeAtForCell(final ViewModelCell cell, final Tile tile) {
		configureWallImageView(cell, tile);
		configureGrainImageView(cell, tile);
		configureBreadcrumbImageView(cell, tile);

		final Optional<ReadOnlyHamster> hamsterOptional = findHamsterOnTile(tile);
		hamsterOptional.ifPresent(readOnlyHamster -> configureHamsterImageView(cell, readOnlyHamster));
	}

	private Optional<ReadOnlyHamster> findHamsterOnTile(final Tile tile) {
		return tile.getContents().stream()
				.filter(ReadOnlyHamster.class::isInstance)
				.map(ReadOnlyHamster.class::cast).findFirst();
	}

	private void configureWallImageView(final ViewModelCell cell, final Tile tile) {
		final var layer = new ViewModelCellLayer();
		layer.setImageName("Wall");
		refreshWallLayer(layer, tile);
		cell.getLayers().add(layer);
	}

	private void refreshWallLayer(final ViewModelCellLayer layer, final Tile tile) {
		layer.setVisible(tile.getContents().stream().anyMatch(Wall.class::isInstance));
	}

	private void configureGrainImageView(final ViewModelCell cell, final Tile tile) {
		final var layer = new ViewModelCellLayer();
		refreshGrainLayer(layer, tile);
		cell.getLayers().add(layer);
	}

	private void refreshGrainLayer(final ViewModelCellLayer layer, final Tile tile) {
		final int grainCount = getGrainOfTile(tile).size();
		layer.setVisible(grainCount > 0);

		if (grainCount <= 12) {
			layer.setImageName(grainCount + "Corn");
		} else {
			layer.setImageName("12PlusCorn");
		}
	}

	// create a layer for the breadcrumb image
	private void configureBreadcrumbImageView(final ViewModelCell cell, final Tile tile) {
		final var layer = new ViewModelCellLayer();
		layer.setImageName("Breadcrumb");
		refreshBreadcrumbLayer(layer, tile);
		cell.getLayers().add(layer);
	}

	// set the breadcrumb visibility to true, if the tile contains a Breadcrumb object
	private void refreshBreadcrumbLayer(final ViewModelCellLayer layer, final Tile tile) {
		final boolean containsBreadcrumb = tile.getContents().stream().anyMatch(Breadcrumb.class::isInstance);
		layer.setVisible(containsBreadcrumb);
	}

	private List<Grain> getGrainOfTile(final Tile tile) {
		return tile.getContents().stream()
				.filter(Grain.class::isInstance)
				.map(Grain.class::cast)
				.collect(Collectors.toList());
	}

	private void configureHamsterImageView(final ViewModelCell cell, final ReadOnlyHamster hamster) {
		updateColorMap();

		final var layer = new ViewModelCellLayer();
		layer.setImageName("Hamster" + hamsterToColorMap.get(hamster).name());

		addHamsterDirectionListener(layer, hamster);

		refreshHamsterLayer(layer, hamster);
		cell.getLayers().add(layer);
	}

	/*
	 * Adds a listener for the change of the direction, to also update the layers if the hamster turns left.
	 * Note: Since onSetTileNodeAtForCell() is called every time the contents of a tile changes, a Hamster might
	 * be configured multiple times. Avoid, that multiple direction listeners are attached.
	 */
	private void addHamsterDirectionListener(final ViewModelCellLayer layer, final ReadOnlyHamster hamster) {
		if (hamsterDirectionChangeListeners.containsKey(hamster)) {
			final ChangeListener<Direction> oldChangeListener = hamsterDirectionChangeListeners.remove(hamster);
			hamster.directionProperty().removeListener(oldChangeListener);
		}
		final ChangeListener<Direction> hamsterChangeListener = (property, oldValue, newValue) -> {
			runLocked(() -> {
				refreshHamsterLayer(layer, hamster);
			});
		};
		hamster.directionProperty().addListener(hamsterChangeListener);
		hamsterDirectionChangeListeners.put(hamster, hamsterChangeListener);
	}

	private void refreshHamsterLayer(final ViewModelCellLayer layer, final ReadOnlyHamster hamster) {
		layer.setVisible(hamster.getCurrentTile() != null);
		if (hamster.getDirection() != null) {
			layer.setRotation(getRotationForDirection(hamster.getDirection()));
		}
	}

	private void updateColorMap() {
		territory.getInternalTerritory().getTileContents().stream()
				.filter(ReadOnlyHamster.class::isInstance)
				.map(ReadOnlyHamster.class::cast)
				.filter(hamster -> !hamsterToColorMap.containsKey(hamster))
				.forEach(hamster -> {
					final var color = HamsterColors.getColorForNthHamster(hamsterToColorMap.size());
					hamsterToColorMap.put(hamster, color);
				});
	}

}
