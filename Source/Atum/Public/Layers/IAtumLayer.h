﻿// © 2023 Kaya Adrian.

#pragma once

#include "Tensors/IAtumTensor.h"
#include "UObject/Interface.h"

#include "IAtumLayer.generated.h"


UINTERFACE(MinimalAPI, Blueprintable, BlueprintType, DisplayName = "ATUM Layer")
class UAtumLayer : public UInterface
{
	GENERATED_BODY()
};

class ATUM_API IAtumLayer
{
	GENERATED_BODY()
	
	bool bInitialized = false;

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool InitializeData();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool Forward(const TScriptInterface<IAtumTensor>& Input, TScriptInterface<IAtumTensor>& Output);

	UFUNCTION(BlueprintNativeEvent, BlueprintPure)
	bool IsInitialized() const;
	
	FORCEINLINE bool operator()(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) noexcept
	{ return Execute_Forward(_getUObject(), Input, Output); }

protected:
	virtual bool InitializeData_Implementation() noexcept;
	
	virtual bool Forward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) noexcept;

	UE_NODISCARD
	FORCEINLINE bool IsInitialized_Implementation() const noexcept { return bInitialized; }
};