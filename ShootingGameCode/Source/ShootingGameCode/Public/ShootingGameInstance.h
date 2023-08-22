// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "ShootingGameCode.h"
#include "FindSessionsCallbackProxy.h"
#include "Engine/DataTable.h"
#include "Weapon.h"
#include "Engine/GameInstance.h"
#include "ShootingGameInstance.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FDele_SessionResult, 
	bool, IsFind, const TArray<FBlueprintSessionResult>&, SessionResult);

/**
 * 
 */
UCLASS()
class SHOOTINGGAMECODE_API UShootingGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UShootingGameInstance(const FObjectInitializer& ObjectInitializer);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDataTable* WeaponData;

	FST_Weapon* GetWeaponRowData(FName name);

	FName GetWeaponRandomRowName();

	//--------------------------------------------------------------[ Start - Create Session Code ]------------------------------------------------------------------//
public:
	/**
	*	Function to host a game!
	*
	*	@Param		UserID			User that started the request
	*	@Param		SessionName		Name of the Session
	*	@Param		bIsLAN			Is this is LAN Game?
	*	@Param		bIsPresence		"Is the Session to create a presence Session"
	*	@Param		MaxNumPlayers	        Number of Maximum allowed players on this "Session" (Server)
	*/
	bool HostSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, bool bIsLAN, bool bIsPresence, int32 MaxNumPlayers);

	/* Delegate called when session created */
	FOnCreateSessionCompleteDelegate OnCreateSessionCompleteDelegate;
	/* Delegate called when session started */
	FOnStartSessionCompleteDelegate OnStartSessionCompleteDelegate;

	/** Handles to registered delegates for creating/starting a session */
	FDelegateHandle OnCreateSessionCompleteDelegateHandle;
	FDelegateHandle OnStartSessionCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSettings> SessionSettings;
	// In our UNWGameInstance.h:

	/**
	*	Function fired when a session create request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnCreateSessionComplete(FName SessionName, bool bWasSuccessful);

	/**
	*	Function fired when a session start request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnStartOnlineGameComplete(FName SessionName, bool bWasSuccessful);

	//--------------------------------------------------------------[ End - Create Session Code ]------------------------------------------------------------------//


	//--------------------------------------------------------------[ Start - Find Session Code ]------------------------------------------------------------------//

	/**
	*	Find an online session
	*
	*	@param UserId user that initiated the request
	*	@param bIsLAN are we searching LAN matches
	*	@param bIsPresence are we searching presence sessions
	*/
	void FindSessions(TSharedPtr<const FUniqueNetId> UserId, bool bIsLAN, bool bIsPresence);

	/** Delegate for searching for sessions */
	FOnFindSessionsCompleteDelegate OnFindSessionsCompleteDelegate;

	/** Handle to registered delegate for searching a session */
	FDelegateHandle OnFindSessionsCompleteDelegateHandle;

	TSharedPtr<class FOnlineSessionSearch> SessionSearch;

	/**
	*	Delegate fired when a session search query has completed
	*
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnFindSessionsComplete(bool bWasSuccessful);

	//--------------------------------------------------------------[ End - Find Session Code ]------------------------------------------------------------------//

	//--------------------------------------------------------------[ Start - Join Session Code ]------------------------------------------------------------------//

	/**
	*	Joins a session via a search result
	*
	*	@param SessionName name of session
	*	@param SearchResult Session to join
	*
	*	@return bool true if successful, false otherwise
	*/
	bool JoinSession(TSharedPtr<const FUniqueNetId> UserId, FName SessionName, const FOnlineSessionSearchResult& SearchResult);

	/** Delegate for joining a session */
	FOnJoinSessionCompleteDelegate OnJoinSessionCompleteDelegate;

	/** Handle to registered delegate for joining a session */
	FDelegateHandle OnJoinSessionCompleteDelegateHandle;

	/**
	*	Delegate fired when a session join request has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	void OnJoinSessionComplete(FName SessionName, EOnJoinSessionCompleteResult::Type Result);

	//--------------------------------------------------------------[ End - Join Session Code ]------------------------------------------------------------------//


	//--------------------------------------------------------------[ Start - Destroy Session Code ]------------------------------------------------------------------//

	/** Delegate for destroying a session */
	FOnDestroySessionCompleteDelegate OnDestroySessionCompleteDelegate;

	/** Handle to registered delegate for destroying a session */
	FDelegateHandle OnDestroySessionCompleteDelegateHandle;

	/**
	*	Delegate fired when a destroying an online session has completed
	*
	*	@param SessionName the name of the session this callback is for
	*	@param bWasSuccessful true if the async action completed without error, false if there was an error
	*/
	virtual void OnDestroySessionComplete(FName SessionName, bool bWasSuccessful);

	//--------------------------------------------------------------[ End - Destroy Session Code ]------------------------------------------------------------------//

	//--------------------------------------------------------------[ Start - Session Test Code ]------------------------------------------------------------------//

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void StartOnlineGame(bool bIsLAN, int MaxNumPlayers, FString Name);

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void FindOnlineGames();

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void JoinOnlineGame(FBlueprintSessionResult SessionResult, FString Name);

	UFUNCTION(BlueprintCallable, Category = "Network|Test")
	void DestroySessionAndLeaveGame();

	//--------------------------------------------------------------[ End - Session Test Code ]------------------------------------------------------------------//

	/** virtual function to allow custom GameInstances an opportunity to do cleanup when shutting down */
	virtual void Shutdown() override;

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnUpdateSessionResult(const TArray<FBlueprintSessionResult>& SessionResults);

	void OnUpdateSessionResult_Implementation(const TArray<FBlueprintSessionResult>& SessionResults);

	UPROPERTY(BlueprintAssignable, VisibleAnywhere, BlueprintCallable)
	FDele_SessionResult Fuc_Dele_SessionResult;

public:
	FString UserName;

	UFUNCTION(BlueprintCallable)
	void SetUserName(FString name) { UserName = name; };

	UFUNCTION(BlueprintPure)
	FString GetUserName() { return UserName; };
};
