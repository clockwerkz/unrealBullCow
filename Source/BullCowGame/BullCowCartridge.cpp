// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    InitGame();
    PrintLine(TEXT("The Hidden Word is %s, it is %i\ncharacters long."), *HiddenWord, HiddenWord.Len()); //Debug Line
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
            Lives--;
            if (Lives <= 0) {
                EndGame();  
            } else {
                if (Input.Len() != HiddenWord.Len()) {
                    PrintLine(TEXT("Sorry! Your guess is not %i letters!\nTry again."), HiddenWord.Len());
                } else {
                    PrintLine("Sorry! Wrong guess! Try again.");
                }
                PrintLine(TEXT("You are down to %i lives."), Lives);
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
    PrintLine("Game over! Press <ENTER> to continue.");
}