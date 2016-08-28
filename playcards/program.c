/*
 * File:   program.cpp
 * Author: sid.li@alcatel.lucent.com
 *
 * Created on
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define N 17
char Cards[N] = {0};
int Maxtime = N;
char* Sequence = "3456789SJQKA";
int Seqlen = 12;
//optimize option
int cardsTailDeep[N] = {0};
char cardsTailRecord[N][2*N] = {0};

int execute(char[]);
int findleastdeep(char*);
char* strdel(char*, char);
int playSomeCards(char*, char*);
int play1singlecards(char*);
int play2singlecards(char*);
int play1doublecards(char*);
int play2doublecards(char*);
int handleOtherCases(char*);

int execute(char cards[N])
{
    char mycards[2*N];
    for(int i=0;i<N;i++) mycards[i]=cards[i];
    mycards[N]='\0';
    strcpy(Cards,mycards);
    memset(cardsTailDeep,0,sizeof(int)*(2*N));
    // TRC printf("in execute cards:%s mycards:%s\n",cards,mycards);
    int rst = findleastdeep(mycards);
    // TRC printf("result: min play times:%d playcards:%s\n",rst,mycards);
    printf("%s\n%d\n%s\n\n",Cards,rst,mycards);
    return rst;
}

int findleastdeep(char* cards)
{
    // TRC printf("Enter findleastdeep:%s\n",cards);
    int length = strlen(cards);
    char* tailPos = strstr(Cards,cards);
    int IsCardsTail = 0;
    if(NULL != tailPos)
    {
        if(N == tailPos - Cards + length)
        {
            IsCardsTail = 1;
            // TRC printf("In findleastdeep IsCardsTail:%s time:%d\n",cards,cardsTailDeep[length]);
            if(0 != cardsTailDeep[length])
            {
                strcpy(cards,cardsTailRecord[length]);
                return cardsTailDeep[length];
            }
        }
    }
    //end condition out of cards
    if(0 == length) return 0;
    if(1 == length) return 1;

    char key = cards[0];
    char* pos = strchr(Sequence,key);   //key position in Sequence
    int leasttime = Maxtime;
    //mycards record current cards, playcards record the cards played all times, thisplay record the card play this time
    char mycards[2*N] = {0}, playcards[2*N] = {0}, thisplay[N] = {0};
    int cardcount = 0;
    //play single card
    cardcount = 0;
    thisplay[cardcount++] = key;
    thisplay[cardcount++]=' '; thisplay[cardcount] = '\0';
    strcpy(mycards,cards);
    playSomeCards(mycards,thisplay);
    int tmptime = findleastdeep(mycards) + 1;
    if(tmptime<leasttime)
    {
        leasttime = tmptime;
        strcpy(playcards,thisplay);
        strcat(playcards,mycards);
    }
    // TRC printf("After play single cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play double cards
    cardcount = 0;
    if(key == cards[1])
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key;
        thisplay[cardcount++]=' '; thisplay[cardcount] = '\0';
        strcpy(mycards,cards);
        playSomeCards(mycards,thisplay);
        int tmptime = findleastdeep(mycards) + 1;
        if(tmptime<leasttime)
        {
            leasttime = tmptime;
            strcpy(playcards,thisplay);
            strcat(playcards,mycards);
        }
    }
    // TRC printf("After play double cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //end condition when cards <= 2
    if(length == 2)
    {
        if(1 == IsCardsTail)
        {
            cardsTailDeep[length] = leasttime;
            strcpy(cardsTailRecord[length],playcards);
        }
        strcpy(cards,playcards);
        return leasttime;
    }
    //play three cards
    cardcount = 0;
    if(key == cards[1] && key == cards[2])
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key; thisplay[cardcount++] = key;
        thisplay[cardcount++]=' '; thisplay[cardcount] = '\0';
        strcpy(mycards,cards);
        playSomeCards(mycards,thisplay);
        int tmptime = findleastdeep(mycards) + 1;
        if(tmptime<leasttime)
        {
            leasttime = tmptime;
            strcpy(playcards,thisplay);
            strcat(playcards,mycards);
        }
    }
    // TRC printf("After play three cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //end condition when cards <= 3
    if(length == 3)
    {
        if(1 == IsCardsTail)
        {
            cardsTailDeep[length] = leasttime;
            strcpy(cardsTailRecord[length],playcards);
        }
        strcpy(cards,playcards);
        return leasttime;
    }
    //play four cards
    cardcount = 0;
    if(key == cards[1] && key == cards[2] && key == cards[3])
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key; thisplay[cardcount++] = key; thisplay[cardcount++] = key;
        thisplay[cardcount++]=' '; thisplay[cardcount] = '\0';
        strcpy(mycards,cards);
        playSomeCards(mycards,thisplay);
        int tmptime = findleastdeep(mycards) + 1;
        if(tmptime<leasttime)
        {
            leasttime = tmptime;
            strcpy(playcards,thisplay);
            strcat(playcards,mycards);
        }
    }
    // TRC printf("After play four cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play three and one cards xxx + y
    cardcount = 0;
    if(key == cards[1] && key == cards[2])
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key; thisplay[cardcount++] = key;
        thisplay[cardcount] = '\0';
        strcpy(mycards,cards);
        playSomeCards(mycards,thisplay);
        int tmptime = play1singlecards(mycards) + 1;
        if(tmptime<leasttime)
        {
            leasttime = tmptime;
            strcpy(playcards,thisplay);
            strcat(playcards,mycards);
        }
    }
    // TRC printf("After play xxx + y cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play three and one cards x + yyy
    cardcount = 0;
    thisplay[cardcount++] = key;
    for(int i=1,tmpcount=cardcount;i<=length-3;i++,cardcount=tmpcount)
    {
        if(cards[i]==cards[i+1] && cards[i] == cards[i+2])
        {
            thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i];
            thisplay[cardcount++]=' '; thisplay[cardcount] = '\0';
            strcpy(mycards,cards);
            playSomeCards(mycards,thisplay);
            int tmptime = findleastdeep(mycards) + 1;
            if(tmptime<leasttime)
            {
                leasttime = tmptime;
                strcpy(playcards,thisplay);
                strcat(playcards,mycards);
            }
        }
    }
    // TRC printf("After play x + yyy cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //end condition when cards <= 4
    if(length == 4)
    {
        if(1 == IsCardsTail)
        {
            cardsTailDeep[length] = leasttime;
            strcpy(cardsTailRecord[length],playcards);
        }
        strcpy(cards,playcards);
        return leasttime;
    }

    //play three and two cards xxx + yy
    cardcount = 0;
    if(key == cards[1] && key == cards[2])
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key; thisplay[cardcount++] = key;
        thisplay[cardcount] = '\0';
        strcpy(mycards,cards);
        playSomeCards(mycards,thisplay);
        int tmptime = play1doublecards(mycards) + 1;
        if(tmptime<leasttime)
        {
            leasttime = tmptime;
            strcpy(playcards,thisplay);
            strcat(playcards,mycards);
        }
    }
    // TRC printf("After play xxx + yy cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play three and two cards xx + yyy
    cardcount = 0;
    if(key == cards[1])
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key;
        for(int i=2,tmpcount=cardcount;i<=length-3;i++,cardcount=tmpcount)
        {
            if(cards[i]==cards[i+1] && cards[i] == cards[i+2])
            {
                thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i];
                thisplay[cardcount++]=' '; thisplay[cardcount] = '\0';
                strcpy(mycards,cards);
                playSomeCards(mycards,thisplay);
                int tmptime = findleastdeep(mycards) + 1;
                if(tmptime<leasttime)
                {
                    leasttime = tmptime;
                    strcpy(playcards,thisplay);
                    strcat(playcards,mycards);
                }
            }
        }
    }
    // TRC printf("After play xx + yyy cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play single queue cards 56789
    cardcount = 0;
    if(NULL != pos && pos < Sequence+Seqlen-4 && NULL!=strchr(cards,*(pos+1)) && NULL!=strchr(cards,*(pos+2)) && NULL!=strchr(cards,*(pos+3)) && NULL!=strchr(cards,*(pos+4)))
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = *(pos+1); thisplay[cardcount++] = *(pos+2); thisplay[cardcount++] = *(pos+3);
        for(char* pc=pos+4; *pc != '\0' && NULL != strchr(cards,*pc); pc++)
        {
            thisplay[cardcount++] = *pc;
            thisplay[cardcount]=' '; thisplay[cardcount+1] = '\0';
            strcpy(mycards,cards);
            playSomeCards(mycards,thisplay);
            int tmptime = findleastdeep(mycards) + 1;
            if(tmptime<leasttime)
            {
                leasttime = tmptime;
                strcpy(playcards,thisplay);
                strcat(playcards,mycards);
            }
        }
    }
    // TRC printf("After play 56789 cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //end condition when cards <= 5
    if(length == 5)
    {
        if(1 == IsCardsTail)
        {
            cardsTailDeep[length] = leasttime;
            strcpy(cardsTailRecord[length],playcards);
        }
        strcpy(cards,playcards);
        return leasttime;
    }
    char *pkey2 = NULL, *pkey3 = NULL;
    if(pos != NULL)
    {
        pkey2 = strchr(cards,*(pos+1));
        pkey3 = strchr(cards,*(pos+2));
    }
    //play double queue cards xx yy zz
    cardcount = 0;
    if(NULL != pos && pos < Sequence+Seqlen-2 && key == cards[1] && NULL != pkey2 && *pkey2 == *(pkey2+1) && NULL != pkey3 && *pkey3 == *(pkey3+1))
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key; thisplay[cardcount++] = *(pos+1); thisplay[cardcount++] = *(pos+1);
        for(char* pc=pos+2, *pkeytmp = strchr(cards,*(pos+2)); *pc != '\0' && NULL != pkeytmp && *pkeytmp == *(pkeytmp+1); pc++)
        {
            thisplay[cardcount++] = *pc; thisplay[cardcount++] = *pc;
            thisplay[cardcount]=' '; thisplay[cardcount+1] = '\0';
            strcpy(mycards,cards);
            playSomeCards(mycards,thisplay);
            int tmptime = findleastdeep(mycards) + 1;
            if(tmptime<leasttime)
            {
                leasttime = tmptime;
                strcpy(playcards,thisplay);
                strcat(playcards,mycards);
            }
            pkeytmp = strchr(cards,*(pc+1));
        }
    }
    // TRC printf("After play double queue cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play three queue cards xxx yyy
    cardcount = 0;
    if(NULL != pos && pos < Sequence + Seqlen - 1 && key == cards[1] && key == cards[2] && NULL != pkey2 && *pkey2 == *(pkey2+1) && *pkey2 == *(pkey2+2))
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key; thisplay[cardcount++] = key;
        for(char *pc=pos+1,*pkeytmp = strchr(cards,*pos); '\0' != *pc && NULL != pkeytmp && *pkeytmp == *(pkeytmp+1) && *pkeytmp == *(pkeytmp+2); pc++)
        {
            thisplay[cardcount++]=*pc; thisplay[cardcount++]=*pc; thisplay[cardcount++]=*pc;
            thisplay[cardcount]=' '; thisplay[cardcount+1] = '\0';
            strcpy(mycards,cards);
            playSomeCards(mycards,thisplay);
            int tmptime = findleastdeep(mycards) + 1;
            if(tmptime<leasttime)
            {
                leasttime = tmptime;
                strcpy(playcards,thisplay);
                strcat(playcards,mycards);
            }
            pkeytmp = strchr(cards,*(pc+1));
        }
    }
    // TRC printf("After play three queue cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play plane xxx yyy m n
    cardcount = 0;
    if(NULL != pos && pos < Sequence + Seqlen - 1 && key == cards[1] && key == cards[2] && NULL != pkey2 && *pkey2 == *(pkey2+1) && *pkey2 == *(pkey2+2))
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key; thisplay[cardcount++] = key;
        thisplay[cardcount++]=*pkey2; thisplay[cardcount++]=*pkey2; thisplay[cardcount++]=*pkey2;
        thisplay[cardcount] = '\0';
        strcpy(mycards,cards);
        playSomeCards(mycards,thisplay);
        int tmptime = play2singlecards(mycards) + 1;
        if(tmptime<leasttime)
        {
            leasttime = tmptime;
            strcpy(playcards,thisplay);
            strcat(playcards,mycards);
        }
    }
    // TRC printf("After play plane xxx yyy m n cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play four and two cards x mmmnnn y
    cardcount = 0;
    thisplay[cardcount++] = key;
    for(int i=1,tmpcount=cardcount;i<=length-7;i++,cardcount=tmpcount)
    {
        char* pmypos = strchr(Sequence,cards[i]);
        if(cards[i]==cards[i+1] && cards[i] == cards[i+2] && NULL != pmypos)
        {
            thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i];
            char* mykey = strchr(cards,*(pmypos+1));
            if(NULL != mykey && *mykey == *(mykey+1) && *mykey == *(mykey+2))
            {
                thisplay[cardcount++]=*mykey; thisplay[cardcount++]=*mykey; thisplay[cardcount++]=*mykey;
                thisplay[cardcount] = ' '; thisplay[cardcount] = '\0';
                strcpy(mycards,cards);
                playSomeCards(mycards,thisplay);
                int tmptime = play1singlecards(mycards) + 1;
                if(tmptime<leasttime)
                {
                    leasttime = tmptime;
                    strcpy(playcards,thisplay);
                    strcat(playcards,mycards);
                }
            }
        }
    }
    // TRC printf("After play x mmmnnn y cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play plane xxx yyy mm nn
    cardcount = 0;
    if(NULL != pos && pos < Sequence + Seqlen - 1 && key == *(pos+1) && key != *(pos+2) && NULL != pkey2 && *pkey2 == *(pkey2+1) && *pkey2 == *(pkey2+2))
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key; thisplay[cardcount++] = key;
        thisplay[cardcount++] = *pkey2; thisplay[cardcount++] = *pkey2; thisplay[cardcount++] = *pkey2;
        thisplay[cardcount++]=' '; thisplay[cardcount] = '\0';
        strcpy(mycards,cards);
        playSomeCards(mycards,thisplay);
        int tmptime = play2doublecards(mycards) + 1;
        if(tmptime<leasttime)
        {
            leasttime = tmptime;
            strcpy(playcards,thisplay);
            strcat(playcards,mycards);
        }
    }
    // TRC printf("After play xxx yyy mm nn cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play four and two cards xx mmmnnn yy
    cardcount = 0;
    if(key == cards[1])
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key;
        for(int i=2,tmpcount=cardcount;i<=length-8;i++,cardcount=tmpcount)
        {
            char* mypos = strchr(Sequence,cards[i]);
            if(cards[i]==cards[i+1] && cards[i] == cards[i+2] && NULL != mypos)
            {
                thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i];
                char* mykey = strchr(cards,*(mypos+1));
                if(NULL != mykey && *mykey == *(mykey+1) && *mykey == *(mykey+2))
                {
                    thisplay[cardcount++]=*mykey; thisplay[cardcount++]=*mykey; thisplay[cardcount++]=*mykey;
                    thisplay[cardcount] = ' '; thisplay[cardcount] = '\0';
                    strcpy(mycards,cards);
                    playSomeCards(mycards,thisplay);
                    int tmptime = play1doublecards(mycards) + 1;
                    if(tmptime<leasttime)
                    {
                        leasttime = tmptime;
                        strcpy(playcards,thisplay);
                        strcat(playcards,mycards);
                    }
                }
            }
        }
    }
    // TRC printf("After play xx mmmnnn yy cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play four and two cards xxxx m n
    cardcount = 0;
    if(key == cards[1] && key == cards[2] && key == cards[3])
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key; thisplay[cardcount++] = key; thisplay[cardcount++] = key;
        thisplay[cardcount] = '\0';
        strcpy(mycards,cards);
        playSomeCards(mycards,thisplay);
        int tmptime = play2singlecards(mycards) + 1;
        if(tmptime<leasttime)
        {
            leasttime = tmptime;
            strcpy(playcards,thisplay);
            strcat(playcards,mycards);
        }
    }
    // TRC printf("After play xxxx m n cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play four and two cards x yyyy m
    cardcount = 0;
    thisplay[cardcount++] = key;
    for(int i=1,tmpcount=cardcount;i<=length-5;i++,cardcount=tmpcount)
    {
        if(cards[i]==cards[i+1] && cards[i] == cards[i+2] && cards[i] == cards[i+3])
        {
            thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i];
            thisplay[cardcount] = '\0';
            strcpy(mycards,cards);
            playSomeCards(mycards,thisplay);
            int tmptime = play1singlecards(mycards) + 1;
            if(tmptime<leasttime)
            {
                leasttime = tmptime;
                strcpy(playcards,thisplay);
                strcat(playcards,mycards);
            }
        }
    }
    // TRC printf("After play x yyyy m cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play four and four cards xxxx mm nn
    cardcount = 0;
    if(key == cards[1] && key == cards[2] && key == cards[3])
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key; thisplay[cardcount++] = key; thisplay[cardcount++] = key;
        thisplay[cardcount++]=' '; thisplay[cardcount] = '\0';
        strcpy(mycards,cards);
        playSomeCards(mycards,thisplay);
        int tmptime = play2doublecards(mycards) + 1;
        if(tmptime<leasttime)
        {
            leasttime = tmptime;
            strcpy(playcards,thisplay);
            strcat(playcards,mycards);
        }
    }
    // TRC printf("After play xxxx mm nn cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play four and four cards xx yyyy mm
    cardcount = 0;
    if(key == cards[1])
    {
        thisplay[cardcount++] = key; thisplay[cardcount++] = key;
        for(int i=2,tmpcount=cardcount;i<=length-6;i++,cardcount=tmpcount)
        {
            if(cards[i]==cards[i+1] && cards[i] == cards[i+2] && cards[i] == cards[i+3])
            {
                thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i];
                thisplay[cardcount] = '\0';
                strcpy(mycards,cards);
                playSomeCards(mycards,thisplay);
                int tmptime = play1doublecards(mycards) + 1;
                if(tmptime<leasttime)
                {
                    leasttime = tmptime;
                    strcpy(playcards,thisplay);
                    strcat(playcards,mycards);
                }
            }
        }
    }
    // TRC printf("After play xx yyyy mm cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    //play aaabbbccc... or aaabbbcccddd... cards
    if(N == length)
    {
        strcpy(mycards,cards);
        int tmptime = handleOtherCases(mycards);
        if(tmptime<leasttime)
        {
            leasttime = tmptime;
            strcpy(playcards,mycards);
        }
        // TRC printf("After play other cases cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    }
    // TRC printf("findleastdeep return cards:%s playcards:%s time:%d\n",cards,playcards,leasttime);
    if(1 == IsCardsTail)
    {
        cardsTailDeep[length] = leasttime;
        strcpy(cardsTailRecord[length],playcards);
    }
    strcpy(cards,playcards);
    return leasttime;
}

char* strdel(char* str, char ch)
{
    int length = strlen(str);
    char* pos = strchr(str,ch);
    if(pos==NULL) return NULL;
    for(char* pc=pos; *pc!='\0'; pc++)
    {
        *pc = *(pc+1);
    }
    str[length-1] = '\0';
    return pos;
}

int playSomeCards(char* cards, char* thisplay)
{
    for(char* c = thisplay; *c!=' ' && *c != '\0'; c++)
    {
        strdel(cards,*c);
    }
    return 1;
}

int play1singlecards(char* cards)
{
    int leasttime = Maxtime - 1;
    int length = strlen(cards);
    char mycards[2*N] = {0}, playcards[2*N] = {0}, thisplay[N] = {0};
    int cardcount = 0;
    if(1 == length)
    {
        return 1;
    }
    else if(0 == length)
    {
        strcpy(cards,playcards);
        return leasttime;
    }
    for(int i = 0,tmpcount = cardcount; i < length; i++,cardcount = tmpcount)
    {
        thisplay[cardcount++]=cards[i];
        thisplay[cardcount++]=' '; thisplay[cardcount] = '\0';
        strcpy(mycards,cards);
        playSomeCards(mycards,thisplay);
        int tmptime = findleastdeep(mycards);
        if(tmptime<leasttime)
        {
            leasttime = tmptime;
            strcpy(playcards,thisplay);
            strcat(playcards,mycards);
        }
    }
    strcpy(cards,playcards);
    return leasttime;
}

int play2singlecards(char* cards)
{
    int leasttime = Maxtime - 1;
    int length = strlen(cards);
    char mycards[2*N] = {0}, playcards[2*N] = {0}, thisplay[N] = {0};
    int cardcount = 0;
    if(2 > length) return leasttime;
    if(2 == length) return 1;
    for(int i = 0,tmpcount = cardcount; i < length; i++,cardcount = tmpcount)
    {
        thisplay[cardcount++]=cards[i];
        for(int j = i+1,tmpcount2 = cardcount; j < length; j++,cardcount = tmpcount2)
        {
            thisplay[cardcount++]=cards[j];
            thisplay[cardcount++]=' '; thisplay[cardcount] = '\0';
            strcpy(mycards,cards);
            playSomeCards(mycards,thisplay);
            int tmptime = findleastdeep(mycards);
            if(tmptime<leasttime)
            {
                leasttime = tmptime;
                strcpy(playcards,thisplay);
                strcat(playcards,mycards);
            }
        }
    }
    strcpy(cards,playcards);
    return leasttime;
}

int play1doublecards(char* cards)
{
    int leasttime = Maxtime - 1;
    int length = strlen(cards);
    char mycards[2*N] = {0}, playcards[2*N] = {0}, thisplay[N] = {0};
    int cardcount = 0;
    if(2 > length) return leasttime;
    for(int i = 0,tmpcount = cardcount; i < length; i++,cardcount = tmpcount)
    {
        if(cards[i] == cards[i+1])
        {
            thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i];
            thisplay[cardcount++]=' '; thisplay[cardcount] = '\0';
            strcpy(mycards,cards);
            playSomeCards(mycards,thisplay);
            int tmptime = findleastdeep(mycards);
            if(tmptime<leasttime)
            {
                leasttime = tmptime;
                strcpy(playcards,thisplay);
                strcat(playcards,mycards);
            }
        }
    }
    strcpy(cards,playcards);
    return leasttime;
}

int play2doublecards(char* cards)
{
    int leasttime = Maxtime - 1;
    int length = strlen(cards);
    char mycards[2*N] = {0}, playcards[2*N] = {0}, thisplay[N] = {0};
    int cardcount = 0;
    if(4 > length)
    {
        strcpy(cards,playcards);
        return leasttime;
    }
    for(int i = 0,tmpcount = cardcount; i < length; i++,cardcount = tmpcount)
    {
        if(cards[i]==cards[i+1])
        {
            thisplay[cardcount++]=cards[i]; thisplay[cardcount++]=cards[i];
            for(int j = i+1,tmpcount2 = cardcount; j < length-1; j++,cardcount = tmpcount2)
            {
                if(cards[j]==cards[j+1])
                {
                    thisplay[cardcount++]=cards[j]; thisplay[cardcount++]=cards[j];
                    thisplay[cardcount++]=' '; thisplay[cardcount] = '\0';
                    strcpy(mycards,cards);
                    playSomeCards(mycards,thisplay);
                    int tmptime = findleastdeep(mycards);
                    if(tmptime<leasttime)
                    {
                        leasttime = tmptime;
                        strcpy(playcards,thisplay);
                        strcat(playcards,mycards);
                    }
                }
            }
        }
    }
    strcpy(cards,playcards);
    return leasttime;
}

int handleOtherCases(char* cards)
{
    int leasttime = Maxtime - 1;
    int length = strlen(cards);
    char mycards[2*N] = {0}, playcards[2*N] = {0}, thisplay[N] = {0};
    int cardcount = 0;
    //aaabbbccc
    for(int i=0; i<=Seqlen-3; i++)
    {
        char* pkey = strchr(cards,Sequence[i]);
        if(NULL != pkey && *(pkey+1) == *pkey && *(pkey+2) == *pkey)
        {
            char* pkey2 = strchr(cards,Sequence[i+1]),*pkey3=strchr(cards,Sequence[i+2]);
            if(NULL != pkey2 && *pkey2 == *(pkey2+1) && *pkey2 == *(pkey2+2) && NULL != pkey3 && *pkey3 == *(pkey3+1) && *pkey3 == *(pkey3+2))
            {
                thisplay[cardcount++] = Sequence[i]; thisplay[cardcount++] = Sequence[i]; thisplay[cardcount++] = Sequence[i];
                thisplay[cardcount++] = Sequence[i+1]; thisplay[cardcount++] = Sequence[i+1]; thisplay[cardcount++] = Sequence[i+1];
                thisplay[cardcount++] = Sequence[i+2]; thisplay[cardcount++] = Sequence[i+2]; thisplay[cardcount++] = Sequence[i+2];
                thisplay[cardcount] = ' ';
                strcpy(mycards,cards);
                playSomeCards(mycards,thisplay);
                int tmptime = findleastdeep(mycards);
                if(tmptime>1)
                {
                    thisplay[cardcount] = '\0';
                    char statistics[N-9][N-9] = {0};
                    for(int j=0,k=0;j<strlen(mycards);k=0)
                    {
                        while(' ' != mycards[j+k] && '\0' != mycards[j+k]) k++;
                        if(0 == k)
                        {
                            j++;
                            continue;
                        }
                        strncat(statistics[k],mycards+j,k);
                        j += k;
                    }
                    if(strlen(statistics[1]) >= 3)
                    {
                        leasttime = tmptime-3+1;
                        strncat(thisplay,statistics[1],3);
                    }
                    if(strlen(statistics[2]) >= 3*2)
                    {
                        leasttime = tmptime-3+1;
                        strncat(thisplay,statistics[2],3*2);
                        cardcount += 6;
                    }
                    else if(strlen(statistics[1]) >= 1 && strlen(statistics[2]) >= 2)
                    {
                        leasttime = tmptime-2+1;
                        strncat(thisplay,statistics[1],1);
                        strncat(thisplay,statistics[2],2);
                        cardcount += 3;
                    }
                    else if(strlen(statistics[3]) >= 3)
                    {
                        leasttime = tmptime-1+1;
                        strncat(thisplay,statistics[3],1);
                        cardcount += 3;
                    }
                    else if(strlen(statistics[2]) >= 2*2)
                    {
                        leasttime = tmptime-1+1;
                        strncat(thisplay,statistics[2],3);
                        cardcount += 3;
                    }
                    else if(6 == strlen(statistics[6]) && statistics[6][0]==statistics[6][1] && statistics[6][2] == statistics[6][3] && statistics[6][4] == statistics[6][5])
                    {
                        leasttime = tmptime-1+1;
                        strncat(thisplay,statistics[6],6);
                        cardcount += 6;
                    }
                    else break;
                    strcpy(mycards,cards);
                    thisplay[cardcount++]=' '; thisplay[cardcount] = '\0';
                    playSomeCards(mycards,thisplay);
                    findleastdeep(mycards);
                    strcpy(playcards,thisplay);
                    strcat(playcards,mycards);
                }
                break;
            }
        }
    }
    //aaabbbcccddd
    for(int i=0; i<=Seqlen-4; i++)
    {
        char* pkey = strchr(cards,Sequence[i]);
        if(NULL != pkey && *pkey == *(pkey+1) && *pkey == *(pkey+2))
        {
            char* pkey2 = strchr(cards,Sequence[i+1]),*pkey3=strchr(cards,Sequence[i+2]),*pkey4 = strchr(cards,Sequence[i+3]);
            if(NULL != pkey2 && *pkey2 == *(pkey2+1) && *pkey2 == *(pkey2+2) && NULL != pkey3 && *pkey3 == *(pkey3+1) && *pkey3 == *(pkey3+2) && NULL != pkey4 && *pkey4 == *(pkey4+1) && *pkey4 == *(pkey4+2))
            {
                if(N == 17 && leasttime > 2)
                {
                    leasttime = 2;
                    for(int j=0; j<length; j++)
                    {
                        if(cards[j]!=Sequence[i] && cards[j]!=Sequence[i+1] && cards[j]!=Sequence[i+2] && cards[j]!=Sequence[i+3])
                        {
                            strcpy(playcards,cards);
                            strdel(playcards,cards[j]);
                            playcards[N-1] = ' '; playcards[N] = cards[j]; playcards[N+1] = '\0';
                        }
                    }
                }
            }
        }
    }
    strcpy(cards,playcards);
    return leasttime;
}
