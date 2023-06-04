#pragma once
#include "BaseActionData.h"

namespace GetGudSdk {
class DamageActionData : public BaseActionData {
  std::string m_weaponGuid;
  std::string m_victimPlayerGuid;
  float m_damageDone = 0;

 public:
  DamageActionData(std::string matchGuid,
                   long long actionTimeEpoch,
                   std::string playerGuid,
                   std::string victimPlayerGuid,
                   float damageDone,
                   std::string weaponGuid);
  DamageActionData(const DamageActionData& data);
  DamageActionData() = delete;
  ~DamageActionData() override;
  bool IsValid() override;
  std::string ToString() override;
  std::string ToStringMeta() override;
  DamageActionData* Clone() override;
};
}  // namespace GetGudSdk