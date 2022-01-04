#ifndef __TEST_KILA_COMP__
#define __TEST_KILA_COMP__

#include <Akel.h>

class Comp : public Ak::Component
{
    public:
        explicit Comp();

        void onAttach() override;
        void update() override;
        void onEvent(Ak::Input& input) override;
        void onQuit() override;

        ~Comp() = default;
};

#endif // __TEST_KILA_COMP__
