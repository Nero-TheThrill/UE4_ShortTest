// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "IndirectTexture.generated.h"

UCLASS()
class ENGINE_API UIndirectTexture : public UDataAsset
{
	GENERATED_BODY()
public:
	UIndirectTexture();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
		UTexture2D* TilesetTexture;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
		FIntPoint TilesetTileCount;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "MyCategory")
		FIntPoint IndirectTextureResolution;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "MyCategory")
		UTexture2D* TileIndexTexture;

private:
	void GenerateTileIndexTexture();
	void OnPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent);
};
