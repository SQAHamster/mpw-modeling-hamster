#include "GameLogControl.h"

#include "WidgetBackgroundWrapper.h"
#include "ListTheme.h"
#include "ColorConverter.h"

#include <sdlgui/label.h>
#include <sdlgui/vscrollpanel.h>

const int TILE_SIZE = 80; // TODO: reuse
const int LOG_OFFSET = 10;

using namespace sdlgui;

hamstersimulator::GameLogControl::GameLogControl(sdlgui::Screen& screen)
    : Window(&screen, "")
    , screen(screen) {

    Vector2i windowSize(200, screen.height() - LOG_OFFSET*2);
    setFixedSize(windowSize);

    setTheme(new ListTheme(screen.sdlRenderer()));
    scrollPanel = &vscrollpanel();
    listPanel = &scrollPanel->withFixedSize({ windowSize.x, windowSize.y - 8 })
        .widget()
        .withLayout<BoxLayout>(Orientation::Vertical, Alignment::Fill, 0, 0);
}

void hamstersimulator::GameLogControl::bindToGameLog(const viewmodel::GameViewModel& viewModel) {
    int x = TILE_SIZE * viewModel.getSize().getColumnCount() + LOG_OFFSET;
    setPosition(x, LOG_OFFSET);

    viewModel.logEntriesProperty().addOnAddedListener([&](const viewmodel::ViewModelLogEntry& logEntry) {
        SDL_Color color = {174, 214, 241, 150};
        if (viewModel.getLogEntries().size() % 2 == 0) {
            color = {0, 0, 0, 0};
        }

        auto& widget = listPanel->wdg<WidgetBackgroundWrapper>(color)
            .withFixedSize({width()-6, 20});
        widget.label(logEntry.getMessage())
            .setColor(ColorConverter::toNanoguiColor(logEntry.getColor()));
        logEntryWidgets[&logEntry] = &widget;
        
        scrollPanel->scrollEvent({}, {0, static_cast<float>(-scrollPanel->height())});
        screen.performLayout();
    });

    viewModel.logEntriesProperty().addOnRemovedListener([&](const viewmodel::ViewModelLogEntry& logEntry) {
        auto iterator = logEntryWidgets.find(&logEntry);
        if (iterator != logEntryWidgets.end()) {
            auto widget = (*iterator).second;
            listPanel->removeChild(widget);
            logEntryWidgets.erase(iterator);
        }
        screen.performLayout();
    });
    
    screen.performLayout();
}

void hamstersimulator::GameLogControl::draw(SDL_Renderer* surface) {
    SDL_Rect previousSdlRect;
    SDL_RenderGetClipRect(surface, &previousSdlRect);

    const PntRect& rect = getAbsoluteCliprect();
    SDL_Rect sdlRect = {rect.x1, rect.y1, rect.x2-rect.x1, rect.y2-rect.y1};

    SDL_RenderSetClipRect(surface, &sdlRect);
    Window::draw(surface);
    SDL_RenderSetClipRect(surface, nullptr);

    SDL_RenderDrawRect(surface, &sdlRect);
}
