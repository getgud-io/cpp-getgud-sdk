# GetGud C++ SDK Documentation 

This C++ SDK allows you to integrate the GetGud platform in your application for toxicity protection and analytics purposes.

## Table of Contents

- Getting Started
- Configuration
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

Ensure you compile and link with the provided GetGud library.

Please note: In debug mode, some variables are used to track and monitor actions and empty actions. This will display the number of actions and empty actions being processed through the SDK.

```cpp
#ifdef _DEBUG
 public:
  int actionsAmount = 0;
  int totalCreatedActions = 0;
  int emptyActionsAmount = 0;
  int totalCreatedEmptyActions = 0;
#endif
```

## Configuration

To load the SDK configuration, create a `Config` object:

```cpp
GetGudSdk::Config sdkConfig;
```

You can set configuration settings by calling the `LoadSettings()` method on the `Config` object. Configuration settings can be loaded from a file. The file should have keys corresponding to the required settings.

Example configuration file:

```ini
streamGameURL=https://api.getgud.com/stream/game/
updatePlayersURL=https://api.getgud.com/player/update/
sendReportsURL=https://api.getgud.com/report/outside-match/
throttleCheckUrl=https://api.getgud.com/game/throttle-check/
```

### Loading the config file

To load a configuration file, set the `CONFIG_PATH` and `CONFIG_FILENAME` environment variables to the path and filename of the configuration file, respectively.

```cpp
sdkConfig.LoadSettings();
```

Please note that error logs will be generated if `CONFIG_PATH` and `CONFIG_FILENAME` are not set.

Make sure to adjust the values in the configuration file according to your application's requirements.

## Usage

### Initialization

#### Init()

Before using the GetGud SDK, you must initialize it:

```cpp
GetGudSdk::Init();
```

This sets up internal components, such as memory management and network connections, and prepares the SDK for use.

### Starting and Ending Games

#### StartGame(titleId, privateKey, serverName, gameMode)

To start a new game, call `StartGame()` with the following parameters:
* titleId : internal titleId from Getgud, provided when you create a new title in Getgud
* privateKey : private key, provided along with the titleId after creating a new title in Getgud
* serverName : name of your game server
* gameMode : mode of the game you are about to start

```cpp
std::string gameGuid = GetGudSdk::StartGame(titleId, privateKey, serverName, gameMode);
```

#### StartGame(serverName, gameMode)

You can start a new game using environment variables `TITLE_ID` and `PRIVATE_KEY` for the titleId and privateKey:

```cpp
std::string gameGuid = GetGudSdk::StartGame(serverName, gameMode);
```

#### MarkEndGame(gameGuid)

When the game ends, you should mark it as finished for Getgud. To mark a game as finished, call `MarkEndGame()` with the game GUID:

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
