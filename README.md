# GetGud C++ SDK

## What Can You Do With Getgud's SDK:

Getgud's C++ SDK allows you to integrate your game with the GetGud platform. Once integrated, you will be able to:

- Stream live game data to GetGud's cloud, including in-match actions, in-match reports, and in-match chat messages.
- Send Reports about historical matches to Getgud.
- Send (and update) player information to Getgud.

## Build requirements:
The shared and static libraries are different. The shared library can be linked directly to a project because it only requires the binaries and headers.
However, here is the way to link the static library correctly:
### Linux:
Dependencies:
- libcurl development kit.
- zlib development kit.
- openssl development kit.
- libssl development kit.
- libcrypto development kit.
- g++ and gcc packages.
- pthread library.

### Windows:
- libcurl library package.
- zlib library package.

A test project with completed setup is included in each release folder.

## Prerequisites

To start, we need to understand the basic structure GetGud's SDK uses to describe a video game: 

**Titles->1->N->Games->1->N->Matches->1->N->Actions**

* The top container in Getgud's SDK is `Title`, which represents a literal game’s title, you as a client can have many titles, for example, a `Title` named CS:GO represents the CS:GO video game.

  ```
  An example of a Title: CS:GO 
  ```

* Next up is `Game`, a `Game` is a container of matches that belong to the same `Title` from the same server session, where mostly the same players in the same teams, play one or more `Matches` together. You as a client can identify every game with a unique `gameGuid` that is provided to you once the `Game` starts. 

  ```
  An example of a Game is a CS:GO game which has 30 matches (also known as rounds) within it.
  ```

* `Match` represents the actual play time that is streamed for analysis.
A `Match` contains the actions that occurred during the match's timespan.
Like `Game`, `Match` also has a GUID which will be provided to you once you start a new match.

  ```
  An example of a Match is a single CS:GO round inside the game.
  ```

* `Action` represents an in-match activity that is associated with a player. We collect seven different action types which are common to all first person shooter gamnes:
1. `Spawn` - Whenever a player appears or reappears in-match, on the map.
2. `Death` - A death of a player, either by another player, the environemnt or the player itself.
3. `Position` - player position change (including looking direction).
4. `Attack` - Whenever a player initiates any action that might cause damage, now or in the future. Examples: shooting, throwning a granade, planting a bomb, swinging a sword, punching, firing a photon torpedo, etc.
5. `Damage` - Whenever a player recieves any damage, either from another player, the environemnt or the player itself.
6. `Heal` - Whenever a player is healed, doesn't matter by whom or how.
7. `Affect` - Whenever an in-match affect of any kind is applied to the player. Examples: crouch, prone, jump, fly, see through walls, extra speed/ammo/shield/health, etc. 


## Getting Started

Insert the Title Id and Private Key you recieved from Getgud.io to the `GETGUD_TITLE_ID ` and `GETGUD_PRIVATE_KEY` environment variables, or use them as arguments for StartGame. (multiple title support available below)

Include the follwing header file:

```cpp
#include <GetGudSdk.h>
```

Initialize the SDK:

```cpp
GetGudSdk::Init();
```

Start a Game:

```cpp
std::string gameGuid = GetGudSdk::StartGame(
  "cs2-server-1", // serverGuid
  "203.0.113.42", // serverLocation
  "deathmatch" // gameMode
);
```

Once the Game starts, you'll recieve the Game's guid, now you can start a Match:

```cpp
std::string matchGuid = GetGudSdk::StartMatch(
  gameGuid, 
  "Knives-only", // matchMode
  "de-dust" // mapName
);
```

Once you create a match, you can send Actions to it.
Let's create a deque of Actions and send it to the match:

```cpp
//Create a deque of Actions
std::deque<GetGudSdk::BaseActionData*> actionsToSend {
new GetGudSdk::SpawnActionData(
            matchGuid, curTimeEpoch, "player-10", "ttr", 0, 100.f,
            GetGudSdk::PositionF{1, 2, 3}, GetGudSdk::RotationF{10, 20}),
			
new GetGudSdk::PositionActionData(
          matchGuid, curTimeEpoch, "player-5",
          GetGudSdk::PositionF{20.32000f, 50.001421f, 0.30021f},
          GetGudSdk::RotationF{10, 20})
};

//Send it to the SDK
GetGudSdk::SendActions(actionsToSend);

//Clean up the actions
for (auto* sentAction : actionsToSend)
    delete sentAction;
  actionsToSend.clear();
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

### StartGame(serverName, serverLocation, gameMode)

To start a new game, call `StartGame()`, this will use the environment variables `TITLE_ID` and `PRIVATE_KEY`.
`StartGame` returns `gameGuid` - a unique identifier of the game which you will use later to start new Matches inside the Game as well as to end the Game when it is over.

```cpp
std::string gameGuid = GetGudSdk::StartGame(serverName, serverLocation, gameMode);
```
* `serverName` - a qunique name of your game server - String, Alphanumeric, 36 chars max.
* `serverLocation` - a name/ip of your game server's location - String, Alphanumeric, 36 chars max.
* `gameMode` - the mode of the game (each mode has a separate AI learning processes) - String, Alphanumeric, 36 chars max.

#### StartGame(titleId, privateKey, serverName, serverLocation, gameMode)

You can also call the `StartGame()` method with titleId and privateKey that you pass (supporting multiple titles on the same machine)

```cpp
std::string gameGuid = GetGudSdk::StartGame(titleId, privateKey, serverName, gameMode);
```
* `titleId` - The title Id you recieved from Getgud.io
* `privateKey` - The Private Key for the above title you recieved together with it's Title Id
* `serverName` - a qunique name of your game server - String, Alphanumeric, 36 chars max.
* `serverLocation` - a name/ip of your game server's location - String, Alphanumeric, 36 chars max.
* `gameMode` - the mode of the game (each mode has an additional AI learning processes) - String, Alphanumeric, 36 chars max.

### StartMatch(gameGuid, matchMode, mapName)

Once you've started a live Game, you can now attach Matches to that Game.
When a live Match starts it returns a `matchGuid`, which is used to add Actions, Chat messages, and Reports to that specific match.
To start a new match, call `StartMatch()`:

```cpp
std::string matchGuid = GetGudSdk::StartMatch(gameGuid, matchMode, mapName);
```
* `gameGuid` - The Game guid you recieved when starting a new Game
* `matchMode` - the mode of the match (each mode has an additional AI learning processes) - String, Alphanumeric, 36 chars max.
* `mapName` - the unique name of the map - String, Alphanumeric, 36 chars max.

### AddActions(std::deque<BaseActionData*> actions)

Once you've started a Match, you can now send actions to it.
To add a batch of actions to a match, use the `SendActions` function.
This is an async method which will not block the calling thread.

```cpp
bool SendActions(std::deque<BaseActionData*> actions);
```
* `actions` - deque of `BaseActionData` objects, where `BaseActionData` is the base calss of all the primal 7 actions (Spawn, Position, Attack, Damage, Heal, Affect and Death).

#### AddAction(BaseActionData* action)

You can also send single actions when you need to, using the `AddAction()` method.
This is an async method which will not block the calling thread.

```cpp
bool SendActions(action);
```
* `action` - a `BaseActionData` object that is the base class of all the primal 7 actions (Spawn, Position, Attack, Damage, Heal, Affect and Death).

### MarkEndGame(gameGuid)

Ends a live Game and it's associated matches.
When the live Game ends, you should mark it as finished in order to close it on Getgud's side.
Once the game is marked as ended, it will not accept new live data.

```cpp
bool gameEnded = GetGudSdk::MarkEndGame(gameGuid);
```
* `gameGuid` - The Game guid you recieved when starting a new Game

`MarkEndGame` returns true/false depending if the Game was successfully closed or not.

## Creating Actions 

When a live Match starts, you can add Actions, Chat Data, and Reports to it. 
There are 7 Action types you can add to the Match, all derived from base action which holds the actions base properties.

### Base Action

`BaseAction` is the base class that all actions derive from and holds common information to all action.

```cpp
BaseAction(std::string matchGuid,
        long long actionTimeEpoch,
        std::string playerId);
```
* `matchGuid` - guid of the live Match where the action happened, is given to you when `StartMatch` is called.
* `actionTimeEpoch` - epoch time in milliseconds when the action happened
* `playerId` - your player Id (which will called playerGuid on Getgud's side) 

### Spawn Action

A Spawn action should be sent whenever a player appears or reappears in-match, on the map.
To create a Spawn Action, use the `SpawnActionData` class.
This action marks the appearance or reappearance of a `Player` inside the Match.

```cpp
GetGudSdk::BaseActionData* action = new SpawnActionData(
        BaseAction::baseAction,
        std::string characterGuid,
        int teamId,
        float initialHealth,
        PositionF position,
        RotationF rotation);
```
* `baseAction` - See BaseAction
* `characterGuid` - Guid of the spwaned character from your game, 36 max length.
* `teamId` - The identifier number of the player's team
* `initialHealth` - The initial health of the player
* `position` - X,Y,Z coordinates of the player at the moment of action.
* `rotation` - PITCH, ROLL rotation of player view at the moment of action.

### Position Action

A Position action should be sent on player position change (including looking direction).
To create a Position Action, use the `PositionActionData` class.
This action marks the change of `Player` position and view site.

```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::PositionActionData(
                     BaseAction::baseAction,
                     PositionF position,
                     RotationF rotation
);
```
* `BaseAction` - See BaseAction
* `Position` - X,Y,Z coordinates of the player at the moment of action.
* `Rotation` - PITCH, ROLL rotation of player view at the moment of action.

### Attack Action

An Attack action is any attempt to create damage, now or in the future, for example, firing a shot, swinging a sword, placing a bomb, throwing a grenade, or any other action that may result in damage.
To create an Attack Action, use the `AttackActionData` Class.
Note that the Attack action is not bound to the `Damage` action, it is an attempt to cause Damage, not the Damage event itself.

```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::AttackActionData(
                     BaseAction:: baseAction,
                     std::string attackerPlayerId,
                     std::string weaponGuid,
);
```
* `BaseAction` - See BaseAction
* `attackerPlayerId` - A unique name (your player id) of the player which created the damage, if the damage was created by the environment, you can singal this by using the 'PvE' symbol as the player guid.
* `weaponGuid` - A unique name of the weapon that the attack was performed with, max length is 36 chars.

### Affect Action

An Affect action should be sent whenever an in-match affect of any kind is applied to the player. Examples: crouch, prone, jump, fly, see through walls, extra speed/ammo/shield/health, etc.
To create an Affect Action, use the `AffectActionData` Class.

```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::AffectActionData(
                     BaseAction:: baseAction,
                     std::string affectedPlayerId,
                     std::string affectGuid,
                     AffectState affectState
);
```
* `BaseAction` - See BaseAction
* `affectedPlayerId` - A unique name (your player id) of the player which received the affect, if the affect was created by the environment, you can singal this by using the 'PvE' symbol as the player guid.
* `affectGuid` - A unique name of the affect, max length is 36 chars.
* `affectState` - An emumiration unit that allows you to flag the state of the Affect:
  	Attach - indicate affect is attahced to a player (not mandatory).
  	Detach - indicate affect is detached from a player (not mandatory).
  	Activate - indicate affect is affecting the playter.
  	Deactivate - indicate affect stopped affecting the playter.  

### Damage Action

A Damage action should be raised when a player loses health, both PVP and PVE. If the Damage is caused by the environment you can specify this in a playerGuid using a predefined variable `GetGudSdk::Values::Environment`
To create a Damage Action, use the `DamageActionData` class. 

```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::DamageActionData(
                     BaseAction:: baseAction,
                     std::string victimPlayerGuid,
                     float damageDone,
                     std::string weaponGuid
);
```
* `BaseAction` - See BaseAction
* `victimPlayerGuid` - guid of the player who is the victim of the Damage action, max length is 36 chars.
* `damageDone` - How much damage was given
* `weaponGuid` - A unique name of the weapon that the attack was performed with, max length is 36 chars.

### Heal Action

A Heal action should be triggered whenever a player is healed, doesn't matter by whom or how.
To create a heal action, use the `HealActionData` class.
```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::HealActionData(
                     BaseAction:: baseAction,
                     float healthGained
);
```
* `BaseAction` - See BaseAction
* `healthGained` - How much health the player gained.

### Death Action

A Death action should be triggered on a death of a player, either by another player, the environemnt or the player itself.
To create a death action to a match, use the `DeathActionData` class. 

```cpp
GetGudSdk::BaseActionData* action = new GetGudSdk::DeathActionData(
                     BaseAction:: baseAction,
                     std::string killerPlayerGuid,
);
```
* `BaseAction` - See BaseAction
* `killerPlayerGuid` - guid of the player who killed the victim of the Damage action, max length is 36 chars. Use `GetGudSdk::Values::Environment` to indicate that PvE killed the player

## Adding Chat Messages
To add a chat message to a live Match:

```cpp
GetGudSdk::ChatMessageInfo messageData;
messageData.message = "Hi from Getgud!";
messageData.messageTimeEpoch = 1684059337532;
messageData.playerId = "player1";
GetGudSdk::SendChatMessage(
  "6a3d1732-8f72-12eb-bdef-56d89392f384", // matchGuid 
  messageData
);
```

## Adding Reports

To add a reports to a live Match:
Note that all of the fields are optional exept `MatchGuid` and `SuspectedPlayerId` (a report must have a valid match and player).<br> 
To fill `ReporterType`, `ReporterSubType` and `TbType` fields you can use enums exposed to you by our SDK.
This is an async method which will not block the calling thread.

```cpp
GetGudSdk::ReportInfo reportInfo;
reportInfo.MatchGuid = "549cf69d-0d55-4849-b2d1-a49a4f0a0b1e";
reportInfo.ReportedTimeEpoch = 1684059337532;
reportInfo.ReporterName = "player1";
reportInfo.ReporterType = GetGudSdk::Values::ReporterSubtype.Moderator;
reportInfo.ReporterSubType = GetGudSdk::Values::ReporterSubtype.QA;
reportInfo.SuggestedToxicityScore = 100;
reportInfo.SuspectedPlayerId = "player1";
reportInfo.TbTimeEpoch = 1684059337532;
reportInfo.TbType = GetGudSdk::Values::TBType.Wallhack;
GetGudSdk::SendInMatchReport(reportInfo);
```
* `MatchGuid`- guid of the live Match you are sending a report to **(Mandatory field)**
* `ReportedTimeEpoch`- epoch time of when the report was created **(Mandatory field)**
* `ReporterName`- the name of the entity that created the report **(optional field)**
* `ReporterType`- the type of the entity that created the report **(optional field)**
* `ReporterSubType`-   the subtype of the entity that created the report **(optional field)**
* `SuggestedToxicityScore`- 0-100 toxicity score, ie: how much do you suspect the player **(optional field)**
* `SuspectedPlayerId`- the player Id of the suspected player **(Mandatory field)**
* `TbType` - id of the toxic behavior type, for example, Aimbot **(optional field)**
* `TbTimeEpoch` - epoch time of when the toxic behavior event occured **(optional field)**

### Sending Reports On Historical Matches

To add a reports to a histotical Match (a match which is not live and has ended):

```cpp
std::deque<GetGudSdk::ReportInfo> reports;
GetGudSdk::ReportInfo reportInfo;
reportInfo.MatchGuid = "549cf69d-0d55-4849-b2d1-a49a4f0a0b1e";
reportInfo.ReportedTimeEpoch = 1684059337532;
reportInfo.ReporterName = "player1";
reportInfo.ReporterSubType = GetGudSdk::Values::ReporterSubtype.QA;
reportInfo.ReporterType = GetGudSdk::Values::ReporterSubtype.Moderator;
reportInfo.SuggestedToxicityScore = 100;
reportInfo.SuspectedPlayerId = "player1";
reportInfo.TbTimeEpoch = 1684059337532;
reportInfo.TbType = GetGudSdk::Values::ReporterSubtype.Wallhack;
reports.push_back(reportInfo);

GetGudSdk::SendReports(
  28, // titleId
  "6a3d1732-8f72-12eb-bdef-56d89392f384",  // privateKey
  reports
);
```
You can also use SendReports function without `titleId` and `privateKey` arguments, in case you have `TITLE_ID` and `PRIVATE_KEY` env variables defined.

Deque of reports:

```cpp
GetGudSdk::SendReports(
  reports
);
```

## Sending Player Updates

To update player information, you can call `UpdatePlayers`:
All fields are optional except player Id.
Use a deque of PlayerInfo objects to send to Getgud SDK.
This is an async method which will not block the calling thread.

```cpp
std::deque<GetGudSdk::PlayerInfo> playerInfos;
GetGudSdk::PlayerInfo playerInfo;
playerInfo.PlayerGuid = "549cf69d-0d55-4849-b2d1-a49a4f0a0b1e";
playerInfo.PlayerNickname = "test";
playerInfo.PlayerEmail = "test@test.com";
playerInfo.PlayerRank = 10;
playerInfo.playerSuspectScore: 12,
playerInfo.playerReputation: "esteemed",
playerInfo.PlayerJoinDateEpoch = 1684059337532;
playerInfos.push_back(playerInfo);
bool playersUpdated = GetGudSdk::UpdatePlayers(
  28, //titleId
  "6a3d1732-8f72-12eb-bdef-56d89392f384", // privateKet
  players
);
```
* `PlayerGuid`- Your player Id - String, 36 chars max. **(Mandatory field)**
* `PlayerNickname`- Nickname of the player **(optional field)**
* `PlayerEmail`- Email of the player **(optional field)**
* `PlayerRank`- Integer rank of the player **(optional field)**
* `PlayerJoinDateEpoch`:  Date when the player joined **(optional field)**

You can use the `UpdatePlayers` function without `titleId` and `privateKey` arguments, in case you have `TITLE_ID` and `PRIVATE_KEY` env variables defined.

```cpp
bool playersUpdated = GetGudSdk::UpdatePlayers(players);
```

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
  "maxConcurrentGames": 100,
  "maxMatchesPerGame": 30,
  "minPacketSizeForSendingInBytes": 1000000,
  "packetTimeoutInMilliseconds": 100000,
  "gameCloseGraceAfterMarkEndInMilliseconds": 20000,
  "liveGameTimeoutInMilliseconds": 100000,
  "hyperModeFeatureEnabled": true,
  "hyperModeMaxThreads": 10,
  "hyperModeAtBufferPercentage": 10,
  "hyperModeUpperPercentageBound": 90,
  "hyperModeThreadCreationStaggerMilliseconds": 100,
  "logLevel": "warn"
}
```


## Examples

An example of how to use the GetGud C++ SDK can be found in the [examples](/examples/) directory.
