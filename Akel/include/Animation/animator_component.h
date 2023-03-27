// This file is a part of Akel
// Authors : @kbz_8
// Created : 27/03/2023
// Updated : 27/03/2023

#ifndef __AK_ANIMATOR_COMPONENT__
#define __AK_ANIMATOR_COMPONENT__

#include <Akpch.h>
#include <Core/Components/components.h>

namespace Ak
{
	class AK_API AnimatorComponent : public Component
	{
		public:
			AnimatorComponent();

			void onAttach() override;
			void update() override;
			void onQuit() override;

			~AnimatorComponent() = default;

		private:
	};
}

#endif
