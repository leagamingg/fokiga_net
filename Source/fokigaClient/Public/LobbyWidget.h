#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LobbyWidget.generated.h"

class UButton;
class UEditableTextBox;

/**
 * 大厅界面控件
 * 用于输入服务器IP、端口，并连接
 */
UCLASS()
class FOKIGACLIENT_API ULobbyWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	ULobbyWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UEditableTextBox* IpAddressBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UEditableTextBox* PortBox;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* JoinButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* CancelButton;

private:
	UFUNCTION()
	void OnJoinButtonClicked();

	UFUNCTION()
	void OnCancelButtonClicked();

	void ConnectToServer(const FString& Ip, int32 Port);
};
