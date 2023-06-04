#pragma once

#include "BaseActionData.h"

namespace GetGudSdk {
class DeathActionData : public BaseActionData {
 public:
  DeathActionData(std::string matchGuid,
                  long long actionTimeEpoch,
                  std::string playerGuid);
  DeathActionData(const DeathActionData& data);
  DeathActionData() = delete;
  ~DeathActionData() override;
  bool IsValid() override;
  std::string ToString() override;
  std::string ToStringMeta() override;
  DeathActionData* Clone() override;
};
}  // namespace GetGudSdk