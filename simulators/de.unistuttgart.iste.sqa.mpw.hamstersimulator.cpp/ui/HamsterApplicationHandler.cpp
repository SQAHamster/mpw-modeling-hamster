#include "HamsterApplicationHandler.h"

#include "HamsterColors.h"

#include <utility>
#include <thread>

using namespace viewmodel;

const int TOOLBAR_MARGIN = 8;
const int BUTTON_SIZE = 48;
const int TERRITORY_OFFSET = 80;
const int TILE_SIZE = 80;
const std::string imagePath = "resources/images/";

namespace hamstersimulator {

HamsterApplicationHandler::HamsterApplicationHandler(std::shared_ptr<hamster::HamsterGame> game,
                                                     std::function<void()> hamsterProgram)
        : game(std::move(game)), hamsterProgram(std::move(hamsterProgram))
        , presenter(std::make_shared<HamsterGameViewPresenter>(this->game))
        , sdlGameInputInterface(std::make_shared<SdlGameInputInterface>()) {
    this->game->setUserInputInterface(sdlGameInputInterface);
}

void HamsterApplicationHandler::onInitialized(SdlApplication& application) {
    this->application = &application;

    createButton("Play24", [this]() { presenter->playClicked(); });
    createButton("Pause24", [this]() { presenter->pauseClicked(); });
    createButton("Undo24", [this]() { presenter->undoClicked(); });
    createButton("Redo24", [this]() { presenter->redoClicked(); });

    loadTexture("Tile64");

    std::vector<Color> colorValues { Color::BLACK, Color::BLUE, Color::GREEN, Color::YELLOW, Color::PINK, Color::MAGENTA, Color::RED };
    for (auto color : colorValues) {
        const std::basic_string<char, std::char_traits<char>, std::allocator<char>>& textureName =
                "Hamster32" + HamsterColors::toColorName(color);
        loadTextureWithCustomKey("Hamster32", textureName);
        SDL_Color sdlColor = toSdlColor(color);
        SDL_SetTextureColorMod(texturesByImageName[textureName], sdlColor.r, sdlColor.g, sdlColor.b);
    }
    loadTexture("Wall32");
    for (int i = 1; i <= 12; i++) {
        loadTexture(std::to_string(i) + "Corn32");
    }
    loadTexture("12PlusCorn32");

    game->startGamePaused();
    presenter->bind();

    hamsterThread = std::thread(hamsterProgram);
}

void HamsterApplicationHandler::createButton(const std::string& imageName, std::function<void()> clickFunction) {
    SDL_Rect rect {TOOLBAR_MARGIN, TOOLBAR_MARGIN, BUTTON_SIZE, BUTTON_SIZE};
    int previousButtonsCount = static_cast<int>(buttons.size());
    rect.x += (previousButtonsCount * BUTTON_SIZE + previousButtonsCount * TOOLBAR_MARGIN);
    loadTexture(imageName);

    auto& button = buttons.emplace_back();
    button.rect = rect;
    button.texture = texturesByImageName[imageName];
    button.clickFunction = clickFunction;
    button.clicking = false;
    button.enabled = true;
}

void HamsterApplicationHandler::loadTexture(const std::string& imageName) {
    texturesByImageName[imageName] = &application->loadTexture(imagePath + imageName + ".png");
}

void HamsterApplicationHandler::loadTextureWithCustomKey(const std::string& imageName, const std::string& key) {
    texturesByImageName[key] = &application->loadTexture(imagePath + imageName + ".png");
}

void HamsterApplicationHandler::onEvent(SDL_Event& event) {
    if (sdlGameInputInterface->isActive())
    {
        sdlGameInputInterface->onEvent(event);
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
            buttons[buttonIndex.value()].clickFunction();
        }
        for (auto& button : buttons) {
            button.clicking = false;
        }
    }
}

std::optional<size_t> HamsterApplicationHandler::getButtonForPosition(int x, int y) {
    SDL_Point point {x, y};
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
    renderGameLog(renderer);

    if (sdlGameInputInterface->isActive())
    {
        sdlGameInputInterface->onRender(renderer);
    }

    SDL_Delay(16);
}

void HamsterApplicationHandler::renderToolbar(SDL_Renderer& renderer) {
    for (auto& button : buttons) {
        if (button.enabled == false) {
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
    SDL_Rect rect{0, 0, TILE_SIZE, TILE_SIZE};

    auto lock = presenter->getSemaphore().lock();
    auto viewModel = presenter->getViewModel();

    unsigned rowIndex = 0;
    for (auto& row : viewModel->getRows()) {
        unsigned columnIndex = 0;
        rect.y = rowIndex * TILE_SIZE + TERRITORY_OFFSET;
        for (auto& cell : row.getCells()) {
            rect.x = columnIndex * TILE_SIZE;
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

void HamsterApplicationHandler::renderGameLog(SDL_Renderer& renderer) {
    static std::unordered_map<ViewModelLogEntry*, SDL_Texture*> textTextures;

    auto lock = presenter->getSemaphore().lock();
    auto viewModel = presenter->getViewModel();

    const int offsetX = viewModel->getSize().getColumnCount() * TILE_SIZE + 20;
    const int offsetY = 20;

    SDL_Rect rect{offsetX, offsetY, 200, viewModel->getSize().getRowCount() * TILE_SIZE + TERRITORY_OFFSET - 20};
    SDL_SetRenderDrawColor(&renderer, 0, 0, 0, 255);
    SDL_RenderDrawRect(&renderer, &rect);

    rect.x += 4;
    rect.y += 4;

    auto& logEntries = viewModel->getLogEntries();
    for (auto iter = logEntries.rbegin(); iter != logEntries.rend(); ++iter) {
        auto& logEntry = *iter;
        SDL_Texture* texture;
        if (textTextures.find(&logEntry) != textTextures.end()) {
            texture = textTextures[&logEntry];
        } else {
            SDL_Color color = toSdlColor(logEntry.getColor());
            texture = &application->createTextureForText(logEntry.getMessage(), 12, color);
            textTextures[&logEntry] = texture;
        }

        SDL_QueryTexture(texture, nullptr, nullptr, &rect.w, &rect.h);
        SDL_RenderCopyEx(&renderer, texture, nullptr, &rect, 0, nullptr, SDL_FLIP_NONE);
        rect.y += rect.h;
    }
}

void HamsterApplicationHandler::onClose() {

}

SDL_Color HamsterApplicationHandler::toSdlColor(viewmodel::Color color) {
    switch (color) {
        case Color::BLACK: return { 0, 0, 0, 255 };
        case Color::BLUE: return { 0, 0, 255, 255 };
        case Color::GREEN: return { 0, 255, 0, 255 };
        case Color::YELLOW: return { 255, 255, 0, 255 };
        case Color::PINK: return { 255, 175, 175, 255 };
        case Color::MAGENTA: return { 255, 0, 255, 255 };
        case Color::RED: return { 255, 0, 0, 255 };
    }
    return { 0, 0, 0, 255 };
}


}
