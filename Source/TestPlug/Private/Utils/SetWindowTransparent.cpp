// Fill out your copyright notice in the Description page of Project Settings.


#include "Utils/SetWindowTransparent.h"
#if PLATFORM_WINDOWS && !WITH_EDITOR
#include "Windows/WindowsWindow.h"
#include "dwmapi.h"
#endif


// Sets default values for this component's properties
USetWindowTransparent::USetWindowTransparent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

#if PLATFORM_WINDOWS && !WITH_EDITOR
void SetWindowTransparent()
{
	auto hwnd = ::GetActiveWindow();
	if (hwnd)
	{
		//SetWindowLongPtr(hwnd, GWL_STYLE, WS_VISIBLE);
		//SetWindowLongPtr(hwnd, GWL_EXSTYLE, WS_EX_LAYERED | WS_EX_TRANSPARENT);
		//const MARGINS margins{ -1,0,0,0 };
		//DwmExtendFrameIntoClientArea(hwnd, &margins);
		
		::SetWindowLong(hwnd, GWL_EXSTYLE, WS_EX_LAYERED|WS_EX_TRANSPARENT);
		::SetLayeredWindowAttributes(hwnd,RGB(255,0,0),0,LWA_COLORKEY);
	};
	
	
}
#endif
// Called when the game starts
void USetWindowTransparent::BeginPlay()
{
	Super::BeginPlay();

	// ...
#if PLATFORM_WINDOWS && !WITH_EDITOR
	SetWindowTransparent();
#endif
}


// Called every frame
void USetWindowTransparent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

