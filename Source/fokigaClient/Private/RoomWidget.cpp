#include "RoomWidget.h"
#include "Components/Button.h"
#include "Components/ListView.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "GameFramework/PlayerState.h"
#include "PlayerListEntry.h"

URoomWidget::URoomWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
}

void URoomWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (LeaveButton)
	{
		LeaveButton->OnClicked.AddDynamic(this, &URoomWidget::OnLeaveButtonClicked);
	}

	if (RoomTitleText)
	{
		RoomTitleText->SetText(FText::FromString(TEXT("Game Room")));
	}

	RefreshPlayerList();
}

void URoomWidget::OnLeaveButtonClicked()
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

	UE_LOG(LogTemp, Warning, TEXT("Leave room clicked"));
	PC->ClientTravel(TEXT("127.0.0.1:7777"), ETravelType::TRAVEL_Absolute);
}

void URoomWidget::RefreshPlayerList()
{
	if (!PlayerListView)
	{
		return;
	}

	PlayerListView->ClearListItems();

	UWorld* World = GetWorld();
	if (!World)
	{
		return;
	}

	for (FConstPlayerControllerIterator It = World->GetPlayerControllerIterator(); It; ++It)
	{
		APlayerController* PC = It->Get();
		if (!PC)
		{
			continue;
		}

		APlayerState* PS = PC->GetPlayerState<APlayerState>();
		if (!PS)
		{
			continue;
		}

		FString PlayerName = PS->GetPlayerName();
		if (PlayerName.IsEmpty())
		{
			PlayerName = TEXT("Player");
		}

		UPlayerListEntry* Entry = NewObject<UPlayerListEntry>();
		Entry->PlayerName = PlayerName;
		PlayerListView->AddItem(Entry);
	}
}
