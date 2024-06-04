// Midnight Madness Inc.


#include "AbilityInfo.h"
#include "Minerva/MinervaLogChannels.h"

FMinervaAbilityInfo UAbilityInfo::FindAbilityInfoForTag(const FGameplayTag& AbilityTag, bool bLogNotFound) const
{
    for (const FMinervaAbilityInfo& Info : AbilityInformation)
    {
        if (Info.AbilityTag.MatchesTagExact(AbilityTag))
        {
            return Info;
        }
    }

    if (bLogNotFound) UE_LOG(LogMinerva, Error, TEXT("Can't find Info for Attribute Tag [%s] on AttributeInfo [%s]."), *AbilityTag.ToString(), *GetNameSafe(this));

    return FMinervaAbilityInfo();
}
