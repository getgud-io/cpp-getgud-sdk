#pragma once

#if defined(__cplusplus) && defined(_WIN32)
#ifndef GETGUDSDK_EXPORTS
#define GETGUDSDK_API __declspec(dllexport)
#else
#define GETGUDSDK_API __declspec(dllimport)
#endif
#else // not win32
#define GETGUDSDK_API
#endif

#include "actions/AttackActionData.h"
#include "actions/DamageActionData.h"
#include "actions/DeathActionData.h"
#include "actions/HealActionData.h"
#include "actions/Helpers.h"
#include "actions/PositionActionData.h"
#include "actions/SpawnActionData.h"
#include "actions/AffectActionData.h"

#include <deque>

namespace GetGudSdk {

GETGUDSDK_API bool Init();
GETGUDSDK_API std::string StartGame(int titleId,
                      std::string privateKey,
                      std::string serverGuid,
                      std::string gameMode,
                      std::string serverLocation);
GETGUDSDK_API std::string StartGame(std::string serverGuid, std::string gameMode, std::string serverLocation);
GETGUDSDK_API std::string StartMatch(std::string gameGuid,
                       std::string matchMode,
                       std::string mapName);
GETGUDSDK_API bool MarkEndGame(std::string gameGuid);
GETGUDSDK_API bool SendInMatchReport(ReportInfo reportInfo);
GETGUDSDK_API bool SendChatMessage(std::string matchGuid, ChatMessageInfo messageInfo);
GETGUDSDK_API bool SendActions(std::deque<BaseActionData*> actions);
GETGUDSDK_API bool SendAction(BaseActionData* action);
GETGUDSDK_API bool SendAffectAction(std::string matchGuid,
                      long long actionTimeEpoch,
                      std::string affectGuid,
                      std::string playerGuid,
                      AffectState affectState);
GETGUDSDK_API bool SendAttackAction(std::string matchGuid,
                      long long actionTimeEpoch,
                      std::string playerGuid,
                      std::string weaponGuid);
GETGUDSDK_API bool SendDamageAction(std::string matchGuid,
                      long long actionTimeEpoch,
                      std::string playerGuid,
                      std::string victimPlayerGuid,
                      float damageDone,
                      std::string weaponGuid);
GETGUDSDK_API bool SendHealAction(std::string matchGuid,
                    long long actionTimeEpoch,
                    std::string playerGuid,
                    float healthGained);
GETGUDSDK_API bool SendSpawnAction(std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
                     std::string characterGuid,
                     int teamId,
                     float initialHealth,
                     PositionF position,
                     RotationF rotation);
GETGUDSDK_API bool SendDeathAction(std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
                     std::string attackerGuid);
GETGUDSDK_API bool SendPositionAction(std::string matchGuid,
                        long long actionTimeEpoch,
                        std::string playerGuid,
                        PositionF position,
                        RotationF rotation);

GETGUDSDK_API bool SendReports(int titleId,
                 std::string privateKey,
                 std::deque<ReportInfo>& reports);
GETGUDSDK_API bool SendReports(std::deque<ReportInfo>& reports);
GETGUDSDK_API bool UpdatePlayers(int titleId,
                   std::string privateKey,
                   std::deque<PlayerInfo>& players);
GETGUDSDK_API bool UpdatePlayers(std::deque<PlayerInfo>& players);
GETGUDSDK_API void Dispose();

}  // namespace GetGudSdk