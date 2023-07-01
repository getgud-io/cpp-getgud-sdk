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
  enum class AffectState : int
  {
    Attach, Activate, Deactivate, Detach
  };

class AffectActionData : public BaseActionData {
  std::string m_affectGuid;
  AffectState m_affectState;

 public:
   GETGUDSDK_API AffectActionData(std::string matchGuid,
                   long long actionTimeEpoch,
                   std::string playerGuid,
                   std::string affectGuid,
                   AffectState affectState);
  GETGUDSDK_API AffectActionData(const AffectActionData& data);
  GETGUDSDK_API AffectActionData() = delete;
  GETGUDSDK_API ~AffectActionData() override;
  GETGUDSDK_API bool IsValid() override;
  GETGUDSDK_API std::string ToString() override;
  GETGUDSDK_API std::string ToStringMeta() override;
  GETGUDSDK_API AffectActionData* Clone() override;
};
}  // namespace GetGudSdk