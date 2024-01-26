#include <GetgudSDK.h>
#include <iostream>

#include <chrono>
#include <random>
#include <thread>

std::random_device
rdMain;  // a system based device that generates data randomly
std::uniform_int_distribution<int> actionTypeDist(0, 5);

GetgudSDK::BaseActionData* MakeRandomAction(std::string matchGuid,
    long long curTimeEpoch) {
    int actionType = actionTypeDist(rdMain);

    GetgudSDK::BaseActionData* outAction = nullptr;
    switch (actionType) {
    case 0:
        outAction = new GetgudSDK::AttackActionData(matchGuid, curTimeEpoch,
            "player-5", "abc");
        break;
    case 1:
        outAction = new GetgudSDK::DamageActionData(
            matchGuid, curTimeEpoch, "player-5", "player-0", 50.001421f, "glc");
        break;
    case 2:
        outAction =
            new GetgudSDK::DeathActionData(matchGuid, curTimeEpoch, "player-0", "player-1");
        break;
    case 3:
        outAction = new GetgudSDK::HealActionData(matchGuid, curTimeEpoch,
            ":plkayer-5", 20.32100F);
        break;
    case 4:
        outAction = new GetgudSDK::PositionActionData(
            matchGuid, curTimeEpoch, "player-5",
            GetgudSDK::PositionF{20.32000f, 50.001421f, 0.30021f},
            GetgudSDK::RotationF{10, 20});
        break;
    case 5:
        outAction = new GetgudSDK::SpawnActionData(
            matchGuid, curTimeEpoch, "player-10", "ttr", 0, 100.f,
            GetgudSDK::PositionF{1, 2, 3}, GetgudSDK::RotationF{10, 20});
        break;
    }

    return outAction;
}

std::deque<GetgudSDK::BaseActionData*> CreateActionsVector(
    std::string matchGuid,
    int actionsAmount) {
    std::deque<GetgudSDK::BaseActionData*> outVector;
    long long actionsEpochTime = 1684059337532;
    for (int actionNum = 0; actionNum < actionsAmount; actionNum++) {
        GetgudSDK::BaseActionData* outAction =
            MakeRandomAction(matchGuid, actionsEpochTime);
        actionsEpochTime += 2;
        outVector.push_back(outAction);
    }
    return outVector;
}

void CreateReports(std::string matchGuid, int numberOfReports) {
    std::deque<GetgudSDK::ReportInfo> reports;
    std::string privateKey = "41e99370-b12f-11ee-89f0-4b4e9fccc950";
    for (int gameNum = 0; gameNum < numberOfReports; gameNum++) {
        GetgudSDK::ReportInfo reportInfo;
        reportInfo.MatchGuid = matchGuid;
        reportInfo.ReportedTimeEpoch = 1684059337532;
        reportInfo.ReporterName = "reporter_name";
        reportInfo.ReporterSubType = GetgudSDK::ReporterSubtype::VAC;
        reportInfo.ReporterType = GetgudSDK::ReporterType::AntiCheat;
        reportInfo.SuggestedToxicityScore = 100;
        reportInfo.SuspectedPlayerGuid = "suspected_player_guid";
        reportInfo.TbTimeEpoch = 1684059337532;
        reportInfo.TbType = GetgudSDK::TbType::Aimbot;

        reports.push_back(reportInfo);
    }

    GetgudSDK::SendReports(132, privateKey, reports);
}

void CreatePlayerUpdates(int numberOfPlayerUpdates) {
    std::deque<GetgudSDK::PlayerInfo> playerInfos;
    std::string privateKey = "41e99370-b12f-11ee-89f0-4b4e9fccc950";
    for (int playerUpdateNum = 0; playerUpdateNum < numberOfPlayerUpdates;
        playerUpdateNum++) {
        GetgudSDK::PlayerInfo playerInfo;
        playerInfo.PlayerGuid = "player-5";
        playerInfo.PlayerNickname = "test";
        playerInfo.PlayerEmail = "test@test.com";
        playerInfo.PlayerRank = 10;
        playerInfo.PlayerJoinDateEpoch = 1684059337532;
        playerInfos.push_back(playerInfo);
    }

    GetgudSDK::UpdatePlayers(132, privateKey, playerInfos);
}

int main() {
    // Initialize the SDK:
    GetgudSDK::Init();

    std::string serverGuid = "us-west-1";
    std::string gameMode = "deathmatch";
    std::string serverLocation = "UK";

    // Start a Game:
    std::string gameGuid = GetgudSDK::StartGame(132,
        "41e99370-b12f-11ee-89f0-4b4e9fccc950",
        serverGuid,  // serverGuid
        gameMode,     // gameMode
        serverLocation
    );

    std::string matchGuid = GetgudSDK::StartMatch(gameGuid,
        "Knives-only",  // matchMode
        "de-dust"       // mapName
    );
    // Once you have a match, you can send Actions to it. Let's create a vector of
    // Actions and send it to the match:
    int actionsAmount = 100;
    int reportsAmount = 3;
    int playersAmount = 10;
    std::deque<GetgudSDK::BaseActionData*> actionsVector =
        CreateActionsVector(matchGuid, actionsAmount);
    // Send the actions to the SDK:
    GetgudSDK::SendActions(actionsVector);

    // Delete the pointers and clear the vector:
    for (auto* sentAction : actionsVector)
        delete sentAction;
    actionsVector.clear();

    // Send Reports to the match:
    CreateReports(matchGuid, reportsAmount);
    // Send Players to the SDK:
    CreatePlayerUpdates(playersAmount);

    // End a game (All Game's Matches will close as well):
    bool gameEnded = GetgudSDK::MarkEndGame(gameGuid);

    // Wait until packets will be sent
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    // Close and Dispose of the SDK:
    GetgudSDK::Dispose();

    // Wait until the threads will be stopped
    std::this_thread::sleep_for(std::chrono::milliseconds(3000));

    system("pause");

    return 0;
}
