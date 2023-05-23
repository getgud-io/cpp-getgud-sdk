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
    - Adding Actions, Reports and Chat data to live Matches
    - Ending Games and Matches
    - Sending Reports to past Matches
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

A live Match is where you are going to accumulate actions, chat data and reports for this live Match entity. Remember a single live Game will have one or more live Matches, each match will contain it's own actions, chat and reports.

You do not have to Stop the match manually, this is done for you automatically when you `MarkEndGame`


### Adding Actions, Reports and Chat data to live Matches

### Ending Games and Matches

When the live Game ends, you should mark it as finished for Getgud. To mark a game as finished, call `MarkEndGame()` with the game GUID you received when you started the Game:

```cpp
bool gameEnded = GetGudSdk::MarkEndGame(gameGuid);
```

### Sending Reports to past Matches

### Sending Reports to past Matches

### Sending Player Updates

### Disposing the SDK

### Sending Reports and Actions

To send a report for a specific match while it's live, call `SendInMatchReport()`:

```cpp
bool inMatchReportAdded = GetGudSdk::SendInMatchReport(reportInfo);
```

To send a chat message for a specific match while it's live, call `SendChatMessage()`:

```cpp
bool chatMessageSent = GetGudSdk::SendChatMessage(matchGuid, messageInfo);
```

There are several action-specific sending functions provided, such as `SendAttackAction()`, `SendDamageAction()`, `SendHealAction()`, `SendSpawnAction()`, `SendDeathAction()`, and `SendPositionAction()`.

They can be sent one by one or in a batch, using `SendActions()` or `SendAction()`:

```cpp
bool actionsSent = GetGudSdk::SendActions(actions);
bool actionSent = GetGudSdk::SendAction(action);
```

### Updating Players

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
