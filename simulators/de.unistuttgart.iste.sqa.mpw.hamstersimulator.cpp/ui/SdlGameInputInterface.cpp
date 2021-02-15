#include "SdlGameInputInterface.h"

namespace hamstersimulator {
    void SdlGameInputInterface::onRender(SDL_Renderer& /*renderer*/)
    {
    }

    void SdlGameInputInterface::onEvent(SDL_Event& /*event*/)
    {
    }

    bool SdlGameInputInterface::isActive() const
    {
        return active;
    }

    const std::string& SdlGameInputInterface::getUserInput()
    {
        static std::string dummy;
        return dummy;
    }

    void SdlGameInputInterface::showMessage(const std::string& /*message*/) const
    {
    }

    void SdlGameInputInterface::showMessageForTextInput(const std::string& /*message*/) const
    {
    }

    int SdlGameInputInterface::readInteger(std::string /*message*/)
    {
        return 0;
    }
    
    std::string SdlGameInputInterface::readString(std::string /*message*/)
    {
        return "";
    }
    
    void SdlGameInputInterface::confirmAlert(std::runtime_error /*t*/)
    {
    }
    
    void SdlGameInputInterface::abort()
    {
    }
}
