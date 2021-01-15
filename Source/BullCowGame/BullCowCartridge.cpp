// Fill out your copyright notice in the Description page of Project Settings.
#include "BullCowCartridge.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

void UBullCowCartridge::BeginPlay() // When the game starts
{
    Super::BeginPlay();
    FBullCowCount Count;
    HiddenWordList = GetValidWords();
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
    FBullCowCount CurrentCount = GetBullCows(Guess);
    PrintLine(TEXT("There are %i bulls and %i cows in your guess! Try Again."), CurrentCount.Bulls, CurrentCount.Cows);
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
    int32 randomChoice = FMath::RandRange(0, HiddenWordList.Num()-1);
    HiddenWord = HiddenWordList[randomChoice];
    Lives = HiddenWord.Len() * 2;
    bGameOver = false;

    PrintLine(TEXT("Welcome to Bull Cows!"));
    PrintLine(TEXT("Please guess the %i letter word!"), HiddenWord.Len());
    PrintLine(TEXT("You start with %i lives."), Lives);
    PrintLine(TEXT("Type in your guess.\nPress <ENTER> to continue..."), HiddenWord.Len());
}

void UBullCowCartridge::EndGame()
{
    bGameOver = true;
    PrintLine("Press <ENTER> to continue.");
}

bool UBullCowCartridge::IsIsogram(const FString& Word)
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

FBullCowCount UBullCowCartridge::GetBullCows(const FString& Word) const
{
    FBullCowCount Count;
    for (int i=0; i < Word.Len(); i++) {
        if (Word[i] == HiddenWord[i]) {
            Count.Bulls++;
        } else {
            for (int j=0; j < HiddenWord.Len(); j++) {
                if (Word[i] == HiddenWord[j]) {
                    Count.Cows++;
                    break;
                }
            }
        }
    }
    return Count;
}
