#include <iostream>
#include "Window.h"

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

int main(int argc, char** argv)
{
	pick_accelerator();/*

	array_view<Cube, 3> world_arr(chunk_height, chunk_length, chunk_width, Renderer::world.cubeSet);

	Cube c;
	c.type = Solid;
	SetCube(2, 2, 8, world_arr, c);
	SetCube(4, 2, 8, world_arr, c);
	SetCube(6, 2, 8, world_arr, c);

	SetCube(1, 5, 8, world_arr, c);
	SetCube(3, 5, 8, world_arr, c);
	SetCube(5, 5, 8, world_arr, c);*/

	initWindow(argc, argv);
}