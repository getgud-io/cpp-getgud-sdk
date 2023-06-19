#pragma once

#include "BaseActionData.h"

#if defined(__cplusplus) && defined(_WIN32)
#ifndef GETGUDSDK_EXPORTS
#define GETGUDSDK_API __declspec(dllexport)
#else
#define GETGUDSDK_API __declspec(dllimport)
#endif
#else
#define GETGUDSDK_API
#endif

namespace GetGudSdk {
class DeathActionData : public BaseActionData {
 public:
   GETGUDSDK_API DeathActionData(std::string matchGuid,
                  long long actionTimeEpoch,
                  std::string playerGuid);
  GETGUDSDK_API DeathActionData(const DeathActionData& data);
  GETGUDSDK_API DeathActionData() = delete;
  GETGUDSDK_API ~DeathActionData() override;
  GETGUDSDK_API bool IsValid() override;
  GETGUDSDK_API std::string ToString() override;
  GETGUDSDK_API std::string ToStringMeta() override;
  GETGUDSDK_API DeathActionData* Clone() override;
};
}  // namespace GetGudSdk