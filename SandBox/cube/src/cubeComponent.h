#ifndef __CUBE_COMPONENT__
#define __CUBE_COMPONENT__

#include <Akel.h>

class CubeComponent : Ak::WindowComponent
{
    public:
        explicit CubeComponent();

        void onAttach() override;
        void update() override;
        void onEvent(Ak::Input& input) override;
        void onQuit() override;

        ~CubeComponent() = default;
};

#endif // __CUBE_COMPONENT__
