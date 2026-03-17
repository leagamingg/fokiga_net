// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MyGameMode.generated.h"

/**
 * 
 */
UCLASS()
class FOKIGASERVER_API AMyGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	AMyGameMode();

protected:

	virtual void StartPlay() override;
	
	// Match 流程
	virtual void BeginPlay() override;

	// 玩家登录
	virtual void PostLogin(APlayerController* NewPlayer) override;

	// 玩家登出
	virtual void Logout(AController* Exiting) override;

	// 玩家重生点选择
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;

private:
	// 自增ID
	int32 NextPlayerId = 1;

	// ID -> PlayerState
	UPROPERTY()
	TMap<int32, APlayerState*> PlayerMap;

	// 反查（方便删除）
	UPROPERTY()
	TMap<APlayerState*, int32> ReversePlayerMap;
};
