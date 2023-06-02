# GetGud C++ SDK
Getgud C++ SDK allows you to integrate your game with the GetGud platform. Once integrated, you will be able to stream your matches to Getgud's cloud, as well as to send reports and update player's data.

## Table of Contents

- [Prerequsites](https://github.com/getgud-io/cpp-getgud-sdk#prerequisites)
- [How SDK works](https://github.com/getgud-io/cpp-getgud-sdk#how-sdk-works)
- [Getting Started](https://github.com/getgud-io/cpp-getgud-sdk#getting-started)
- [Configuration](https://github.com/getgud-io/cpp-getgud-sdk#configuration)
    - [Description of the Config fields](https://github.com/getgud-io/cpp-getgud-sdk#description-of-the-config-fields)
- [Logging](https://github.com/getgud-io/cpp-getgud-sdk#logging)
- [Usage](https://github.com/getgud-io/cpp-getgud-sdk#usage)
    - [Initialization](https://github.com/getgud-io/cpp-getgud-sdk#initialization)
    - [Starting Games and Matches](https://github.com/getgud-io/cpp-getgud-sdk#starting-games-and-matches)
    - [Adding Actions to live Match](https://github.com/getgud-io/cpp-getgud-sdk#adding-actions-to-live-match)
    - [Adding Chat messages and Reports to live Match](https://github.com/getgud-io/cpp-getgud-sdk#adding-chat-and-reports-to-live-match)
    - [Ending Games and Matches](https://github.com/getgud-io/cpp-getgud-sdk#ending-games-and-matches)
    - [Sending Reports to past Matches](https://github.com/getgud-io/cpp-getgud-sdk#sending-reports-to-finished-matches)
    - [Sending Player Updates](https://github.com/getgud-io/cpp-getgud-sdk#sending-player-updates)
    - [Disposing the SDK](https://github.com/getgud-io/cpp-getgud-sdk#disposing-the-sdk)
- [Examples](https://github.com/getgud-io/cpp-getgud-sdk#examples)


## What Can You Do With Getgud's SDK:

- Send live Game data to Getgud's cloud (In-match Actions, In-match Reports, In-match Chat messages)
- Send Reports about historical matches to Getgud
- Send player information to Getgud

## Prerequisites

To start, we should understand the basic hierarchy Getgud's SDK uses to understand an FPS: 

**Titles->1->N->Games->1->N->Matches->1->N->Actions**

* The top container in Getgud's SDK is `Title`, which represents a literal game’s title, you as a client can have many titles, for example, a `Title` named CS:GO represents the CS:GO video game.

  ```
  Example of Title: CS:GO 
  ```

* Next up is `Game`, it is a container of matches that belong to the same `Title` from the same server session, where mostly the same players in the same teams, play one or more `Matches` together. You as a client can identify every game with a unique `gameGuid` that is provided to you once the `Game` starts. 

  ```
  An example of a Game is a CS:GO Game which has 30 macthes (AKA rounds) inside it.
  ```

* `Match` represents the actual play time that is streamed for analysis.  Like `Game`, `Match` also has a GUID which will be provided to you once you start a new match.

  ```
  An example of a Match is a single CS:GO round inside the game.
  ```

* `Action` represents an in-match activity. We collect six different action types which are common to all first person shooter gamnes, these are:
1. `Spwan` - Whenever a player appears or reappears in-match, on the map.
2. `Death` - A death of a player.
3. `Position` - player position change (including looking direction). 124 tick sensitive.
4. `Attack` - Whenever a player initiates any action that might cause damage, now or in the future. Examples: shooting, throwning a granade, planting a bomb, swinging a sword.
5. `Damage` - Whenever a player recieves any damage, from players or the environment.
6. `Heal` - Whenever is player is healed.


## Getting Started

Insert the Title Id and Private Key you recieved from Getgud.io to the following environment variables:

```
EXAMPLE
```

For multiple title support on the same machine - Link. (TODO)


Include the follwing header file:

```cpp
#include "../include/GetGudSdk.h"
```

Initialize the SDK:

```cpp
GetGudSdk::Init();
```

Start a Game:

```cpp
std::string gameGuid = GetGudSdk::StartGame(
  "us-west-1", // serverGuid
  "deathmatch" // gameMode
);
```

Once the Game starts, you'll recieve the Game's guid.
Now you can start a Match:

```cpp
std::string matchGuid = GetGudSdk::StartMatch(
  gameGuid, 
  "Knives-only", // matchMode
  "de-dust" // mapName
);
```

Once you have a match, you can send Actions to it.
Let's create a vector of Actions and send it to the match:

```cpp
EXAMPLE
);
```

Let's send a report to this match:

```cpp
EXAMPLE
);
```

Let's also send a chat massge to this match:

```cpp
EXAMPLE
);
```

End a game (All Game's Matches will close as well):

```cpp
bool gameEnded = GetGudSdk::MarkEndGame(gameGuid);
```

Close and Dispose of the SDK:

```cpp
GetGudSdk::Dispose();
```



## SDK Methods

### StartGame(serverName, gameMode)

To start a new game, call `StartGame()` with the following parameters, yhis will use the environment variables `TITLE_ID` and `PRIVATE_KEY`.
* serverName : the name of your game server - String, Alphanumeric, 36 chars max.
* gameMode : the mode of your the game - String, Alphanumeric, 36 chars max.

```cpp
std::string gameGuid = GetGudSdk::StartGame(serverName, gameMode);
```
* `serverName` - TODO
* `gameMode` - TODO

`StartGame` returns `gameGuid` - a unique identifier of the game which you will use later to start new Matches inside the Game as well as to end the Game when it is over.

#### StartGame(titleId, privateKey, serverName, gameMode)

You can also call the `StartGame()` method with titleId and privateKey that you pass (supporting multiple titles on the same machine)

```cpp
std::string gameGuid = GetGudSdk::StartGame(titleId, privateKey, serverName, gameMode);
```
* `titleId` - TODO
* `privateKey` - TODO
* `serverName` - TODO
* `gameMode` - TODO

### StartMatch(gameGuid, matchMode, mapName)

Once you've started a live Game, you can now attach Matches to that Game.
When a live Match starts it returns a `matchGuid`, you'll need it to add Actions, Chat, and Reports to that match
To start a new match for a live game, call `StartMatch()`:

```cpp
std::string matchGuid = GetGudSdk::StartMatch(gameGuid, matchMode, mapName);
```
* `serverName` - TODO
* `gameMode` - TODO

### AddActions(TODO: signature)

Once you've started a Match, you can now send actions to it.
To send actions to a match, call `AddActions()`:

```cpp
TODO: EXAMPLE OF ADD ACTIONS
```

### MarkEndGame(gameGuid)

Ends a live Game and it's associated matches.

```cpp
bool gameEnded = GetGudSdk::MarkEndGame(gameGuid);
```
* `gameMode` - TODO



## Adding Actions to Live Matches 

When the live Match starts, you can add Actions, Chat Data, and Reports to it. There are 6 Action types you can add to the Match. We call them the primal 6. Let's dive into each Action Type.

#### Spawn Action

To add a Spawn Action to a match, use the `SendSpawnAction` function. This marks the Spawn of every `Player` inside the Match.

```cpp
bool SendSpawnAction(std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
                     std::string characterGuid,
                     int teamId,
                     float initialHealth,
                     PositionF position,
                     RotationF rotation);
```

Here is an example:
```cpp
bool isActionSent = GetGudSdk::SendSpawnAction(
          "6a3d1732-8f72-12eb-bdef-56d89392f384", //matchGuid
          1684059337532,  // actionTimeEpoch
          "player_1", // playerGuid
          "ttr", // characterGuid
          GetGudSdk::PositionF{1, 2, 3}, // position
          GetGudSdk::RotationF{10, 20} // rotation
);
```

The `SpawnActionData` uses the following parameters:

* `matchGuid` - guid of the live Match where the action happened, is given to you when `StartMatch` is called.
* `actionTimeEpoch` - epoch time in milliseconds of when the action happened.
* `playerGuid` - player guid which is your player Id that belongs to the player whom is doing this action, max length is 10 chars.
* `characterGuid` - guid of the spwaned character from your game, max length is 10 chars.
* `position` - X,Y,Z coordinates of the player at the moment of action.
* `rotation` - PITCH, ROLL rotation of player view at the moment of action.

#### Position Action

To add a Position Action to a match, use the `SendPositionAction` function. This marks the change of `Player` position and view site. You can do this every tick.

```cpp
bool SendPositionAction(std::string matchGuid,
                        long long actionTimeEpoch,
                        std::string playerGuid,
                        PositionF position,
                        RotationF rotation);
```

Here is an example:
```cpp
bool isActionSent =  GetGudSdk::SendPositionAction(
          "6a3d1732-8f72-12eb-bdef-56d89392f384", //matchGuid
          1684059337532,  // actionTimeEpoch
          "player_1", // playerGuid
          GetGudSdk::PositionF{1, 2, 3}, // position
          GetGudSdk::RotationF{10, 20} // rotation
);
```

The `PositionActionData` uses the following parameters:

* `matchGuid` - guid of the live Match where the action happened, is given to you when `StartMatch` is called.
* `actionTimeEpoch` - epoch time in milliseconds when the action happened
* `playerGuid` - player guid which is your player Id that belongs to the player whom is doing this action, max length is 10 chars.
* `position` - X,Y,Z coordinates of the player at the moment of action.
* `rotation` - PITCH, ROLL rotation of player view at the moment of action.

#### Attack Action

To add a Attack Action to a match, use the `SendAttackAction` function. An Attack action is any attempt to attack, for example, firing a shot, swinging a sword, placing a bomb, throwing a grenade, or any other action that may result in damage, now or in the future. Note that the Attack action is not bound to damage, it is an attempt to cause Damage, not the Damage event itself.

```cpp
bool SendAttackAction(std::string matchGuid,
                      long long actionTimeEpoch,
                      std::string playerGuid,
                      std::string weaponGuid);
```

Here is an example:
```cpp
bool isActionSent =  GetGudSdk::SendAttackAction(
          "6a3d1732-8f72-12eb-bdef-56d89392f384", //matchGuid
          1684059337532,  // actionTimeEpoch
          "player_1", // playerGuid
          "akm" // weaponGuid
);
```

The `AttackActionData` uses the following parameters:

* `matchGuid` - guid of the live Match where the action happened, is given to you when `StartMatch` is called.
* `actionTimeEpoch` - epoch time in milliseconds when the action happened
* `playerGuid` - player guid which is your player Id that belongs to the player whom is doing this action, max length is 10 chars.
* `weaponGuid` - guid AKA name of the weapon attack was performed with, max length is 3 chars

#### Damage Action

To add a Damage Action to a match, use the `SendDamageAction` function. A Damage action is when a player if hit and loses health, both PVP and PVE. If the Damage is caused by the environment you can specify this in a playerGuid using a predefined variable `GetGudSdk::Values::Environment`

```cpp
bool SendDamageAction(std::string matchGuid,
                      long long actionTimeEpoch,
                      std::string playerGuid,
                      std::string victimPlayerGuid,
                      float damageDone,
                      std::string weaponGuid);
```

Here is an example:
```cpp
bool isActionSent =  GetGudSdk::SendDamageAction(
          "6a3d1732-8f72-12eb-bdef-56d89392f384", //matchGuid
          1684059337532,  // actionTimeEpoch
          "player_1", // playerGuid
          "player_2", // victimPlayerGuid
          23.0, // damageDone
          "akm" // weaponGuid
);
```

The `DamageActionData` uses the following parameters:

* `matchGuid` - guid of the live Match where the action happened, is given to you when `StartMatch` is called.
* `actionTimeEpoch` - epoch time in milliseconds when the action happened
* `playerGuid`  - player guid which is your player Id that belongs to the player whom is doing this action, max length is 10 chars.
* `victimPlayerGuid` - guid AKA nickname of the player who is the victim of the Damage action, max length is 36 chars.
* `damageDone` - How much damage was given
* `weaponGuid` - guid AKA name of the weapon attack was performed with, max length is 3 chars

#### Heal Action

To add a heal action to a match, use the `SendHealAction` function. A Heal action causes the player to increase his health while healing.

```cpp
bool SendHealAction(std::string matchGuid,
                    long long actionTimeEpoch,
                    std::string playerGuid,
                    float healthGained);
```

Here is an example:
```cpp
bool isActionSent =  GetGudSdk::SendHealAction(
          "6a3d1732-8f72-12eb-bdef-56d89392f384", //matchGuid
          1684059337532,  // actionTimeEpoch
          "player_1", // playerGuid
          55.0, // healthGained
);
```

The `HealActionData` uses the following parameters:

* `matchGuid` - guid of the live Match where the action happened, is given to you when `StartMatch` is called.
* `actionTimeEpoch` - epoch time in milliseconds when the action happened.
* `playerGuid`  - player guid which is your player Id that belongs to the player whom is doing this action, max length is 10 chars.
* `healthGained` - How much health the player gained.

#### Death Action

To add a death action to a match, use the `SendDeathAction` function. The Death player causes the player to Die, if the player died it should ALWAYS be marked. We do not detect this automatically.

```cpp
bool SendDeathAction(std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid);
```

Here is an example:
```cpp
bool isActionSent =  GetGudSdk::SendDeathAction(
          "6a3d1732-8f72-12eb-bdef-56d89392f384", //matchGuid
          1684059337532,  // actionTimeEpoch
          "player_1", // playerGuid
);
```

The `DeathActionData` uses the following parameters:

* `matchGuid` - guid of the live Match where the action happened, is given to you when `StartMatch` is called.
* `actionTimeEpoch` - epoch time in milliseconds when the action happened.
* `playerGuid` - guid AKA nickname of the player who is doing this action, max length is 36 chars.


All these actions help you record player behaviors during a live match.

In addition to the specific action functions mentioned earlier, you can also add actions using these alternative methods:

#### SendActions(actions)

To add a batch of actions to a match, use the `SendActions` function. This may contain any amount of the actions from our primal 6.

```cpp
bool SendActions(std::deque<BaseActionData*> actions);
```

This function accepts a deque of actions, where `BaseActionData` type actions can be any of the primal 6 actions (Spawn, Position, Attack, Damage, Heal, or Death actions). This method is useful when you want to send multiple actions at once.

Here is how you can create all 6 of the primal action types:

**Spawn Action:**
```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::SpawnActionData(
                     std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
                     std::string characterGuid,
                     int teamId,
                     float initialHealth,
                     PositionF position,
                     RotationF rotation
);
```

**Position Action:**
```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::PositionActionData(
                     std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
                     PositionF position,
                     RotationF rotation
);
```

**Attack Action:**
```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::AttackActionData(
                     std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
);
```

**Damage Action:**
```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::DamageActionData(
                     std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
                     std::string victimPlayerGuid,
                     float damageDone,
                     std::string weaponGuid
);
```

**Heal Action:**
```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::HealActionData(
                     std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
                     float healthGained
);
```

**Death Action:**
```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::DeathActionData(
                     std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid
);
```

Once you have created the amount of actions you need push them to `std::deque<BaseActionData*>` and pass it to `SendActions`

Here is an example:
```cpp
bool isActionsSent = SendActions(actions);
```



#### SendAction(action)

To add a single action to a match, use the `SendAction` function the same way we used `SendActions` but this time pass a single action you created directly.

```cpp
bool SendAction(BaseActionData* action);
```

This function accepts any action derived from `BaseActionData` type, including any of the primal 6 actions. This method is useful when you want to send a single action without specifying its type explicitly.

Here is an example:
```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::AttackActionData(
                     std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
);
bool isActionsSent = SendAction(action);
```


### Adding Chat and Reports to live Match

When your Game is live you can add Chat and Report data to any of the running matches using `matchGuid`. Let's see how you can add Chats and Reports for the live games.

#### Adding Chat Message
Here is how you can create a chat message and send it to live Match:

```cpp
GetGudSdk::ChatMessageInfo messageData;
messageData.message = "Hi from Getgud!";
messageData.messageTimeEpoch = 1684059337532;
messageData.playerGuid = "player1";
GetGudSdk::SendChatMessage(
  "6a3d1732-8f72-12eb-bdef-56d89392f384", // matchGuid 
  messageData
);
```

#### Adding Report

Here is how you can add Report to the live Match:
```cpp
GetGudSdk::ReportInfo reportInfo;
reportInfo.MatchGuid = "6a3d1732-8f72-12eb-bdef-56d89392f384";
reportInfo.ReportedTimeEpoch = 1684059337532;
reportInfo.ReporterName = "player1";
reportInfo.ReporterSubType = 0;
reportInfo.ReporterType = 0;
reportInfo.SuggestedToxicityScore = 100;
reportInfo.SuspectedPlayerGuid = "player1";
reportInfo.TbSubType = 0;
reportInfo.TbTimeEpoch = 1684059337532;
reportInfo.TbType = 0;
GetGudSdk::SendInMatchReport(reportInfo);
```

Here is the description of each report field. Note that all of the fields are optional exept suspected player guid.
- `MatchGuid`: guid of the live Match you are sending a report for
- `ReportedTimeEpoch`: epoch time in milliseconds of when the report was sent **(optional field)**
- `ReporterName`: Name of the entity that created the report **(optional field)**
- `ReporterType`: Id of the entity type that created the report, it could be "anticheat", "in-match report" and others **(optional field)**
- `ReporterSubType`:  If of the subtype of the entity that created the report, for type "anticheat" the subtypes could be "Easy Anticheat", "Internal Anticheat, and others" **(optional field)**
- `SuggestedToxicityScore`: 0-100 toxicity score, in other words, how much do you suspect the player **(optional field)**
- `SuspectedPlayerGuid`: guid of the suspected player **(Mandatory field)**
- `TbType`:: Id of the toxic behavior type, for example, Aimbot **(optional field)**
- `TbSubType`: Id of the toxic behavior subtype, for example, Spinbot **(optional field)**
- `TbTimeEpoch`: Epoch time in milliseconds when toxic behavior event happened **(optional field)**

Note: for Reporter and Tb types and subtypes you should use reference tables provided to you by Getgud to determine the correct mapping to Ids

### Ending Games and Matches

#### MarkEndGame(gameGuid)

When the live Game ends, you should mark it as finished for Getgud. To mark a game as finished, call `MarkEndGame` with the game GUID you received when you started the Game:

```cpp
bool gameEnded = GetGudSdk::MarkEndGame(gameGuid);
```

When the Game is marked as ended your Actions, Chat Data, and Report Data for ANY of the Game's Matches will not be added anymore.

`MarkEndGame` returns true/false depending if the Game was successfully closed or not.

### Sending Reports to finished Matches

If the Match and its corresponding Game are finished you still can send a report to the Match. 

Here is an example of how you can do this:

```cpp
std::deque<GetGudSdk::ReportInfo> reports;
GetGudSdk::ReportInfo reportInfo;
reportInfo.MatchGuid = "549cf69d-0d55-4849-b2d1-a49a4f0a0b1e";
reportInfo.ReportedTimeEpoch = 1684059337532;
reportInfo.ReporterName = "player1";
reportInfo.ReporterSubType = 0;
reportInfo.ReporterType = 0;
reportInfo.SuggestedToxicityScore = 100;
reportInfo.SuspectedPlayerGuid = "player1";
reportInfo.TbSubType = 0;
reportInfo.TbTimeEpoch = 1684059337532;
reportInfo.TbType = 0;
reports.push_back(reportInfo);

GetGudSdk::SendReports(
  28, // titleId
  "6a3d1732-8f72-12eb-bdef-56d89392f384",  // privateKey
  reports
);
```

Here we use a deque of reports to which we add reports and then send them to Getgud. You can also use SendReports function without `titleId` and `privateKey` arguments, in case you have `TITLE_ID` and `PRIVATE_KEY` env variables defined.

```cpp
GetGudSdk::SendReports(
  reports
);
```

### Sending Player Updates

To update player information outside a live Match, you can call `UpdatePlayers` like this:

```cpp
std::deque<GetGudSdk::PlayerInfo> playerInfos;
GetGudSdk::PlayerInfo playerInfo;
playerInfo.PlayerGuid = "549cf69d-0d55-4849-b2d1-a49a4f0a0b1e";
playerInfo.PlayerNickname = "test";
playerInfo.PlayerEmail = "test@test.com";
playerInfo.PlayerRank = 10;
playerInfo.PlayerJoinDateEpoch = 1684059337532;
playerInfos.push_back(playerInfo);
bool playersUpdated = GetGudSdk::UpdatePlayers(
  28, //titleId
  "6a3d1732-8f72-12eb-bdef-56d89392f384", // privateKet
  players
);
```

Note, that `PlayerNickname`, `PlayerEmail`, `PlayerRank` and `PlayerJoinDateEpoch` fields are optional!
As you see similarly to SendReports we use a deque of PlayerInfo objects to send it to Getgud SDK.

You can use the `UpdatePlayers` function without `titleId` and `privateKey` arguments, in case you have `TITLE_ID` and `PRIVATE_KEY` env variables defined.

```cpp
bool playersUpdated = GetGudSdk::UpdatePlayers(players);
```

Here is the description of each player field:
- `PlayerGuid`: Guid of the player, identifies this player in every title Game, and is unique for the title.
- `PlayerNickname`: Nickname of the player **(optional field)**
- `PlayerEmail`: Email of the player **(optional field)**
- `PlayerRank`: Integer rank of the player **(optional field)**
- `PlayerJoinDateEpoch`:  Date when the player joined **(optional field)**


## Configuration

The default Config file is loaded during `GetGudSdk::Init();` and is located in the same dir as the SDK files.
Example of configuration file `config.json`:

```json
{
  "throttleCheckUrl": "https://www.getgud.io/api/game_stream/throttle_match_check",
  "streamGameURL": "https://www.getgud.io/api/game_stream/send_game_packet",
  "updatePlayersURL": "https://www.getgud.io/api/player_data/update_players",
  "sendReportsURL": "https://www.getgud.io/api/report_data/send_reports",
  "logToFile": true,
  "logFileSizeInBytes": 2000000,
  "circularLogFile": true,
  "reportsMaxBufferSizeInBytes": 100000,
  "maxReportsToSendAtOnce": 100,
  "maxChatMessagesToSendAtOnce": 100,
  "playersMaxBufferSizeInBytes": 100000,
  "maxPlayerUpdatesToSendAtOnce": 100,
  "gameSenderSleepIntervalMilliseconds": 100,
  "apiTimeoutMilliseconds": 600,
  "apiWaitTimeMilliseconds": 100,
  "packetMaxSizeInBytes": 2000000,
  "actionsBufferMaxSizeInBytes": 10000000,
  "gameContainerMaxSizeInBytes": 50000000,
  "maxGames": 25,
  "maxMatchesPerGame": 10,
  "minPacketSizeForSendingInBytes": 1000000,
  "packetTimeoutInMilliseconds": 100000,
  "gameCloseGraceAfterMarkEndInMilliseconds": 20000,
  "liveGameTimeoutInMilliseconds": 100000,
  "hyperModeFeatureEnabled": true,
  "hyperModeMaxThreads": 10,
  "hyperModeAtBufferPercentage": 10,
  "hyperModeUpperPercentageBound": 90,
  "hyperModeThreadCreationStaggerMilliseconds": 100,
  "logLevel": "FULL"
}
```


## Examples

An example of how to use the GetGud C++ SDK can be found in the [examples](../examples) directory.
