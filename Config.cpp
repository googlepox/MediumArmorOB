#include "MediumArmor.h"
#include "Config.h"

#include "OBSEKeywords/KeywordAPI.h"

#include "obse/GameAPI.h"
#include "obse/GameData.h"
#include "obse/GameForms.h"
#include "obse/GameObjects.h"
#include "obse/GameExtraData.h"

#include <algorithm>
#include <cmath>
#include <obse/ModTable.h>
#include <EditorIDMapper/EditorIDMapperAPI.h>

#include <boost/algorithm/string.hpp>

namespace MediumArmor
{
    float kARMultiplier = 1.0f;
    float kARFlat = 0.0f;

    float kPerkNoviceDamageMult = 1.5f;
    float kPerkApprenticeDamageMult = 1.0f;
    float kPerkJourneymanDamageMult = 0.5f;

    float kPerkExpertEncumbranceMult = 0.5f;
    float kPerkMasterEncumbranceMult = 0.0f;

    float kPerkMasterARBonus = 1.25f;
    float kFullMediumSetCount = 5.0f;

    float kXPPerHit = 1.0f;
    float kXPSkillFactor = 0.5f;

    float kMediumArmorSkill = 5.0f;

    std::vector<std::string> MA_MATERIALS = {};

    std::unordered_map<std::string, float*> configMap =
    {
        { "kARMultiplier", &kARMultiplier },
        { "kARFlat", &kARFlat },
        { "kPerkNoviceDamageMult", &kPerkNoviceDamageMult },
        { "kPerkApprenticeDamageMult", &kPerkApprenticeDamageMult },
        { "kPerkJourneymanDamageMult", &kPerkJourneymanDamageMult },
        { "kPerkExpertEncumbranceMult", &kPerkExpertEncumbranceMult },
        { "kPerkMasterEncumbranceMult", &kPerkMasterEncumbranceMult },
        { "kPerkMasterARBonus", &kPerkMasterARBonus },
        { "kFullMediumSetCount", &kFullMediumSetCount },
        { "kXPPerHit", &kXPPerHit },
        { "kXPSkillFactor", &kXPSkillFactor },
    };

    void LoadConfig()
    {
        std::ifstream file("Data\\OBSE\\Plugins\\MediumArmor\\Config.ini");
        if (!file.is_open())
        {
            _MESSAGE("Config.ini not found");
            return;
        }

        std::string line;
        enum Section { NONE, CONFIG, MATERIALS } section = NONE;

        while (std::getline(file, line))
        {
            if (line.empty() || line[0] == ';')
                continue;

            if (line[0] == '[')
            {
                if (line == "[Config]") section = CONFIG;
                else if (line == "[Materials]") section = MATERIALS;
                else section = NONE;
                continue;
            }

            std::stringstream ss(line);

            if (section == CONFIG)
            {
                std::string key, value;

                std::getline(ss, key, ',');
                std::getline(ss, value);

                float f = std::stof(value);

                auto it = configMap.find(key);
                if (it != configMap.end())
                {
                    *it->second = f;
                }
            }
            else if (section == MATERIALS)
            {
                MA_MATERIALS.clear();

                std::string material;

                while (std::getline(ss, material, ','))
                {
                    boost::algorithm::trim(material);
                    boost::algorithm::to_lower(material);

                    if (!material.empty())
                    {
                        MA_MATERIALS.push_back(material);
                    }
                }
            }
        }
    }
}