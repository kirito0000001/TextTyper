#include "ForEachLoopDelay.h"

UForEachLoopDelay::UForEachLoopDelay(const FObjectInitializer& ObjectInitializer)//构造函数
{
}

UForEachLoopDelay::~UForEachLoopDelay()//析构函数
{
}

// 创建一个异步循环延迟节点，并返回该节点，和主要函数对应
UForEachLoopDelay* UForEachLoopDelay::Async_ForLoopDelay(int InStart, int InEnd, float InDuration, bool bInForce)
{
	UForEachLoopDelay* Node = NewObject<UForEachLoopDelay>();//创建一个异步循环延迟节点
	Node->Start = InStart;//设置起始值和结束值
	Node->End = InEnd;
	Node->Duration = InDuration;//设置延迟时间
	Node->bForce = bInForce;//设置是否循环

	Node->RegisterWithGameInstance(GWorld);//注册到游戏实例中，异步需要让函数持续存在
	return Node;//返回节点
}

void UForEachLoopDelay::Break()
{
	GWorld->GetTimerManager().ClearTimer(Handle);
}

void UForEachLoopDelay::Activate()//激活函数
{
	if (bForce)//如果循环，触发循环函数，就是下面那个
		LoopInternal();
	GWorld->GetTimerManager().SetTimer(Handle, this, &UForEachLoopDelay::LoopInternal, Duration, true);
	// 设置定时器，每秒触发一次LoopInternal函数，参数1是定时器句柄，参数2是this指针，参数3是函数指针，参数4是延迟时间，参数5是循环
}

void UForEachLoopDelay::LoopInternal()//循环函数
{
	OnLoop.Broadcast(Start, this);
	Start++;//循环次数加一
	
	if (Start > End)//如果start参数大于结束参数，则结束循环，并触发结束函数
	{
		GWorld->GetTimerManager().ClearTimer(Handle);
		OnFinish.Broadcast(End, this);//.Broadcast前面的就是创建的函数
	}
}


