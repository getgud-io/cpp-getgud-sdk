#if defined(__cplusplus) && defined(_WIN32)
#ifndef GETGUDSDK_EXPORTS
#define GETGUDSDK_API __declspec(dllexport)
#else
#define GETGUDSDK_API __declspec(dllimport)
#endif
#else // not win32
#define GETGUDSDK_API
#endif

enum Actions { None = -1, Affect, Attack, Damage, Death, Heal, Position, Spawn };
enum AffectState { Attach, Activate, Deactivate, Detach };

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

struct PlayerTransactions
{
    char* TransactionGuid;
    int TransactionGuidSize;
    char* TransactionName;
    int TransactionNameSize;
    long long TransactionDateEpoch;
    float TransactionValueUSD;
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
  char* serverLocation;
  int serverLocationSize;
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
  char* playerSuspectScore;
  int playerSuspectScoreSize;
  char* playerReputation;
  int playerReputationSize;
  char* playerStatus;
  int playerStatusSize;
  char* PlayerCampaign;
  int PlayerCampaignSize;
  char* playerNotes;
  int playerNotesSize;
  char* playerDevice;
  int playerDeviceSize;
  char* playerOS;
  int playerOSSize;
  int playerAge;
  char* playerGender;
  int playerGenderSize;
  char* playerLocation;
  int playerLocationSize;
  struct PlayerTransactions* transactions;
  int transactionsSize;
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
  long long tbTimeEpoch;
  int suggestedToxicityScore;
  long long reportedTimeEpoch;
};

#ifdef __cplusplus
extern "C" {
#endif

/**
* Init:
*
* Init Getgud SDK
**/
GETGUDSDK_API int init();

/**
 * StartGame:
 *
 * Start new game
 * Returns size
 **/
GETGUDSDK_API int StartGame(struct StartGameInfo gameInfo, char* gameGuidOut);

/**
 * Start match:
 *
 * Start a new match for an existing game
 **/
GETGUDSDK_API int StartMatch(struct StartMatchInfo matchInfo, char* matchGuidOut);

/**
 * MarkEndGame:
 *
 * Mark started game as finished
 **/
GETGUDSDK_API int MarkEndGame(char* gameGuid, int guidSize);

/**
 * SendAffectAction:
 *
 **/
GETGUDSDK_API int SendAffectAction(struct BaseActionData baseData,
  char* affectGuid,
  int affectGuidSize,
  enum AffectState affectState);

/**
 * SendAttackAction:
 *
 **/
GETGUDSDK_API int SendAttackAction(struct BaseActionData baseData,
                     char* weaponGuid,
                     int weaponGuidSize);

/**
 * SendDamageAction:
 *
 **/
GETGUDSDK_API int SendDamageAction(struct BaseActionData baseData,
                     char* victimPlayerGuid,
                     int victimPlayerGuidSize,
                     float damageDone,
                     char* weaponGuid,
                     int weaponGuidSize);

/**
 * SendHealAction:
 *
 **/
GETGUDSDK_API int SendHealAction(struct BaseActionData baseData, float healthGained);

/**
 * SendSpawnAction:
 *
 **/
GETGUDSDK_API int SendSpawnAction(struct BaseActionData baseData,
                    char* characterGuid,
                    int characterGuidSize,
                    int teamId,
                    float initialHealth,
                    struct PositionF position,
                    struct RotationF rotation);

/**
 * SendDeathAction:
 *
 **/
GETGUDSDK_API int SendDeathAction(struct BaseActionData baseData,
                                  char* attackerGuid,
                                  int attackerGuidSize);

/**
 * SendPositionAction:
 *
 **/
GETGUDSDK_API int SendPositionAction(struct BaseActionData baseData,
                       struct PositionF position,
                       struct RotationF rotation);
/**
 * SendInMatchReport:
 *
 * Send a report which belongs to specifc match which is now live
 **/
GETGUDSDK_API int SendInMatchReport(struct ReportInfo reportInfo);

/**
 * SendChatMessage:
 *
 *  Send a message which belongs to specifc match which is now live
 **/
GETGUDSDK_API int SendChatMessage(struct ChatMessageInfo messageInfo);

/**
 * SendReport:
 *
 * Send report which are outside of the live match
 **/
GETGUDSDK_API int SendReport(int titleId,
  char* privateKey, int privateKeySize, struct ReportInfo report);

/**
 * UpdatePlayer:
 *
 * Update player info outside of the live match
 **/
GETGUDSDK_API int UpdatePlayer(int titleId,
  char* privateKey, int privateKeySize, struct PlayerInfo player);

/**
 * Dispose:
 *
 **/
GETGUDSDK_API void dispose();

#ifdef __cplusplus
}
#endif