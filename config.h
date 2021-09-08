#ifndef SPANDEX_ENGINE_CONFIG_H_
#define SPANDEX_ENGINE_CONFIG_H_

#include <string>

namespace spandex
{
	struct Config
	{
		struct
		{
			bool enabled = true;
			int minimum_error = 0;
			int maximum_error = 0;
		} bunnyhop;

		struct
		{
			bool enabled = true;
			float fov = 2.0f;
			bool while_firing = true;
			float smoothing = 1.0f;
		} aimbot;

		struct
		{
			bool enabled = false;
			float strength = 0.8f;
		} faststop;

		struct
		{
			bool enabled = false;
			std::string clan_tag = "spandex";
		} clantag;

		struct
		{
			bool enabled = true;
			bool head_box = true;
		} esp;
	};
}

#endif