// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("Welcome to Cows!"));
    PrintLine(TEXT("Please press <Enter> to continue:"));
    InitGame();
    //TODO: Prompt the Player for a guess
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    ClearScreen();
    if (Input != "")
    {
        if (Input == HiddenWord)
        {
            PrintLine("You guessed correct!");
            HiddenWord = "";
        }
        else
        {
            PrintLine("Sorry! Wrong guess!");
            Lives--;
        }
    }
    //Check if input is an isogram
    //If no:
    //Prompt to Guess again
    //If Yes:
    //Check if input matches hiddenword
    //Deduct a life
    // Check lives >0
    //If yes:
    //GuessAgain
    //Show lives left
    //If No:
    //Game Over show HiddenWord?
    //Prompt to play again
    //Yes -> Play Again
    //No -> Exit
}

void UBullCowCartridge::InitGame()
{
    //Setting up the game
    //TODO Assign a random isogram as the HiddenWord
    HiddenWord = TEXT("dialogue");
    Lives = 3;
}