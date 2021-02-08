include(CMakeListsImpl.cmake)
message("gen-src" ${IMPL_GEN_SRCS})
set(IMPL_SRCS ${IMPL_SRCS}
    "core/src/impl/HamsterCore.h"
    "core/src/impl/TerritoryLoader.h"
    "core/src/impl/TerritoryLoader.cpp"
    "core/src/impl/HamsterGameViewPresenter.h"
    "core/src/impl/HamsterGameViewPresenter.cpp"
    ${IMPL_GEN_SRCS}
    PARENT_SCOPE)
    