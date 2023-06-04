#pragma once
#include "BaseActionData.h"

namespace GetGudSdk {
unsigned int GetPositionActionSize();

class PositionActionData : public BaseActionData {
  PositionF m_position;
  RotationF m_rotation;
  unsigned int m_size = 0;

 public:
  PositionActionData(std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
                     PositionF position,
                     RotationF rotation);
  PositionActionData(const PositionActionData& data);
  PositionActionData() = delete;
  ~PositionActionData() override;
  bool IsValid() override;
  std::string ToString() override;
  std::string ToStringMeta() override;
  PositionActionData* Clone() override;
};
}  // namespace GetGudSdk