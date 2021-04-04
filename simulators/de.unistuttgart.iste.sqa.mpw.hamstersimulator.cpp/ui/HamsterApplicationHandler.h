#ifndef HAMSTERSIMULATOR_CPP_HAMSTERAPPLICATIONHANDLER_H
#define HAMSTERSIMULATOR_CPP_HAMSTERAPPLICATIONHANDLER_H

#include "SdlApplicationListener.h"
#include "SdlApplication.h"

#include "SdlGameInputInterface.h"
#include "HamsterCore.h"
#include "HamsterView.h"
#include "util/GameLogControl.h"

#include <thread>
#include <unordered_map>
#include <functional>
#include <optional>
#include <vector>
#include <string>

namespace hamstersimulator {

class HamsterApplicationHandler : public SdlApplicationListener {
private:

    const std::shared_ptr<hamster::HamsterGame> game;
    const std::shared_ptr<viewmodel::GameViewPresenter> presenter;
    const std::function<void()> hamsterProgram;

    SdlApplication* application{nullptr};
    std::shared_ptr<SdlGameInputInterface> sdlGameInputInterface;

    std::unordered_map<std::string, SDL_Texture*> texturesByImageName;

    int currentTileSize = 0;
    GameLogControl* gameLogControl = nullptr;

    struct SimpleButton {
        SDL_Rect rect;
        SDL_Texture* texture;
        std::function<void()> clickFunction;
        bool clicking;
        const framework::ObservablePrimitiveProperty<bool>* buttonEnabledProperty;
    };
    std::vector<SimpleButton> buttons;


    std::thread hamsterThread;

public:
    HamsterApplicationHandler(std::shared_ptr<hamster::HamsterGame> game, std::function<void()> hamsterProgram);
    ~HamsterApplicationHandler() override;

    void onInitialized(SdlApplication& application) override;

    void onEvent(SDL_Event& event) override;

    void onRender(SDL_Renderer& renderer) override;

    void onClose() override;

private:

    void onResized();

    void createButton(const std::string& imageName,
                      const framework::ObservablePrimitiveProperty<bool>& buttonEnabledProperty,
                      std::function<void()> clickFunction);

    void renderToolbar(SDL_Renderer& renderer);
    void renderTerritory(SDL_Renderer& renderer);

    void loadTexture(const std::string& imageName);
    void loadTextureWithCustomKey(const std::string& imageName, const std::string& key);
    void renderCell(SDL_Rect& rect, viewmodel::ViewModelCell& cell, SDL_Renderer& renderer);
    void render(SDL_Renderer& renderer, SDL_Rect& rect, const std::string& imageName, int rotation = 0);

    std::optional<size_t> getButtonForPosition(int x, int y);

    int calculateTileSize();
    int calculateGameLogSize();
};

}

#endif //HAMSTERSIMULATOR_CPP_HAMSTERAPPLICATIONHANDLER_H
