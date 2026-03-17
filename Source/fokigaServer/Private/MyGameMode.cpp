#include "MyGameMode.h"
#include "MyServerGameState.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/PlayerState.h"

AMyGameMode::AMyGameMode()
{
	GameStateClass = AMyServerGameState::StaticClass();
}

void AMyGameMode::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("GameMode BeginPlay"));
}

void AMyGameMode::StartPlay()
{
	Super::StartPlay();
	AMyServerGameState* GS = GetGameState<AMyServerGameState>();
	if (GS)
	{
		UE_LOG(LogTemp, Warning, TEXT("GameState connected"));
	}
}

void AMyGameMode::PostLogin(APlayerController* NewPlayer)
{
	Super::PostLogin(NewPlayer);

	if (!NewPlayer) return;

	APlayerState* PS = NewPlayer->GetPlayerState<APlayerState>();
	if (!PS) return;

	// 分配ID
	int32 AssignedId = NextPlayerId++;

	// 记录
	PlayerMap.Add(AssignedId, PS);
	ReversePlayerMap.Add(PS, AssignedId);

	// 你也可以把ID写进 PlayerState
	PS->SetPlayerId(AssignedId);

	UE_LOG(LogTemp, Warning, TEXT("Player Joined: ID=%d"), AssignedId);
}

void AMyGameMode::Logout(AController* Exiting)
{
	Super::Logout(Exiting);

	if (!Exiting) return;

	APlayerState* PS = Exiting->GetPlayerState<APlayerState>();
	if (!PS) return;

	if (ReversePlayerMap.Contains(PS))
	{
		int32 Id = ReversePlayerMap[PS];

		PlayerMap.Remove(Id);
		ReversePlayerMap.Remove(PS);

		UE_LOG(LogTemp, Warning, TEXT("Player Left: ID=%d"), Id);
	}
}

AActor* AMyGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	return Super::ChoosePlayerStart_Implementation(Player);
}