// Midnight Madness Inc.


#include "AttributeInfo.h"

FMinervaAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag& AttributeTag, bool bLogNotFound) const
{
    for (const FMinervaAttributeInfo& Info : AttributeInformation)
    {
        if (Info.AttributeTag.MatchesTagExact(AttributeTag))
        {
            return Info;
        }
    }

    if (bLogNotFound) UE_LOG(LogTemp, Error, TEXT("Can't find Info for Attribute Tag [%s] on AttributeInfo [%s]."), *AttributeTag.ToString(), *GetNameSafe(this));

    return FMinervaAttributeInfo();
}
