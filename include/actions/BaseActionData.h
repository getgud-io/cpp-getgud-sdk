#pragma once

#include <map>
#include <string>

#include "Helpers.h"

namespace GetGudSdk {
unsigned int GetEmptyActionSize();

class BaseActionData {
 public:
  Actions m_actionType = Actions::None;
  long long m_actionTimeEpoch = 0;
  std::string m_playerGuid;
  std::string m_matchGuid;
  bool m_isEmpty = false;

 public:
  BaseActionData(BaseData data, bool _isEmpty = false);
  BaseActionData(const BaseActionData& data);
  BaseActionData() = delete;
  virtual ~BaseActionData();
  virtual bool IsValid();
  virtual std::string ToString();
  virtual std::string ToStringMeta();
  virtual BaseActionData* Clone();
};
}  // namespace GetGudSdk