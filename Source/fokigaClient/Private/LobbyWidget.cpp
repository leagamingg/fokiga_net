#include "LobbyWidget.h"
#include "Components/Button.h"
#include "Components/EditableTextBox.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/GameModeBase.h"

ULobbyWidget::ULobbyWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void ULobbyWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (JoinButton)
	{
		JoinButton->OnClicked.AddDynamic(this, &ULobbyWidget::OnJoinButtonClicked);
	}

	if (CancelButton)
	{
		CancelButton->OnClicked.AddDynamic(this, &ULobbyWidget::OnCancelButtonClicked);
	}
}

void ULobbyWidget::OnJoinButtonClicked()
{
	FString IpAddress = TEXT("127.0.0.1");
	int32 Port = 7777;

	if (IpAddressBox)
	{
		IpAddress = IpAddressBox->GetText().ToString();
		if (IpAddress.IsEmpty())
		{
			IpAddress = TEXT("127.0.0.1");
		}
	}

	if (PortBox)
	{
		FString PortStr = PortBox->GetText().ToString();
		if (!PortStr.IsEmpty())
		{
			Port = FCString::Atoi(*PortStr);
		}
	}

	if (Port <= 0 || Port > 65535)
	{
		Port = 7777;
	}

	ConnectToServer(IpAddress, Port);
}

void ULobbyWidget::OnCancelButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("Cancel clicked"));
}

void ULobbyWidget::ConnectToServer(const FString& Ip, int32 Port)
{
	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	APlayerController* PC = UGameplayStatics::GetPlayerController(this, 0);
	if (!PC)
	{
		return;
	}

	FString LevelName = FString::Printf(TEXT("%s:%d"), *Ip, Port);
	UE_LOG(LogTemp, Warning, TEXT("Connecting to: %s"), *LevelName);

	PC->ClientTravel(LevelName, ETravelType::TRAVEL_Absolute);
}
