#include <GetGudSdk.h>
#include <iostream>

#include <chrono>
#include <random>
#include <thread>

std::random_device
    rdMain;  // a system based device that generates data randomly
std::uniform_int_distribution<int> actionTypeDist(0, 5);

GetGudSdk::BaseActionData* MakeRandomAction(std::string matchGuid,
                                            long long curTimeEpoch) {
  int actionType = actionTypeDist(rdMain);

  GetGudSdk::BaseActionData* outAction = nullptr;
  switch (actionType) {
    case 0:
      outAction = new GetGudSdk::AttackActionData(matchGuid, curTimeEpoch,
                                                  "player-5", "abc");
      break;
    case 1:
      outAction = new GetGudSdk::DamageActionData(
          matchGuid, curTimeEpoch, "player-5", "player-0", 50.001421f, "glc");
      break;
    case 2:
      outAction =
          new GetGudSdk::DeathActionData(matchGuid, curTimeEpoch, "player-0");
      break;
    case 3:
      outAction = new GetGudSdk::HealActionData(matchGuid, curTimeEpoch,
                                                "player-5", 20.32100F);
      break;
    case 4:
      outAction = new GetGudSdk::PositionActionData(
          matchGuid, curTimeEpoch, "player-5",
          GetGudSdk::PositionF{20.32000f, 50.001421f, 0.30021f},
          GetGudSdk::RotationF{10, 20, 30});
      break;
    case 5:
        outAction = new GetGudSdk::SpawnActionData(
            matchGuid, curTimeEpoch, "player-10", "ttr", 0, 100.f,
            GetGudSdk::PositionF{1, 2, 3}, GetGudSdk::RotationF{10, 20, 30});
      break;
  }

  std::vector < GetGudSdk::BaseActionData*> actionsToSend{
new GetGudSdk::SpawnActionData(
            matchGuid, curTimeEpoch, "player-10", "ttr", 0, 100.f,
            GetGudSdk::PositionF{1, 2, 3}, GetGudSdk::RotationF{10, 20, 30}),

new GetGudSdk::PositionActionData(
          matchGuid, curTimeEpoch, "player-5",
          GetGudSdk::PositionF{20.32000f, 50.001421f, 0.30021f},
          GetGudSdk::RotationF{10, 20, 30})
  };

  return outAction;
}

std::deque<GetGudSdk::BaseActionData*> CreateActionsVector(
    std::string matchGuid,
    int actionsAmount) {
  std::deque<GetGudSdk::BaseActionData*> outVector;
  long long actionsEpochTime = 1684059337532;
  for (int actionNum = 0; actionNum < actionsAmount; actionNum++) {
    GetGudSdk::BaseActionData* outAction =
        MakeRandomAction(matchGuid, actionsEpochTime);
    actionsEpochTime += 2;
    outVector.push_back(outAction);
  }
  return outVector;
}

void CreateReports(std::string matchGuid, int numberOfReports) {
  std::deque<GetGudSdk::ReportInfo> reports;
  std::string privateKey = "private_key";
  for (int gameNum = 0; gameNum < numberOfReports; gameNum++) {
    GetGudSdk::ReportInfo reportInfo;
    reportInfo.MatchGuid = matchGuid;
    reportInfo.ReportedTimeEpoch = 1684059337532;
    reportInfo.ReporterName = "reporter_name";
    reportInfo.ReporterSubType = GetGudSdk::ReporterSubtype::Custom;
    reportInfo.ReporterType = GetGudSdk::ReporterType::Custom;
    reportInfo.SuggestedToxicityScore = 100;
    reportInfo.SuspectedPlayerGuid = "suspected_player_guid";
    reportInfo.TbTimeEpoch = 1684059337532;
    reportInfo.TbType = GetGudSdk::TbType::Laghack;

    reports.push_back(reportInfo);
  }

  GetGudSdk::SendReports(28, privateKey, reports);
}

void CreatePlayerUpdates(int numberOfPlayerUpdates) {
  std::deque<GetGudSdk::PlayerInfo> playerInfos;
  std::string privateKey = "private_key";
  for (int playerUpdateNum = 0; playerUpdateNum < numberOfPlayerUpdates;
       playerUpdateNum++) {
    GetGudSdk::PlayerInfo playerInfo;
    playerInfo.PlayerGuid = "player-5";
    playerInfo.PlayerNickname = "test";
    playerInfo.PlayerEmail = "test@test.com";
    playerInfo.PlayerRank = 10;
    playerInfo.PlayerJoinDateEpoch = 1684059337532;
    playerInfos.push_back(playerInfo);
  }

  GetGudSdk::UpdatePlayers(28, privateKey, playerInfos);
}

int main() {
  // Initialize the SDK:
  GetGudSdk::Init();

  std::string serverGuid = "us-west-1";
  std::string gameMode = "deathmatch";

  // Start a Game:
  std::string gameGuid = GetGudSdk::StartGame(serverGuid,  // serverGuid
                                              gameMode     // gameMode
  );

  std::string matchGuid = GetGudSdk::StartMatch(gameGuid,
                                                "Knives-only",  // matchMode
                                                "de-dust"       // mapName
  );
  // Once you have a match, you can send Actions to it. Let's create a vector of
  // Actions and send it to the match:
  int actionsAmount = 1000;
  int reportsAmount = 3;
  int playersAmount = 10;
  std::deque<GetGudSdk::BaseActionData*> actionsVector =
      CreateActionsVector(matchGuid, actionsAmount);
  // Send the actions to the SDK:
  GetGudSdk::SendActions(actionsVector);

  // Delete the pointers and clear the vector:
  for (auto* sentAction : actionsVector)
    delete sentAction;
  actionsVector.clear();

  // Send Reports to the match:
  CreateReports(matchGuid, reportsAmount);
  // Send Players to the SDK:
  CreatePlayerUpdates(playersAmount);

  // End a game (All Game's Matches will close as well):
  bool gameEnded = GetGudSdk::MarkEndGame(gameGuid);

  // Wait until packets will be sent
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  // Close and Dispose of the SDK:
  GetGudSdk::Dispose();

  // Wait until the threads will be stopped
  std::this_thread::sleep_for(std::chrono::milliseconds(3000));

  system("pause");

  return 0;
}