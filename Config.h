#pragma once

#include <string>
#include <vector>
#include <unordered_map>

namespace MediumArmor
{
    constexpr const char* kPluginName = "MediumArmor";
    constexpr unsigned kPluginVersion = 1;
    constexpr unsigned kOBSEVersionRequired = 21;
    constexpr const char* kMediumArmorKeyword = "MediumArmor";

    extern float kARMultiplier;
    extern float kARFlat;

    extern float kPerkNoviceDamageMult;
    extern float kPerkApprenticeDamageMult;
    extern float kPerkJourneymanDamageMult;

    extern float kPerkExpertEncumbranceMult;
    extern float kPerkMasterEncumbranceMult;

    extern float kPerkMasterARBonus;
    extern float kFullMediumSetCount;

    extern float kXPPerHit;
    extern float kXPSkillFactor;

    extern float kMediumArmorSkill;

    extern std::vector<std::string> MA_MATERIALS;

    extern std::unordered_map<std::string, float*> configMap;

    constexpr unsigned kCoSaveChunkID = 'MARM';

    void LoadConfig();
}