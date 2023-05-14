﻿// © 2023 Kaya Adrian.

#pragma once

#include "Kismet/BlueprintFunctionLibrary.h"

#include <format>
#include <sstream>
#include <vector>

#include "AtumLibraryUtilities.generated.h"


UCLASS(Abstract, Blueprintable, BlueprintType, DisplayName = "ATUM Utility Library")
class ATUM_API UAtumLibraryUtilities : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	template <typename T>
	UE_NODISCARD
	static std::string FormatWithConjunction(
		const std::vector<T>& Values,
		std::string_view Separator,
		std::string_view Prefix = "",
		std::string_view Suffix = "",
		std::string_view Conjunction = "",
		bool bSerialSeparator = true
	) noexcept;
};


template <typename T>
std::string UAtumLibraryUtilities::FormatWithConjunction(
	const std::vector<T>& Values,
	const std::string_view Separator,
	const std::string_view Prefix,
	const std::string_view Suffix,
	const std::string_view Conjunction,
	const bool bSerialSeparator
) noexcept
{
	const size_t ValueCount = Values.size();
	if (UNLIKELY(ValueCount == 0u))
		return "";
	
	std::ostringstream Stream;
	
	Stream << Prefix;
	if (ValueCount > 1u)
	{
		if (ValueCount > 2u)
		{
			std::copy(
				Values.begin(),
				Values.end() - 2u,
				std::ostream_iterator<T>(Stream, std::format("{}{}{}", Suffix, Separator, Prefix).c_str())
			);
		}
		Stream << Values[ValueCount - 2u] << Suffix << (bSerialSeparator ? Separator : "") << Conjunction << Prefix;
	}
	Stream << Values.back() << Suffix;
	
	return Stream.str();
}