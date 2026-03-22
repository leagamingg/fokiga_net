#include "LobbyPlayerController.h"
#include "LobbyWidget.h"
#include "RoomWidget.h"
#include "Blueprint/UserWidget.h"
#include "Components/WidgetComponent.h"

ALobbyPlayerController::ALobbyPlayerController()
{
	LobbyWidgetClass = nullptr;
	RoomWidgetClass = nullptr;
	LobbyWidget = nullptr;
	RoomWidget = nullptr;
}

void ALobbyPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG(LogTemp, Warning, TEXT("LobbyPlayerController BeginPlay"));

	if (!IsLocalPlayerController())
	{
		UE_LOG(LogTemp, Warning, TEXT("Not local controller, skipping UI"));
		return;
	}

	ShowLobbyUI();
}

void ALobbyPlayerController::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	HideAllUI();

	Super::EndPlay(EndPlayReason);
}

void ALobbyPlayerController::ShowLobbyUI()
{
	HideAllUI();

	UE_LOG(LogTemp, Warning, TEXT("ShowLobbyUI called, LobbyWidgetClass: %s"), 
		LobbyWidgetClass ? TEXT("Set") : TEXT("NULL"));

	if (!LobbyWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("LobbyWidgetClass is not set"));
		return;
	}

	if (!LobbyWidget)
	{
		LobbyWidget = CreateWidget<ULobbyWidget>(this, LobbyWidgetClass);
	}

	if (LobbyWidget)
	{
		LobbyWidget->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("LobbyWidget added to viewport"));
	}
}

void ALobbyPlayerController::ShowRoomUI()
{
	HideAllUI();

	UE_LOG(LogTemp, Warning, TEXT("ShowRoomUI called, RoomWidgetClass: %s"),
		RoomWidgetClass ? TEXT("Set") : TEXT("NULL"));

	if (!RoomWidgetClass)
	{
		UE_LOG(LogTemp, Error, TEXT("RoomWidgetClass is not set"));
		return;
	}

	if (!RoomWidget)
	{
		RoomWidget = CreateWidget<URoomWidget>(this, RoomWidgetClass);
	}

	if (RoomWidget)
	{
		RoomWidget->AddToViewport();
		UE_LOG(LogTemp, Warning, TEXT("RoomWidget added to viewport"));
	}
}

void ALobbyPlayerController::HideAllUI()
{
	if (LobbyWidget)
	{
		LobbyWidget->RemoveFromParent();
	}

	if (RoomWidget)
	{
		RoomWidget->RemoveFromParent();
	}
}
