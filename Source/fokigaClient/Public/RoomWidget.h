#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RoomWidget.generated.h"

class UButton;
class UListView;
class UTextBlock;

/**
 * 房间界面控件
 * 显示当前房间成员列表，提供离开按钮
 */
UCLASS()
class FOKIGACLIENT_API URoomWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	URoomWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UListView* PlayerListView;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UButton* LeaveButton;

	UPROPERTY(BlueprintReadOnly, meta = (BindWidget))
	UTextBlock* RoomTitleText;

private:
	UFUNCTION()
	void OnLeaveButtonClicked();

	void RefreshPlayerList();
};
