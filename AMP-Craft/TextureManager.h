#ifndef __TextureManager
#define __TextureManager
#include <amp.h>
using namespace concurrency;

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include "Color.h"

#define max_textures 10

#define texture_w_h 100

namespace Texture_Manager {

	unsigned int active_textures = 0;
	array_view<Color, 3> texture_arr(max_textures,texture_w_h, texture_w_h);

	void RegisterTexture(const char* file) {
		int x, y, channels;
		
		Color* image = (Color*)stbi_load(file, &x, &y, &channels, STBI_rgb_alpha);

		array_view<Color, 3> _text_arr = texture_arr;
		array_view<Color, 2> image_arr(y,x,image);

		unsigned int text_id = active_textures;

		parallel_for_each(
			image_arr.extent,
			[=](index<2>idx)restrict(amp) {
				_text_arr[text_id][idx] = image_arr[idx];
			}
		);

		texture_arr.synchronize();
		active_textures++;
	}

}

#endif // !__TextureManager
