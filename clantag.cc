#include "clantag.h"

void spandex::Clantag::Tick()
{
	Config config = engine_->GetConfig();

	if (config.clantag.enabled)
	{
		GlobalVars global_vars = engine_->GetGlobalVars();

		int current_length = (int)floorf(global_vars.m_flCurrentTime) % (config.clantag.clan_tag.size() * 2 + 1);

		if (last_length_ != current_length)
		{
			if (current_length > config.clantag.clan_tag.size())
			{
				engine_->SetClanTag(config.clantag.clan_tag.substr(0, config.clantag.clan_tag.size() * 2 - current_length).c_str());
			}
			else
			{
				engine_->SetClanTag(config.clantag.clan_tag.substr(0, current_length).c_str());
			}

			last_length_ = current_length;
		}
	}
}