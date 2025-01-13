// Fill out your copyright notice in the Description page of Project Settings.


#include "IndirectTexture.h"

#include "Engine/Texture.h"

UIndirectTexture::UIndirectTexture()
{
	TilesetTexture = nullptr;
	TilesetTileCount = FIntPoint(0, 0);
	IndirectTextureResolution = FIntPoint(0, 0);
	FCoreUObjectDelegates::OnObjectPropertyChanged.AddUObject(this, &UIndirectTexture::OnPropertyChanged);
}

void UIndirectTexture::GenerateTileIndexTexture()
{
	int width = IndirectTextureResolution.X;
	int height = IndirectTextureResolution.Y;
	UTexture2D* tiTexture = UTexture2D::CreateTransient(width, height, PF_B8G8R8A8);
	if (!tiTexture) return;

	tiTexture->Filter = TextureFilter::TF_Nearest;
	tiTexture->SRGB = false;

	FTexture2DMipMap& Mip = tiTexture->PlatformData->Mips[0];
	void* TextureData = Mip.BulkData.Lock(LOCK_READ_WRITE);


	FColor* Pixels = static_cast<FColor*>(TextureData);
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			int getRand = FMath::RandRange(0, TilesetTileCount.X * TilesetTileCount.Y - 1);
			int idxX = getRand % TilesetTileCount.X;
			int idxY = getRand / TilesetTileCount.X;

			Pixels[y * width + x] = FColor(idxX, idxY, 0, 0);
		}
	}

	Mip.BulkData.Unlock();
	tiTexture->UpdateResource();
	TileIndexTexture = tiTexture;
}

void UIndirectTexture::OnPropertyChanged(UObject* ObjectBeingModified, FPropertyChangedEvent& PropertyChangedEvent)
{
	if (ObjectBeingModified == this)
	{
		GenerateTileIndexTexture();
	}

}
