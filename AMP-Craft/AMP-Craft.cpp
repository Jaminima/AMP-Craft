#include <iostream>
#include "Window.h"
#include "TextureManager.h"
#include <stdlib.h>

bool pick_accelerator()
{
	std::vector<accelerator> accs = accelerator::get_all();
	accelerator chosen_one;

	auto result = std::find_if(accs.begin(), accs.end(),
		[](const accelerator& acc)
		{
			return !acc.is_emulated &&
				acc.supports_double_precision &&
				!acc.has_display;
		});

	if (result != accs.end())
	{
		chosen_one = *(result);
	}

	std::wcout << chosen_one.description << std::endl;
	bool success = accelerator::set_default(chosen_one.device_path);
	return success;
}

float posRand() {
	return (rand() % 1000) / 10;
}

int main(int argc, char** argv)
{
	pick_accelerator();

	Texture_Manager::RegisterTexture("C:/Users/oscar/Programming/AMP-Craft/x64/Release/image.png");

	/*srand(50);

	for (int i = 0; i < 20; i++) {
		Triangle_Manager::RegisterTriangle(Triangle(Vec3(posRand(), posRand(), posRand()), Vec3(posRand(), posRand(), posRand()), Vec3(posRand(), posRand(), posRand()),Color(rand()%255,rand()%255,rand()%255)));
	}*/

	//Triangle_Manager::RegisterTriangle(Triangle(Vec3(0,0, 5), Vec3(1, 0, 5), Vec3(1, 1, 5), Color(255,0,0)));

	initWindow(argc, argv);
}