// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    InitGame();
}

void UBullCowCartridge::OnInput(const FString &Input) // When the player hits enter
{
    //TODO: Reinstate check to make sure input is not empty
    if (bGameOver) 
    {
        ClearScreen();
        InitGame();
    } else {
        if (Input == HiddenWord)
        {
            PrintLine("You guessed correct!");
            EndGame();      
        }
        else 
        {
            ProcessGuess(Input);
        }
    }


}

void UBullCowCartridge::ProcessGuess(const FString& Guess)
{
    if (Guess.Len() != HiddenWord.Len()) {
        PrintLine(TEXT("Sorry! Your guess is not %i letters!\nTry again."), HiddenWord.Len());
        return;
    }
    //TODO: Check if Guess is an isogram
    PrintLine("Sorry! Wrong guess! Try again.");
    PrintLine(TEXT("You still have %i lives."), --Lives);
    if (Lives <= 0) {
        PrintLine(TEXT("Game over!\nThe hidden word was %s.\n"), *HiddenWord);
        return EndGame();  
    }
}

void UBullCowCartridge::InitGame()
{
/*     
    Setting up the game
    TODO Assign a random isogram as the HiddenWord
 */
    HiddenWord = TEXT("cake");
    Lives = HiddenWord.Len();
    bGameOver = false;

    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Please guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You start with %i lives."), HiddenWord.Len());
    PrintLine(TEXT("Type in your guess.\nPress <ENTER> to continue..."), HiddenWord.Len());
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine("Press <ENTER> to continue.");
}