
#include <Akel.h>

#define AK_PROJECT_FILE_DIR std::string(Ak::Core::getMainDirPath() + "SandBox/rect")
#define AK_PROJECT_FILE_NAME std::string("rect")

#include <Akel_main.h>
#include "rectComponent.h"

class Rect : public Ak::Application
{
    public:
        Rect() : Ak::Application("Rect")
        {
            add_component(Ak::custom_malloc<RectComponent>());
        }
        ~Rect() = default;
};

Ak::Application* Akel_main()
{
    return Ak::custom_malloc<Rect>();
}
