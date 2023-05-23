# GetGud C++ SDK
Getgud C++ SDK allows you to integrate the GetGud platform in your application. With the help of Getgud SDK you will be able to send your Game and Match data to Getgud as well as reports and players metadata.

## Table of Contents

- Prerequsites
- Getting Started
- Configuration
    - Description of the Config fields
- Logging
- Usage
    - Initialization
    - Starting Games and Matches
    - Adding Actions to live Match
    - Adding Chat messages and Reports to live Match
    - Ending Games and Matches
    - Adding Reports to past Matches
    - Sending Player Updates
    - Disposing the SDK
- Examples

## Prerequisites

To start, let’s talk about the logical structure of how getgud is built.

`Client->1->N->Title->1->N->Game->1->N->Match`

* The top entity in getgud is `Client`, it represents a company that uses Getgud. Client is the main container for all other entities. it holds all the company’s PII, permissions, status and as with all entities, an integer primary key, in this case – `clientId`.

  ```
  Example of client: Valve 
  ```

* The second top container is `Title`, it represents a literal game’s title, a client can have many titles, for example: a `Title` named CS:GO represents the CS:GO video game.  Title holds an Id, PII, permissions, etc. 

  ```
  Example of Title: CS:GO 
  ```

* Next up is `Game`, it is a container of matches that belong to the same `Title` from the same server session, where mostly the same players in the same teams, play one or more `Matches` together. You as a client can identify every game with a unique `gameGuid` that is given to you when the `Game` starts. 

  ```
  An example of Game is a CS:GO Game which has 30 rounds inside it.
  ```

* `Match` represents the actual play time; the game stream we collect and analyze.  Like `Game`, `Match` also has a GUID `matchGuid` and like `Game`, `Match` holds a bunch of statistics about itself.

  ```
  An example of Match is a single CS:GO round inside the game.
  ```

Now that the basic structure is set and we understand the main containers, we should talk about the `Player` entity, although it is not part of the main chain, it’s not less important than any entity in the chain.

* The `Player` entity represents a literal player and holds the player’s PII. A Player belongs to a `Title`. Player also has a GUID, which should be unique to the `titleId`. A player has an interesting relationship with `Match`, it’s a N:N relationship; a match holds many players and a player plays in many matches.

* A `TB Type` (AKA toxic behavior type) and its child `TB Subtype` are entities that represent toxic behaviors (cheating as well as griefing). For example, one TB-Type might represent the Aimbot cheat and one of its child TB-Subtypes would be Spinbot. You are going to use this when sending your `Reports` to Getgud.


## Getting Started

To use the GetGud SDK, you will need to include the required header file:

```cpp
#include "../include/GetGudSdk.h"
```


## Configuration

The Config JSON file is loaded during `GetGudSdk::Init();` operation using `CONFIG_PATH` env variable.
Example of configuration file `config.json`:

```json
{
  "streamGameURL": "test_link",
  "updatePlayersURL": "test_link",
  "sendReportsURL": "test_link",
  "throttleCheckUrl": "test_link",
  "reportsMaxBufferSizeInBytes": 100000,
  "maxReportsToSendAtOnce": 100,
  "playersMaxBufferSizeInBytes": 100000,
  "maxPlayerUpdatesToSendAtOnce": 100,
  "gameSenderSleepIntervalMilliseconds": 100,
  "apiTimeoutMilliseconds": 400,
  "apiWaitTimeMilliseconds": 100,
  "packetMaxSizeInBytes": 2000000,
  "actionsBufferMaxSizeInBytes": 1000000,
  "gameContainerMaxSizeInBytes": 50000000,
  "maxGames": 50,
  "maxMatchesPerGame": 50,
  "minPacketSizeForSendingInBytes": 1000000,
  "packetTimeoutInMilliseconds": 1000,
  "gameCloseGraceAfterMarkEndInMilliseconds": 1000,
  "liveGameTimeoutInMilliseconds": 20000,
  "hyperModeFeatureEnabled": true,
  "hyperModeMaxThreads": 10,
  "hyperModeAtBufferPercentage": 10,
  "hyperModeUpperPercentageBound": 90,
  "hyperModeThreadCreationStaggerMilliseconds": 100,
  "logLevel": "WARN_AND_ERROR"
}
```

Please note that SDK will not start if `CONFIG_PATH` is not set.
Make sure to adjust the values in the configuration file according to your application's requirements.

### Description of the Config fields

## Logging

## Usage

### Initialization

#### Init()

Before using the GetGud SDK, you must initialize it:

```cpp
GetGudSdk::Init();
```

This sets up internal components, such as memory management, network connections, loads config file, starts Logger and prepares the SDK for use.

### Starting Games and Matches

#### StartGame(titleId, privateKey, serverName, gameMode)

To start a new game, call `StartGame()` with the following parameters:
* titleId : internal titleId from Getgud, provided when you create a new title in Getgud
* privateKey : private key, provided along with the titleId after creating a new title in Getgud
* serverName : name of your game server
* gameMode : mode of the game you are about to start

```cpp
std::string gameGuid = GetGudSdk::StartGame(titleId, privateKey, serverName, gameMode);
```

This will start a new live Game which will accumulate live Matches and once has enough data will send a request to Getgud.

`StartGame` returns `gameGuid` - a unique identifier of the game which you will use later to start new Matches inside the Game as well as to end the Game when it is over.

#### StartGame(serverName, gameMode)

You can also start a live Game using environment variables `TITLE_ID` and `PRIVATE_KEY`, in this case you do not have to specify `titleId` and `privateKey` as function arguments:

```cpp
std::string gameGuid = GetGudSdk::StartGame(serverName, gameMode);
```

#### StartMatch(gameGuid, matchMode, mapName)

When you have started a live Game you can now attach Matches to the Game.
To start a new match for an existing game, call `StartMatch()`:

```cpp
std::string matchGuid = GetGudSdk::StartMatch(gameGuid, matchMode, mapName);
```

When you start a new live Match you get a `matchGuid`, you will need to use it when you add Actions, Chat Data and Report Data to this live Match.

A live Match is where you are going to accumulate actions, chat data and reports for this live Match entity. Remember a single live Game will have one or more live Matches, each match will contain it's own actions, chat and reports.

You do not have to Stop the match manually, this is done for you automatically when you `MarkEndGame`


### Adding Actions to live Match

When the live Match is started, you can add Actions, Chat Data and Reports to this match. There are 6 Action types you can add to the Match. We call them the primal 6 actions. Let's dive into each Action Type.

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
* `actionTimeEpoch` - epoch time in milliseconds when the action happened.
* `playerGuid` - guid AKA nickname of the player who is doing this action, max length is 36 chars.
* `characterGuid` - guid of the character from your game, max length is 36 chars.
* `position` - X,Y,Z coordinates of player at the moment of action.
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
* `playerGuid` - guid AKA nickname of the player who is doing this action, max length is 36 chars
* `position` - X,Y,Z coordinates of player at the moment of action.
* `rotation` - PITCH, ROLL rotation of player view at the moment of action.

#### Attack Action

To add a Attack Action to a match, use the `SendAttackAction` function. An Attack action is any attempt to attack, for example: fire shot, throwing granade, or any other action that may result in damage. Though Attack action is not bound to damaging anyone, it is an attempt to cause Damage, not the Damage itself.

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
* `playerGuid` - guid AKA nickname of the player who is doing this action, max length is 36 chars
* `weaponGuid` - guid AKA name of the weapon attack was performed with, max length is 3 chars

#### Damage Action

To add a Damage Action to a match, use the `SendDamageAction` function. A Damage action is an attack which caused damage to the victim player. Damage can be caused not only by player but by the environment too. If the Damage is caused by the environment you can specify this in a playerGuid.

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
* `playerGuid` - guid AKA nickname of the player who is doing this action, max length is 36 chars. This can be marked as an environment
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
* `playerGuid` - guid AKA nickname of the player who is doing this action, max length is 36 chars.
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

* Spawn Action:
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

* Position Action:
```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::PositionActionData(
                     std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
                     PositionF position,
                     RotationF rotation
);
```

* Attack Action:
```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::AttackActionData(
                     std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
);
```

* Damage Action:
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

* Heal Action:
```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::HealActionData(
                     std::string matchGuid,
                     long long actionTimeEpoch,
                     std::string playerGuid,
                     float healthGained
);
```

* Death Action:
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

Here is the description of each report field:
- MatchGuid: 
- ReportedTimeEpoch:
- ReporterName: 
- ReporterSubType:
- ReporterType: 
- SuggestedToxicityScore: 
- SuspectedPlayerGuid:
- TbSubType: 
- TbTimeEpoch: 
- TbType:

### Ending Games and Matches

#### MarkEndGame(gameGuid)

When the live Game ends, you should mark it as finished for Getgud. To mark a game as finished, call `MarkEndGame` with the game GUID you received when you started the Game:

```cpp
bool gameEnded = GetGudSdk::MarkEndGame(gameGuid);
```

When the Game is marked as ended your Actions, Chat Data and Report Data for ANY of the Game's Matches will not be added anymore.

`MarkEndGame` returns true/false depending if the Game was succesfully closed or not.

### Sending Reports to finished Matches

### Sending Player Updates

To update player information outside a live match, call `UpdatePlayers()` with the appropriate parameters:

```cpp
bool playersUpdated = GetGudSdk::UpdatePlayers(titleId, privateKey, players);
```

You can use the `UpdatePlayers()` function with environment variables for `titleId` and `privateKey`:

```cpp
bool playersUpdated = GetGudSdk::UpdatePlayers(players);
```

### Disposing the SDK

To properly clean up the SDK before exiting your application, call `Dispose()`:

```cpp
GetGudSdk::Dispose();
```

This will release any resources or connections being used by the SDK.

## Example

An example of how to use the GetGud C++ SDK can be found in the [test](../test) directory.
