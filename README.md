# GetGud C++ SDK Documentation

This C++ SDK allows you to integrate the GetGud in your application for toxicity protection and analytics purposes.

## Table of Contents

- Getting Started
- Usage
    - Initialization
    - Starting and Ending Games
    - Match Management
    - Sending Reports and Actions
    - Updating Players
    - Disposing the SDK
- Example

## Getting Started

To use the GetGud SDK, you will need to include the required header file:

```cpp
#include "../include/GetGudSdk.h"
```

Make sure to compile and link with the provided GetGud library.

## Usage

### Initialization

#### Init()

Before using the GetGud SDK, you must initialize it:

```cpp
GetGudSdk::Init();
```

This sets up internal components and prepares the SDK for use.

### Starting and Ending Games

#### StartGame(titleId, privateKey, serverName, gameMode)
To start a new game, call `StartGame()` with the following parameters:
* `titleId` - internal titleId from Getgud, it is provided to you when you create new title in Getgud
* `privateKey` - private key is always provided to you along the titleId after creation of new title in Getgud
* `serverName` - name of your game server
* `gameMode` - mode of the game you are about to start

```cpp
std::string gameGuid = GetGudSdk::StartGame(titleId, privateKey, serverName, gameMode);
```

#### StartGame(serverName, gameMode)
You can start new game but this time you can specify your titleId and privateKey as environment variables through `TITLE_ID` and `PRIVATE_KEY` variables.

```cpp
std::string gameGuid = GetGudSdk::StartGame(serverName, gameMode);
```

#### MarkEndGame(gameGuid)
When the game ends you should mark it as finished for Getgud. To mark a game as finished, call `MarkEndGame()` with the game GUID:

```cpp
bool gameEnded = GetGudSdk::MarkEndGame(gameGuid);
```

### Match Management

To start a new match for an existing game, call `StartMatch()`:

```cpp
std::string matchGuid = GetGudSdk::StartMatch(gameGuid, matchMode, mapName);
```

### Sending Reports and Actions

To send a report for a specific match while it's live, call `SendInMatchReport()`:

```cpp
bool inMatchReportAdded = GetGudSdk::SendInMatchReport(reportInfo);
```

To send a chat message for a specific match while it's live, call `SendChatMessage()`:

```cpp
bool chatMessageSent = GetGudSdk::SendChatMessage(matchGuid, messageInfo);
```

To send one or more actions to the action buffer, call `SendActions()` or `SendAction()`:

```cpp
bool actionsSent = GetGudSdk::SendActions(actions);
bool actionSent = GetGudSdk::SendAction(action);
```

Various action-specific sending functions are also provided, such as `SendAttackAction()`, `SendDamageAction()`, `SendHealAction()`, `SendSpawnAction()`, `SendDeathAction()`, and `SendPositionAction()`.

### Updating Players

To update player information outside a live match, call `UpdatePlayers()` with the appropriate parameters:

```cpp
bool playersUpdated = GetGudSdk::UpdatePlayers(titleId, privateKey, players);
```

To update player information using environment variables for `titleId` and `privateKey`:

```cpp
bool playersUpdated = GetGudSdk::UpdatePlayers(players);
```

### Disposing the SDK

To properly clean up the SDK before exiting your application, call `Dispose()`:

```cpp
GetGudSdk::Dispose();
```

## Example

An example of how to use the GetGud C++ SDK can be found in the [test](../test) directory.
