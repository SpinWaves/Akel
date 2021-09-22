
#ifndef __AK_SANDBOX_RECT__
#define __AK_SANDBOX_RECT__

#include <Akel.h>

class RectComponent : public Ak::WindowComponent
{
    public:
        explicit RectComponent();

        void onAttach() override;
        void update() override;
        void onEvent(Ak::Input& input) override;
        void onQuit() override;

        ~RectComponent() = default;
};

#endif // __AK_SANDBOX_RECT__
