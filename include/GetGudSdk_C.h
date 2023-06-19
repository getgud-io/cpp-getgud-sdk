#if defined(__cplusplus) && defined(_WIN32)
#ifndef GETGUDSDK_EXPORTS
#define GETGUDSDK_API __declspec(dllexport)
#else
#define GETGUDSDK_API __declspec(dllimport)
#endif
#else // not win32
#define GETGUDSDK_API
#endif

enum Actions { None, Attack, Damage, Death, Heal, Position, Spawn };

struct PositionF {
  float X;
  float Y;
  float Z;
};

struct RotationF {
  float Yaw;
  float Pitch;
  float Roll;
};
struct BaseActionData {
  long long actionTimeEpoch;
  char* matchGuid;
  int matchGuidSize;
  char* playerGuid;
  int playerGuidSize;
};
struct StartGameInfo {
  int titleId;
  char* privateKey;
  int privateKeySize;
  char* serverGuid;
  int serverGuidSize;
  char* gameMode;
  int gameModeSize;
};

struct StartMatchInfo {
  char* gameGuid;
  int gameGuidSize;
  char* matchMode;
  int matchModeSize;
  char* mapName;
  int mapNameSize;
};

struct ChatMessageInfo {
  long long messageTimeEpoch;
  char* matchGuid;
  int matchGuidSize;
  char* playerGuid;
  int playerGuidSize;
  char* message;
  int messageSize;
};

struct PlayerInfo {
  char* playerGuid;
  int playerGuidSize;
  char* playerNickname;
  int playerNicknameSize;
  char* playerEmail;
  int playerEmailSize;
  int playerRank;
  long long playerJoinDateEpoch;
};

struct ReportInfo {
  char* matchGuid;
  int matchGuidSize;
  char* reporterName;
  int reporterNameSize;
  int reporterType;
  int reporterSubType;
  char* suspectedPlayerGuid;
  int suspectedPlayerGuidSize;
  int tbType;
  int tbSubType;
  long long tbTimeEpoch;
  int suggestedToxicityScore;
  long long reportedTimeEpoch;
};

#ifdef __cplusplus
extern "C" {
#endif

GETGUDSDK_API int init();
GETGUDSDK_API int StartGame(struct StartGameInfo gameInfo, char* gameGuidOut);
GETGUDSDK_API int StartMatch(struct StartMatchInfo matchInfo, char* matchGuidOut);
GETGUDSDK_API int MarkEndGame(char* gameGuid, int guidSize);
GETGUDSDK_API int SendInMatchReport(struct ReportInfo reportInfo);
GETGUDSDK_API int SendChatMessage(struct ChatMessageInfo messageInfo);
GETGUDSDK_API int SendAttackAction(struct BaseActionData baseData,
                     char* weaponGuid,
                     int weaponGuidSize);
GETGUDSDK_API int SendDamageAction(struct BaseActionData baseData,
                     char* victimPlayerGuid,
                     int victimPlayerGuidSize,
                     float damageDone,
                     char* weaponGuid,
                     int weaponGuidSize);
GETGUDSDK_API int SendHealAction(struct BaseActionData baseData, float healthGained);
GETGUDSDK_API int SendSpawnAction(struct BaseActionData baseData,
                    char* characterGuid,
                    int characterGuidSize,
                    int teamId,
                    float initialHealth,
                    struct PositionF position,
                    struct RotationF rotation);
GETGUDSDK_API int SendDeathAction(struct BaseActionData baseData);
GETGUDSDK_API int SendPositionAction(struct BaseActionData baseData,
                       struct PositionF position,
                       struct RotationF rotation);
GETGUDSDK_API void dispose();

#ifdef __cplusplus
}
#endif