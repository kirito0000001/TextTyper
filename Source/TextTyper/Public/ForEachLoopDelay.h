#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintAsyncActionBase.h"
#include "Engine/World.h"
#include "TimerManager.h"
#include "ForEachLoopDelay.generated.h"

/**
 * 
 */
UCLASS()
class TEXTTYPER_API UForEachLoopDelay : public UBlueprintAsyncActionBase
{
	GENERATED_BODY()

public: //公开
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnLoopDelegate, int, Index, UForEachLoopDelay*, Node);

	//多播委托的结构体，OneParam是单个参数，还有TwoParam等多个形式，括号是名字，和参数类型，名字

	UForEachLoopDelay(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
	virtual ~UForEachLoopDelay(); //析构函数

	/**
	 * For Loop 延迟
	 * @param InStart 开始的索引
	 * @param InEnd 结束的索引
	 * @param InDuration 每次的延迟时间
	 * @param bInForce 略过第一次延迟
	 */
	UFUNCTION(BlueprintCallable,  Category = "Foreachloopdelay",Meta = (BlueprintInternalUseOnly = true, DisplayName = "Dream Async For Loop Delay"))
	static UForEachLoopDelay* Async_ForLoopDelay(int InStart = 0, int InEnd = 1, float InDuration = 0.1f,
	                                            bool bInForce = false);
	//创建主要函数，创建输入参数【括号里】，返回一个UAsync_LoopDelay对象，名字后

	// 调用这个对象的自身break事件
	UFUNCTION(BlueprintCallable, Category = "Foreachloopdelay")
	void Break();

	/**
	 * Loop
	 */
	UPROPERTY(BlueprintAssignable ,Category = "Foreachloopdelay") //每次循环触发
	FOnLoopDelegate OnLoop;
	//输出引脚，cpp里可以触发

	/**
	 * Completed
	 */
	UPROPERTY(BlueprintAssignable, Category = "Foreachloopdelay") //结束时触发
	FOnLoopDelegate OnFinish;
	//输出引脚，cpp里可以触发

protected: //不会改变

	virtual void Activate() override;
	//激活函数，重写父类函数
	void LoopInternal();
	//循环函数，内部调用
	FTimerHandle Handle; //定时器句柄
	int Start = 0; //初始化输入参数
	int End = 0;
	float Duration = 0.f;
	bool bForce = false;
};
