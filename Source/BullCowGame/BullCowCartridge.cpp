// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    PrintLine(TEXT("The Hidden Word is %s, it is %i\ncharacters long."), *HiddenWord, HiddenWord.Len()); //Debug Line
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
            if (Input.Len() != HiddenWord.Len()) {
                PrintLine(TEXT("Sorry! Your guess is not %i letters!\nTry again."), HiddenWord.Len());
            } else {
                PrintLine("Sorry! Wrong guess! Try again.");
            }
            Lives--;
            if (Lives < 0) {
                EndGame();  
            }
        }
    }

    /*  
    Check if input is an isogram
    If no:
    Prompt to Guess again
    If Yes:
    Check if input matches hiddenword
    Deduct a life
    Check lives >0
    If yes:
    GuessAgain
    Show lives left
    If No:
    Game Over show HiddenWord?
    Prompt to play again
    Yes -> Play Again
    No -> Exit 
    */
}

void UBullCowCartridge::InitGame()
{
/*     
    Setting up the game
    TODO Assign a random isogram as the HiddenWord
 */
    HiddenWord = TEXT("dialogue");
    Lives = 3;
    bGameOver = false;

    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Please guess the %i letter word.\nPress <ENTER> to continue."), HiddenWord.Len());
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine("Game over! Press <ENTER> to continue.");
}