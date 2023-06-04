#pragma once

#include <string>

namespace GetGudSdk {

  namespace Values {
  const std::string g_Environment = "Environment";
  }

/**
 * LogLevel:
 *
 * What information will logger log?
 **/
enum class LogLevel : unsigned int { FATAL = 0, _ERROR, WARN_AND_ERROR, FULL };

/**
 * LogType:
 *
 * Type of each log message is one of the following
 **/
enum class LogType : unsigned int { DEBUG = 0, WARN, _ERROR, FATAL };

/**
 * Actions:
 *
 * Our primal 6, action types you can send to Getgud
 **/
enum class Actions : unsigned int {
  None = 0,
  Attack,
  Damage,
  Death,
  Heal,
  Position,
  Spawn
};

/**
 * PositionF:
 *
 * Defines the <x, y, z> position vector you send to us with Position and Spawn
 * actions
 **/
struct PositionF {
  float X = 0;
  float Y = 0;
  float Z = 0;
};

/**
 * RotationF:
 *
 * Defines the <pitch, roll> view vector you send to us with Position and Spawn
 * actions
 **/
struct RotationF {
  float Pitch = 0;
  float Roll = 0;
};

/**
 * ReportInfo:
 *
 * Report data that you send to Getgud in match our outside match
 **/
struct ReportInfo {
  std::string MatchGuid; //36 + SQL
  std::string ReporterName = "";  // SQL, size <=10.000
  int ReporterType = -1; // >= 1, < max
  int ReporterSubType = -1; // >= 1, < max
  std::string SuspectedPlayerGuid = "";  // 36 + SQL
  int TbType = -1; //>=1, <max
  int TbSubType = -1; //>=1, < max
  long long TbTimeEpoch = -1; //>=time.min, <= time.max
  int SuggestedToxicityScore = -1; //>=0, <=100
  long long ReportedTimeEpoch = -1; //>=time.min, <=time.max
};

/**
 * PlayerInfo:
 *
 * Player data you send to Getgud on UpdatePlayer
 **/
struct PlayerInfo {
  std::string PlayerGuid;//36 + SQL
  std::string PlayerNickname = "";  // SQL, size <=10.000
  std::string PlayerEmail = "";     // SQL, size <=10.000
  int PlayerRank = -1;//>=0, <=max
  long long PlayerJoinDateEpoch = -1;//>=time.min, <=time.max
};

/**
 * ChatMessageInfo:
 *
 * Chat message data you sent to Getgud from match
 **/
struct ChatMessageInfo {
  long long messageTimeEpoch = 0;//>=time.min, <=time.max
  std::string playerGuid;//36 + SQL
  std::string message;//SQL, size <=10.000
};

/**
 * BaseData:
 *
 **/
struct BaseData {
  Actions ActionType = Actions::None;
  long long ActionTimeEpoch = 0;
  std::string PlayerGuid;
  std::string MatchGuid;
};
}  // namespace GetGudSdk