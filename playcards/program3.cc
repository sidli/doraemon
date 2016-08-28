/*
 * File:   main.cpp
 * Author: Hugo Wen
 *
 * Created on
 */
#include <stdio.h>
#include <string.h>

#define MEMCMP(a, b, c)               (memcmp((a), (b), (c)))
#define MEMSET(a, b, c)               (memset((a), (b), (c)))
#define MEM_CPY_OR_INIT(a, b, c)      ((b) == NULL) ? (memset((a), 0, (c))) : (memcpy((a), (b), (c)))

#define CARD_NUM              17

#define CARD_TYPE             14
#define HANDS_MAX_NUM         50000

#define STRING_MAX_LEN        53
#define STRING_NUM_START_IDX  50

typedef enum {
    IsEqual,
    IsInclusion,
    NotInclusion
} eInclusionOrSame;


// All input cards, card number and index:
// 0,1,2,3,4,5,6,7,8,9,10,11,12,13
// 3,4,5,6,7,8,9,S,J,Q,K ,A ,2 ,W
char allCards[CARD_TYPE] = {0};

// All the single hands, without repetition.
int allSingleHandsCount = 0;
char allSingleHands[HANDS_MAX_NUM][CARD_TYPE] = {0};

// All kinds of play schema.
int allPlaySchemaCount = 0;
char allPlaySchema[HANDS_MAX_NUM][STRING_MAX_LEN] = {0};

// How many hands are needed for the best schema.
int minHandsNum = 0xFF;




///////////////////////////////////////////////////////////////////////////////
// Function Name     : initCards
// Description       : Function to format "cards" string into array.
// 
void initCards(char cards[CARD_NUM])
{
    // Init global object.
    MEMSET(allCards, 0, CARD_TYPE);
    allSingleHandsCount = 0;
    MEMSET(allSingleHands, 0, HANDS_MAX_NUM*CARD_TYPE);
    allPlaySchemaCount = 0;
    MEMSET(allPlaySchema, 0, HANDS_MAX_NUM*STRING_MAX_LEN);
    minHandsNum = 0xFF;

   for (int i = 0; i < CARD_NUM; i++)
    {
        switch (cards[i])
        {
            case '3':
                allCards[0]++;
                break;
            case '4':
                allCards[1]++;
                break;
            case '5':
                allCards[2]++;
                break;
            case '6':
                allCards[3]++;
                break;
            case '7':
                allCards[4]++;
                break;
            case '8':
                allCards[5]++;
                break;
            case '9':
                allCards[6]++;
                break;
            case 'S':
                allCards[7]++;
                break;
            case 'J':
                allCards[8]++;
                break;
            case 'Q':
                allCards[9]++;
                break;
            case 'K':
                allCards[10]++;
                break;
            case 'A':
                allCards[11]++;
                break;
            case '2':
                allCards[12]++;
                break;
            case 'W':
                allCards[13]++;
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : isEqualOrInclusion
// Description       : Function to judge if "input" is part of the "base", or equal.
// 
eInclusionOrSame isEqualOrInclusion(char input[CARD_TYPE], char base[CARD_TYPE])
{
    eInclusionOrSame ret = IsEqual;
    for (int i = 0; i < CARD_TYPE; i++)
    {
        if (input[i] > base[i])
        {
            return NotInclusion;
        }
        if (input[i] < base[i])
        {
            ret = IsInclusion;
        }
    }
    return ret;
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : getUnusedCards
// Description       : Function to get unused cards. "base" minus "used".
// 
void getUnusedCards(char used[CARD_TYPE], char base[CARD_TYPE])
{
    if (used == NULL || base == NULL)
    {
        return;
    }
    for (int i = 0; i < CARD_TYPE; i++)
    {
        base[i] -= used[i];
    }
    return;
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : addCardsToString
// Description       : Function to format "cards" array into string and add 
//                     it at the end of "str".
// 
void addCardsToString(char cards[CARD_TYPE], char str[STRING_MAX_LEN])
{
    if (*str != '\0')
    {
        strcat(str, " ");
    }
    for (int i = 0; i < CARD_TYPE; i++)
    {
        for (int j = 0; j < cards[i]; j++)
        {
            switch (i)
            {
                case 0:
                    strcat(str, "3");
                    break;
                case 1:
                    strcat(str, "4");
                    break;
                case 2:
                    strcat(str, "5");
                    break;
                case 3:
                    strcat(str, "6");
                    break;
                case 4:
                    strcat(str, "7");
                    break;
                case 5:
                    strcat(str, "8");
                    break;
                case 6:
                    strcat(str, "9");
                    break;
                case 7:
                    strcat(str, "S");
                    break;
                case 8:
                    strcat(str, "J");
                    break;
                case 9:
                    strcat(str, "Q");
                    break;
                case 10:
                    strcat(str, "K");
                    break;
                case 11:
                    strcat(str, "A");
                    break;
                case 12:
                    strcat(str, "2");
                    break;
                case 13:
                    strcat(str, "W");
                    break;
                default:
                    ;
            }
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : addSingleHand
// Description       : Function to save a "singleHand".
//
void addSingleHand(char singleHand[CARD_TYPE])
{
    for (int i = 0; i < allSingleHandsCount; i++)
    {
        if (!MEMCMP(allSingleHands[i], singleHand, CARD_TYPE))
        {
            return;
        }
    }
    MEM_CPY_OR_INIT(&(allSingleHands[allSingleHandsCount]), singleHand, CARD_TYPE);
    allSingleHandsCount++;
    return;
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : analyze_A_Hands
// Description       : Function analyze A kind of "singleHand".
// 
void analyze_A_Hands(char inUsedCards[CARD_TYPE] = NULL)
{
    char tempAllCards[CARD_TYPE] = {0};
    char tempInUsedCards[CARD_TYPE] = {0};
    MEM_CPY_OR_INIT(tempAllCards, allCards, CARD_TYPE);
    MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
    getUnusedCards(inUsedCards, tempAllCards);
    for (int i = 0; i < CARD_TYPE; i++)
    {
        MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
        switch (tempAllCards[i])
        {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                tempInUsedCards[i] += 1;
                addSingleHand(tempInUsedCards);
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : analyze_AA_Hands
// Description       : Function analyze AA kind of "singleHand".
// 
void analyze_AA_Hands(char inUsedCards[CARD_TYPE] = NULL)
{
    char tempAllCards[CARD_TYPE] = {0};
    char tempInUsedCards[CARD_TYPE] = {0};
    MEM_CPY_OR_INIT(tempAllCards, allCards, CARD_TYPE);
    MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
    getUnusedCards(inUsedCards, tempAllCards);
    for (int i = 0; i < CARD_TYPE; i++)
    {
        MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
        switch (tempAllCards[i])
        {
            case 0:
            case 1:
                break;
            case 2:
            case 3:
            case 4:
                tempInUsedCards[i] += 2;
                addSingleHand(tempInUsedCards);
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : analyze_AAA_Hands
// Description       : Function analyze AAA kind of "singleHand".
// 
void analyze_AAA_Hands(char inUsedCards[CARD_TYPE] = NULL)
{
    char tempAllCards[CARD_TYPE] = {0};
    char tempInUsedCards[CARD_TYPE] = {0};
    MEM_CPY_OR_INIT(tempAllCards, allCards, CARD_TYPE);
    MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
    getUnusedCards(inUsedCards, tempAllCards);
    for (int i = 0; i < CARD_TYPE; i++)
    {
        MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
        switch (tempAllCards[i])
        {
            case 0:
            case 1:
            case 2:
                break;
            case 3:
            case 4:
                tempInUsedCards[i] += 3;
                addSingleHand(tempInUsedCards);
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : analyze_AAAA_Hands
// Description       : Function analyze AAAA kind of "singleHand".
// 
void analyze_AAAA_Hands(char inUsedCards[CARD_TYPE] = NULL)
{
    char tempAllCards[CARD_TYPE] = {0};
    char tempInUsedCards[CARD_TYPE] = {0};
    MEM_CPY_OR_INIT(tempAllCards, allCards, CARD_TYPE);
    MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
    getUnusedCards(inUsedCards, tempAllCards);
    for (int i = 0; i < CARD_TYPE; i++)
    {
        MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
        switch (tempAllCards[i])
        {
            case 0:
            case 1:
            case 2:
            case 3:
                break;
            case 4:
                tempInUsedCards[i] += 4;
                addSingleHand(tempInUsedCards);
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : analyze_AAA_B_or_BB_Hands
// Description       : Function analyze AAA_B or AAA_BB kind of "singleHand".
// 
void analyze_AAA_B_or_BB_Hands(char inUsedCards[CARD_TYPE] = NULL)
{
    char tempAllCards[CARD_TYPE] = {0};
    char tempInUsedCards[CARD_TYPE] = {0};
    MEM_CPY_OR_INIT(tempAllCards, allCards, CARD_TYPE);
    MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
    getUnusedCards(inUsedCards, tempAllCards);
    for (int i = 0; i < CARD_TYPE; i++)
    {
        MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
        switch (tempAllCards[i])
        {
            case 0:
            case 1:
            case 2:
                break;
            case 3:
            case 4:
                tempInUsedCards[i] += 3;
                analyze_A_Hands(tempInUsedCards);
                analyze_AA_Hands(tempInUsedCards);
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : analyze_ABCDE_Hands
// Description       : Function analyze ABCDE kind of "singleHand".
// 
void analyze_ABCDE_Hands(char inUsedCards[CARD_TYPE] = NULL)
{
    char tempAllCards[CARD_TYPE] = {0};
    char tempInUsedCards[CARD_TYPE] = {0};
    MEM_CPY_OR_INIT(tempAllCards, allCards, CARD_TYPE);
    MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
    getUnusedCards(inUsedCards, tempAllCards);
    for (int i = 0; i < CARD_TYPE; i++)
    {
        MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
        switch (tempAllCards[i])
        {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                for (int endCard = i+1; endCard <= 11; endCard++)
                {
                    if (tempAllCards[endCard] == 0)
                    {
                        break;
                    }
                    if (endCard - i >= 4)
                    {
                        MEMSET(&(tempInUsedCards[i]), 1, endCard - i + 1);
                        addSingleHand(tempInUsedCards);
                    }
                }
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : analyze_AABBCC_Hands
// Description       : Function analyze AABBCC kind of "singleHand".
// 
void analyze_AABBCC_Hands(char inUsedCards[CARD_TYPE] = NULL)
{
    char tempAllCards[CARD_TYPE] = {0};
    char tempInUsedCards[CARD_TYPE] = {0};
    MEM_CPY_OR_INIT(tempAllCards, allCards, CARD_TYPE);
    MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
    getUnusedCards(inUsedCards, tempAllCards);
    for (int i = 0; i < CARD_TYPE; i++)
    {
        MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
        switch (tempAllCards[i])
        {
            case 0:
            case 1:
                break;
            case 2:
            case 3:
            case 4:
                for (int endCard = i+1; endCard <= 11; endCard++)
                {
                    if (tempAllCards[endCard] <= 1)
                    {
                        break;
                    }
                    if (endCard - i >= 2)
                    {
                        MEMSET(&(tempInUsedCards[i]), 2, endCard - i + 1);
                        addSingleHand(tempInUsedCards);
                    }
                }
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : analyze_AAABBB_Hands
// Description       : Function analyze AAABBB kind of "singleHand".
// 
void analyze_AAABBB_Hands(char inUsedCards[CARD_TYPE] = NULL)
{
    char tempAllCards[CARD_TYPE] = {0};
    char tempInUsedCards[CARD_TYPE] = {0};
    MEM_CPY_OR_INIT(tempAllCards, allCards, CARD_TYPE);
    MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
    getUnusedCards(inUsedCards, tempAllCards);
    for (int i = 0; i < CARD_TYPE; i++)
    {
        MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
        switch (tempAllCards[i])
        {
            case 0:
            case 1:
            case 2:
                break;
            case 3:
            case 4:
                for (int endCard = i+1; endCard <= 11; endCard++)
                {
                    if (tempAllCards[endCard] <= 2)
                    {
                        break;
                    }
                    if (endCard - i >= 1)
                    {
                        MEMSET(&(tempInUsedCards[i]), 3, endCard - i + 1);
                        addSingleHand(tempInUsedCards);
                    }
                }
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : analyzeSeveralSingleCards
// Description       : Function analyze several single card, 
//                     sub-function called by other singleHands get functions.
// 
void analyzeSeveralSingleCards(char cardNum, char inUsedCards[CARD_TYPE] = NULL, char startIdx = 0)
{
    char tempAllCards[CARD_TYPE] = {0};
    char tempInUsedCards[CARD_TYPE] = {0};
    MEM_CPY_OR_INIT(tempAllCards, allCards, CARD_TYPE);
    MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
    getUnusedCards(inUsedCards, tempAllCards);
    for (int i = startIdx; i < CARD_TYPE; i++)
    {
        MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
        switch (tempAllCards[i])
        {
            case 0:
                break;
            case 1:
            case 2:
            case 3:
            case 4:
                if (cardNum == 1)
                {
                    tempInUsedCards[i] += 1;
                    addSingleHand(tempInUsedCards);
                }
                else
                {
                    tempInUsedCards[i]++;
                    analyzeSeveralSingleCards(cardNum - 1, tempInUsedCards, i);
                }
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : analyzeSeveralDoubleCards
// Description       : Function analyze several double card, 
//                     sub-function called by other singleHands get functions.
// 
void analyzeSeveralDoubleCards(char cardNum, char inUsedCards[CARD_TYPE] = NULL, char startIdx = 0)
{
    char tempAllCards[CARD_TYPE] = {0};
    char tempInUsedCards[CARD_TYPE] = {0};
    MEM_CPY_OR_INIT(tempAllCards, allCards, CARD_TYPE);
    MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
    getUnusedCards(inUsedCards, tempAllCards);
    for (int i = startIdx; i < CARD_TYPE; i++)
    {
        MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
        switch (tempAllCards[i])
        {
            case 0:
            case 1:
                break;
            case 2:
            case 3:
            case 4:
                if (cardNum == 1)
                {
                    tempInUsedCards[i] += 2;
                    addSingleHand(tempInUsedCards);
                }
                else
                {
                    tempInUsedCards[i] += 2;
                    analyzeSeveralDoubleCards(cardNum - 1, tempInUsedCards, i);
                }
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : analyze_AAABBB_DE_or_DDEE_Hands
// Description       : Function analyze AAABBB_DE or AAABBB_DDEE kind of "singleHand".
// 
void analyze_AAABBB_DE_or_DDEE_Hands(char inUsedCards[CARD_TYPE] = NULL)
{
    char tempAllCards[CARD_TYPE] = {0};
    char tempInUsedCards[CARD_TYPE] = {0};
    MEM_CPY_OR_INIT(tempAllCards, allCards, CARD_TYPE);
    MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
    getUnusedCards(inUsedCards, tempAllCards);
    for (int i = 0; i < CARD_TYPE; i++)
    {
        MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
        switch (tempAllCards[i])
        {
            case 0:
            case 1:
            case 2:
                break;
            case 3:
            case 4:
                for (int endCard = i; endCard <= 11; endCard++)
                {
                    if (tempAllCards[endCard] <= 2)
                    {
                        break;
                    }
                    tempInUsedCards[endCard] += 3;
                    if (endCard - i >= 1)
                    {
                        analyzeSeveralSingleCards(endCard - i + 1, tempInUsedCards);
                        analyzeSeveralDoubleCards(endCard - i + 1, tempInUsedCards);
                    }
                }
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : analyze_AAAA_DE_or_DDEE_Hands
// Description       : Function analyze AAAA_DE or AAAA_DDEE kind of "singleHand".
// 
void analyze_AAAA_DE_or_DDEE_Hands(char inUsedCards[CARD_TYPE] = NULL)
{
    char tempAllCards[CARD_TYPE] = {0};
    char tempInUsedCards[CARD_TYPE] = {0};
    MEM_CPY_OR_INIT(tempAllCards, allCards, CARD_TYPE);
    MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
    getUnusedCards(inUsedCards, tempAllCards);
    for (int i = 0; i < CARD_TYPE; i++)
    {
        MEM_CPY_OR_INIT(tempInUsedCards, inUsedCards, CARD_TYPE);
        switch (tempAllCards[i])
        {
            case 0:
            case 1:
            case 2:
            case 3:
                break;
            case 4:
                tempInUsedCards[i] += 4;
                analyzeSeveralSingleCards(2, tempInUsedCards);
                analyzeSeveralDoubleCards(2, tempInUsedCards);
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : analyzeAllPlaySchema
// Description       : Function analyze all kinds of play schema and save 
//                     into "allPlaySchema".
// 
void analyzeAllPlaySchema(char remainCards[CARD_TYPE], char playSchema[STRING_MAX_LEN] = NULL, int startIdx = 0, int handsCount = 0)
{
    char tempRemainCards[CARD_TYPE] = {0};
    char tempPlaySchema[STRING_MAX_LEN] = {0};
    int tempHandsCount = handsCount;
    for (int i = startIdx; i < allSingleHandsCount; i++)
    {
        tempHandsCount = handsCount;
        MEM_CPY_OR_INIT(tempRemainCards, remainCards, CARD_TYPE);
        MEM_CPY_OR_INIT(tempPlaySchema, playSchema, STRING_MAX_LEN);
        switch (isEqualOrInclusion(allSingleHands[i], tempRemainCards))
        {
            case IsEqual:
                tempHandsCount++;
                addCardsToString(allSingleHands[i], tempPlaySchema);
                sprintf(allPlaySchema[allPlaySchemaCount], "%s", tempPlaySchema);
                allPlaySchema[allPlaySchemaCount][STRING_NUM_START_IDX] = tempHandsCount;
                allPlaySchemaCount++;
                if (minHandsNum > tempHandsCount)
                {
                    minHandsNum = tempHandsCount;
                }
                //printf("%s total: %d\r\n", tempPlaySchema, tempHandsCount);
                break;
            case IsInclusion:
                tempHandsCount++;
                addCardsToString(allSingleHands[i], tempPlaySchema);
                getUnusedCards(allSingleHands[i], tempRemainCards);
                analyzeAllPlaySchema(tempRemainCards, tempPlaySchema, i, tempHandsCount);
                break;
            case NotInclusion:
                break;
            default:
                ;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : printBestPlaySchema
// Description       : Function to print the best schema.
//
void printBestPlaySchema()
{
    for (int i = 0; i < allPlaySchemaCount; i++)
    {
        if (allPlaySchema[i][STRING_NUM_START_IDX] == minHandsNum)
        {
            printf("%s\r\n", allPlaySchema[i]);
        }
    }
}

///////////////////////////////////////////////////////////////////////////////
// Function Name     : PlayCard
// Description       : Analyse the best play schema. 
//                     Play all cards with least hands.
//
int PlayCard(char cards[CARD_NUM])
{
    if (cards == NULL || strlen(cards) != CARD_NUM)
    {
        return 0;
    }
    initCards(cards);
    analyze_A_Hands();
    analyze_AA_Hands();
    analyze_AAA_Hands();
    analyze_AAAA_Hands();
    analyze_AAA_B_or_BB_Hands();
    analyze_ABCDE_Hands();
    analyze_AABBCC_Hands();
    analyze_AAABBB_Hands();
    analyze_AAABBB_DE_or_DDEE_Hands();
    analyze_AAAA_DE_or_DDEE_Hands();

    
    analyzeAllPlaySchema(allCards);
    
    //printf("%d,%d\r\n", allSingleHandsCount, allPlaySchemaCount);
    
    printf("%d\r\n", minHandsNum);
    
    printBestPlaySchema();

    return 0;
}


// test main
//int main()
//{
//    PlayCard("333444555666AA");
//    return 0;
//}

#if 0
int main()
{
    while(1)
    {
        char inputC[18] = {0};
        scanf("%s", inputC);
        PlayCard(inputC);
        //printf("%d\r\n", allPlaySchemaCount);
    }
    return 0;
}
#endif
