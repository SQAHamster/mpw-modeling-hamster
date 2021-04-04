#include "HamsterApplicationHandler.h"

#include "HamsterColors.h"
#include "util/GameLogControl.h"
#include "util/SpeedSliderControl.h"
#include "util/ColorConverter.h"
#include "util/UiDimensions.h"

#include <utility>
#include <thread>

using namespace viewmodel;

const std::string imagePath = "resources/images/";

namespace hamstersimulator {

HamsterApplicationHandler::HamsterApplicationHandler(std::shared_ptr<hamster::HamsterGame> game,
                                                     std::function<void()> hamsterProgram)
        : game(std::move(game)), hamsterProgram(std::move(hamsterProgram)),
          presenter(std::make_shared<HamsterGameViewPresenter>(this->game)) {
}

HamsterApplicationHandler::~HamsterApplicationHandler() {
    this->game->getPerformance()->abortOrStopGame();
    hamsterThread.join();
}

void HamsterApplicationHandler::onInitialized(SdlApplication& application) {
    this->application = &application;

    this->sdlGameInputInterface = std::make_shared<SdlGameInputInterface>(application.getNanoguiScreen());
    this->game->setUserInputInterface(sdlGameInputInterface);

    auto viewModel = this->presenter->getViewModel();
    createButton("Play24", viewModel->playButtonEnabledProperty(), [this]() { presenter->playClicked(); });
    createButton("Pause24", viewModel->pauseButtonEnabledProperty(), [this]() { presenter->pauseClicked(); });
    createButton("Undo24", viewModel->undoButtonEnabledProperty(), [this]() { presenter->undoClicked(); });
    createButton("Redo24", viewModel->redoButtonEnabledProperty(), [this]() { presenter->redoClicked(); });

    loadTexture("Tile64");

    std::vector<Color> colorValues{Color::BLACK, Color::BLUE, Color::GREEN, Color::YELLOW, Color::PINK, Color::MAGENTA,
                                   Color::RED};
    for (auto color : colorValues) {
        const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& textureName =
                "Hamster32" + HamsterColors::toColorName(color);
        loadTextureWithCustomKey("Hamster32", textureName);
        SDL_Color sdlColor = ColorConverter::toSdlColor(color);
        SDL_SetTextureColorMod(texturesByImageName[textureName], sdlColor.r, sdlColor.g, sdlColor.b);
    }
    loadTexture("Wall32");
    for (int i = 1; i <= 12; i++) {
        loadTexture(std::to_string(i) + "Corn32");
    }
    loadTexture("12PlusCorn32");

    presenter->bind();

    gameLogControl = new GameLogControl(application.getNanoguiScreen());
    gameLogControl->bindToGameLog(*viewModel);

    auto speedControl = new SpeedSliderControl(application.getNanoguiScreen());
    speedControl->bindToSpeed(*viewModel, *presenter);

    onResized(); // initially ensure that resizing logic is triggered

    hamsterThread = std::thread(hamsterProgram);
}

void HamsterApplicationHandler::createButton(const std::string& imageName,
                                             const framework::ObservablePrimitiveProperty<bool>& buttonEnabledProperty,
                                             std::function<void()> clickFunction) {
    SDL_Rect rect{TOOLBAR_MARGIN, TOOLBAR_MARGIN, BUTTON_SIZE, BUTTON_SIZE};
    int previousButtonsCount = static_cast<int>(buttons.size());
    rect.x += (previousButtonsCount * BUTTON_SIZE + previousButtonsCount * TOOLBAR_MARGIN);
    loadTexture(imageName);

    auto& button = buttons.emplace_back();
    button.rect = rect;
    button.texture = texturesByImageName[imageName];
    button.clickFunction = clickFunction;
    button.clicking = false;
    button.buttonEnabledProperty = &buttonEnabledProperty;
}

void HamsterApplicationHandler::loadTexture(const std::string& imageName) {
    texturesByImageName[imageName] = &application->loadTexture(imagePath + imageName + ".png");
}

void HamsterApplicationHandler::loadTextureWithCustomKey(const std::string& imageName, const std::string& key) {
    texturesByImageName[key] = &application->loadTexture(imagePath + imageName + ".png");
}

void HamsterApplicationHandler::onEvent(SDL_Event& event) {
    sdlGameInputInterface->onEvent(event);

    if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_SIZE_CHANGED) {
        onResized();
    }

    if (sdlGameInputInterface->isActive()) {
        return;
    }

    if (event.type == SDL_MOUSEBUTTONDOWN) {
        SDL_MouseButtonEvent& buttonEvent = event.button;
        auto buttonIndex = getButtonForPosition(buttonEvent.x, buttonEvent.y);
        if (buttonIndex.has_value()) {
            buttons[buttonIndex.value()].clicking = true;
        }
    } else if (event.type == SDL_MOUSEBUTTONUP) {
        SDL_MouseButtonEvent& buttonEvent = event.button;
        auto buttonIndex = getButtonForPosition(buttonEvent.x, buttonEvent.y);
        if (buttonIndex.has_value()) {
            SimpleButton& button = buttons[buttonIndex.value()];
            if (button.buttonEnabledProperty->get()) {
                button.clickFunction();
            }
        }
        for (auto& button : buttons) {
            button.clicking = false;
        }
    }
}

std::optional<size_t> HamsterApplicationHandler::getButtonForPosition(int x, int y) {
    SDL_Point point{x, y};
    for (size_t i = 0; i < buttons.size(); i++) {
        if (SDL_PointInRect(&point, &buttons[i].rect)) {
            return i;
        }
    }
    return std::nullopt;
}

void HamsterApplicationHandler::onRender(SDL_Renderer& renderer) {
    renderToolbar(renderer);
    renderTerritory(renderer);

    SDL_Delay(16);
}

void HamsterApplicationHandler::renderToolbar(SDL_Renderer& renderer) {
    for (auto& button : buttons) {
        if (!button.buttonEnabledProperty->get()) {
            SDL_SetTextureColorMod(button.texture, 128, 128, 128);
        } else if (button.clicking) {
            SDL_SetTextureColorMod(button.texture, 128, 128, 255);
        } else {
            SDL_SetTextureColorMod(button.texture, 255, 255, 255);
        }
        SDL_RenderCopy(&renderer, button.texture, nullptr, &button.rect);
    }
}

void HamsterApplicationHandler::renderTerritory(SDL_Renderer& renderer) {
    SDL_Rect rect{0, 0, currentTileSize, currentTileSize};

    auto lock = presenter->getSemaphore().lock();
    auto viewModel = presenter->getViewModel();

    unsigned rowIndex = 0;
    for (auto& row : viewModel->getRows()) {
        unsigned columnIndex = 0;
        rect.y = rowIndex * currentTileSize + TERRITORY_OFFSET;
        for (auto& cell : row.getCells()) {
            rect.x = columnIndex * currentTileSize;
            renderCell(rect, cell, renderer);
            columnIndex++;
        }
        rowIndex++;
    }
}

void HamsterApplicationHandler::renderCell(SDL_Rect& rect, ViewModelCell& cell,
                                           SDL_Renderer& renderer) {
    render(renderer, rect, "Tile64");
    for (auto& layer : cell.getLayers()) {
        if (layer.getVisible()) {
            render(renderer, rect, layer.getImageName(), layer.getRotation());
        }
    }
}

void HamsterApplicationHandler::render(SDL_Renderer& renderer, SDL_Rect& rect,
                                       const std::string& imageName, int rotation) {
    SDL_Texture* texture = texturesByImageName[imageName];
    SDL_RenderCopyEx(&renderer, texture, nullptr, &rect, rotation, nullptr, SDL_FLIP_NONE);
}

void HamsterApplicationHandler::onClose() {

}

void HamsterApplicationHandler::onResized() {
    currentTileSize = calculateTileSize();
    gameLogControl->setFixedWidth(calculateGameLogSize());
    application->getNanoguiScreen().performLayout();
}

int HamsterApplicationHandler::calculateTileSize() {
    const mpw::Size size = game->getTerritory()->getTerritorySize();
    const int columns = size.getColumnCount();
    const int rows = size.getRowCount();

    sdlgui::Screen& screen = application->getNanoguiScreen();
    const int pixPerCellWidth = (screen.width() - (TERRITORY_GAMELOG_MARGIN + GAMELOG_MIN_WIDTH)) / (columns == 0 ? 1 : columns);
    const int pixPerCellHeight = (screen.height() - TERRITORY_OFFSET) / (rows == 0 ? 1 : rows);

    const int tileSize = std::min(pixPerCellHeight, pixPerCellWidth);
    return std::max(MINIMUM_TILE_SIZE, tileSize);
}

int HamsterApplicationHandler::calculateGameLogSize() {
    const mpw::Size size = game->getTerritory()->getTerritorySize();
    const int columns = size.getColumnCount();

    sdlgui::Screen& screen = application->getNanoguiScreen();
    return screen.width() - (columns*currentTileSize) - TERRITORY_GAMELOG_MARGIN;
}

}
