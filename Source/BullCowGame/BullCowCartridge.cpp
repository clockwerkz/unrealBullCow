// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
FString HiddenWord;

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Cows!"));
    PrintLine(TEXT("Please press <Enter> to continue:"));
    HiddenWord = TEXT("dialogue");
}

void UBullCowCartridge::OnInput(const FString& Input) // When the player hits enter
{
    ClearScreen();
    PrintLine("Hidden word is: " + HiddenWord);
    if (Input != "") {
        if (Input == HiddenWord)
        {
            PrintLine("You guessed correct!");
            HiddenWord = "";
        } else {
            PrintLine("Sorry! Wrong guess!");
        }
    }
}