#pragma once

#include "actions/AttackActionData.h"
#include "actions/DamageActionData.h"
#include "actions/DeathActionData.h"
#include "actions/HealActionData.h"
#include "actions/Helpers.h"
#include "actions/PositionActionData.h"
#include "actions/SpawnActionData.h"

#include <deque>

namespace GetGudSdk {

void Init();
std::string StartGame(int titleId,
                      std::string privateKey,
                      std::string serverGuid,
                      std::string gameMode);
std::string StartGame(std::string serverGuid, std::string gameMode);
std::string StartMatch(std::string gameGuid,
                       std::string matchMode,
                       std::string mapName);
bool MarkEndGame(std::string gameGuid);
bool SendInMatchReport(ReportInfo reportInfo);
bool SendChatMessage(std::string matchGuid, ChatMessageInfo messageInfo);
bool SendActions(std::deque<BaseActionData*> actions);
bool SendAction(BaseActionData* action);
bool SendAttackAction(std::string matchGuid,
                      long long actionTimeEpoch,
                      std::string playerGuid,
                      std::string weaponGuid);
bool SendDamageAction(std::string matchGuid,
                      long long actionTimeEpoch,
                      std::string playerGuid,
                      std::string victimPlayerGuid,
                      float damageDone,
                      std::string weaponGuid);
bool SendHealAction(std::string matchGuid,
                    long long actionTimeEpoch,
                    std::string playerGuid,
                    float healthGained);
bool SendSpawnAction(std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
                     std::string characterGuid,
                     int teamId,
                     float initialHealth,
                     PositionF position,
                     RotationF rotation);
bool SendDeathAction(std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid);
bool SendPositionAction(std::string matchGuid,
                        long long actionTimeEpoch,
                        std::string playerGuid,
                        PositionF position,
                        RotationF rotation);

bool SendReports(int titleId,
                 std::string privateKey,
                 std::deque<ReportInfo>& reports);
bool SendReports(std::deque<ReportInfo>& reports);
bool UpdatePlayers(int titleId,
                   std::string privateKey,
                   std::deque<PlayerInfo>& players);
bool UpdatePlayers(std::deque<PlayerInfo>& players);
void Dispose();

}  // namespace GetGudSdk