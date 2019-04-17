#pragma once

#include "CoreMinimal.h"

using FTsuTypeSet = TSet<UField*>;

class TSURUNTIME_API FTsuReflection
{
	static const FName MetaWorldContext;
	static const FName MetaNativeMakeFunc;
	static const FName MetaNativeBreakFunc;
	static const FName MetaBlueprintInternalUseOnly;
	static const FName MetaTsuExtensionLibrary;

public:
	using TypeVisitor = TFunction<void(UField*, const FTsuTypeSet&)>;
	using LibraryVisitor = TFunction<void(UClass*)>;
	using MakeVisitor = TFunction<void(UFunction*, UScriptStruct*)>;
	using BreakVisitor = TFunction<void(UFunction*, UScriptStruct*)>;
	using PropertyVisitor = TFunction<void(UProperty*, bool)>;
	using MethodVisitor = TFunction<void(UFunction*)>;
	using ExtensionVisitor = TFunction<void(UFunction*)>;
	using ParameterVisitor = TFunction<void(UProperty*)>;
	using ReturnVisitor = TFunction<void(UProperty*)>;
	using PropertyTypeVisitor = TFunction<void(UField*)>;

	static bool IsInternalType(UField* Type);
	static bool IsInternalProperty(UProperty* Property);
	static bool UsesInternalTypes(UFunction* Function);
	static bool IsInternalFunction(UFunction* Function);
	static bool IsExposedFunction(UFunction* Function);
	static bool IsStaticBlueprintFunction(UFunction* Function);
	static bool IsExplicitExtension(UClass* Class);
	static bool IsExplicitExtension(UFunction* Function);
	static bool IsExplicitExtension(UField* Field);
	static bool IsExtensionFunction(UFunction* Function);
	static bool IsInvalidClass(UClass* Class);
	static bool IsValidClass(UClass* Class);
	static bool IsExposedProperty(UProperty* Property);
	static bool IsDelegateProperty(UProperty* Property);
	static bool HasDelegateParameter(UFunction* Function);
	static bool IsReadOnlyProperty(UProperty* Property);
	static bool IsReferenceParameter(UProperty* Param);
	static bool IsK2Method(const FString& FunctionName);
	static bool IsK2Method(UFunction* Function);
	static bool IsOutputParameter(UProperty* Param, bool bAllowReturnParam = false);
	static bool HasOutputParameters(UFunction* Function);
	static bool IsInputParameter(UProperty* Param);

	static void VisitAllTypes(const TypeVisitor& Visitor);
	static void VisitFunctionLibraries(const LibraryVisitor& Visitor);
	static void VisitMakeFunctions(const MakeVisitor& Visitor);
	static void VisitBreakFunctions(const BreakVisitor& Visitor);
	static void VisitObjectProperties(const PropertyVisitor& Visitor, UStruct* Object, bool bIncludeDerived = false);
	static void VisitObjectMethods(const MethodVisitor& Visitor, UStruct* Object);
	static void VisitObjectExtensions(const ExtensionVisitor& Visitor, UStruct* Object);
	static bool VisitFunctionParameters(const ParameterVisitor& Visitor, UFunction* Function, bool bSkipFirst = false, bool bSkipWorldContext = true);
	static void VisitFunctionReturns(const ReturnVisitor& Visitor, UFunction* Function);
	static void VisitPropertyType(const PropertyTypeVisitor& Visitor, UProperty* Property);

	static bool GetReferencesInType(UField* Type, FTsuTypeSet& OutReferences);
	static void GetReferencesInFunction(UFunction* Function, FTsuTypeSet& OutReferences);
	static void GetReferencesInProperty(UProperty* Property, FTsuTypeSet& OutReferences);

	static UFunction* FindMakeFunction(UStruct* Struct);
	static UFunction* FindBreakFunction(UStruct* Struct);
	static bool HasMakeFunction(UStruct* Struct);
	static bool HasBreakFunction(UStruct* Struct);

	static UField* FindTypeByName(const FString& TypeName);
};
