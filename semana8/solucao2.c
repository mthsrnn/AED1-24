#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define EMPTY -1
#define INISIZE 100

typedef struct SStack {
    char * sStackArray;
    int sSize;
    int sTop;
} SStack;

SStack *SReset ( void ) {
    SStack *stack = ( SStack *) malloc( sizeof(SStack) );
    if ( stack == NULL ) {
            puts("DEU PAU!");
            exit(-1);
    }

    stack->sTop = EMPTY;
    stack->sSize = INISIZE;

    stack->sStackArray = (char *) malloc(1 + INISIZE * sizeof( char ) );
    if ( stack->sStackArray == NULL ) {
            puts("DEU PAU!");
            exit(-1);
    }

    return stack;
}

void SPush ( SStack * stack, char letter ) {
    if (stack->sTop + 1 == stack->sSize) {
        size_t newSize = ((stack->sSize * 2)+1);
        stack->sStackArray = (char *)realloc(stack->sStackArray, newSize * sizeof(char));
        stack->sSize = (int) newSize;
    }

    stack->sStackArray[++stack->sTop] = letter;
}

void SPop ( SStack * stack ) {
    if (stack->sTop >= 0) {
        stack->sTop--;
    }
}

char * RemoveSubstring ( char * string, char * substring) {
    SStack *stack = SReset();
    for (int i = 0; i < strlen(string); i++) {
        if ( stack->sTop >= 0 ) {
            if( stack->sStackArray[stack->sTop] == substring[0] && string[i] == substring[1]) {
                SPop(stack);
                continue;
            }
        }
        SPush(stack, string[i]);
    }

    // quebrando a regra da pilha pra economizar runtime e espaço
    stack->sStackArray[stack->sTop + 1] = '\0';
    return stack->sStackArray;

    free(stack);

}

int maximumGain( char *s, int x, int y ) {
    int score = 0, originalLength = strlen(s);

    if ( x > y ) {
        s = RemoveSubstring(s, "ab");
        score += x * ( ( originalLength - strlen(s) ) /2 );
        originalLength = strlen(s);
        s = RemoveSubstring(s, "ba");
        score += y * ( ( originalLength - strlen(s) ) /2 );
    } else {
        s = RemoveSubstring(s, "ba");
        score += y * ( ( originalLength - strlen(s) ) /2 );
        originalLength = strlen(s);
        s = RemoveSubstring(s, "ab");
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

	return EXIT_SUCCESS;
}