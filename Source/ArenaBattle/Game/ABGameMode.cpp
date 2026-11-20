// Fill out your copyright notice in the Description page of Project Settings.


#include "Game/ABGameMode.h"
#include "ABGameMode.h"
#include "Player/ABPlayerController.h"

// < 이모양의 괄호가 최근 C++에서 권장하는 인클루드 구문입니다.
// " 따옴표는 같은 경로에 있는 헤더 인클루드할 때 사용하라고 권장합니다.
#include <ArenaBattle.h>
#include "ABGameState.h"

AABGameMode::AABGameMode()
{
	static ConstructorHelpers::FClassFinder<APawn> DefaultPawnClassRef(TEXT("/Script/Engine.Blueprint'/Game/ArenaBattle/Blueprint/BP_ABCharacterPlayer.BP_ABCharacterPlayer_C'"));
	if (DefaultPawnClassRef.Class)
	{
		DefaultPawnClass = DefaultPawnClassRef.Class;
	}

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassRef(TEXT("/Script/ArenaBattle.ABPlayerController"));
	if (PlayerControllerClassRef.Class)
	{
		PlayerControllerClass = PlayerControllerClassRef.Class;
	}

	GameStateClass = AABGameState::StaticClass();
}

void AABGameMode::OnPlayerDead()
{

}

void AABGameMode::PreLogin(
	const FString& Options, 
	const FString& Address, 
	const FUniqueNetIdRepl& UniqueId, 
	FString& ErrorMessage)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("==============================="));
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::PreLogin(Options, Address, UniqueId, ErrorMessage);

	// NetDriver 가져오기.
	UNetDriver* NetDriver = GetNetDriver();
	if (NetDriver)
	{
		// 서버 입장에서 클라이언트의 접속이 있는지 확인.
		if (NetDriver->ClientConnections.Num() == 0)
		{
			AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("No client connections"));
		}
		else
		{
			for (const auto& Connection : NetDriver->ClientConnections)
			{
				AB_LOG(
					LogABNetwork, 
					Log, 
					TEXT("Client connection: %s"), 
					*Connection->GetName()
				);
			}
		}
	}
	else
	{
		AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("No NetDriver"));
	}

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

APlayerController* AABGameMode::Login(
	UPlayer * NewPlayer, 
	ENetRole InRemoteRole, 
	const FString & Portal, 
	const FString & Options, 
	const FUniqueNetIdRepl & UniqueId, 
	FString & ErrorMessage)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));

	APlayerController* NewPlayerController = Super::Login(
		NewPlayer, InRemoteRole, Portal, Options, UniqueId, ErrorMessage);

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));

	return NewPlayerController;
}

void AABGameMode::PostLogin(APlayerController* NewPlayer)
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));

	Super::PostLogin(NewPlayer);

	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}

void AABGameMode::StartPlay()
{
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("Begin"));
	
	Super::StartPlay();
	
	AB_LOG(LogABNetwork, Log, TEXT("%s"), TEXT("End"));
}
