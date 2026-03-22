#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "LobbyPlayerController.generated.h"

class ULobbyWidget;
class URoomWidget;

/**
 * 大厅玩家控制器
 * 负责管理大厅UI和房间UI的显示与切换
 */
UCLASS()
class FOKIGACLIENT_API ALobbyPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ALobbyPlayerController();

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowLobbyUI();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void ShowRoomUI();

	UFUNCTION(BlueprintCallable, Category = "UI")
	void HideAllUI();

protected:
	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<ULobbyWidget> LobbyWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category = "UI")
	TSubclassOf<URoomWidget> RoomWidgetClass;

private:
	UPROPERTY()
	ULobbyWidget* LobbyWidget;

	UPROPERTY()
	URoomWidget* RoomWidget;
};
