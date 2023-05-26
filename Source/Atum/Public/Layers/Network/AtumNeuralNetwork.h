﻿// © 2023 Kaya Adrian.

#pragma once

#include "AtumMacros.h"
#include "AtumNeuralNetworkOptions.h"
#include "Layers/IAtumLayer.h"

LIBTORCH_INCLUDES_START
#include <torch/nn/cloneable.h>
LIBTORCH_INCLUDES_END

#include "AtumNeuralNetwork.generated.h"


#define LOCTEXT_NAMESPACE "AtumNeuralNetwork"

// ReSharper disable CppUE4CodingStandardNamingViolationWarning
namespace torch::nn
{
	class AtumNetworkImpl : public Cloneable<AtumNetworkImpl>
	{
	public:
		AtumNetworkOptions options;
		
		UE_NODISCARD_CTOR
		explicit AtumNetworkImpl(const AtumNetworkOptions& options_) noexcept;
		
		UE_NODISCARD
		// ReSharper disable once CppMemberFunctionMayBeStatic
		FORCEINLINE Tensor forward(const Tensor& input) { return input; }
		
		virtual void reset() override;
		virtual void pretty_print(std::ostream& stream) const override;
	};
	
	TORCH_MODULE(AtumNetwork);
}
// ReSharper restore CppUE4CodingStandardNamingViolationWarning


UCLASS(Blueprintable, BlueprintType, DisplayName = "ATUM Neural Network")
class ATUM_API UAtumNeuralNetwork : public UObject, public IAtumLayer
{
	GENERATED_BODY()
	GENERATED_ATUM_LAYER(torch::nn::AtumNetwork)
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess, ShowOnlyInnerProperties))
	FAtumNeuralNetworkOptions Options;
	
	UPROPERTY(Transient, NonTransactional, VisibleAnywhere)
	TArray<TScriptInterface<IAtumLayer>> RegisteredLayers;
	
public:
	UFUNCTION(BlueprintCallable, Category = "ATUM|Network", meta = (Keywords = "ATUM Register Layer"))
	FORCEINLINE bool RegisterLayer(const TScriptInterface<IAtumLayer>& Layer) noexcept
	{ return RegisterLayerAt(Layer, RegisteredLayers.Num()); }
	
	UFUNCTION(BlueprintCallable, Category = "ATUM|Network", meta = (Keywords = "ATUM Register Layer At Index"))
	bool RegisterLayerAt(const TScriptInterface<IAtumLayer>& Layer, int32 Index = 0) noexcept;
	
protected:
	virtual bool OnInitializeData_Implementation(bool bRetry = false) noexcept override;
	
	virtual bool OnForward_Implementation(
		const TScriptInterface<IAtumTensor>& Input,
		TScriptInterface<IAtumTensor>& Output
	) override;
};

#undef LOCTEXT_NAMESPACE