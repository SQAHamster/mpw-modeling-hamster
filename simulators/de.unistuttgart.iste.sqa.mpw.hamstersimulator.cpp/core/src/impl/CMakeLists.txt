include(CMakeListsImpl.cmake)
message("gen-src" ${IMPL_GEN_SRCS})
set(IMPL_SRCS ${IMPL_SRCS}
    "src/impl/HamsterCore.h"
    "src/impl/TerritoryLoader.h" "src/impl/TerritoryLoader.cpp"
    "src/impl/HamsterGameViewPresenter.h" "src/impl/HamsterGameViewPresenter.cpp"
    "src/impl/HamsterColors.h" "src/impl/HamsterColors.cpp"
    ${IMPL_GEN_SRCS}
    PARENT_SCOPE)
    