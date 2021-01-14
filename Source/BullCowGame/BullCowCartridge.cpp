// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    HiddenWordList = GetValidWords();
    PrintLine(TEXT("Number of isogram words in WordList: %i"), HiddenWordList.Num());
    InitGame();
}

TArray<FString> UBullCowCartridge::GetValidWords() const
{
    const FString WordListPath = FPaths::ProjectContentDir() / TEXT("WordLists/HiddenWordList.txt");
    TArray <FString> AllWords, FilteredWords;
    FFileHelper::LoadFileToStringArray(AllWords, *WordListPath);
    for (FString Word : AllWords)
    {
        if (IsIsogram(Word) && Word.Len() >= 4 && Word.Len() <= 8){
            FilteredWords.Emplace(Word);
        }
    }
    return FilteredWords;
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
    if (!IsIsogram(Guess)) {
        PrintLine(TEXT("Your guess, %s, is not a valid isogram. Try again!\n"), *Guess);
        return;
    }
    CountBullsAndCows(Guess);
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

    HiddenWord = TEXT("chosen");
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

bool UBullCowCartridge::IsIsogram(const FString& Word) const
{
    for (int i=0; i < Word.Len(); i++)
    {
        char currentLetter = Word[i];
        for (int j=i+1; j < Word.Len(); j++){
            if (currentLetter == Word[j]) {
                return false;
            }
        }
    }
    return true;
}

void UBullCowCartridge::CountBullsAndCows(const FString& Word) const
{
    int bulls = 0;
    int cows = 0;
    for (int i=0; i < Word.Len(); i++) {
        if (Word[i] == HiddenWord[i]) {
            bulls++;
        } else {
            for (int j=0; j < HiddenWord.Len(); j++) {
                if (Word[i] == HiddenWord[j]) {
                    cows++;
                }
            }
        }
    }
    PrintLine(TEXT("There are %i bulls and %i cows in your guess! Try Again."), bulls, cows);
}