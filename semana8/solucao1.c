#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct SNode {
    char nChar;
    struct SNode * nNext;
} SNode;

typedef struct SStack {
    SNode * sTop;
    int sSize;
} SStack;

SNode * CreateNewNode ( char content ) {
    SNode *node = (SNode *) malloc( sizeof(SNode));
    if ( node == NULL) {
        puts("DEU PAU!");
        exit(-1);
    }
    node->nChar = content;
    return node;
}

void SPush ( SStack * stack, char letter ) {
    SNode *node = CreateNewNode(letter);
    node->nNext = stack->sTop;
    stack->sTop = node;
    stack->sSize++;
}

void SPop ( SStack * stack ) {
    if (stack->sSize > 0) {
        SNode *removed = stack->sTop;
        stack->sTop = stack->sTop->nNext;
        stack->sSize--;
        free(removed);
    }
}

SStack *SReset ( void ) {
    SStack *stack = ( SStack *) malloc( sizeof(SStack) );
    if ( stack == NULL ) {
            puts("DEU PAU!");
            exit(-1);
    }

    stack->sSize = 0;
    stack->sTop = NULL; 

    return stack;
}

void SDelete (SStack * stack) {
    while ( stack->sSize > 0 ) {
        SPop( stack );
    }
    free ( stack );
}

char * RemoveSubstring ( char * string, char * substring) {
    char * newString = calloc( strlen(string) + 1, sizeof(char) );
    SStack *stack = SReset();

    for (int i = 0; i < strlen(string); i++) {
        if ( stack->sSize > 0 ) {
            if( stack->sTop->nChar == substring[0] && string[i] == substring[1]) {
                SPop(stack);
                continue;
            }
        }
        SPush(stack, string[i]);
    }

    int j = 0;

    while( stack->sSize ) {
        newString[j++] = stack->sTop->nChar;
        SPop(stack);
    }

    SDelete(stack);

    return newString;

}

int maximumGain( char *s, int x, int y ) {
    int score = 0, originalLength = strlen(s);

    if ( x > y) {
        s = RemoveSubstring(s, "ab");
        score += x * ( ( originalLength - strlen(s) ) /2 );
        //printf("%s", s);
        originalLength = strlen(s);
        s = RemoveSubstring(s, "ab");
        score += y * ( ( originalLength - strlen(s) ) /2 );
    } else {
        s = RemoveSubstring(s, "ba");
        score += y * ( ( originalLength - strlen(s) ) /2 );
        //printf("%s\n", s);
        originalLength = strlen(s);
        s = RemoveSubstring(s, "ba");
        score += x * ( ( originalLength - strlen(s) ) /2 );
    }

    return score;
}

int main( void ) {
	char *s =
	    "azbauaasbbbpuaabbaabwbababyabafabsauofaaaayaabaaaaubbababaaabxaaaoyeaaaa"
	    "bbbhbqaqbaavababbbahbbhxdbaaanjbbtbbbiaabkakbbaaawbbbambbbwaagabbbbabaai"
	    "bbababbbbarbabbkainbbabaaarbznwaaarapababaebababzyabaabbbaqbabrftbbbauaa"
	    "fnabaabkbraanbiabbbbabbasdaabnbaaaaaabbfabbgbaabbababbbbbnunaaabyavabgab"
	    "bbeidbaahbbabybsbbabhaksdaaabtaabasxfababbapaskfbbaaavhfbapbabjxabqadgbb"
	    "babbbibcbabaaagbbvaabahbbbkamlabubbananbabbaababbbbbbbbbbaqbbqabfabribaj"
	    "bbbaaamlbbbbbaaaabpabcqabppbaabtlbuuugbiabakabaaazebababbbbaaaabbhqbabbb"
	    "abatbazbbrbbiabbbabbabbbaafvbabaaababraczbbaakbabbbaacajbarglzaabjbbbafn"
	    "aabaadbratbeybbbaaababepcbbbyabbbtabypababbqbaaaiqasgqabtbbvalaaaaibbiag"
	    "bbhfbbbbaabaepbauaxaababaabbobaahhamahaababuaaaabaarlbaaaaamaavbwaabaqbs"
	    "apaaaxbabaaabbboaaabaabozacavabamaaaasbaaiaabbsaebybisvbaabbbbaagaaaeaaa"
	    "aabybabbabbacbbbbabtbaahzabmxbkfnbbcbaaalabtabbbbbbbbplbsbdbabgabaabbbaa"
	    "qabjsaabbbobaarbatzabbxbgabuabaaqaababbbabvggnabbaazbabababfbbbabsbuaaba"
	    "stbbbbbabmbkbabbbvvybbabqbjbabgbbbaaaezzuadwmbababaacodaabafpbbabbzybajb"
	    "awaacabibaabaaebjblabbgaabbabbbbxbabribaaaawbbaaaabaabbunraaaasbbiaaabye"
	    "gobbranejadagbdaabbbkxaabbaaaabqbbbanaaalbbbbaaagaafaaaaaaacababcbaoaabb"
	    "ibaancbbaabaabaabbaareaabbssobabavsgbaaabbbbaaubbaaabbabbbxoaabbbpdbbabb"
	    "boaavaaebaabbhajeasbbtacbabbaabbbabablpbbaapaczaabbaggobskbabbwaabobaaaa"
	    "abnpbahasbababxabbdraamqbababbtbbaaaaixaaababbbzbayababybuabbaablabbabaa"
	    "ababwabaabbavbsbbbbaajuaabbbbtbobbblbbbbzbabbbbbsbgbbabbsablasbbbbbxbabi"
	    "cbdbabtbbbaabacgaabaarabaaabbbbaaabaqatabhbhjbbabbaaqfaambuaaknbfabbbaaa"
	    "oaabaababababbuaababaaafabbababababbadbbabuaawfbztabbaonltbaataaaapbaatz"
	    "aaaaybbananevaabaabxsabbbaabkabbbjaakbaazzbbcbbbbs";

	int score = maximumGain( s, 3605, 192 );

	printf( "%d\n", score );

    free(s);

	return EXIT_SUCCESS;
}