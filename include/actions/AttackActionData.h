#pragma once
#include "BaseActionData.h"

namespace GetGudSdk {
class AttackActionData : public BaseActionData {
  std::string m_weaponGuid;

 public:
  AttackActionData(std::string matchGuid,
                   long long actionTimeEpoch,
                   std::string playerGuid,
                   std::string weaponGuid);
  AttackActionData(const AttackActionData& data);
  AttackActionData() = delete;
  ~AttackActionData() override;
  bool IsValid() override;
  std::string ToString() override;
  std::string ToStringMeta() override;
  AttackActionData* Clone() override;
};
}  // namespace GetGudSdk