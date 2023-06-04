#pragma once
#include "BaseActionData.h"

#include <vector>

namespace GetGudSdk {
class SpawnActionData : public BaseActionData {
  PositionF m_position;
  RotationF m_rotation;
  float m_initialHealth = 0;
  int m_teamId = 0;
  std::string m_characterGuid;

 public:
  SpawnActionData(std::string matchGuid,
                  long long actionTimeEpoch,
                  std::string playerGuid,
                  std::string characterGuid,
                  int teamId,
                  float initialHealth,
                  PositionF position,
                  RotationF rotation);
  SpawnActionData(const SpawnActionData& data);
  SpawnActionData() = delete;
  ~SpawnActionData() override;
  bool IsValid() override;
  std::string ToString() override;
  std::string ToStringMeta() override;
  SpawnActionData* Clone() override;
};
}  // namespace GetGudSdk