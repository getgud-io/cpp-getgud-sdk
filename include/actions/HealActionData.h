#pragma once
#include "BaseActionData.h"

namespace GetGudSdk {
class HealActionData : public BaseActionData {
  float m_healthGained = 0;

 public:
  HealActionData(std::string matchGuid,
                 long long actionTimeEpoch,
                 std::string playerGuid,
                 float healthGained);
  HealActionData(const HealActionData& data);
  HealActionData() = delete;
  ~HealActionData() override;
  bool IsValid() override;
  std::string ToString() override;
  std::string ToStringMeta() override;
  HealActionData* Clone() override;
};
}  // namespace GetGudSdk