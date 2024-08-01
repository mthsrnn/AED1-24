#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int RemoveTwoCharacters( char *source, size_t sizeOfSource, char* substring, int points ) {
    int score = 0, i = 0, j;


    for ( j = 0; j < sizeOfSource + 1; j++) {
        source[i++] = source[j];

        if (i > 1 && source[i - 2] == substring[0] && source[i - 1] == substring[1] ) {
            i -= 2;
            score += points;
        }
    }
    
    return score;
	
}

int maximumGain( char *s, int x, int y ) {

	int score = 0, i = 0, originalSize = strlen( s ), newSize = originalSize;

	if( x > y ) {
        score += RemoveTwoCharacters(s, originalSize, "ab", x);
        score += RemoveTwoCharacters(s, strlen( s ), "ba", y);
        return score;

    } else {
        score += RemoveTwoCharacters(s, originalSize, "ba", y);
        score += RemoveTwoCharacters(s, strlen( s ), "ab", x);
        return score;
    }
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